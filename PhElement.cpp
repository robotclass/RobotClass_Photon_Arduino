/*!
 *  @file RobotClass_PhButton.cpp
 *  Реализация класса для работы с элементом
 *  Автор: Олег Евсегнеев, 2023.
 *  e-mail: oleg.evsegneev@gmail.com
 */
 
#include "PhElement.h"

Element::Element( PhHardware* hw, uint8_t pid, uint8_t id, uint8_t type, uint8_t touch ){
	_hw = hw;
	_touch = touch;
	_id = id;
	_pid = pid;
	_type = type;
}

uint16_t Element::getValue(char *buf, uint16_t len){
	/*
    String cmd;
    cmd += "get ";
    cmd += getObjName();
    cmd += ".txt";
    _ph->sendCommand(cmd.c_str());
	*/
    return _hw->getResponse();    
}

bool Element::setValue(const char *buf){
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
    _hw->sendCommand(cmd.c_str());
    return _hw->getResponse();    
}

bool Element::setValue(uint32_t v){
	char buf[12];
	ultoa(v, buf, 10);
	setValue(buf);
}

uint8_t Element::getId(){
	return _id;
}

uint8_t Element::getPid(){
	return _pid;
}

uint8_t Element::getTouch(){
	return _touch;
}

uint8_t Element::isTouch( uint8_t pid, uint8_t id ){
	return _touch && _pid == pid && _id == id;
}

void Element::attachPush( PhTouchEventCb push ){
    _cb_push = push;
}

void Element::detachPush( void ){
    _cb_push = NULL;
}

void Element::attachPop( PhTouchEventCb pop ){
    _cb_pop = pop;
}

void Element::detachPop( void ){
    _cb_pop = NULL;    
}
