//
//  ofxTouche.h
//  toucheOpenSource
//
//  Created by BRenfer on 3/21/13.
//  Copyright (c) 2013 __MyCompanyName__. All rights reserved.
//

#pragma once

#include "ofMain.h"

class ofxTouche : protected ofThread
{
public:
    
    // if empty, tries to find usbserial
    bool setup( string name = "" );
    void draw( int x, int y, int width=400, int height=400 );
    
    vector<int> currentReads_store;
    vector<int> calculated_difference;
    vector<int> currentReads;
    vector<int> currentTimeReads;
    
protected:
    void threadedFunction();
    
    vector<int> powerBuffer;
    vector<int> voltageBuffer;
    vector<int> timeBuffer;
    
    ofSerial serial;
    
    static const int    packetSize = 8; // The size of the buffer array
    vector<int>         serialInArray;  //buffer of raw reads
    
    
private:
    bool bSetup, bStartedUnpacking;
};

