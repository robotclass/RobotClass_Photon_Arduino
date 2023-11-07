/*!
 *  @file PhHardware.cpp
 *  Реализация класса для работы с интерфейсом передачи данных на дисплейный модуль Фотон RobotClass
 *  Автор: Олег Евсегнеев, 2023.
 *  e-mail: oleg.evsegneev@gmail.com
 */
#include "PhHardware.h"

PhHardware::PhHardware( uint8_t hwif, HardwareSerial *serial ){
  _hwif = hwif;
  _serial_hs = serial;
}

void PhHardware::begin( uint32_t v ){
    switch( _hwif ){
	case PH_HWIF_UART:
		_serial_hs->begin(v);
		break;
	case PH_HWIF_I2C:
		break;
    }
}

uint8_t PhHardware::readCommands( uint8_t& eid, uint8_t& cmd ){
    static uint8_t buf[16];

    eid = 0xFF;

	uint8_t idx = 0;
    if( _hwif == PH_HWIF_UART ){
		if( _serial_hs->available() ){
			delay(10);
			while( _serial_hs->available() ){
				buf[idx] = _serial_hs->read();
				idx++;
			}
		}
	}

	if( !idx ){
		return 0;
	}
	for( uint8_t k=0; k<idx; k++ ){
		if( buf[k] == 0xFF && (k+3)<idx && buf[k+1] == 0xFF ){
			cmd = buf[k+2];
			if( cmd == CMD_EVENT_PUSH || cmd == CMD_EVENT_POP ){
				eid = buf[k+3];
				return 1; // TODO
			}
		}
	}
	return 0;
}

void PhHardware::sendCommand( const char* cmd ){
    if( _hwif == PH_HWIF_UART ){
		while( _serial_hs->available() ){
			_serial_hs->read();
		}
    
		_serial_hs->write(cmd);
    }
}

bool PhHardware::getResponse(){    
    bool ret = false;
    uint8_t buf[3] = {0};
    
    if( sizeof(buf) != _serial_hs->readBytes( (char *)buf, sizeof(buf) )){
        ret = false;
    }

    if( buf[0] == 0xFF && buf[1] == 0xFF && buf[2] == CMD_ACK ){
        ret = true;
    }

    return ret;
}