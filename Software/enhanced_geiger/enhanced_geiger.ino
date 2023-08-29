/*
    
    Mini Scintillation Counter Software
    
    2023, NuclearPhoenix

    TODO:
      - !!!!!! LED_BUILTIN should be a charging indicator

      - !!! Temperaturbegrenzung zeigt nur 1x an und laden reaktiviert sich nicht
      - !!! Test LittleFS + Implement Saving/Loading (buzzer + letzter screen)
      - Akku Modell + Debug entfernen
      - Energiesparfunktionen deaktivieren, wenn USB Verbindung: Pin Interrupt startet/stoppt Task

      - RunningAverage Lib

      - Radiation Evolution Chart
      - Info Screen mit Temp, Akkuladung, Spannung, On-time, Ein/Ausschaltungen, Totzeit, Frequenz, FW Version, LittleFS

      - Displaywechsel setzt cps zurück (wegen time delta fix auf 1s)...

      - Display runterfahren bevor Gerät in Standby geht?

*/

#include "gfx.h"            // Icons and other graphics
#include "helper.h"         // Some misc helper functions
#include "pico/stdlib.h"    // Used for set_sys_clock_khz
#include "hardware/vreg.h"  // Used for vreg_set_voltage
#include <LittleFS.h>       // Used for FS, stores last display and buzzer

#define _TASK_TIMECRITICAL  // Enable monitoring scheduling overruns
#define _TASK_SCHEDULING_OPTIONS
#define _TASK_SLEEP_ON_IDLE_RUN  // Enable 1 ms SLEEP_IDLE powerdowns between tasks if no callback methods were invoked during the pass
#include <TaskScheduler.h>

#include <Adafruit_SSD1306.h>       // OLED Display
#include "fonts/Roboto_Light_12.h"  // Display font
#include "fonts/Roboto_Light_24.h"
//#include "fonts/Roboto_Light_32.h"
//#include "fonts/Roboto_Condensed_Light_12.h"
#include "fonts/Roboto_Condensed_Light_48.h"
#include "fonts/Roboto_Condensed_Light_56.h"
//#include "fonts/Roboto_12.h"
//#include "fonts/Roboto_24.h"
//#include "fonts/Open_Sans_Regular_12.h"
//#include "fonts/Open_Sans_Regular_24.h"

//#include <Adafruit_SleepyDog.h> // Doesn't use any low power functions! :c

const uint8_t REFRESH_INT = 1;             // Display refresh interval in s
const uint8_t POLL_TIME = 10;              // Button poll time in ms
const uint8_t LONG_PRESS = 80;             // How many POLL_TIME cycles
const uint16_t BUZZER_FREQ = 2700;         // Frequency used for the buzzer PWM
const uint8_t TICK_RATE = 10;              // Buzzer clicks once every TICK_RATE counts
const uint8_t BUZZER_TICK = 1;             // Buzzer on-time in ms
const uint8_t BAT_WARN = 20;               // % at which a warning icon appears for low battery
const uint8_t DEADTIME_BUFFER_SIZE = 100;  // Size of the dead time buffer -> MUST BE DONE BEFORE warmed_up
const uint8_t SIGN_DIGITS = 3;             // Significant digits for display
const double CPS_SV_CONVERSION = 15.0;     // Conversion factor for cps to nSv
const double CORR_TEMP = 3.235;            // Imaginary reference voltage to calibrate the temp sensor
const String FILENAME = "config.csv";      // Save file storing the device config

const bool ALLOW_STANDBY = true;              // Allow going into standby mode after some time
const uint32_t STANDBY_TIME = 600 * 1000;     // Standby time in ms
const uint32_t REMINDER_OFFSET = 600 * 1000;  // Time offset between display dark and reminder alarm in ms
const uint32_t REMINDER_TIME = 60 * 1000;     // Shutoff alarm (reminder) time in ms
const unsigned long SHUTDOWN_BEEPS = 10;      // Do some more agressive energy saving after x beeps

const uint8_t MIN_FREQ_USB = 50;  // Min CPU freq in USB mode
const uint8_t MIN_FREQ_BAT = 20;  // Min CPU freq in battery mode
const uint8_t MAX_FREQ = 133;     // Max CPU freq
const uint32_t MAX_CPS = 70000;   // Derived to only get 10% deviation to the real cps due to dead time

