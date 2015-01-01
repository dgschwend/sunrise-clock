/**
 * @file MAX7221.cpp
 * @version 1.0
 *
 * @section License
 * Copyright (C) 2014, DAVID GSCHWEND
 *
 */

#include "MAX7221.h"

/**
 * No-Decode Mode Data Bits and Corresponding Segment Lines (Table 6, pp 8.).
 * @code
 *      A
 *    +---+
 *   F| G |B
 *    +---+	Standard 7-Segment LED
 *   E|   |C
 *    +---+ DP
 *      D
 *
 *  D7 D6 D5 D4 D3 D2 D1 D0
 *  DP  A  B  C  D  E  F  G
 * @endcode
 */

/* PROGMEM prog_uchar MAX7221::font7[] = {
    0b01111100, // 0,	idx: 0,     len: 3
    0b10000010,
    0b01111100,
    0b11111110, // 1,	idx: 3,	    len: 2
    0b10000000,
    0b01100010, // 2,	idx: 5,	    len: 3
    0b10011010,
    0b01000110,
    0b01101100, // 3,	idx: 8,	    len: 3
    0b10010010,
    0b01000100,
    0b11111110, // 4,	idx: 11,	len: 3
    0b01101000,
    0b00011000,
    0b10011100, // 5,	idx: 14,	len: 3
    0b10100010,
    0b11100010,
    0b01001100, // 6,	idx: 17,	len: 3
    0b10010010,
    0b01111100,
    0b11000000, // 7,	idx: 20,	len: 3
    0b10110000,
    0b10001110,
    0b01101100, // 8,	idx: 23,	len: 3
    0b10010010,
    0b01101100,
    0b01111100, // 9,	idx: 26,	len: 3
    0b10010010,
    0b01100100,
    0b01111110, // A,	idx: 29,	len: 3
    0b10010000,
    0b01111110,
    0b01101100, // B,	idx: 32,	len: 3
    0b10010010,
    0b11111110,
    0b01000100, // C,	idx: 35,	len: 3
    0b10000010,
    0b01111100,
    0b01111100, // D,	idx: 38,	len: 3
    0b10000010,
    0b11111110,
    0b10000010, // E,	idx: 41,	len: 3
    0b10010010,
    0b11111110,
    0b10000000, // F,	idx: 44,	len: 3
    0b10010000,
    0b11111110,
    0b10011110, // G,	idx: 47,	len: 3
    0b10010010,
    0b01111100,
    0b11111110, // H,	idx: 50,	len: 3
    0b00010000,
    0b11111110,
    0b11111110, // I,	idx: 53,	len: 1
    0b11111100, // J,	idx: 54,	len: 2
    0b10000010,
    0b10000010, // K,	idx: 56,	len: 3
    0b01100100,
    0b11111110,
    0b00000010, // L,	idx: 59,	len: 3
    0b00000010,
    0b11111110,
    0b01111110, // M,	idx: 62,	len: 5
    0b10000000,
    0b01111110,
    0b10000000,
    0b01111110,
    0b11111110, // N,	idx: 67,	len: 4
    0b00000110,
    0b00100000,
    0b11111110,
    0b01111100, // O,	idx: 71,	len: 3
    0b10000010,
    0b01111100,
    0b01100000, // P,	idx: 74,	len: 3
    0b10010000,
    0b11111110,
    0b01111010, // Q,	idx: 77,	len: 3
    0b10000100,
    0b01111000,
    0b01101110, // R,	idx: 80,	len: 3
    0b10010000,
    0b11111110,
    0b10001100, // S,	idx: 83,	len: 3
    0b10010010,
    0b01100010,
    0b10000000, // T,	idx: 86,	len: 3
    0b11111110,
    0b10000000,
    0b11111100, // U,	idx: 89,	len: 3
    0b00000010,
    0b11111100,
    0b11111000, // V,	idx: 92,	len: 3
    0b00000110,
    0b11111000,
    0b11111100, // W,	idx: 95,	len: 5
    0b00000010,
    0b11111100,
    0b00000010,
    0b11111100,
    0b11000110, // X,	idx: 100,	len: 3
    0b00101000,
    0b11000110,
    0b11111100, // Y,	idx: 103,	len: 3
    0b00010010,
    0b11100000,
    0b11100010, // Z,	idx: 106,	len: 3
    0b10010010,
    0b10000110,
    0b00000010, // .,	idx: 109,	len: 1
    0b00000000, //  ,	idx: 110,	len: 1
    0b00101000, // :,	idx: 111,	len: 1
}; */

