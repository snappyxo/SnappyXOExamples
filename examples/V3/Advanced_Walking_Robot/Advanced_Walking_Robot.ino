// This project aims to educate the user on how two motors can generate the
// motion needed to create a walking robot
//
// Developed by A+ Mobile Solutions Inc
// Licensed under the MIT License. See LICENSE for details.
#include <SnappyXOShield.h>

SnappyXOShield shield(SnappyXOShield::V3);  // the shield version printed on the board: V3 or V2

// This setup section will be executed once
void setup() { shield.begin(); }

// This is the main loop the code will follow
void loop() { shield.forward(); }
