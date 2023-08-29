/*

  Helper functions for the mini scintillation counter

*/

double roundToSignificantDigits(double number, uint8_t digits, uint8_t& decimalPlaces) {
  if (number == 0) {
    decimalPlaces = 0;
    return 0.0;
  }

  int magnitude = -int(log10(fabs(number))) + (digits - 1);
  double roundedNumber = round(number * pow(10, magnitude)) / pow(10, magnitude);

  decimalPlaces = digits - (int(log10(fabs(roundedNumber))) + 1);
  return roundedNumber;
}

uint8_t battery_percent(uint16_t adc_reading) {
  double L = 184.78;
  double k = 0.01;
  double x0 = 1718.64;
  double a = 0.25;
  double result = a + L / (1 + pow(2.7182818284, -k * (double(adc_reading) - x0)));

  if (result < 0.0) {
    return 0;
  } else if (result > 100.0) {
    return 100;
  } else {
    return round(result);
  }
}