const uint8_t MIN_TEMP = 0;     // Max temperature for battery charging given by regulator
const uint8_t MAX_TEMP = 45;    // Min temperature for battery charging given by regulator
const uint8_t TEMP_OFFSET = 5;  // Temperature offset of the battery vs the processor when charging

const uint8_t EVENT_PIN = 13;   // SiPM events pin (interrupts)
const uint8_t BUTTON_PIN = 17;  // Button in pin
const uint8_t BUZZER_PIN = 12;  // Buzzer out pin

const uint8_t BAT_PIN = 29;       // Battery voltage measurement pin
const uint8_t USB_PIN = 24;       // USB status pin
const uint8_t NEW_SDA = 14;       // Custom SDA pin for I2C0
const uint8_t NEW_SCL = 15;       // Custom SCL pin for I2C0
const uint8_t CHARGE_PIN = 28;    // Battery charger IC status pin
const uint8_t BAT_REG_PIN = 27;   // Battery charger IC thermal shutdown pin
const uint8_t SIPM_REG_PIN = 18;  // SiPM voltage regulator enable pin
const uint8_t ACT_PIN = 16;       // Activity LED pin

// Dynamic variables
bool buzzer_enable = true;
uint8_t show_screen = 0;
bool standby_enabled = false;
bool dynamic_clock = true;

double counts_buffer[5] = {};

volatile uint32_t events = 0;  // Number of events

volatile uint8_t dt_buffer_index = DEADTIME_BUFFER_SIZE;  // Dynamically compute deadtime due to dynamic CPU clocking
volatile double deadtime_buffer[DEADTIME_BUFFER_SIZE] = {};

// Forward declaration of callbacks
void updateDisplay();
void queryButton();
void enterStandby();
void reminderBeep();
void reminderBeepEnd();
void queryBOOTSEL();

// Tasks
Task updateDisplayTask(REFRESH_INT * 1000, TASK_FOREVER, &updateDisplay);
Task queryButtonTask(POLL_TIME, TASK_FOREVER, &queryButton);
Task enterStandbyTask(STANDBY_TIME, TASK_ONCE, &enterStandby);
Task reminderBeepTask(REMINDER_TIME, TASK_FOREVER, &reminderBeep);
Task reminderBeepEndTask(0, TASK_ONCE, &reminderBeepEnd);
Task queryBOOTSELTask(100, TASK_FOREVER, &queryBOOTSEL);

// Scheduler
Scheduler schedule;

Adafruit_SSD1306 display(128, 64, &Wire1, -1);  // 128 by 64 pixel OLED


void setStandbyMode(bool enable = false) {
  if (enable) {
    // Do more energy saving?
  } else {
    digitalWrite(SIPM_REG_PIN, HIGH);  // Enable SiPM voltage regulator
  }

  dynamic_clock = !enable;
  display.dim(enable);
  standby_enabled = enable;
}


void enterStandby() {
  setStandbyMode(true);

  reminderBeepTask.enableDelayed(REMINDER_OFFSET);  // Enable reminder beep after some time
}


void reminderBeep() {
  detachInterrupt(digitalPinToInterrupt(EVENT_PIN));  // Remove interrupt to not interrupt the beeping

  const uint16_t BUZZER_ON_TIME = 1000;
  tone(BUZZER_PIN, 4000, BUZZER_ON_TIME);

  if (reminderBeepTask.getRunCounter() == SHUTDOWN_BEEPS + 1) {
    digitalWrite(SIPM_REG_PIN, LOW);  // Disable SiPM voltage regulator
    buzzer_enable = false;            // Disable buzzer

    // More energy saving?!
  }

  reminderBeepEndTask.restartDelayed(BUZZER_ON_TIME);
}


void reminderBeepEnd() {
  // Re-enable interrupts after beeping is done
  attachInterrupt(digitalPinToInterrupt(EVENT_PIN), registerEvent, RISING);
}


