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

class Element{
	public:
		PhTouchEventCb _cb_push;
		PhTouchEventCb _cb_pop;

		Element( PhHardware* hw, uint8_t pid, uint8_t id, uint8_t type, uint8_t touch );
		uint16_t getValue(char *buf, uint16_t len);
		bool setValue(const char *buf);
		bool setValue(uint32_t v);

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