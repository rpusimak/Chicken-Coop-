/********************************************
 *Chicken Coop Drive Program
 *Paul Usimaki
 *Oct 10, 2021 
 *This program is a GPS guided guidance system to controls two 12v gear motors for motion and steering.
 *Arduino Mega, Adafruit HMC5883L Compass, BTS7960 Motor Shield, HC-06 BlueTooth Module,  NEO 6M Compass Module
 *
 *CompassSCL = Arduino 21
 *CompassSDA = Arduino 20  
 *
 *GPS RX = Arduino TX Pin 16
 *GPS TX = Arduino RX Pin 17
 *
 *BT RX = Arduino TX Pin 18
 *BT TX = Arduino RX Pin 19
 ******************************************/
#include <Wire.h>                             //Generic wire library       
#include <HMC5883L.h>
#include <TinyGPSPlus.h>                      
#include <SoftwareSerial.h>
HMC5883L compass;

/********************************************
 *Initialize variables for Bluetooth  
********************************************/
const byte numChars = 32;
char receivedChars[numChars];
boolean newData = false;
int newDataTimer = 500;
boolean newDataTimerOn;

/********************************************
 *Initialize two variables to control vehicle heading.  When the Arduino resets it will store an
 *initial heading.  The vehicle will try to keep this heading.  
********************************************/
float   headingDeg;                         // Current heading of the vehicle
int     WPNumber = 1;                       // initialise the first course target that GPS will guide towards
double  courseToWP;                         // This is the GPS course to the next way point
double  MetersToWP ;
float   offHeading;
int     arraySize = 20;
double  gpsLatArray[20];
double  gpsLngArray[20];
int     gpsLatIndex = 0;
int     gpsLngIndex = 0;
float   averageLat;
float   averageLng;

/********************************************
 Declare the variables for the GPS and initialize the GPS object
 Initialize the soft serial connection to the GPS
********************************************/
TinyGPSPlus gps;                              //  Initialize TinyGPSPlus 
float wpTime = 0; 
/********************************************
 *Initialize the variables that control the motor shields (BTS7960).  The motor shields use PWM to
 *vary the running voltage.  
 *L_PWM and R_PWM are pwm signals between 0 and 255
 *L_IS and R_IS Pin is current feed back and not used
 *Right_R_EN, Right_L_EN, Left_R_EN,Left_L_EN   wired to 5v
********************************************/
int     travelSpeed = 40;
int     PID_Output;
float   PID_P;
float   PID_I;
float   PID_D;
float   PID_millis;


int     Right_R_PWM_Target;
int     Left_R_PWM_Target;
int     Right_R_PWM;                         // PWM speed for right motor 0-255
int     Left_R_PWM;                          // PWM speed for left motor 0-255
int     Right_L_PWM;
int     Left_L_PWM;

float   Time;
float   Time_Target;
int     motorSampleInterval = 10;
int     motorSampleIncrement = 1;

int     Right_R_PWM_Pin =2 ;    
int     Right_L_PWM_Pin =3 ;
int     Left_R_PWM_Pin =4 ;
int     Left_L_PWM_Pin =5;
int     Right_R_EN_Pin = 6;
int     Right_L_EN_Pin = 7;
int     Left_R_EN_Pin = 8;
int     Left_L_EN_Pin = 9;

/********************************************
 *State variables to control the state of the robot. 
********************************************/
char mode[] = "man";  //(1) Gps auto control, (2) Phone control
char man[] = "man";
char atm[] = "atm"; 
 
void setup(){   
  Serial.begin(9600);                 // Serial connection to the PC 
  Serial1.begin(19200);                // Serial connection to the BlueTooth module
  Serial2.begin(9600);                // Serial connection to the GPS.

  pinMode(Right_R_PWM_Pin, OUTPUT);
  pinMode(Right_L_PWM_Pin, OUTPUT);
  pinMode(Left_R_PWM_Pin, OUTPUT);
  pinMode(Left_L_PWM_Pin, OUTPUT);
  pinMode(Right_R_EN_Pin, OUTPUT);
  pinMode(Right_L_EN_Pin, OUTPUT);
  pinMode(Left_R_EN_Pin, OUTPUT);
  pinMode(Left_L_EN_Pin, OUTPUT); 
   
  Serial.println("Initialize HMC5883L");              // Initialize Initialize HMC5883L
  while (!compass.begin())
  {
    Serial.println("Could not find a valid HMC5883L sensor, check wiring!");
    delay(500);
  }
  
    compass.setRange(HMC5883L_RANGE_1_3GA);           // Set measurement range
    compass.setMeasurementMode(HMC5883L_CONTINOUS);   // Set measurement mode
    compass.setDataRate(HMC5883L_DATARATE_30HZ);      // Set data rate
    compass.setSamples(HMC5883L_SAMPLES_8);           // Set number of samples averaged
    compass.setOffset(-20, -165);                     // Set calibration offset. See HMC5883L_calibration.ino
}

  
void loop(){

//1. Look for bluetooth command
recvWithStartEndMarkers();

//2. Update run conditions
if (newData == true){setRunConditions();}

//3. if in gps mode then run the GPS motor control functions
if (strcmp(mode, atm) == 0){gpsMotors();} 

//4. Run manual motor controls
if (strcmp(mode, man) == 0){manMotors();}


GPSHeading();

//compassHeading();

serialPrint(); 

  
  if(MetersToWP <= 2 && millis() >= wpTime + 20000) 
  { 
    wpTime = millis();            
    WPNumber++; ;
  }  
  if(WPNumber == 6)WPNumber = 1;    
  
}