double computeAverageCPS() {
  const double CPS = double(events) / double(REFRESH_INT);
  events = 0;

  static uint8_t buffer_index = 0;
  static bool warmed_up = false;
  const uint8_t BUFFER_SIZE = sizeof(counts_buffer) / sizeof(counts_buffer[0]);
  counts_buffer[buffer_index] = CPS;

  if (buffer_index + 1 >= BUFFER_SIZE) {
    buffer_index = 0;
    warmed_up = true;
  } else {
    buffer_index++;
  }

  double avg_cps = 0.0;
  for (uint8_t i = 0; i < BUFFER_SIZE; i++) {
    avg_cps += counts_buffer[i];
  }

  if (warmed_up) {  // Avoid warm-up time of the circular cps buffer
    avg_cps /= BUFFER_SIZE;
  } else {
    avg_cps /= buffer_index;
  }

  // Change min CPU frequency depending on battery or USB power to fix USB connections
  uint8_t min_freq = MIN_FREQ_BAT;
  if (digitalRead(USB_PIN)) {
    min_freq = MIN_FREQ_USB;
  }

  uint32_t clock_freq = min_freq;  // Minimum frequency possible in MHz

  // Dynamically change CPU clock depending on the needed dead time
  if (dynamic_clock) {
    clock_freq = constrain(map(avg_cps, 0, MAX_CPS, min_freq, MAX_FREQ), min_freq, MAX_FREQ);
  }

  set_sys_clock_khz(clock_freq * 1000, true);

  double deadtime = 0.0;
  for (uint8_t i = 0; i < DEADTIME_BUFFER_SIZE; i++) {
    deadtime += deadtime_buffer[i];
  }

  if (warmed_up) {
    deadtime /= double(DEADTIME_BUFFER_SIZE);
  } else {
    deadtime /= double(dt_buffer_index);
  }

  // Correct for dead time
  double avg_corrected_cps = avg_cps / (1 - avg_cps * deadtime * 0.000001);

  return avg_corrected_cps;
}


/*
void displayBootscreen() {
  display.clearDisplay();
  display.setFont(&Roboto_Light_24);

  display.setCursor(0, 20);
  display.println("Booting");
  display.println("FW 1.0.0");

  display.drawBitmap(128 - 30, 0, opengamma_pcb, 30, 30, SSD1306_WHITE);
  display.drawBitmap(128 - 30, 64 - 30, nuclearphnx_pcb, 30, 30, SSD1306_WHITE);

  display.setFont(&Roboto_Light_12);

  display.display();
}
*/


void displayInfobar() {
  const uint16_t ADC_OFFSET = round(0.032 / 3.3 * 4096);  // Remove ADC offset of ~30 - 34 mV
  double batv1 = analogRead(BAT_PIN);
  delay(2);  // Allow the ADC to stabilize
  double batv2 = analogRead(BAT_PIN);
  delay(2);  // Allow the ADC to stabilize
  double batv3 = analogRead(BAT_PIN);
  uint16_t avg_batv = round((batv1 + batv2 + batv3) / 3.0) - ADC_OFFSET;

  uint8_t bat_lvl = battery_percent(avg_batv);
  bool charging = (digitalRead(CHARGE_PIN) == LOW);

  double temp1 = analogReadTemp(CORR_TEMP);
  delay(2);
  double temp2 = analogReadTemp(CORR_TEMP);
  delay(2);
  double temp3 = analogReadTemp(CORR_TEMP);
  double avg_temp = round((temp1 + temp2 + temp3) / 3.0);

  display.setCursor(20, 9);

  if (bat_lvl > 80) {
    display.drawBitmap(0, 0, battery_full_solid, 16, 10, SSD1306_WHITE);
  } else if (bat_lvl > 60) {
    display.drawBitmap(0, 0, battery_three_quarters_solid, 16, 10, SSD1306_WHITE);
  } else if (bat_lvl > 40) {
    display.drawBitmap(0, 0, battery_half_solid, 16, 10, SSD1306_WHITE);
  } else if (bat_lvl > 20) {
    display.drawBitmap(0, 0, battery_quarter_solid, 16, 10, SSD1306_WHITE);
  } else {
    display.drawBitmap(1, 0, battery_empty_solid, 16, 10, SSD1306_WHITE);

    if (!charging) {
      display.drawBitmap(18, 0, exclamation_solid, 4, 10, SSD1306_WHITE);
      display.setCursor(26, 9);

      // Battery is almost dead
      // TODO: Energy save??
    }
  }

  /*
    =============
    BATTERY DEBUG
    =============
  */
  static unsigned long last_write = 0;
  const uint16_t WRITE_TIME = 60 * 1000;

  if (millis() - last_write > WRITE_TIME) {
    // Open the file in append mode
    File file = LittleFS.open("akku.csv", "a");
    if (file) {
      uint16_t a = analogRead(BAT_PIN);
      delay(2);
      uint16_t b = analogRead(BAT_PIN);
      delay(2);
      uint16_t c = analogRead(BAT_PIN);
      uint16_t v = round((double(a) + double(b) + double(c)) / 3.0);

      file.print(millis());
      file.print(", ");
      file.print(avg_temp);
      file.print(", ");
      file.println(v);
    } else {
      file = LittleFS.open("akku.csv", "w");
    }
    // Close the file
    file.close();

    last_write = millis();
  }
  /*
    ===
    END
    ===
  */

  // Check if charging battery
  if (charging) {
    // Over- or under-temperature check for battery
    if (avg_temp - TEMP_OFFSET < MIN_TEMP || avg_temp - TEMP_OFFSET > MAX_TEMP) {
      // Set to OUTPUT and LOW to disable charging!
      pinMode(BAT_REG_PIN, OUTPUT);
      gpio_set_slew_rate(BAT_REG_PIN, GPIO_SLEW_RATE_SLOW);
      digitalWrite(BAT_REG_PIN, LOW);

      // SHOW HOT OR COLD ICON INSTEAD OF CHARGING IF CHARGING
      if (avg_temp - TEMP_OFFSET < MIN_TEMP) {
        display.drawBitmap(18, 0, temperature_arrow_down_solid, 10, 10, SSD1306_WHITE);  // Too cold
      } else {
        display.drawBitmap(18, 0, temperature_arrow_up_solid, 10, 10, SSD1306_WHITE);  // Too hot
      }
      display.setCursor(32, 9);
    } else {
      // Set as input for high impedance so that battery charge works as normal
      pinMode(BAT_REG_PIN, INPUT);

      // Draw charging icon
      display.drawBitmap(18, 0, bolt_solid, 9, 10, SSD1306_WHITE);
      display.setCursor(31, 9);
    }
  }

  display.print(bat_lvl);
  display.print("% ");
  display.print(avg_temp, 0);
  display.print("C  ");

  if (digitalRead(USB_PIN) && Serial) {
    // Micro USB Connection to computer
    display.drawBitmap(128 - 11 - 4 - 15, 0, usb, 15, 9, SSD1306_WHITE);
  }

  if (buzzer_enable) {
    display.drawBitmap(128 - 11, 0, volume_low_solid, 11, 10, SSD1306_WHITE);
  } else {
    display.drawBitmap(128 - 11, 0, volume_xmark_solid, 11, 10, SSD1306_WHITE);
  }

  display.drawFastHLine(0, 10, 128, SSD1306_WHITE);
}


