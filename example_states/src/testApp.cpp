#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    touche.setup();
    currentState = 0;
}

//--------------------------------------------------------------
void testApp::update(){
    ofVec2f peak = touche.getPeak();
    
    // you can play with this threshold a bit,
    // or just try to match the 'x' value (position in array)
    // instead of matching the position and value
    
    if ( peak.distance(state1) < 5){
        currentState = 1;
    } else if ( peak.distance(state2) < 5){
        currentState = 2;
    } else {
        currentState = 0;
    }
}

//--------------------------------------------------------------
void testApp::draw(){
    if ( currentState == 1 ){
        ofBackgroundGradient(ofColor(150,0,150), ofColor(150,0,0));
    } else if ( currentState == 2 ){
        ofBackgroundGradient(ofColor(0,150,150), ofColor(100,100,0));
    } else {
        ofBackground(0);
    }
    
    ofDrawBitmapString("Press '1' to capture state 1\nPress '2' to capture state 2", 20,20);
    touche.draw(0, 0, 300,300,ofColor(255));
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
    if ( key == '1'){
        state1 = touche.getPeak();
    } else if ( key == '2'){
        state2 = touche.getPeak();
    }
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

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