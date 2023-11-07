#include "RobotClass_Photon.h"

byte counter = 0;

RobotClass_Photon photon = RobotClass_Photon();
Element& phtxt = photon.registerElement(0, 0, EL_TEXT);
Element& phbtn = photon.registerElement(0, 1, EL_BUTTON, ENABLE_TOUCH);

void callbackBtn(){
    char str[3];
    sprintf(str, "%02d", counter);
    if( phtxt.setValue( str )){
        counter++;
    }
}

void setup () {
    phbtn.attachPush( callbackBtn );
    photon.begin();
}

void loop () {
    photon.handle();
}