void displayScreen0() {
  display.setFont(&Roboto_Condensed_Light_56);
  display.setCursor(0, 60);
  //display.setTextSize(2);

  double cps = computeAverageCPS();
  uint8_t decimalPlaces;

  if (cps < 1000.0) {  // cps
    display.print(cps, 0);
  } else if (cps < 1000000.0) {  // kcps
    double new_cps = cps / 1000.0;

    display.print(roundToSignificantDigits(new_cps, SIGN_DIGITS, decimalPlaces), decimalPlaces);

    display.setFont(&Roboto_Condensed_Light_48);
    display.setCursor(100, 50);

    display.print("k");
  } else {  // Mcps
    double new_cps = cps / 1000000.0;

    display.print(roundToSignificantDigits(new_cps, SIGN_DIGITS, decimalPlaces), decimalPlaces);

    display.setFont(&Roboto_Condensed_Light_48);
    display.setCursor(95, 50);

    display.print("M");
  }

  display.setFont(&Roboto_Light_12);
  display.setCursor(102, 60);

  display.print("cps");

  if (Serial) {
    Serial.println(cps, 0);
  }
}


void displayScreen1() {
  display.setFont(&Roboto_Condensed_Light_56);
  display.setCursor(0, 60);

  double nano_Sv = computeAverageCPS() * CPS_SV_CONVERSION;  // Convert to nSv
  uint8_t decimalPlaces;

  if (nano_Sv < 1000.0) {  // nSv
    display.print(nano_Sv, 0);

    display.setFont(&Roboto_Condensed_Light_48);
    display.setCursor(100, 45);

    display.print("n");
  } else if (nano_Sv < 1000000.0) {  // uSv
    double new_nano_Sv = nano_Sv / 1000.0;

    display.print(roundToSignificantDigits(new_nano_Sv, SIGN_DIGITS, decimalPlaces), decimalPlaces);

    display.setFont(&Roboto_Condensed_Light_48);
    display.setCursor(100, 38);

    // Draw µ
    display.print("u");

    display.fillRect(103, 11, 20, 9, SSD1306_BLACK);  // Remove some of the u
    display.fillRect(103, 30, 3, 15, SSD1306_WHITE);  // Draw |
  } else {                                            // mSv
    double new_nano_Sv = nano_Sv / 1000000.0;

    display.print(roundToSignificantDigits(new_nano_Sv, SIGN_DIGITS, decimalPlaces), decimalPlaces);

    display.setFont(&Roboto_Condensed_Light_48);
    display.setCursor(95, 45);

    display.print("m");
  }

  display.setFont(&Roboto_Light_12);
  display.setCursor(102, 60);

  display.print("Sv");

  if (Serial) {
    Serial.println(nano_Sv, 0);
  }
}


