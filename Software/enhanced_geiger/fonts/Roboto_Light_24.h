// Created by http://oleddisplay.squix.ch/ Consider a donation
// In case of problems make sure that you are using the font file with the correct version!
const uint8_t Roboto_Light_24Bitmaps[] PROGMEM = {

	// Bitmap Data:
	0x00, // ' '
	0xAA,0xAA,0xAA,0x02,0xC0, // '!'
	0xBB,0xBA,0xA0, // '"'
	0x04,0x20,0x21,0x01,0x08,0x08,0xC0,0xC4,0x3F,0xFC,0x21,0x01,0x08,0x08,0x40,0xC6,0x04,0x21,0xFF,0xE1,0x08,0x08,0x40,0x46,0x06,0x20,0x21,0x00, // '#'
	0x04,0x00,0x80,0x10,0x0F,0x83,0x0C,0xC0,0x90,0x1A,0x03,0x40,0x0C,0x00,0xE0,0x07,0x00,0x18,0x01,0x80,0x1E,0x03,0xC0,0x68,0x09,0x83,0x0F,0x80,0x40,0x08,0x00, // '$'
	0x38,0x00,0x44,0x00,0xC2,0x10,0x82,0x10,0x82,0x20,0xC2,0x60,0x44,0x40,0x38,0x80,0x01,0x80,0x01,0x3C,0x03,0x62,0x02,0x42,0x04,0x43,0x0C,0x43,0x08,0x42,0x10,0x62,0x00,0x3C, // '%'
	0x0F,0x00,0x46,0x03,0x08,0x08,0x20,0x20,0x80,0xC6,0x01,0x30,0x03,0x00,0x1C,0x00,0xD8,0x66,0x31,0x90,0x64,0xC0,0xD3,0x01,0xC4,0x06,0x18,0x34,0x1F,0x1C, // '&'
	0xFF,0x80, // '''
	0x08,0xC4,0x46,0x21,0x18,0xC4,0x21,0x08,0x42,0x10,0xC6,0x10,0x86,0x10,0x43,0x08, // '('
	0x43,0x02,0x04,0x10,0x60,0x82,0x0C,0x30,0x41,0x04,0x10,0x43,0x0C,0x30,0x86,0x10,0x42,0x18,0x80, // ')'
	0x04,0x01,0x00,0x41,0x13,0xFF,0x83,0x01,0xE0,0x48,0x21,0x08,0x60, // '*'
	0x04,0x00,0x40,0x04,0x00,0x40,0x04,0x0F,0xFF,0x04,0x00,0x40,0x04,0x00,0x40,0x04,0x00,0x40, // '+'
	0x57,0x80, // ','
	0xF8, // '-'
	0xF0, // '.'
	0x01,0x80,0x80,0xC0,0x40,0x20,0x30,0x10,0x08,0x08,0x04,0x06,0x02,0x01,0x01,0x00,0x80,0xC0,0x40,0x60,0x00, // '/'
	0x1F,0x06,0x31,0x83,0x20,0x2C,0x07,0x80,0xF0,0x1E,0x03,0xC0,0x78,0x0F,0x01,0xE0,0x3C,0x06,0x80,0x98,0x31,0x8C,0x1F,0x00, // '0'
	0x0C,0xFC,0x41,0x04,0x10,0x41,0x04,0x10,0x41,0x04,0x10,0x41,0x04, // '1'
	0x1F,0x0C,0x31,0x03,0x60,0x2C,0x04,0x00,0x80,0x30,0x04,0x01,0x80,0x60,0x18,0x06,0x00,0x80,0x20,0x0C,0x03,0x00,0xFF,0xE0, // '2'
	0x1F,0x0C,0x31,0x03,0x60,0x2C,0x04,0x00,0x80,0x30,0x0C,0x0F,0x00,0x10,0x01,0x00,0x38,0x07,0x80,0xD0,0x13,0x06,0x1F,0x00, // '3'
	0x01,0x80,0x18,0x02,0x80,0x68,0x04,0x80,0xC8,0x08,0x81,0x08,0x30,0x82,0x08,0x40,0x8C,0x08,0xFF,0xF0,0x08,0x00,0x80,0x08,0x00,0x80, // '4'
	0x7F,0xD0,0x04,0x01,0x00,0x40,0x10,0x05,0xE3,0x86,0x00,0x80,0x30,0x04,0x01,0x80,0x60,0x3C,0x09,0x86,0x1E,0x00, // '5'
	0x07,0x81,0x80,0xC0,0x10,0x06,0x00,0x80,0x13,0xC7,0x86,0xE0,0x58,0x0F,0x01,0xE0,0x14,0x06,0x80,0xD8,0x11,0x84,0x1F,0x00, // '6'
	0xFF,0xE0,0x0C,0x01,0x00,0x60,0x08,0x01,0x00,0x60,0x08,0x03,0x00,0x40,0x18,0x02,0x00,0xC0,0x10,0x06,0x00,0xC0,0x30,0x00, // '7'
	0x1F,0x06,0x31,0x03,0x20,0x24,0x04,0x80,0xD0,0x11,0x8C,0x1F,0x0C,0x19,0x01,0x60,0x3C,0x03,0x80,0xD0,0x1B,0x06,0x1F,0x00, // '8'
	0x1F,0x04,0x31,0x03,0x60,0x2C,0x05,0x00,0xE0,0x1E,0x03,0x40,0xEC,0x3C,0x79,0x00,0x20,0x0C,0x01,0x00,0x60,0x18,0x3C,0x00, // '9'
	0xF0,0x00,0x03,0xC0, // ':'
	0x6C,0x00,0x00,0x00,0x24,0xB4, // ';'
	0x00,0xC0,0xE0,0xE0,0xC0,0xC0,0x30,0x03,0x00,0x38,0x03,0x80,0x30, // '<'
	0xFF,0xC0,0x00,0x00,0x00,0x00,0x3F,0xF0, // '='
	0xC0,0x1C,0x00,0xC0,0x0C,0x00,0xC0,0x30,0x30,0x30,0x70,0x30,0x00, // '>'
	0x3E,0x31,0xB0,0x70,0x30,0x18,0x0C,0x04,0x06,0x06,0x06,0x02,0x03,0x00,0x00,0x00,0x00,0x30,0x18,0x00, // '?'
	0x01,0xFC,0x00,0x70,0x30,0x0C,0x00,0x81,0x80,0x04,0x30,0x00,0x62,0x07,0x82,0x60,0x84,0x24,0x10,0x42,0x43,0x04,0x34,0x20,0xC1,0x42,0x0C,0x3C,0x20,0x83,0xC2,0x08,0x24,0x20,0x82,0x42,0x18,0x24,0x31,0xC4,0x61,0xE7,0x82,0x00,0x00,0x30,0x00,0x01,0x80,0x00,0x0E,0x04,0x00,0x3F,0x80, // '@'
	0x01,0x00,0x07,0x00,0x0A,0x00,0x36,0x00,0x44,0x00,0x88,0x03,0x18,0x04,0x10,0x08,0x20,0x30,0x60,0x40,0x41,0xFF,0xC2,0x00,0x84,0x01,0x18,0x03,0x20,0x02,0xC0,0x06, // 'A'
	0xFF,0x0C,0x0C,0xC0,0x6C,0x06,0xC0,0x6C,0x06,0xC0,0x4C,0x0C,0xFF,0x0C,0x0C,0xC0,0x2C,0x02,0xC0,0x3C,0x02,0xC0,0x6C,0x0C,0xFF,0x80, // 'B'
	0x0F,0x83,0x06,0x60,0x34,0x01,0xC0,0x18,0x00,0x80,0x08,0x00,0x80,0x08,0x00,0x80,0x08,0x00,0xC0,0x14,0x01,0x60,0x33,0x06,0x0F,0x80, // 'C'
	0xFF,0x0C,0x1C,0xC0,0x6C,0x02,0xC0,0x3C,0x01,0xC0,0x1C,0x01,0xC0,0x1C,0x01,0xC0,0x1C,0x01,0xC0,0x3C,0x02,0xC0,0x6C,0x1C,0xFF,0x00, // 'D'
	0xFF,0xF8,0x03,0x00,0x60,0x0C,0x01,0x80,0x30,0x06,0x00,0xFF,0xD8,0x03,0x00,0x60,0x0C,0x01,0x80,0x30,0x06,0x00,0xFF,0xE0, // 'E'
	0xFF,0xF8,0x03,0x00,0x60,0x0C,0x01,0x80,0x30,0x07,0xFE,0xC0,0x18,0x03,0x00,0x60,0x0C,0x01,0x80,0x30,0x06,0x00,0xC0,0x00, // 'F'
	0x0F,0xC0,0xC3,0x8C,0x04,0xC0,0x34,0x00,0xA0,0x01,0x00,0x18,0x00,0xC0,0x06,0x0F,0xD0,0x02,0x80,0x14,0x00,0xB0,0x04,0xC0,0x23,0x07,0x07,0xE0, // 'G'
	0xC0,0x1E,0x00,0xF0,0x07,0x80,0x3C,0x01,0xE0,0x0F,0x00,0x78,0x03,0xFF,0xFE,0x00,0xF0,0x07,0x80,0x3C,0x01,0xE0,0x0F,0x00,0x78,0x03,0xC0,0x18, // 'H'
	0xFF,0xFF,0xFF,0xFF,0xC0, // 'I'
	0x00,0x40,0x10,0x04,0x01,0x00,0x40,0x10,0x04,0x01,0x00,0x40,0x10,0x04,0x01,0x80,0x60,0x3C,0x09,0x86,0x3E,0x00, // 'J'
	0xC0,0x36,0x03,0x30,0x31,0x83,0x0C,0x30,0x63,0x03,0x30,0x1B,0x00,0xFC,0x07,0x30,0x30,0x81,0x86,0x0C,0x18,0x60,0x63,0x01,0x98,0x04,0xC0,0x38, // 'K'
	0xC0,0x30,0x0C,0x03,0x00,0xC0,0x30,0x0C,0x03,0x00,0xC0,0x30,0x0C,0x03,0x00,0xC0,0x30,0x0C,0x03,0x00,0xFF,0xC0, // 'L'
	0xC0,0x03,0xF0,0x01,0xE8,0x00,0xF6,0x00,0xFD,0x00,0x5E,0x80,0x6F,0x60,0x27,0x90,0x33,0xCC,0x19,0xE2,0x08,0xF1,0x0C,0x78,0xC4,0x3C,0x26,0x1E,0x1A,0x0F,0x05,0x07,0x83,0x83,0xC0,0x81,0x80, // 'M'
	0xC0,0x1F,0x00,0xF8,0x07,0xE0,0x3D,0x81,0xE4,0x0F,0x30,0x78,0xC3,0xC2,0x1E,0x18,0xF0,0x67,0x81,0x3C,0x0D,0xE0,0x3F,0x00,0xF8,0x07,0xC0,0x18, // 'N'
	0x0F,0xC0,0x61,0x82,0x01,0x18,0x06,0x40,0x09,0x00,0x2C,0x00,0xF0,0x03,0xC0,0x0F,0x00,0x3C,0x00,0xD0,0x02,0x40,0x09,0x80,0x62,0x01,0x06,0x18,0x0F,0xC0, // 'O'
	0xFF,0x8C,0x0C,0xC0,0x2C,0x03,0xC0,0x3C,0x03,0xC0,0x3C,0x02,0xC0,0xEF,0xF8,0xC0,0x0C,0x00,0xC0,0x0C,0x00,0xC0,0x0C,0x00,0xC0,0x00, // 'P'
	0x0F,0xC0,0x61,0x82,0x01,0x18,0x06,0x40,0x0B,0x00,0x2C,0x00,0xF0,0x03,0xC0,0x0F,0x00,0x3C,0x00,0xF0,0x02,0x40,0x09,0x80,0x62,0x01,0x06,0x18,0x0F,0xE0,0x00,0xC0,0x01,0x80,0x02, // 'Q'
	0xFF,0x08,0x0C,0x80,0x68,0x02,0x80,0x28,0x02,0x80,0x28,0x06,0x80,0xCF,0xF0,0x81,0x08,0x18,0x80,0x88,0x0C,0x80,0x68,0x02,0x80,0x30, // 'R'
	0x1F,0x83,0x0E,0x60,0x24,0x03,0xC0,0x14,0x00,0x60,0x03,0x80,0x0F,0x00,0x0C,0x00,0x20,0x03,0x80,0x1C,0x01,0x40,0x33,0x06,0x1F,0x80, // 'S'
	0xFF,0xF8,0x30,0x01,0x80,0x0C,0x00,0x60,0x03,0x00,0x18,0x00,0xC0,0x06,0x00,0x30,0x01,0x80,0x0C,0x00,0x60,0x03,0x00,0x18,0x00,0xC0,0x06,0x00, // 'T'
	0x80,0x18,0x01,0x80,0x18,0x01,0x80,0x18,0x01,0x80,0x18,0x01,0x80,0x18,0x01,0x80,0x18,0x01,0xC0,0x3C,0x03,0x40,0x23,0x0C,0x1F,0x80, // 'U'
	0xC0,0x05,0x00,0x36,0x00,0xC8,0x02,0x30,0x18,0xC0,0x41,0x01,0x06,0x0C,0x08,0x20,0x21,0x80,0xC6,0x01,0x10,0x04,0xC0,0x1A,0x00,0x28,0x00,0xE0,0x01,0x00, // 'V'
	0x80,0x60,0x3C,0x06,0x03,0xC0,0xE0,0x24,0x0B,0x02,0x40,0x90,0x66,0x09,0x04,0x61,0x90,0x42,0x11,0x84,0x21,0x08,0xC3,0x30,0x88,0x32,0x0C,0x81,0x20,0x48,0x16,0x05,0x81,0xE0,0x50,0x1C,0x07,0x00,0xC0,0x30,0x0C,0x03,0x00, // 'W'
	0xC0,0x1B,0x01,0x98,0x18,0x60,0xC1,0x8C,0x04,0xC0,0x36,0x00,0xE0,0x06,0x00,0x38,0x03,0x60,0x31,0x01,0x0C,0x18,0x31,0x80,0x88,0x06,0xC0,0x18, // 'X'
	0xC0,0x0D,0x80,0x22,0x01,0x8C,0x0C,0x18,0x20,0x61,0x80,0xC4,0x01,0x30,0x06,0x80,0x0E,0x00,0x30,0x00,0xC0,0x03,0x00,0x0C,0x00,0x30,0x00,0xC0,0x03,0x00, // 'Y'
	0xFF,0xF0,0x03,0x00,0x60,0x0C,0x00,0xC0,0x18,0x03,0x00,0x30,0x06,0x00,0xC0,0x0C,0x01,0x80,0x30,0x02,0x00,0x60,0x0C,0x00,0xFF,0xF0, // 'Z'
	0xF8,0x88,0x88,0x88,0x88,0x88,0x88,0x88,0x88,0x88,0x88,0x8F, // '['
	0x80,0xC0,0x40,0x40,0x60,0x20,0x30,0x10,0x10,0x18,0x08,0x08,0x04,0x04,0x06,0x02,0x02,0x03, // '\'
	0xF3,0x33,0x33,0x33,0x33,0x33,0x33,0x33,0x33,0x33,0x33,0x3F, // ']'
	0x18,0x18,0x3C,0x24,0x64,0x42,0x42,0x83, // '^'
	0xFF,0xC0, // '_'
	0xC2,0x30, // '`'
	0x1F,0x08,0x64,0x0D,0x01,0x00,0x40,0x11,0xFD,0x81,0xC0,0x70,0x1C,0x0D,0x85,0x3E,0x40, // 'a'
	0x80,0x20,0x08,0x02,0x00,0x80,0x27,0x8E,0x13,0x02,0x80,0xA0,0x38,0x0E,0x03,0x80,0xE0,0x38,0x0B,0x02,0xE1,0x27,0x80, // 'b'
	0x1F,0x08,0x64,0x0F,0x01,0x80,0x20,0x08,0x02,0x00,0x80,0x30,0x14,0x0C,0x86,0x1F,0x00, // 'c'
	0x00,0x40,0x10,0x04,0x01,0x00,0x47,0x92,0x15,0x03,0xC0,0x70,0x1C,0x07,0x01,0xC0,0x70,0x1C,0x05,0x03,0x21,0xC7,0x90, // 'd'
	0x1F,0x08,0x64,0x0F,0x01,0x80,0x7F,0xF8,0x02,0x00,0xC0,0x30,0x06,0x04,0xC2,0x1F,0x00, // 'e'
	0x1E,0x60,0x81,0x02,0x1F,0x88,0x10,0x20,0x40,0x81,0x02,0x04,0x08,0x10,0x20,0x40, // 'f'
	0x1E,0x48,0x74,0x0F,0x01,0xC0,0x70,0x1C,0x07,0x01,0xC0,0x70,0x14,0x0C,0x87,0x1E,0x40,0x10,0x05,0x03,0x61,0x87,0xC0, // 'g'
	0x80,0x40,0x20,0x10,0x08,0x04,0xF2,0x87,0x81,0x80,0xC0,0x60,0x30,0x18,0x0C,0x06,0x03,0x01,0x80,0xC0,0x40, // 'h'
	0xB0,0x2A,0xAA,0xAA,0xA0, // 'i'
	0x13,0x00,0x01,0x11,0x11,0x11,0x11,0x11,0x11,0x11,0x13,0xE0, // 'j'
	0x80,0x20,0x08,0x02,0x00,0x80,0x20,0x68,0x32,0x18,0x8C,0x26,0x0B,0x03,0xE0,0xC8,0x23,0x08,0x62,0x0C,0x81,0x20,0x30, // 'k'
	0xFF,0xFF,0xC0, // 'l'
	0x9E,0x1F,0x50,0x90,0xF0,0x70,0x30,0x10,0x18,0x08,0x0C,0x04,0x06,0x02,0x03,0x01,0x01,0x80,0x80,0xC0,0x40,0x60,0x20,0x30,0x10,0x18,0x08,0x08, // 'm'
	0x9E,0x50,0xF0,0x30,0x18,0x0C,0x06,0x03,0x01,0x80,0xC0,0x60,0x30,0x18,0x08, // 'n'
	0x1F,0x06,0x31,0x01,0x60,0x38,0x03,0x00,0x60,0x0C,0x01,0x80,0x38,0x0D,0x01,0x18,0xC1,0xF0, // 'o'
	0x9E,0x38,0xCC,0x1A,0x02,0x80,0xE0,0x38,0x0E,0x03,0x80,0xE0,0x2C,0x1B,0x8C,0x9E,0x20,0x08,0x02,0x00,0x80,0x20,0x00, // 'p'
	0x1E,0x48,0x74,0x0F,0x01,0xC0,0x70,0x1C,0x07,0x01,0xC0,0x70,0x14,0x0C,0x87,0x1E,0x40,0x10,0x04,0x01,0x00,0x40,0x10, // 'q'
	0x9E,0x8C,0x20,0x82,0x08,0x20,0x82,0x08,0x20,0x80, // 'r'
	0x1F,0x18,0x64,0x09,0x03,0x40,0x1C,0x01,0xE0,0x06,0x00,0xF0,0x3C,0x0D,0x86,0x3F,0x00, // 's'
	0x10,0x20,0x47,0xF1,0x02,0x04,0x08,0x10,0x20,0x40,0x81,0x02,0x06,0x07, // 't'
	0x80,0xC0,0x60,0x30,0x18,0x0C,0x06,0x03,0x01,0x80,0xC0,0x60,0x68,0x73,0xE8, // 'u'
	0x80,0x70,0x34,0x09,0x02,0x61,0x88,0x42,0x10,0xCC,0x12,0x04,0x80,0xC0,0x30,0x0C,0x00, // 'v'
	0x81,0x81,0xC1,0x83,0xC1,0x83,0x43,0xC2,0x42,0x42,0x62,0x46,0x26,0x64,0x24,0x24,0x24,0x24,0x3C,0x3C,0x18,0x18,0x18,0x18,0x18,0x18, // 'w'
	0xC0,0xD0,0x66,0x10,0xCC,0x16,0x07,0x00,0xC0,0x70,0x16,0x0C,0xC6,0x11,0x06,0xC0,0xC0, // 'x'
	0xC0,0x68,0x09,0x83,0x30,0x62,0x08,0x63,0x04,0x60,0x88,0x1B,0x01,0x40,0x38,0x07,0x00,0x40,0x08,0x03,0x00,0x40,0x18,0x0E,0x00, // 'y'
	0xFF,0x80,0x60,0x10,0x0C,0x06,0x01,0x00,0xC0,0x60,0x10,0x0C,0x06,0x03,0x00,0xFF,0xC0, // 'z'
	0x06,0x18,0x60,0x81,0x02,0x04,0x08,0x30,0x60,0x86,0x06,0x06,0x0C,0x08,0x10,0x20,0x40,0x81,0x03,0x03,0x03, // '{'
	0xFF,0xFF,0xF0, // '|'
	0xC0,0xC0,0xC0,0x81,0x02,0x04,0x08,0x10,0x30,0x20,0x30,0xC3,0x06,0x08,0x10,0x20,0x40,0x81,0x06,0x18,0x60 // '}'
};
const GFXglyph Roboto_Light_24Glyphs[] PROGMEM = {
// bitmapOffset, width, height, xAdvance, xOffset, yOffset
	  {     0,   1,   1,   7,    0,   -1 }, // ' '
	  {     1,   2,  17,   6,    2,  -17 }, // '!'
	  {     6,   4,   5,   8,    2,  -18 }, // '"'
	  {     9,  13,  17,  15,    1,  -17 }, // '#'
	  {    37,  11,  22,  14,    1,  -20 }, // '$'
	  {    68,  16,  17,  19,    1,  -17 }, // '%'
	  {   102,  14,  17,  16,    1,  -17 }, // '&'
	  {   132,   2,   5,   5,    1,  -18 }, // '''
	  {   134,   5,  25,   9,    2,  -19 }, // '('
	  {   150,   6,  25,   9,    0,  -19 }, // ')'
	  {   169,  10,  10,  11,    0,  -17 }, // '*'
	  {   182,  12,  12,  15,    1,  -14 }, // '+'
	  {   200,   2,   5,   6,    1,   -2 }, // ','
	  {   202,   5,   1,   8,    1,   -8 }, // '-'
	  {   203,   2,   2,   7,    2,   -2 }, // '.'
	  {   204,   9,  18,  11,    0,  -17 }, // '/'
	  {   225,  11,  17,  14,    1,  -17 }, // '0'
	  {   249,   6,  17,  14,    2,  -17 }, // '1'
	  {   262,  11,  17,  14,    1,  -17 }, // '2'
	  {   286,  11,  17,  14,    1,  -17 }, // '3'
	  {   310,  12,  17,  14,    1,  -17 }, // '4'
	  {   336,  10,  17,  14,    2,  -17 }, // '5'
	  {   358,  11,  17,  14,    1,  -17 }, // '6'
	  {   382,  11,  17,  14,    1,  -17 }, // '7'
	  {   406,  11,  17,  14,    1,  -17 }, // '8'
	  {   430,  11,  17,  14,    1,  -17 }, // '9'
	  {   454,   2,  13,   6,    2,  -13 }, // ':'
	  {   458,   3,  16,   6,    1,  -13 }, // ';'
	  {   464,  10,  10,  13,    1,  -13 }, // '<'
	  {   477,  10,   6,  14,    2,  -11 }, // '='
	  {   485,  10,  10,  13,    1,  -13 }, // '>'
	  {   498,   9,  17,  12,    1,  -17 }, // '?'
	  {   518,  20,  22,  23,    1,  -17 }, // '@'
	  {   573,  15,  17,  16,    0,  -17 }, // 'A'
	  {   605,  12,  17,  16,    2,  -17 }, // 'B'
	  {   631,  12,  17,  17,    2,  -17 }, // 'C'
	  {   657,  12,  17,  17,    2,  -17 }, // 'D'
	  {   683,  11,  17,  15,    2,  -17 }, // 'E'
	  {   707,  11,  17,  15,    2,  -17 }, // 'F'
	  {   731,  13,  17,  17,    1,  -17 }, // 'G'
	  {   759,  13,  17,  18,    2,  -17 }, // 'H'
	  {   787,   2,  17,   7,    2,  -17 }, // 'I'
	  {   792,  10,  17,  14,    1,  -17 }, // 'J'
	  {   814,  13,  17,  16,    2,  -17 }, // 'K'
	  {   842,  10,  17,  14,    2,  -17 }, // 'L'
	  {   864,  17,  17,  22,    2,  -17 }, // 'M'
	  {   901,  13,  17,  18,    2,  -17 }, // 'N'
	  {   929,  14,  17,  17,    1,  -17 }, // 'O'
	  {   959,  12,  17,  16,    2,  -17 }, // 'P'
	  {   985,  14,  20,  17,    1,  -17 }, // 'Q'
	  {  1020,  12,  17,  16,    2,  -17 }, // 'R'
	  {  1046,  12,  17,  15,    1,  -17 }, // 'S'
	  {  1072,  13,  17,  15,    1,  -17 }, // 'T'
	  {  1100,  12,  17,  17,    2,  -17 }, // 'U'
	  {  1126,  14,  17,  16,    0,  -17 }, // 'V'
	  {  1156,  20,  17,  23,    1,  -17 }, // 'W'
	  {  1199,  13,  17,  16,    1,  -17 }, // 'X'
	  {  1227,  14,  17,  15,    0,  -17 }, // 'Y'
	  {  1257,  12,  17,  15,    1,  -17 }, // 'Z'
	  {  1283,   4,  24,   7,    2,  -20 }, // '['
	  {  1295,   8,  18,  10,    1,  -17 }, // '\'
	  {  1313,   4,  24,   7,    0,  -20 }, // ']'
	  {  1325,   8,   8,  11,    1,  -17 }, // '^'
	  {  1333,  10,   1,  11,    0,    0 }, // '_'
	  {  1335,   4,   3,   8,    1,  -18 }, // '`'
	  {  1337,  10,  13,  14,    1,  -13 }, // 'a'
	  {  1354,  10,  18,  14,    2,  -18 }, // 'b'
	  {  1377,  10,  13,  13,    1,  -13 }, // 'c'
	  {  1394,  10,  18,  14,    1,  -18 }, // 'd'
	  {  1417,  10,  13,  13,    1,  -13 }, // 'e'
	  {  1434,   7,  18,   9,    1,  -18 }, // 'f'
	  {  1450,  10,  18,  14,    1,  -13 }, // 'g'
	  {  1473,   9,  18,  14,    2,  -18 }, // 'h'
	  {  1494,   2,  18,   6,    2,  -18 }, // 'i'
	  {  1499,   4,  23,   6,   -1,  -18 }, // 'j'
	  {  1511,  10,  18,  13,    2,  -18 }, // 'k'
	  {  1534,   1,  18,   6,    2,  -18 }, // 'l'
	  {  1537,  17,  13,  22,    2,  -13 }, // 'm'
	  {  1565,   9,  13,  14,    2,  -13 }, // 'n'
	  {  1580,  11,  13,  14,    1,  -13 }, // 'o'
	  {  1598,  10,  18,  14,    2,  -13 }, // 'p'
	  {  1621,  10,  18,  14,    1,  -13 }, // 'q'
	  {  1644,   6,  13,   9,    2,  -13 }, // 'r'
	  {  1654,  10,  13,  13,    1,  -13 }, // 's'
	  {  1671,   7,  16,   9,    0,  -16 }, // 't'
	  {  1685,   9,  13,  14,    2,  -13 }, // 'u'
	  {  1700,  10,  13,  13,    1,  -13 }, // 'v'
	  {  1717,  16,  13,  19,    1,  -13 }, // 'w'
	  {  1743,  10,  13,  13,    1,  -13 }, // 'x'
	  {  1760,  11,  18,  12,    0,  -13 }, // 'y'
	  {  1785,  10,  13,  13,    1,  -13 }, // 'z'
	  {  1802,   7,  24,   9,    1,  -19 }, // '{'
	  {  1823,   1,  20,   6,    2,  -17 }, // '|'
	  {  1826,   7,  24,   9,    0,  -19 } // '}'
};
const GFXfont Roboto_Light_24 PROGMEM = {
(uint8_t  *)Roboto_Light_24Bitmaps,(GFXglyph *)Roboto_Light_24Glyphs,0x20, 0x7E, 29};