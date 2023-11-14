/*!
 *  @file PhHardware.cpp
 *  Реализация класса для работы с интерфейсом передачи данных на дисплейный модуль Фотон RobotClass
 *  Автор: Олег Евсегнеев, 2023.
 *  e-mail: oleg.evsegneev@gmail.com
 */
#include "PhHardware.h"

PhHardware::PhHardware(){
}

void PhHardware::begin( TwoWire *wire, uint8_t addr ){
	_hwif = PH_HWIF_I2C;
	_wire = wire;
	_i2c_addr = addr;
}

void PhHardware::begin( Stream *serial ){
	_serial = serial;
}

void PhHardware::beginDebug( Stream *serial ){
	_serial_debug = serial;
}

void PhHardware::printDebug( const char* msg ){
	if(_serial_debug != nullptr){
		_serial_debug->println(msg);
	}
}

uint8_t PhHardware::isDebug(){
	return _serial_debug != nullptr;
}

uint8_t PhHardware::isUART(){
	return _hwif == PH_HWIF_UART;
}

uint8_t PhHardware::isI2C(){
	return _hwif == PH_HWIF_I2C;
}

uint8_t PhHardware::readUART( uint8_t* buf ){
	uint8_t count = 0;
	if( _serial->available() ){
		delay(10);
		while( _serial->available() ) buf[count++] = _serial->read();
	}
	return count;
}

uint8_t PhHardware::readI2C( uint8_t* buf ){
	uint8_t count = 0;
	if( _serial->available() ){
		delay(10);
		while( _wire->available() ) buf[count++] = _wire->read();
	}

	return count;
}

uint8_t PhHardware::readCommands( uint8_t& eid, uint8_t& cmd ){
    static uint8_t buf[16];

    eid = 0xFF;

	uint8_t count = 0;
	if( _hwif == PH_HWIF_UART ){
		count = readUART( buf );
	} else {
		return 0;
	}

	if( !count ){
		return 0;
	}
	for( uint8_t k=0; k<count; k++ ){
		if( buf[k] == 0xFF && (k+3)<count && buf[k+1] == 0xFF ){
			cmd = buf[k+2];
			if( cmd == CMD_EVENT_PUSH || cmd == CMD_EVENT_POP ){
				eid = buf[k+3];
				return 1; // TODO
			}
		}
	}
	return 0;
}

uint8_t PhHardware::sendCommandUART( const char* buf ){
	while( _serial->available() ){
		_serial->read();
	}
    
	_serial->write(buf);

	return getResponse();
}

uint8_t PhHardware::sendCommandI2C( const uint8_t *buf, uint8_t size ){
	if( isDebug() ){
		char str[32];
		sprintf(str, "i2c:%02x/%02x", _i2c_addr, buf[0]);
		printDebug(str);
	}
	_wire->beginTransmission(_i2c_addr);
	_wire->write(buf, size);
	_status = _wire->endTransmission();
	return (_status == 0);
}

bool PhHardware::getResponse( uint32_t timeout ){
    bool ret = false;
    uint8_t buf[3] = {0};
    
	_serial->setTimeout(timeout);
    if( sizeof(buf) != _serial->readBytes( (char *)buf, sizeof(buf) )){
        ret = false;
    }

    if( buf[0] == 0xFF && buf[1] == 0xFF && buf[2] == CMD_ACK ){
        ret = true;
    }

    return ret;
}