void displayScreen2() {
  display.setCursor(0, 22);

  double deadtime = 0.0;
  for (uint8_t i = 0; i < DEADTIME_BUFFER_SIZE; i++) {
    deadtime += deadtime_buffer[i];
  }
  deadtime /= double(DEADTIME_BUFFER_SIZE);

  const uint8_t ADC_OFFSET = 35;                                       // Remove ADC offset of ~30 - 34 mV
  double batv1 = double(analogRead(BAT_PIN)) * 3.0 * 3250.0 / 4096.0;  //battery.voltage();
  delay(2);                                                            // Allow the ADC to stabilize
  double batv2 = double(analogRead(BAT_PIN)) * 3.0 * 3250.0 / 4096.0;  //battery.voltage();
  delay(2);                                                            // Allow the ADC to stabilize
  double batv3 = double(analogRead(BAT_PIN)) * 3.0 * 3250.0 / 4096.0;  //battery.voltage();
  uint16_t avg_batv = round((batv1 + batv2 + batv3) / 3.0) - ADC_OFFSET;

  display.print("Radiation Evolution Chart ");
  display.print(avg_batv);
  display.println(" mV");
  display.print(deadtime, 1);
  display.print("  ");
  display.println(double(rp2040.f_cpu()) / 1000000.0, 0);

  computeAverageCPS();  // Execute to reset cps calculation
}


void updateDisplay() {
  display.clearDisplay();
  displayInfobar();

  switch (show_screen) {
    case 0:
      displayScreen0();
      break;
    case 1:
      displayScreen1();
      break;
    case 2:
      displayScreen2();
      break;
    default:
      show_screen = 0;
      displayScreen0();
      break;
  }

  display.display();
}


void queryButton() {
  static uint16_t pressed = 0;
  static bool press_lock = false;

  if (digitalRead(BUTTON_PIN) == LOW) {
    pressed++;

    if (pressed >= LONG_PRESS && !press_lock) {
      /*
        Long Press: Toggle Buzzer
      */
      buzzer_enable = !buzzer_enable;

      updateDisplayTask.forceNextIteration();  // Update the display immediately
      press_lock = true;
    }
  } else {
    if (pressed > 0) {
      if (pressed < LONG_PRESS) {
        /*
          Short Press: Switch Screens
        */
        if (!standby_enabled) {
          show_screen++;
        }

        updateDisplayTask.forceNextIteration();  // Update the display immediately
      }

      // Disable all standby features
      if (standby_enabled) {
        setStandbyMode(false);
        reminderBeepTask.disable();
      }

      if (ALLOW_STANDBY) {
        enterStandbyTask.restartDelayed(STANDBY_TIME);  // Reset standby timer
      }
    }

    pressed = 0;
    press_lock = false;
  }
}


void queryBOOTSEL() {
  /*
    BOOTSEL button pressed
  */
  if (BOOTSEL) {
    rp2040.rebootToBootloader();
  }
}


void registerEvent() {
  unsigned long start = micros();

  const unsigned long start_millis = millis();

  static unsigned long last_tick = start_millis;  // Last buzzer tick in ms, not needed with tone()
  static uint8_t count = 0;

  // Check if ticker is enabled, currently not "ticking" and also catch the millis() overflow
  if (start_millis - last_tick > BUZZER_TICK || start_millis < last_tick) {
    if (count >= TICK_RATE - 1) {  // Only click at every 10th count
      if (buzzer_enable) {
        tone(BUZZER_PIN, BUZZER_FREQ, BUZZER_TICK);  // Worse at higher cps
      }

      tone(ACT_PIN, 50, 1);  // Use the LED as a buzzer alternative

      last_tick = start_millis;
      count = 0;
    } else {
      count++;
    }
  }

  events++;

  // Compute dead time
  dt_buffer_index++;
  if (dt_buffer_index >= DEADTIME_BUFFER_SIZE) {
    dt_buffer_index = 0;
  }
  deadtime_buffer[dt_buffer_index] = micros() - start;
}


