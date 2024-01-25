/*!
 *  @file RobotClass_Photon.cpp
 *  Библиотека для управления дисплейным модулем Фотон RobotClass
 *  Автор: Олег Евсегнеев, 2023.
 *  e-mail: oleg.evsegneev@gmail.com
 */
#include "RobotClass_Photon.h"

RobotClass_Photon::RobotClass_Photon(){
	_hw = new PhHardware();
}

void RobotClass_Photon::begin( TwoWire *wire, uint8_t addr ){
	_hw->begin( wire, addr );
}

void RobotClass_Photon::begin( Stream *serial ){
	_hw->begin( serial );
}

void RobotClass_Photon::beginDebug( Stream *serial ){
	_hw->beginDebug( serial );
}

void RobotClass_Photon::handle(){
	uint8_t eid, cmd;
	_hw->readCommands( eid, cmd );

	if( eid == 0xFF ){
		return;
	}

	_hw->printDebug("ph event received");
	for( uint8_t i=0; i<_elements_n; i++ ){
		if( _elements[i]->isTouch( _page, eid ) ){
			_hw->printDebug("ph istouch");
			if( cmd == CMD_EVENT_PUSH ){
				_elements[i]->_cb_push();
			} else {
				_elements[i]->_cb_pop();
			}
		}
	}
}

PhElement& RobotClass_Photon::registerElement( uint8_t pid, uint8_t id, uint8_t type, uint8_t touch ){
    PhElement **tmp = new PhElement*[_elements_n+1];
    for( uint8_t i=0; i<_elements_n; i++){
        tmp[i] = _elements[i];
    }
    
    tmp[_elements_n] = new PhElement( _hw, pid, id, type, touch );
    _elements = tmp;

    _elements_n++;
    return *(_elements[_elements_n-1]);
}

uint8_t RobotClass_Photon::setPage( uint8_t page ){
	_hw->printDebug("ph set page");

	_page = page;

	if( _hw->isUART() ){
		String cmd;

		if( page<10 ){
			cmd += "00";
		} else
		if( page<100 ){
			cmd += "0";
		}
		cmd += String(page);
		cmd += ".p";

		return _hw->writeCommandUART(cmd.c_str());

	} else {
		uint8_t cmd[2];

		cmd[0] = CMD_SET_PAGE;
		cmd[1] = page;

		return _hw->writeCommandI2C(cmd, 2);
	}
}

uint8_t RobotClass_Photon::getPage( uint16_t *value ){
	if( _hw->isUART() ){
		uint8_t buf[5];

		String cmd = "page";
		if( _hw->readCommandUART(cmd.c_str(), buf, 5)){
			*value = buf[3] | (buf[4]<<8);
			return 1;
		}

	} else {
		uint8_t cmd[1];

		cmd[0] = CMD_GET_PAGE;

		uint8_t buf[2];
		if( _hw->readCommandI2C(cmd, 1, buf, 2) ){
			*value = buf[0] | (buf[1]<<8);
			return 1;
		}
	}
	return 0;
}

uint8_t RobotClass_Photon::getVersion( uint16_t *value ){
	if( _hw->isUART() ){
		uint8_t buf[5];

		String cmd = "version";
		if( _hw->readCommandUART(cmd.c_str(), buf, 5)){
			*value = buf[3] | (buf[4]<<8);
			return 1;
		}

	} else {
		uint8_t cmd[1];

		cmd[0] = CMD_GET_VERSION;

		uint8_t buf[2];
		if( _hw->readCommandI2C(cmd, 1, buf, 2) ){
			*value = buf[0] | (buf[1]<<8);
			return 1;
		}
	}
	return 0;
}

uint8_t RobotClass_Photon::reset(){
	_hw->printDebug("ph reset");
	if( _hw->isUART() ){
		String cmd = "reset";
		return _hw->writeCommandUART(cmd.c_str());

	} else {
		uint8_t cmd[1];

		cmd[0] = CMD_RESET;

		return _hw->writeCommandI2C(cmd, 1);		
	}
}

