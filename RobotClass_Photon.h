#include <Arduino.h>
#include "PhHardware.h"
#include "PhElement.h"

#define EL_TEXT 0
#define EL_BUTTON 1
#define EL_BAR 2
#define EL_GAUGE 3
#define EL_SWITCH 4
#define EL_IMAGE 5

#define DISABLE_TOUCH 0
#define ENABLE_TOUCH 1

class RobotClass_Photon;

class RobotClass_Photon{
	public:
		RobotClass_Photon( uint8_t hwif = PH_HWIF_UART, HardwareSerial *serial = &Serial );
		void begin( uint32_t v = PH_DEFAULT_BAUD );
		void handle();

		Element& registerElement( uint8_t pid, uint8_t id, uint8_t type, uint8_t touch = DISABLE_TOUCH );

		uint8_t setPage( uint8_t page );

	private:
		PhHardware *_hw = NULL;

		Element** _elements = NULL;
		uint8_t _elements_n = 0;

		uint8_t _page = 0;
};