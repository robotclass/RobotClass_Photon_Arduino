//#include <Arduino.h>
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

class RobotClass_Photon: public PhHardware{
	public:
		RobotClass_Photon();
		void begin( TwoWire *wire = &Wire, uint8_t addr = PH_DEFAULT_ADDR );
		void begin( Stream *serial );
		void beginDebug( Stream *serial );

		void handle();

		PhElement& registerElement( uint8_t pid, uint8_t id, uint8_t type, uint8_t touch = DISABLE_TOUCH );

		uint8_t setPage( uint8_t page );
		uint8_t getPage( uint16_t *value );
		uint8_t getVersion( uint16_t *value );
		uint8_t reset();

	private:
		PhHardware *_hw = nullptr;

		PhElement** _elements = nullptr;
		uint8_t _elements_n = 0;

		uint8_t _page = 0;
};