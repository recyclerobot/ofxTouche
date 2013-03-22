// --------------------------------------------------------------------------
//
// ofxTouche
// openframeworks conversion from
// http://www.instructables.com/id/Touche-for-Arduino-Advanced-touch-sensing/

// made at resonate.io 2013
// by Brett Renfer
//    Bjorn Staal
//    Thijs Bernolet

#include "ofxTouche.h"

//------------------------------------------
ofxTouche::~ofxTouche(){
    stopThread();
    serial.close();
}

//------------------------------------------
bool ofxTouche::setup( string name ){
    
    // search for available arduino serial port
    
    vector <ofSerialDeviceInfo> info = serial.getDeviceList();
    
    if ( name == "" ){
        for ( int i=0; i<info.size(); i++){
            if ( info[i].getDeviceName().find("tty.usbmodem") != string::npos ){
                bSetup = serial.setup( info[i].getDevicePath(), 115200 );
                cout<<" setting up "<<info[i].getDevicePath()<<" "<<bSetup<<endl;
                break;
            }
        }
    } else {
        bSetup = serial.setup( name, 115200 );
    }
    
    if ( bSetup){
        startThread();
    }
    
    return bSetup;
}

//------------------------------------------
void ofxTouche::draw( int x, int y, int width, int height, ofColor color ){
    if ( currentTimeReads.size() == 0) return;
    
    ofPushMatrix();
    ofTranslate(x, y);
    ofPushStyle();
    ofNoFill();
    ofBeginShape();
    ofSetColor(color);
    
    for ( int i=1; i<currentReads.size(); i++){
        
        ofCurveVertex( (float) ( currentTimeReads[i]-currentTimeReads[0])/(currentTimeReads[currentTimeReads.size()-1]-currentTimeReads[0])*width,
                      height- (float) currentReads[i]/maxRead*height );
    }
    
    ofVec2f max = getPeak();
    ofEndShape();
    
    ofSetColor(255,0,0);
    ofCircle((float) ( max.x-currentTimeReads[0])/(currentTimeReads[currentTimeReads.size()-1]-currentTimeReads[0])*width, height- (float) max.y/maxRead*height, 20);
      
    ofPopStyle();
    ofPopMatrix();
}


//------------------------------------------
ofVec2f ofxTouche::getPeak(){
    if ( currentReads.size() == 0 ){
        return ofPoint(0,0);
    }
    
    // uses the ever-amazing std::max_element to find the peak
    vector<int>::iterator it = max_element(currentReads.begin(), currentReads.end());
    
    // the * is getting the reference from the iterator, aka the int value
    return ofVec2f( it - currentReads.begin(), *it);
}

//------------------------------------------
void ofxTouche::threadedFunction(){
    while( isThreadRunning() ){
        
        bool DataRecieved=false, Data1Recieved=false, Data2Recieved=false;
        
        int serialCount = 0; // A count of how many bytes received
        int xMSB, xLSB, yMSB, yLSB;

        int xValue, yValue, Command;
        
        while ( serial.available() > 0 ){
            int inByte = serial.readByte();
            
            if (inByte==0){
                serialCount=0;
                serialInArray.clear();
            }
            
            if ( inByte>255 ) {
                break;
            }
            
            // Add the latest byte from the serial port to array:
            serialInArray.push_back( inByte );
            
            bool bError=true;
            if ( serialInArray.size() == packetSize ) {
                
                int Checksum=0;
                
                //Checksum = (Command + yMSB + yLSB + xMSB + xLSB + zeroByte)%255;
                for (int x=0; x<serialInArray.size()-1; x++) {
                    Checksum=Checksum+serialInArray[x];
                }
                
                Checksum=Checksum%255;
                
                // check if checksum is ok
                if (Checksum==serialInArray[serialInArray.size()-1]) {
                    bError = false;
                    DataRecieved=true;
                }
                else {
                    bError = true;
                    DataRecieved=false;
                }
            }
            
            if (!bError) {
                
                int zeroByte = serialInArray[6];                
                xLSB = serialInArray[3];
                if ( (zeroByte & 1) == 1) xLSB=0;
                xMSB = serialInArray[2];
                if ( (zeroByte & 2) == 2) xMSB=0;
                yLSB = serialInArray[5];
                if ( (zeroByte & 4) == 4) yLSB=0;
                yMSB = serialInArray[4];
                if ( (zeroByte & 8) == 8) yMSB=0;
                
                Command  = serialInArray[1];
                
                xValue   = xMSB << 8 | xLSB;    // Get xValue from yMSB & yLSB
                yValue   = yMSB << 8 | yLSB;    // Get yValue from xMSB & xLSB
                

                
                switch(Command) {
                        
                    case 1: // Data is added to dynamic arrays
                        
                        timeBuffer.push_back( xValue );
                        voltageBuffer.push_back( yValue );
                        break;
                        
                    case 2: // An array of unknown size is about to be recieved, empty storage arrays
                        
                        timeBuffer.clear();
                        voltageBuffer.clear();
                        break;
                        
                    case 3:  // Array has finnished being recieved, update arrays being drawn, swap buffers
                        
                        lock();
                        currentReads.clear();
                        currentReads = voltageBuffer;
                        
                        currentTimeReads.clear();
                        currentTimeReads = timeBuffer;
                        unlock();
                        break;  
                        
                    case 20:  
                        powerBuffer.push_back( yValue );
                        break; 
                        
                }
            }
        }
    }
}