void setup() {
  pinMode(LED_BUILTIN, OUTPUT_12MA);  // OPTIONAL
  pinMode(EVENT_PIN, INPUT_PULLDOWN);
  pinMode(BUZZER_PIN, OUTPUT_12MA);

  gpio_set_slew_rate(LED_BUILTIN, GPIO_SLEW_RATE_SLOW);  // Slow slew rate to reduce EMI
  gpio_set_slew_rate(BUZZER_PIN, GPIO_SLEW_RATE_SLOW);

  // Starts FileSystem, autoformats if no FS is detected
  LittleFS.begin();

  // Load last device state from config file
  File file = LittleFS.open(FILENAME, "r");
  if (file) {
    String a = file.readString();
    Serial.println(a);
  }
  file.close();

  delay(100);  // Delay additional 100 ms to make sure the discriminator is ready

  attachInterrupt(digitalPinToInterrupt(EVENT_PIN), registerEvent, RISING);
}


void setup1() {
  //rp2040.wdt_begin(5);
  vreg_set_voltage(VREG_VOLTAGE_0_90);  // Undervolt as much as possible to save power

  pinMode(USB_PIN, INPUT);
  pinMode(BAT_PIN, INPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(CHARGE_PIN, INPUT_PULLUP);
  pinMode(SIPM_REG_PIN, OUTPUT);
  // Set as input for high impedance so that battery charge works as normal
  // Set to OUTPUT and LOW to disable charging!
  pinMode(BAT_REG_PIN, INPUT);
  pinMode(ACT_PIN, OUTPUT_12MA);

  gpio_set_slew_rate(SIPM_REG_PIN, GPIO_SLEW_RATE_SLOW);  // Slow slew rate to reduce EMI
  gpio_set_slew_rate(ACT_PIN, GPIO_SLEW_RATE_SLOW);

  digitalWrite(SIPM_REG_PIN, HIGH);  // Enable SiPM power supply

  Wire1.setSDA(NEW_SDA);
  Wire1.setSCL(NEW_SCL);

  gpio_set_slew_rate(NEW_SDA, GPIO_SLEW_RATE_SLOW);  // Slow slew rate to reduce EMI
  gpio_set_slew_rate(NEW_SCL, GPIO_SLEW_RATE_SLOW);

  // Display Stuff
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  //display.setRotation(0);
  //display.invertDisplay(true);
  //display.setTextSize(1);  // Draw 1X-scale text
  display.setTextColor(SSD1306_WHITE);
  display.setFont(&Roboto_Light_12);
  //display.setCursor(0, 0);
  display.display();  // Show the cleared screen instead of garbage

  //displayBootscreen();

  analogReadResolution(12);  // Highest res for the battery lib!

  Serial.begin(115200);  // Enable Serial which will be used to detect PC connections

  // Set up task scheduler and enable tasks
  updateDisplayTask.setSchedulingOption(TASK_INTERVAL);  // TASK_SCHEDULE, TASK_SCHEDULE_NC, TASK_INTERVAL
  queryButtonTask.setSchedulingOption(TASK_INTERVAL);
  reminderBeepTask.setSchedulingOption(TASK_INTERVAL);

  schedule.init();
  schedule.allowSleep(true);

  schedule.addTask(updateDisplayTask);
  schedule.addTask(queryButtonTask);
  schedule.addTask(enterStandbyTask);
  schedule.addTask(reminderBeepTask);
  schedule.addTask(reminderBeepEndTask);
  schedule.addTask(queryBOOTSELTask);

  updateDisplayTask.enable();
  queryButtonTask.enable();
  //updateDisplayTask.enableDelayed(2000);
  //queryButtonTask.enableDelayed(2000);
  queryBOOTSELTask.enable();

  if (ALLOW_STANDBY) {
    enterStandbyTask.enableDelayed(STANDBY_TIME);
  }
}


void loop() {
  //sleep_ms(POLL_TIME);
  __wfi();  // Wait for interrupt, sleep
}


void loop1() {
  schedule.execute();

  //rp2040.wdt_reset();

  sleep_ms(1);  // Sleep for additional power saving
}
