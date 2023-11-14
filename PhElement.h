/*!
 *  @file RobotClass_PhButton.h
 *  Заголовок класса для работы с элементом
 *  Автор: Олег Евсегнеев, 2023.
 *  e-mail: oleg.evsegneev@gmail.com
 */
 
#ifndef __PHELEMENT_H__
#define __PHELEMENT_H__

#include "PhHardware.h"

typedef void (*PhTouchEventCb)();

class PhElement{
	public:
		PhTouchEventCb _cb_push;
		PhTouchEventCb _cb_pop;

		PhElement( PhHardware* hw, uint8_t pid, uint8_t id, uint8_t type, uint8_t touch );
		uint16_t getValue(char *buf, uint16_t len);
		uint8_t setValue(const char *buf);
		uint8_t setValue(int32_t v);
		uint8_t setValue(int16_t v) {return setValue((int32_t)v);};
		uint8_t setValue(int8_t v) {return setValue((int32_t)v);};
		uint8_t setValue(float v, uint8_t width = 4, uint8_t precision = 2);

		uint8_t getId();
		uint8_t getPid();
		uint8_t getTouch();
		uint8_t isTouch( uint8_t pid, uint8_t id );

		void attachPush( PhTouchEventCb push );
		void detachPush( void );
		void attachPop( PhTouchEventCb pop );
		void detachPop( void );
	private:
		PhHardware *_hw = NULL;

		uint8_t _touch = 0;
		uint8_t _type;
		uint8_t _pid;
		uint8_t _id;
};


#endif /* #ifndef __PHELEMENT_H__ */