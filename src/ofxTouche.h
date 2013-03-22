// --------------------------------------------------------------------------
//
// ofxTouche
// openframeworks conversion from
// http://www.instructables.com/id/Touche-for-Arduino-Advanced-touch-sensing/

// made at resonate.io 2013
// by Brett Renfer
//    Bjorn Staal
//    Thijs Bernolet

#pragma once

#include "ofMain.h"

class ofxTouche : protected ofThread
{
public:
    
    ~ofxTouche();
    
    // if empty, tries to find usbserial
    bool setup( string name = "" );
    
    // draw graph + peak
    void draw( int x, int y, int width=400, int height=400, ofColor color = ofColor(0) );
    
    // vector of current voltage reads (aka 'y')
    vector<int> currentReads;
    
    // vector of current time reads (aka 'x')
    vector<int> currentTimeReads;
    
    // get peak: x == position in array, y == actual value
    ofVec2f getPeak();
    
protected:
    void threadedFunction();
    
    vector<int> powerBuffer;
    vector<int> voltageBuffer;
    vector<int> timeBuffer;
    
    ofSerial serial;
    
    static const int    packetSize = 8;     // The size of the buffer array
    static const int    maxRead     = 1024; // Highest sensor read (for graphing)
    vector<int>         serialInArray;      //buffer of raw reads
    
    
private:
    bool bSetup;
};

