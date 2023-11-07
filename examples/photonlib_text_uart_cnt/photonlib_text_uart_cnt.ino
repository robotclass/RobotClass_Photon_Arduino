#include "RobotClass_Photon.h"

RobotClass_Photon photon = RobotClass_Photon();
Element& phtxt = photon.registerElement(0, 0, EL_TEXT);

int counter = 0;

void setup () {
    photon.begin();
}

void loop () {
    phtxt.setValue(counter);
    counter++;
    delay(100);
}
