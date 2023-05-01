#define outSerial Serial //normal: Serial; BlueTooth: Serial1

//#define SCLK 18
//#define MOSI 23
//#define MISO 19
//#define DA_CS 22
//#define AD_CS 5

#define DIN 3
#define CLK 4
#define LE 5
#define CLR 8

String mess1, mess2, mess3;
String channelIn[20];
String strengthIn[20];

float strength[20];

float smoothFactor = 0.2;
float smoothIncrement[20];
float curStrength[20] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

int pulseWidth;
int frequency;
float invFrequency = 0;
int lastLoopStartTime = 0;

int trigger = 0;
int channel[20];

byte input[21][16] = {
  { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 }, //initial
  { 0,1,0,0,0,0,0,0,0,0,0,1,0,1,0,1 }, //1 thumb
  { 0,1,0,0,0,0,0,0,0,0,0,1,1,0,1,0 }, //2 thumb
  { 0,1,0,0,0,0,0,0,0,0,1,0,0,1,0,1 }, //3 index_top
  { 0,1,0,0,0,0,0,0,0,0,1,0,1,0,1,0 }, //4 index_top
  { 0,1,0,0,0,0,0,0,0,1,0,0,0,1,0,1 }, //5 middle_top
  { 0,1,0,0,0,0,0,0,0,1,0,0,1,0,1,0 }, //6 middle_top
  { 1,0,0,0,0,0,0,0,1,0,0,0,0,1,0,1 }, //7 ring_top
  { 1,0,0,0,0,0,0,0,1,0,0,0,1,0,1,0 }, //8 ring_top
  { 1,0,0,0,0,0,0,1,0,0,0,0,0,1,0,1 }, //9 pinky_top
  { 1,0,0,0,0,0,0,1,0,0,0,0,1,0,1,0 }, //10 pinky_top
  { 0,1,0,0,0,0,1,0,0,0,0,0,0,1,0,1 }, //11 index_bottom
  { 0,1,0,0,0,0,1,0,0,0,0,0,1,0,1,0 }, //12 index_bottom
  { 0,1,0,0,0,1,0,0,0,0,0,0,0,1,0,1 }, //13 middle_bottom
  { 0,1,0,0,0,1,0,0,0,0,0,0,1,0,1,0 }, //14 middle_bottom
  { 1,0,0,0,1,0,0,0,0,0,0,0,0,1,0,1 }, //15 ring_bottom
  { 1,0,0,0,1,0,0,0,0,0,0,0,1,0,1,0 }, //16 ring_bottom
  { 1,0,0,1,0,0,0,0,0,0,0,0,0,1,0,1 }, //17 pinky_bottom
  { 1,0,0,1,0,0,0,0,0,0,0,0,1,0,1,0 }, //18 pinky_bottom
  { 1,1,1,0,0,0,0,0,0,0,0,0,0,1,0,1 }, //19 palm
  { 1,1,1,0,0,0,0,0,0,0,0,0,1,0,1,0 }  //20 palm
};

void setup() {
//  pinMode(DA_CS, OUTPUT);
//  pinMode(AD_CS, OUTPUT);
  pinMode( DIN, OUTPUT );
  pinMode( CLK, OUTPUT );
  pinMode( LE, OUTPUT );
  pinMode( CLR, OUTPUT );

//  SPI.begin(SCLK, MISO, MOSI);
//  SPI.setFrequency(32000000);
//  SPI.setDataMode(SPI_MODE0);
  outSerial.begin(115200);
  while (!outSerial);
  outSerial.setTimeout(15);
   
  digitalWrite(LE, HIGH);
  digitalWrite(CLR, LOW);
}

void loop() { 
  if (millis() < lastLoopStartTime + invFrequency*1000) return; //maintaining stimulation loop operates at the frequency.
  lastLoopStartTime = millis();


  if ( outSerial.available() ) {
    mess1 = outSerial.readStringUntil(',');
    mess2 = outSerial.readStringUntil(',');
    mess3 = outSerial.readStringUntil(',');

    for ( int i=0; i<20; i++ ) {
      strengthIn[i] = outSerial.readStringUntil(',');
      strength[i] = strengthIn[i].toInt();
      if (strength[i] > 1024) strength[i] = 1024;

      smoothIncrement[i] = abs(strength[i])*smoothFactor;
    } 
    
    for ( int i=0; i<20; i++ ) {
      if (i == 19) channelIn[i] = outSerial.readStringUntil('\n');
      else channelIn[i] = outSerial.readStringUntil(',');

      channel[i] = channelIn[i].toInt();
      if (!channel[i])
      {
        curStrength[i] = 0;
      }
    }

    pulseWidth = mess1.toInt();
    frequency = mess2.toInt();
    trigger = mess3.toInt();
        
    invFrequency = 1.0/frequency;
  } else {
    //outSerial.end();
  }
//  else {
//    trigger = 0;
//  }

  if (trigger == 1) {
    for ( int i=0; i<20; i++ ) {
      if (channel[i] == 1) {
      stim(i+1);
      }
      else delayMicroseconds(pulseWidth);
    }
  } 
  else if (trigger == 2) {
    pulseWidth = 50000;
    for ( int i=0; i<20; i++ ) {
      if (channel[i] == 1) {
      stim(i+1);
    }
}
  }
  else {
    //curStrength = 0;
    //digitalWrite(DA_CS, LOW);     //enable clock
    analogWrite(A0, 0); //SPI.transfer16(char(0) << 6);
    //digitalWrite(DA_CS, HIGH);
  }

//  if (pulseWidth == 0){
//    outSerial.end();
//    outSerial.begin(115200);
//    while (!outSerial);
//    outSerial.setTimeout(15);
//   
//    digitalWrite(LE, HIGH);
//    digitalWrite(CLR, LOW);
//  }
  
}
