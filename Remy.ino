// units: time --> mille sec, distance --> cm

const int trigPin1 = 2;//front sensor
const int echoPin1 = 4;

const int trigPin2 = A3; //left sensor
const int echoPin2 = A2;

const int trigPin3 = A0;// right sensor
const int echoPin3 = A1;

const int motor1livepin= 6;  // right motor pins
const int motor1groungpin = 7;

const int motor2livepin = 9; // left motor pins
const int motor2groungpin = 8;

const int en1 = 3; //the wires of the motor driver that will control speed of motors
const int en2 = 5;

char previousDirection; //previous motion direction



#define DIS 18  //distance



void setup()
{
Serial.begin(9600); //means that the serial port is capable of transferring a maximum of 9600 bits per second

pinMode(trigPin1, OUTPUT); //pins of the sensors
pinMode(echoPin1, INPUT);
pinMode(trigPin2, OUTPUT);
pinMode(echoPin2, INPUT);
pinMode(trigPin3, OUTPUT);
pinMode(echoPin3, INPUT);

pinMode (motor1livepin, OUTPUT);   // pins of the motors
pinMode (motor1groungpin, OUTPUT);
pinMode (motor2livepin, OUTPUT);
pinMode (motor2groungpin, OUTPUT);

pinMode(en1, OUTPUT); //pins of the motor driver that will control the speed of 
pinMode(en2, OUTPUT);

}



void loop()
{
        forward();
        delay(100);
        reverse();
        delay(100);
        stop();  
        
        analogWrite(en1 , 80);
        analogWrite(en2 , 80);
        
        // no obstacle in all 3 sides
        if (FrontSensor ()>DIS && RightSensor () >DIS && LeftSensor () >DIS)   
          {
            forward();
            delay(660);
            previousDirection = 's';
          }
        
        // obstacle infront of left & right sides
        else if ( FrontSensor () > DIS && RightSensor () < DIS && LeftSensor ()< DIS) 
         {
            forward();  
            delay(660);
            previousDirection = 's';
         }
         
        // obstacle infront of all 3 sides
        else if ( FrontSensor() < DIS && RightSensor () <DIS && LeftSensor ()<DIS) 
         {
            reverse ();
            delay(700);
            stop();
                if(previousDirection == 'l'){
                  if (RightSensor () >DIS){
                    turn_right (); 
                    delay(730);
                    stop();
                    forward();
                    delay(660);
                    previousDirection = 'r';
                  }
                  else{
                    turn_left (); 
                    delay(730);
                    stop();
                    forward();
                    delay(660);
                    previousDirection = 'l';
                  }
                }
                else {          // if(previousDirection == 'r')
                  if (LeftSensor () >DIS){
                    turn_left (); 
                    delay(730);
                    stop();
                    forward();
                    delay(660);
                    previousDirection = 'l';
                  }
                  else{
                    turn_right (); 
                    delay(730);
                    stop();
                    forward();
                    delay(660);
                    previousDirection = 'r';
                  }
                }
 
         }
        
        // obstacle on right and front sides
        else if (FrontSensor() <DIS && RightSensor () <DIS && LeftSensor ()>DIS) 
         {
            turn_left (); 
            delay(730);
            stop();
            forward();
            delay(660);
            previousDirection = 'l';
         }
        
        // obstacle on left and front sides
        else if (FrontSensor() <DIS && RightSensor () >DIS && LeftSensor ()<DIS) 
         {
            turn_right (); 
            delay(730);
            stop();
            forward();
            delay(660);
            previousDirection = 'r';
         }
        
        // obstacle on front side only
        else if (FrontSensor() <DIS && RightSensor () >DIS && LeftSensor ()>DIS) 
         {
            turn_left (); 
            delay(730);
            stop();
            forward();
            delay(660);
            previousDirection = 'l';
         }
        
        // obstacle on left sides ---------->
        else if (FrontSensor() >DIS && RightSensor () >DIS && LeftSensor ()<DIS) 
         {
            forward(); 
            delay(730);
            stop();
            forward();
            delay(660);
            previousDirection = 's';
         }
        
        // obstacle on right sides
        else if (FrontSensor() >DIS && RightSensor () <DIS && LeftSensor ()>DIS)
         {
            turn_left ();
            delay(730);
            stop();
            forward();
            delay(660);
            previousDirection = 'l';
         }

        // nothing happpened..
        else
         {
            forward();
            delay(660);
            previousDirection = 's';
         }

}


