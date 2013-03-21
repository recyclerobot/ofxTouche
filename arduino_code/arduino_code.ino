
/** Touche conversion from http://www.instructables.com/id/Touche-for-Arduino-Advanced-touch-sensing/   
 *
 *                                                                        s                 
 * 
 * three sensing methods 
 * 1. One Pin
 * 2. QPROX
 * 3. Touche 
 **/

#define  ONEPIN  1
#define  QPROX   2
#define  TOUCHE  3

#define SENSE_METHOD  TOUCHE

//****************************************************************************************
// Illutron take on Disney style capacitive touch sensor using only passives and Arduino
// Dzl 2012
//****************************************************************************************
//                              10n
// PIN 9 --[10k]-+-----10mH---+--||-- OBJECT
//               |            |
//              3.3k          |
//               |            V 1N4148 diode
//              GND           |
//                            |
//Analog 0 ---+------+--------+
//            |      |
//          100pf   1MOmhm
//            |      |
//           GND    GND


// One Pin
uint8_t  gOnePinVal = 0;

// QProx
uint8_t  gQproxVal = 0;

// Touche
#define SET(x,y) (x |=(1<<y))				//-Bit set/clear macros
#define CLR(x,y) (x &= (~(1<<y)))       		// |
#define CHK(x,y) (x & (1<<y))           		// |
#define TOG(x,y) (x^=(1<<y))            		//-+
#define N 160  //How many frequencies
float results[N];            //-Filtered result buffer
float freq[N];            //-Filtered result buffer
int sizeOfArray = N;

boolean request = false;

void setup()
{
  pinMode(12, INPUT);
  Serial.begin(115200); 
  Serial.flush();
}

// One Pin method
uint8_t readCapacitivePin(int pinToMeasure)
{
  // Variables used to translate from Arduino to AVR pin naming
  volatile uint8_t* port;
  volatile uint8_t* ddr;
  volatile uint8_t* pin;

  // Translate input pin number from Arduino
  // to corresponding bit in AVR PORT, PIN, DDR,
  byte bitmask;
  port = portOutputRegister(digitalPinToPort(pinToMeasure));
  ddr = portModeRegister(digitalPinToPort(pinToMeasure));
  bitmask = digitalPinToBitMask(pinToMeasure);
  pin = portInputRegister(digitalPinToPort(pinToMeasure));

  // Discharge the pin first by setting it low and output
  *port &= ~(bitmask);
  *ddr  |= bitmask;
  delay(1);

  // Make the pin an input with the internal pull-up on
  *ddr &= ~(bitmask);
  *port |= bitmask;

  // Now see how long the pin to get pulled up. This manual unrolling of the loop
  // decreases the number of hardware cycles between each read of the pin,
  // thus increasing sensitivity.
  uint8_t cycles;
       if (*pin & bitmask) { cycles =  0;}
  else if (*pin & bitmask) { cycles =  1;}
  else if (*pin & bitmask) { cycles =  2;}
  else if (*pin & bitmask) { cycles =  3;}
  else if (*pin & bitmask) { cycles =  4;}
  else if (*pin & bitmask) { cycles =  5;}
  else if (*pin & bitmask) { cycles =  6;}
  else if (*pin & bitmask) { cycles =  7;}
  else if (*pin & bitmask) { cycles =  8;}
  else if (*pin & bitmask) { cycles =  9;}
  else if (*pin & bitmask) { cycles = 10;}
  else if (*pin & bitmask) { cycles = 11;}
  else if (*pin & bitmask) { cycles = 12;}
  else if (*pin & bitmask) { cycles = 13;}
  else if (*pin & bitmask) { cycles = 14;}
  else if (*pin & bitmask) { cycles = 15;}
  else if (*pin & bitmask) { cycles = 16;}
  else if (*pin & bitmask) { cycles = 17;}
  else if (*pin & bitmask) { cycles = 18;}
  else if (*pin & bitmask) { cycles = 19;}
  else if (*pin & bitmask) { cycles = 20;}
  else if (*pin & bitmask) { cycles = 21;}
  else if (*pin & bitmask) { cycles = 22;}
  else if (*pin & bitmask) { cycles = 23;}
  else if (*pin & bitmask) { cycles = 24;}
  else if (*pin & bitmask) { cycles = 25;}
  else if (*pin & bitmask) { cycles = 26;}
  else if (*pin & bitmask) { cycles = 27;}
  else if (*pin & bitmask) { cycles = 28;}
  else if (*pin & bitmask) { cycles = 29;}
  else if (*pin & bitmask) { cycles = 30;}
  else if (*pin & bitmask) { cycles = 31;}
  else if (*pin & bitmask) { cycles = 32;}
  else if (*pin & bitmask) { cycles = 33;}
  else if (*pin & bitmask) { cycles = 34;}
  else if (*pin & bitmask) { cycles = 35;}
  else if (*pin & bitmask) { cycles = 36;}
  else if (*pin & bitmask) { cycles = 37;}
  else if (*pin & bitmask) { cycles = 38;}
  else if (*pin & bitmask) { cycles = 39;}
  else if (*pin & bitmask) { cycles = 40;}
  else if (*pin & bitmask) { cycles = 41;}
  else if (*pin & bitmask) { cycles = 42;}
  else if (*pin & bitmask) { cycles = 43;}
  else if (*pin & bitmask) { cycles = 44;}
  else if (*pin & bitmask) { cycles = 45;}
  else if (*pin & bitmask) { cycles = 46;}
  else if (*pin & bitmask) { cycles = 47;}
  else if (*pin & bitmask) { cycles = 48;}
  else if (*pin & bitmask) { cycles = 49;}
  else if (*pin & bitmask) { cycles = 50;}
  else if (*pin & bitmask) { cycles = 51;}
  else if (*pin & bitmask) { cycles = 52;}
  else if (*pin & bitmask) { cycles = 53;}
  else if (*pin & bitmask) { cycles = 54;}
  else if (*pin & bitmask) { cycles = 55;}
  else if (*pin & bitmask) { cycles = 56;}
  else if (*pin & bitmask) { cycles = 57;}
  else if (*pin & bitmask) { cycles = 58;}
  else if (*pin & bitmask) { cycles = 59;}
  else if (*pin & bitmask) { cycles = 60;}
  else if (*pin & bitmask) { cycles = 61;}
  else if (*pin & bitmask) { cycles = 62;}
  else cycles = 63;

  // Discharge the pin again by setting it low and output
  //  It's important to leave the pins low if you want to 
  //  be able to touch more than 1 sensor at a time - if
  //  the sensor is left pulled high, when you touch
  //  two sensors, your body will transfer the charge between
  //  sensors.
  *port &= ~(bitmask);
  *ddr  |= bitmask;

  return cycles;
}

