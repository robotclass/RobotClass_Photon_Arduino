#include "RobotClass_Photon.h"

byte ledPin = 13;

RobotClass_Photon photon = RobotClass_Photon();
Element& phtxt = photon.registerElement(0, 0, EL_TEXT);
Element& phbtn = photon.registerElement(0, 1, EL_BUTTON, ENABLE_TOUCH);

void callbackBtn(){
    digitalWrite( ledPin, HIGH );
    delay(50);
    digitalWrite( ledPin, LOW );
    delay(50);
}

void setup () {
    pinMode(ledPin, OUTPUT);
  
    phbtn.attachPush( callbackBtn );
    photon.begin();
}

void loop () {
    photon.handle();
}