//Directions Functions

//Forward Direction
void forward ()
  {
    // right motor go on
    digitalWrite(motor1livepin, HIGH); 
    digitalWrite(motor1groungpin, LOW);
    // left motor go on
    digitalWrite(motor2livepin, HIGH);
    digitalWrite(motor2groungpin, LOW);
  }

//Turn Left Direction
void turn_left ()
  {
    // right motor go on
    digitalWrite(motor1livepin, HIGH);
    digitalWrite(motor1groungpin, LOW);
    // left motor off
    digitalWrite(motor2livepin, LOW);
    digitalWrite(motor2groungpin, LOW);
   
  }

//Turn Right Direction
void turn_right ()
  {
    // right motor go
    digitalWrite(motor1livepin, LOW);
    digitalWrite(motor1groungpin, LOW);
    // left motor off
    digitalWrite(motor2livepin, HIGH);
    digitalWrite(motor2groungpin, LOW);
    
  }
  
//REVERSE -- BACKWARD
void reverse ()
  {
    // right motor go back
    digitalWrite(motor1livepin, LOW);
    digitalWrite(motor1groungpin, HIGH);
    // left motor go back
    digitalWrite(motor2livepin, LOW);
    digitalWrite(motor2groungpin, HIGH);
  }

// STOP
void stop()
  {
    // all motors off
    digitalWrite(motor1livepin, LOW);
    digitalWrite(motor1groungpin, LOW);
    digitalWrite(motor2livepin, LOW);
    digitalWrite(motor2groungpin, LOW);
    delay(1000);
  }



//sensors Functions

 
long FrontSensor ()
  {
    long dur, cm;
    // Clears the trigPin condition
    digitalWrite(trigPin1, LOW);
    // keep this state for 5 microseconds
    delayMicroseconds(5);
    // Sets the trigPin HIGH (ACTIVE) for 10 microseconds [transmit]
    digitalWrite(trigPin1, HIGH);
    //keep this state for 10 microseconds
    delayMicroseconds(10);
    // stop transmitting
    digitalWrite(trigPin1, LOW);
    // pulse in returns the time from transmitting to receiving in microseconds
    // so, duration is this time
    dur = pulseIn(echoPin1, HIGH);
    
    // distance in centimeters.
    cm = (dur / 2) / 29.1;
    Serial.print("Front ");
    Serial.println(cm);
    
    return cm;
  }

long LeftSensor ()
  {
    long dur, cm;
    // Clears the trigPin condition
    digitalWrite(trigPin2, LOW);
    // keep this state for 5 microseconds
    delayMicroseconds(5);
    // Sets the trigPin HIGH (ACTIVE) for 10 microseconds [transmit]
    digitalWrite(trigPin2, HIGH);
    //keep this state for 10 microseconds
    delayMicroseconds(10);
    // stop transmitting
    digitalWrite(trigPin2, LOW);
    // pulse in returns the time from transmitting to receiving in microseconds
    // so, duration is this time
    dur = pulseIn(echoPin2, HIGH);
    
    // distance in centimeters.
    cm = (dur / 2) / 29.1;
    Serial.print("Left ");
    Serial.println(cm);
    
    return cm;
  }

  
long RightSensor ()
  {
    long dur, cm;
    // Clears the trigPin condition
    digitalWrite(trigPin3, LOW);
    // keep this state for 5 microseconds
    delayMicroseconds(5);
    // Sets the trigPin HIGH (ACTIVE) for 10 microseconds [transmit]
    digitalWrite(trigPin3, HIGH);
    //keep this state for 10 microseconds
    delayMicroseconds(10);
    // stop transmitting
    digitalWrite(trigPin3, LOW);
    // pulse in returns the time from transmitting to receiving in microseconds
    // so, duration is this time
    dur = pulseIn(echoPin3, HIGH);
    
    // distance in centimeters.
    cm = (dur / 2) / 29.1;
    Serial.print("Right ");
    Serial.println(cm);
    
    return cm;
  }