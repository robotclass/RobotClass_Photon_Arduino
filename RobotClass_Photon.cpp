/*!
 *  @file RobotClass_Photon.cpp
 *  Библиотека для управления дисплейным модулем Фотон RobotClass
 *  Автор: Олег Евсегнеев, 2023.
 *  e-mail: oleg.evsegneev@gmail.com
 */
#include "RobotClass_Photon.h"

RobotClass_Photon::RobotClass_Photon( uint8_t hwif, HardwareSerial *serial ){
	_hw = new PhHardware( hwif, serial );
}

void RobotClass_Photon::begin( uint32_t v ){
	_hw->begin(v);
}

void RobotClass_Photon::handle(){
	uint8_t eid, cmd;
	_hw->readCommands( eid, cmd );

	if( eid == 0xFF ){
		return;
	}

	for( uint8_t i=0; i<_elements_n; i++ ){
		if( _elements[i]->isTouch( _page, eid ) ){
			if( cmd == CMD_EVENT_PUSH ){
				_elements[i]->_cb_push();
			} else {
				_elements[i]->_cb_pop();
			}
		}
	}
}

Element& RobotClass_Photon::registerElement( uint8_t pid, uint8_t id, uint8_t type, uint8_t touch ){
    Element **tmp = new Element*[_elements_n+1];
    for( uint8_t i=0; i<_elements_n; i++){
        tmp[i] = _elements[i];
    }
    
    tmp[_elements_n] = new Element( _hw, pid, id, type, touch );
    _elements = tmp;

    _elements_n++;
    return *(_elements[_elements_n-1]);
}

uint8_t RobotClass_Photon::setPage( uint8_t page ){
	_page = page;

    String cmd;

    if( page<10 ){
      cmd += "00";
    } else
    if( page<100 ){
      cmd += "0";
    }
    cmd += String(page);
    
    cmd += ".p";
    _hw->sendCommand(cmd.c_str());
	
	return _hw->getResponse();
}


