/*!
 *  @file PhHardware.h
 *  Класс для работы с интерфейсом передачи данных на дисплейный модуль Фотон RobotClass
 *  Автор: Олег Евсегнеев, 2023.
 *  e-mail: oleg.evsegneev@gmail.com
 */
 
#ifndef __PHHARDWARE_H__
#define __PHHARDWARE_H__

#include <Arduino.h>
#include <Wire.h>
#include <SoftwareSerial.h>

#define PH_HWIF_UART 0
#define PH_HWIF_I2C 1
#define PH_DEFAULT_BAUD 115200
#define PH_DEFAULT_ADDR 0x25

#define CMD_RESET 0xF0

#define CMD_ACK 0xA0
#define CMD_EVENT_PUSH 0xA1
#define CMD_EVENT_POP 0xA2
#define CMD_PAGE 0xA3
#define CMD_ERR_PAGE_N 0xB0
#define CMD_ERR_ITEM_N 0xB1

#define CMD_SET_INT 0xC0
#define CMD_SET_FLOAT 0xC1
#define CMD_SET_STR 0xC2
#define CMD_SET_PAGE 0xC3

#define CMD_GET_VERSION 0xD0
#define CMD_GET_PAGE 0xD1

class PhHardware{
	private:
		TwoWire* _wire = nullptr;
		Stream *_serial = nullptr;
		Stream *_serial_debug = nullptr;
		uint8_t _i2c_addr;
		uint8_t _hwif;
		uint8_t _status = 0x00;

	public:
		PhHardware();
		void begin( TwoWire *wire, uint8_t addr );
		void begin( Stream *serial );
		void beginDebug( Stream *serial );
		void printDebug( const char* msg );
		uint8_t isDebug();

		uint8_t isUART();
		uint8_t isI2C();
		uint8_t readUART( uint8_t* buf );

		uint8_t readCommands( uint8_t& eid, uint8_t& cmd );
		uint8_t writeCommandUART( const char* buf );
		uint8_t readCommandUART( const char* buf, uint8_t *data, uint8_t dsize );
		uint8_t writeCommandI2C( const uint8_t *buf, uint8_t size );
		uint8_t readCommandI2C( const uint8_t *buf, uint8_t size, uint8_t *data, uint8_t dsize );
		bool getResponse( uint32_t timeout = 100 );
};

#endif /* #ifndef __PHHARDWARE_H__ */