PROGMEM prog_uchar MAX7221::font[] = {
    0b01111110, // 0,	idx: 0,     len: 4
    0b10000001,
    0b10000001,
    0b01111110,
    
    0b11111111, // 1,	idx: 4,	    len: 3
    0b10000000,
    0b01000000,
    
    0b01100001, // 2,	idx: 7,	    len: 4
    0b10010001,
    0b10001101,
    0b01000011,
    
    0b01101110, // 3,	idx: 11,    len: 4
    0b10010001,
    0b10000001,
    0b01000110,
    
    0b11111111, // 4,	idx: 15,	len: 4
    0b01001000,
    0b00101000,
    0b00011000,
    
    0b10011110, // 5,	idx: 19,	len: 4
    0b10100001,
    0b10100001,
    0b11100010,
    
    0b01001110, // 6,	idx: 23,	len: 4
    0b10010001,
    0b10010001,
    0b01111110,
    
    0b11100000, // 7,	idx: 27,	len: 4
    0b10011000,
    0b10000111,
    0b10000000,
    
    0b01101110, // 8,	idx: 31,	len: 4
    0b10010001,
    0b10010001,
    0b01101110,
    
    0b01111110, // 9,	idx: 35,	len: 4
    0b10010001,
    0b10010001,
    0b01100010,
    
    0b01111110, // A,	idx: 39,	len: 3
    0b10010000,
    0b01111110,
    0b01101100, // B,	idx: 42,	len: 3
    0b10010010,
    0b11111110,
    0b01000100, // C,	idx: 45,	len: 3
    0b10000010,
    0b01111100,
    0b01111100, // D,	idx: 48,	len: 3
    0b10000010,
    0b11111110,
    0b10000010, // E,	idx: 51,	len: 3
    0b10010010,
    0b11111110,
    0b10000000, // F,	idx: 54,	len: 3
    0b10010000,
    0b11111110,
    0b10011110, // G,	idx: 57,	len: 3
    0b10010010,
    0b01111100,
    0b11111110, // H,	idx: 60,	len: 3
    0b00010000,
    0b11111110,
    0b11111110, // I,	idx: 63,	len: 1
    0b11111100, // J,	idx: 64,	len: 2
    0b10000010,
    0b10000010, // K,	idx: 66,	len: 3
    0b01100100,
    0b11111110,
    0b00000010, // L,	idx: 69,	len: 3
    0b00000010,
    0b11111110,
    0b01111110, // M,	idx: 72,	len: 5
    0b10000000,
    0b01111110,
    0b10000000,
    0b01111110,
    0b11111110, // N,	idx: 77,	len: 4
    0b00011000,
    0b01100000,
    0b11111110,
    0b01111100, // O,	idx: 81,	len: 4
    0b10000010,
    0b10000010,
    0b01111100,
    0b01100000, // P,	idx: 85,	len: 3
    0b10010000,
    0b11111110,
    0b01111010, // Q,	idx: 88,	len: 3
    0b10000100,
    0b01111000,
    0b01101110, // R,	idx: 91,	len: 3
    0b10010000,
    0b11111110,
    0b10001100, // S,	idx: 94,	len: 3
    0b10010010,
    0b01100010,
    0b10000000, // T,	idx: 97,	len: 3
    0b11111110,
    0b10000000,
    0b11111100, // U,	idx: 100,	len: 3
    0b00000010,
    0b11111100,
    0b11111000, // V,	idx: 103,	len: 3
    0b00000110,
    0b11111000,
    0b11111100, // W,	idx: 106,	len: 5
    0b00000010,
    0b11111100,
    0b00000010,
    0b11111100,
    0b11000110, // X,	idx: 111,	len: 3
    0b00101000,
    0b11000110,
    0b11111100, // Y,	idx: 114,	len: 3
    0b00010010,
    0b11100000,
    0b11100010, // Z,	idx: 117,	len: 3
    0b10010010,
    0b10000110,
    0b00000010, // .,	idx: 120,	len: 1
    0b00000000, //  ,	idx: 121,	len: 1
    0b00101000, // :,	idx: 122,	len: 1
    0b11111010, // !,	idx: 123,	len: 1
    0b01100000, // ♡,   idx: 124,   len: 9
    0b10010000,
    0b10001000,
    0b10000100,
    0b01000010,
    0b10000100,
    0b10001000,
    0b10010000,
    0b01100000};