void loop()
{
  
  while( Serial.available() > 0 ){
    byte c = Serial.read();
    request = true;  
  }
  uint8_t val;
  
#if SENSE_METHOD == ONEPIN
  // ONE PIN
  val = readCapacitivePin(2);
  if (val != gOnePinVal) {
    gOnePinVal = val;
    Serial.print("OnePin = ");
    Serial.println(val);   
  }
  delay(10);
#endif
  
#if SENSE_METHOD == QPROX
  // QPROX
  val = digitalRead(12);
  if (val != gQproxVal) {
    gQproxVal = val;
    Serial.print("QProx  = ");
    Serial.println(val);   
  }
#endif

#if SENSE_METHOD == TOUCHE
  // TOUCHE
//  unsigned int d;
  int counter = 0;

  TCCR1A = 0b10000010;        //-Set up frequency generator
  TCCR1B = 0b00011001;        //-+
  ICR1 = 110;
  OCR1A = 55;

  pinMode(7, INPUT);        //put wrong connection into Hi-Z
  pinMode(8, OUTPUT);        //-Signal generator pin
  pinMode(9, OUTPUT);        //-Sync (test) pin

  for (int i = 0; i < N; i++)      //-Preset results
    results[i] = 0;         //-+
    
  for (unsigned int d = 0; d < N; d++)
  {
    int v = analogRead(0);    //-Read response signal
    CLR(TCCR1B, 0);           //-Stop generator
    TCNT1 = 0;                //-Reload new frequency
    ICR1 = d;                 // |
    OCR1A = d/2;              //-+
    SET(TCCR1B, 0);           //-Restart generator

    results[d] = results[d] * 0.5 + (float)(v) * 0.5; //Filter results
    freq[d] = d;
  }
   PlottArray(1, freq, results);
  if( request ){
    PlottArray(1, freq, results);
    request = false;
  } 
  TOG(PORTB, 0);            //-Toggle pin 9 after each sweep (good for scope)
#endif
}

