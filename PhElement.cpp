/*!
 *  @file RobotClass_PhButton.cpp
 *  Реализация класса для работы с элементом
 *  Автор: Олег Евсегнеев, 2023.
 *  e-mail: oleg.evsegneev@gmail.com
 */
 
#include "PhElement.h"

PhElement::PhElement( PhHardware* hw, uint8_t pid, uint8_t id, uint8_t type, uint8_t touch ){
	_hw = hw;
	_touch = touch;
	_id = id;
	_pid = pid;
	_type = type;
}

uint16_t PhElement::getValue(char *buf, uint16_t len){
	/*
    String cmd;
    cmd += "get ";
    cmd += getObjName();
    cmd += ".txt";
    _ph->sendCommand(cmd.c_str());
	*/
    return _hw->getResponse();    
}

// передача строки типа char*
// buf - значение
uint8_t PhElement::setValue(const char *buf){
	_hw->printDebug("el set str");
	if( _hw->isUART() ){
		String cmd;

		if( _id<10 ){
			cmd += "00";
		} else
		if( _id<100 ){
			cmd += "0";
		}

		cmd += String(_id);
    
		cmd += ".v=\"";
		cmd += buf;
		cmd += "\"";

		return _hw->sendCommandUART(cmd.c_str());

	} else {

		uint8_t count = strlen(buf);
		uint8_t *cmd = new uint8_t(count+3); // cmd+id+0x00 = 3

		cmd[0] = CMD_SET_STR;
		cmd[1] = _id;
		for( uint8_t i=0; i<count+1; i++ ){
			cmd[i+2] = buf[i];
		}
		//cmd[i+2] = 0x00;
		
		return _hw->sendCommandI2C(cmd, count+3);
	}
}

// передача целого числа типа int32_t
// v - значение
uint8_t PhElement::setValue(int32_t v){
	_hw->printDebug("el set long");
	if( _hw->isUART() ){
		char buf[12];
		ltoa( v, buf, 10 );
		return setValue( buf );

	} else {
		uint8_t cmd[6];

		cmd[0] = CMD_SET_INT;
		cmd[1] = _id;
		cmd[2] = v & 0xFF;
		cmd[3] = (v>>8) & 0xFF;
		cmd[4] = (v>>16) & 0xFF;
		cmd[5] = (v>>24) & 0xFF;

		return _hw->sendCommandI2C(cmd, 6);
	}
}

// передача вещественного числа типа float
// v - значение
// precision - точность, от 1 до 9
uint8_t PhElement::setValue(float v, uint8_t width, uint8_t precision){
	_hw->printDebug("el set float");
	uint8_t p = precision < 1 ? 1 : (precision > 8 ? 8 : precision);
	uint8_t w = width < 3 ? 3 : (width > 16 ? 16 : width);

	if( _hw->isUART() ){
		char buf[17]; // 7 знаков до + точка + 8 после + 0x00
		char str[17]; // 7 знаков до + точка + 8 после + 0x00

		dtostrf( v, w, p, str );
		sprintf( buf, "%s", str );
		return setValue( buf );

	} else {
		uint8_t cmd[8];

		uint8_t fbuf[4];
		memcpy(fbuf, &v, 4);

		cmd[0] = CMD_SET_FLOAT;
		cmd[1] = _id;
		cmd[2] = w;
		cmd[3] = p;
		cmd[4] = fbuf[0];
		cmd[5] = fbuf[1];
		cmd[6] = fbuf[2];
		cmd[7] = fbuf[3];

		return _hw->sendCommandI2C(cmd, 8);
	}
}

uint8_t PhElement::getId(){
	_hw->printDebug("el get id");
	return _id;
}

uint8_t PhElement::getPid(){
	return _pid;
}

uint8_t PhElement::getTouch(){
	return _touch;
}

uint8_t PhElement::isTouch( uint8_t pid, uint8_t id ){
	return _touch && _pid == pid && _id == id;
}

void PhElement::attachPush( PhTouchEventCb push ){
    _cb_push = push;
}

void PhElement::detachPush( void ){
    _cb_push = NULL;
}

void PhElement::attachPop( PhTouchEventCb pop ){
    _cb_pop = pop;
}

void PhElement::detachPop( void ){
    _cb_pop = NULL;    
}
