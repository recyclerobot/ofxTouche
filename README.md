ofxTouche
=========

openframeworks conversion from  
http://www.instructables.com/id/Touche-for-Arduino-Advanced-touch-sensing/ 
 
made at resonate.io 2013 by Brett Renfer, Bjorn Staal, Thijs Bernolet  

Setup:
=======
* Clone into openframeworks/addons
* Use either example or generate new project through the projectGenerator

Example:
=======
```c
void testApp::setup(){
    // First run arduino code at baud: 115200
    // optionally, you can pass in the name of your serial port here
    // (automatically tries to find OS X Arduino)
    touche.setup();
}

void testApp::draw(){
    touche.draw(20, 20);
}
```
