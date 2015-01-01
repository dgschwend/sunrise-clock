/**
 * @file MAX7221.h
 * @version 1.0
 *
 * @section License
 * Copyright (C) 2014, David Gschwend

 */


#include "Cosa/LCD.hh"
#include "Cosa/Trace.hh"

#ifndef LCD_DRIVER_MAX7221_H
#define LCD_DRIVER_MAX7221_H

/**
 * MAX7221 Serially Interfaced, 8-Digit LED Display Drivers,
 * device driver for IOStream access.
 *
 * Expects three daisy-chained MAX7221 devices,
 * 
 *       +--------------+    +--------------+    +--------------+
 *       |              |    |              |    |              |
 * uP -- |DIN       DOUT| -- |DIN       DOUT| -- |DIN           |
 *    -- |              | -- |              | -- |              |
 *    -- |              | -- |              | -- |              |
 *    -- |              | -- |              | -- |              |
 *       |              |    |              |    |              |
 *       +--------------+    +--------------+    +--------------+
 *
 * The MAX7219/MAX7221 are compact, serial input/output common-cathode
 * display drivers that interface microprocessors (μPs) to 7-segment
 * numeric LED displays of up to 8 digits, bar-graph displays, or 64
 * individual LEDs. Included on-chip are a BCD code-B decoder,
 * multiplex scan circuitry, segment and digit drivers, and an 8x8
 * static RAM that stores each digit.
 *
 * @section Circuit
 * @code
 *                    MAX7221/LCD::Serial3W
 *                       +------------+
 * (D6)----------------1-|DIN         |
 * (GND)---------------4-|GND         |
 * (GND)---------------9-|GND         |
 * (D9)---------------12-|CS          |
 * (D7)---------------13-|CLK         |
 * (VCC)--------------19-|VCC         |
 *                       +------------+
 *
 * @endcode
 *
 * @section References
 * 1. Product Specification, MAXIM, MAX7219/7221, 19-5542, Rev.4, 7/03.
 * http://datasheets.maximintegrated.com/en/ds/MAX7219-MAX7221.pdf
 */
class MAX7221 : public LCD::Device {
public:
    /** Display size (pixels). */
    static const uint8_t WIDTH = 8*3;
    static const uint8_t HEIGHT = 8;
    
    /**
     * Construct display device driver with given io adapter and font.
     * The font should be a character to segment mapping table in
     * program memory for character codes SPACE(0x20) to DEL(0x7f).
     * @param[in] io adapter, SPI or in/output pin based.
     * @param[in] font program memory (Default NULL).
     */
    MAX7221(LCD::IO* io);
    
    /**
     * @override LCD::Device
     * Start interaction with display. Turns display on, clears and sets
     * the contrast/intensity to mid-level(7).
     * @return true(1) if successful otherwise false(0)
     */
    virtual bool begin();
    
    /**
     * @override LCD::Device
     * Stop sequence of interaction with device.
     * @return true(1) if successful otherwise false(0)
     */
    virtual bool end();
    
    /**
     * @override LCD::Device
     * Set display contrast/intensity level (0..15).
     * @param[in] contrast level.
     */
    virtual void display_contrast(uint8_t level);
    
    /**
     * @override LCD::Device
     * Turn display on.
     */
    virtual void display_on();
    
    /**
     * @override LCD::Device
     * Turn display off.
     */
    virtual void display_off();
    
    /**
     * @override LCD::Device
     * Clear display and move cursor to home (0, 0).
     */
    virtual void display_clear();
    
    /**
     * @override LCD::Device
     * Set cursor to given position.
     * @param[in] x pixel position (0..WIDTH-1).
     */
    virtual void set_cursor(uint8_t x, uint8_t y);
    
    /**
     * @override IOStream::Device
     * Write character to display. Handles carriage-return-line-feed, horizontal tab and form-feed. Returns character or EOF on error.
     * @param[in] c character to write.
     * @return character written or EOF(-1).
     */
    virtual int putchar(char c);
    
    //protected:
    /**
     * Register Address Map (Table 2, pp 7).
     */
    enum Register {
        NOP = 0x00,			//!< No-operation.
        DIGIT0 = 0x01,		//!< Digit 0 (encode or segment data).
        DIGIT1 = 0x02,		//!< Digit 1 (encode or segment data).
        DIGIT2 = 0x03,		//!< Digit 2 (encode or segment data).
        DIGIT3 = 0x04,		//!< Digit 3 (encode or segment data).
        DIGIT4 = 0x05,		//!< Digit 4 (encode or segment data).
        DIGIT5 = 0x06,		//!< Digit 5 (encode or segment data).
        DIGIT6 = 0x07,		//!< Digit 6 (encode or segment data).
        DIGIT7 = 0x08,		//!< Digit 7 (encode or segment data).
        DECODE_MODE = 0x09,		//!< Decode Mode (0..255, digit bitset).
        INTENSITY = 0x0a,		//!< Intensity (0..15, level).
        SCAN_LIMIT = 0x0b,		//!< Scan Limit (0..7, digits 1..8).
        DISPLAY_MODE = 0x0c,	//!< Display Mode (shutdown, normal).
        DISPLAY_TEST = 0x0f		//!< Display Test (0..1, on/off).
    } __attribute__((packed));
    
    /**
     * Shutdown Register Format (Table 3, pp. 7).
     */
    enum {
        SHUTDOWN_MODE = 0x00,	//!< Shutdown mode.
        NORMAL_OPERATION = 0x01	//!< Normal operation.
    } __attribute__((packed));
    
    /**
     * Decode-Mode Register (Table 4, pp. 7).
     */
    enum {
        NO_DECODE = 0x00,		//!< No decode for digits 7-0.
        ALL_DECODE = 0xff		//!< Code B decode for digits 7-0.
    } __attribute__((packed));
    
    /** Default font. */
    PROGMEM static prog_uchar font[];
    
    /** Character Decoding Functions. */
    uint8_t char_len(char c);
    uint8_t char_index(char c);
    char to_upper(char c);
    
    /** Display pins and state. */
    LCD::IO* m_io;          //!< Display adapter.
    prog_uchar* m_font;	    //!< Font in program memory.
    
    /**
     * Possible Device Addresses for First / Second / Third Matrix.
     * ALL -> Broadcast this to all connected devices.
     */
    enum Device {
        DEV0 = 0x00,
        DEV1 = 0x01,
        DEV2 = 0x02,
        ALL  = 0xFF
    } __attribute__((packed));
    
    /**
     * Set register of specified device to the given value.
     * @param[in] device .
     * @param[in] reg register address.
     * @param[in] value.
     */
    void set(Device device, Register reg, uint8_t value);
    
    /**
     * Set a certain Column of the Display to specified value.
     * @param[in] x Column Number (x coordinate).
     * @param[in] value.
     */
    void set_column(uint8_t x, uint8_t value);
};

#endif