uint8_t
MAX7221::char_index(char c) {
    if (c == '0') return 0;
    if (c == '1') return 4;
    if (c >= '2' && c <= '9') return 7 + (4 * (c-'2'));
    if (c >= 'A' && c <= 'I') return 39 + (3 * (c-'A'));
    if (c == 'J') return 64;
    if (c == 'K') return 66;
    if (c == 'L') return 69;
    if (c == 'M') return 72;
    if (c == 'N') return 77;
    if (c == 'O') return 81;
    if (c >= 'P' && c <= 'W') return 85 + (3 * (c-'P'));
    if (c == 'X') return 111;
    if (c == 'Y') return 114;
    if (c == 'Z') return 117;
    if (c == '.') return 120;
    if (c == ':') return 122;
    if (c == '!') return 123;
    if (c == ' ') return 121;
    if (c == '&') return 124;
    return 121; // invalid characters return position of space, width of 0
}

uint8_t
MAX7221::char_len(char c) {
    // SPECIAL CHARS:
    // 1-line characters
    if (c == 'I' || c == '.' || c == ' ' || c == ':' || c == '!') return 1;
    // 2-line characters
    if (c == 'J') return 2;
    // 3-line characters
    if (c == '1') return 3;
    // 4-line characters
    if (c == 'N' || c == 'O') return 4;
    // 5-line characters
    if (c == 'M' || c == 'W') return 5;
    // 9-line character
    if (c == '&') return 9;
    
    // STANDARD CHARS:
    // Standard for Letters: 3-line characters
    // special characters have returned already...
    if  (c >= 'A' && c <= 'Z') return 3;
    if  (c >= '0' && c <= '9') return 4;
    // 0-line (invalid) characters
    return 0;
}

char
MAX7221::to_upper(char c) {
    return (c >= 'a' && c <= 'z') ? c-'a'+'A' : c;
}

MAX7221::MAX7221(LCD::IO* io) :
    LCD::Device(),
    m_io(io),
    m_font(MAX7221::font)
{
}

void
MAX7221::set(Device device, Register reg, uint8_t value)
{
    m_io->begin();
    m_io->write((device == DEV0 || device == ALL) ? reg : NOP);
    m_io->write((device == DEV0 || device == ALL) ? value : NOP);
    m_io->write((device == DEV1 || device == ALL) ? reg : NOP);
    m_io->write((device == DEV1 || device == ALL) ? value : NOP);
    m_io->write((device == DEV2 || device == ALL) ? reg : NOP);
    m_io->write((device == DEV2 || device == ALL) ? value : NOP);
    m_io->end();
}

void
MAX7221::set_column(uint8_t x, uint8_t value)
{
    Device dev = static_cast<Device> (x/8);
    Register reg = static_cast<Register> (x%8+DIGIT0);
    set(dev, reg, value);
}

bool
MAX7221::begin()
{
    set(ALL, DISPLAY_TEST, 0);
    set(ALL, DECODE_MODE, NO_DECODE);
    set(ALL, SCAN_LIMIT, 7);
    display_contrast(3);
    display_clear();
    display_on();
    return (true);
}

bool
MAX7221::end()
{
    set(ALL, DISPLAY_MODE, SHUTDOWN_MODE);
    return (true);
}

void
MAX7221::display_on()
{
    set(ALL, DISPLAY_MODE, NORMAL_OPERATION);
}

void
MAX7221::display_off()
{
    set(ALL, DISPLAY_MODE, SHUTDOWN_MODE);
}

void
MAX7221::display_clear()
{
    for (uint8_t reg = DIGIT0; reg <= DIGIT7; reg++)
        set(ALL, (Register) reg, 0x00);
    set_cursor(0, 0);
}

void
MAX7221::display_contrast(uint8_t level)
{
    set(ALL, INTENSITY, level);
}

void
MAX7221::set_cursor(uint8_t x, uint8_t y)
{
    m_x = x;
}

int
MAX7221::putchar(char c)
{
    
    // Check for illegal characters
    if (c < 0) return (-1);
    
    // Check for special characters
    if (c < ' ') {
        
        // Alert: blink the backlight
        if (c == '\a') {
            display_off();
            delay(16);
            display_on();
            return (c);
        }
        
        // Form-feed: Next Character will clear the display
        if ((c == '\f') || (c == '\n')) {
            display_clear();
            return (c);
        }
        
        // Horizontal tab
        if (c == '\t') {
            const uint8_t TAB = 14;
            uint8_t x = m_x + TAB - (m_x % TAB);
            set_cursor(x, 0);
            return (c);
        }
    }
    
    // Write character
    c = to_upper(c);
    prog_uchar *base_addr = &m_font[char_index(c)];
    uint8_t char_width = char_len(c);
    
    if (m_x + char_width > WIDTH) { putchar('\n'); }
    
    for (int i = char_width-1; i>=0; i--) {
        
        const uint8_t char_data = pgm_read_byte_near(base_addr + i);        
        set_column(m_x++, char_data);
        
    }
    
     //Inter-character Spacing
    m_x++;
    
    return (c & 0xff);
}
