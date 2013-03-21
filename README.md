ofxTouche
=========

// ofxTouche
// openframeworks conversion from
// http://www.instructables.com/id/Touche-for-Arduino-Advanced-touch-sensing/
 
// made at resonate.io 2013
// by Brett Renfer
//    Bjorn Staal
//    Thijs Bernolet


Example usage:

//--------------------------------------------------------------
void testApp::setup(){

    // First run arduino code at baud: 115200
    touche.setup();
}

//--------------------------------------------------------------
void testApp::update(){
    ofSetWindowTitle(ofToString(ofGetFrameRate()));
}

//--------------------------------------------------------------
void testApp::draw(){
    ofSetColor(0);
    touche.draw(20, 20);
}