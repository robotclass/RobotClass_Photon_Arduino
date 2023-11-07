/*!
 *  @file PhHardware.h
 *  Класс для работы с интерфейсом передачи данных на дисплейный модуль Фотон RobotClass
 *  Автор: Олег Евсегнеев, 2023.
 *  e-mail: oleg.evsegneev@gmail.com
 */
 
#ifndef __PHHARDWARE_H__
#define __PHHARDWARE_H__

#include <Arduino.h>

#define PH_HWIF_UART 0
#define PH_HWIF_I2C 1
#define PH_DEFAULT_BAUD 115200

#define CMD_ACK 0xA0
#define CMD_EVENT_PUSH 0xA1
#define CMD_EVENT_POP 0xA2
#define CMD_ERR_PAGE_N 0xB0
#define CMD_ERR_ITEM_N 0xB1

class PhHardware{
  private:
    HardwareSerial *_serial_hs = NULL;
    //SoftwareSerial *_serial_ss = NULL;
    uint8_t _hwif;
  public:
    PhHardware( uint8_t hwif, HardwareSerial *serial );
    void begin( uint32_t v );
    uint8_t readCommands( uint8_t& eid, uint8_t& cmd );
    void sendCommand( const char* cmd );
	bool getResponse();
};

#endif /* #ifndef __PHHARDWARE_H__ */