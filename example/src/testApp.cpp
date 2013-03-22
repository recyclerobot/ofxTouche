// --------------------------------------------------------------------------
//
// ofxTouche
// openframeworks conversion from
// http://www.instructables.com/id/Touche-for-Arduino-Advanced-touch-sensing/
 
// made at resonate.io 2013
// by Brett Renfer
//    Bjorn Staal
//    Thijs Bernolet
 
// --------------------------------------------------------------------------

#include "testApp.h"

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
    touche.draw(20, 20, 600, 600);
}

//--------------------------------------------------------------
void testApp::keyPressed  (int key){ 
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){ 
	
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y){
	
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){
	
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){
	
}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){
	
}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){
	
}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 
	
}

