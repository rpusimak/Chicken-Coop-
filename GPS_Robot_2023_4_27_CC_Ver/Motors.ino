

void gpsMotors(){
/*************************************
* void gpsMotors()
* Function runs motors for a the duration motorTimeOnFast + motorTimeOn
* The while loop adds 100 milliseconds everytime it is executed.
* Calls the motorSpeedFunction() every 100 ms to adjust motor speed for steering.
* Finally writes a new time for when the motor were run and sets the motors to 0.
**************************************/
    char left[] = "left";
    char right[] = "right";
    char fast[] = "fast";
    char slow[] = "slow";
    char idx[]  = "idx";  
    int headingCorrect; 
       
    offHeading = courseToWP - headingDeg;
    
        if (offHeading <=0 && offHeading>=-180){
          headingCorrect = offHeading;
        }
        else if (offHeading < -180){
          headingCorrect = offHeading +360;
        }
        else if (offHeading >0 && offHeading <= 180){
          headingCorrect = offHeading;
        }
        else if (offHeading >= 180){
          headingCorrect = offHeading -360;
        }
        
    PID_P = headingCorrect;
        
    if(millis()-PID_millis <= 100){
        PID_I = .000001 * headingCorrect * (millis() - PID_millis ) + PID_I;
    }
    PID_millis = millis();
    PID_Output = PID_P + PID_I;
    PID_Output = constrain(PID_Output, -40, 40);

       
    Right_R_PWM = travelSpeed - PID_Output;
        if(Right_R_PWM < 40 ){
          Right_R_PWM = 40;
        }
        else if (Right_R_PWM > 254){
          Right_R_PWM = 254;
        }
          
        
    Left_R_PWM = travelSpeed + PID_Output;
        if(Left_R_PWM < 40){
          Left_R_PWM = 40;
        }
        else if (Left_R_PWM > 254){
          Left_R_PWM = 254;   
        }
    analogWrite(Right_R_PWM_Pin, Right_R_PWM );
    analogWrite(Left_R_PWM_Pin, Left_R_PWM);      
    
      if (newData == true){
        if(strcmp(receivedChars, fast) == 0){
          travelSpeed = travelSpeed +5;
          newData = false;
        }
        if(strcmp(receivedChars, slow) == 0){
          travelSpeed = travelSpeed -5;
          newData = false;
        }
        if(strcmp(receivedChars, idx) == 0){
          WPNumber = WPNumber + 1;
          
          newData = false;
        }
      }
}


void manMotors(){
char left[] = "left";
char right[] = "right";
char fast[] = "fast";
char slow[] = "slow";
char zero[] = "zero";
  
  if (newData == true){

    if(strcmp(receivedChars, left) == 0){
      Left_R_PWM_Target = Left_R_PWM_Target -5;
      Right_R_PWM_Target = Right_R_PWM_Target +5;
      newData = false;
    }
    if(strcmp(receivedChars, right) == 0){
      Left_R_PWM_Target = Left_R_PWM_Target +5;
      Right_R_PWM_Target = Right_R_PWM_Target -5;
      newData = false;
    }
    if(strcmp(receivedChars, fast) == 0){
      Left_R_PWM_Target = Left_R_PWM_Target +5;
      Right_R_PWM_Target = Right_R_PWM_Target +5;
      newData = false;
    }
    if(strcmp(receivedChars, slow) == 0){
      Left_R_PWM_Target = Left_R_PWM_Target -5;
      Right_R_PWM_Target = Right_R_PWM_Target -5;
      newData = false;
    }
    if(strcmp(receivedChars, zero) == 0){
      Left_R_PWM_Target = 0;
      Right_R_PWM_Target = 0;
      newData = false;
    }       
    else {}    

  }


    
    if (Right_R_PWM_Target > 254){Right_R_PWM_Target = 254;}
    if (Left_R_PWM_Target > 254){Left_R_PWM_Target = 254;}




    if( millis() >= Time_Target + motorSampleInterval){

        if (Right_R_PWM_Target > Right_R_PWM){Right_R_PWM = Right_R_PWM + motorSampleIncrement;}
        else if (Right_R_PWM_Target < Right_R_PWM){Right_R_PWM = Right_R_PWM - motorSampleIncrement;}
        
        if (Left_R_PWM_Target > Left_R_PWM){Left_R_PWM = Left_R_PWM + motorSampleIncrement;}
        else if (Left_R_PWM_Target < Left_R_PWM){Left_R_PWM = Left_R_PWM - motorSampleIncrement;}

        Time_Target = millis();
    }

    Right_L_PWM = -1*Right_R_PWM;
    Left_L_PWM = -1*Left_R_PWM;

          
    
    if (Right_R_PWM >= 0) {
      analogWrite(Right_L_PWM_Pin, 0);
      analogWrite(Right_R_PWM_Pin, Right_R_PWM);      

      }
     if (Right_R_PWM < 0) {
      analogWrite(Right_R_PWM_Pin, 0);
      analogWrite(Right_L_PWM_Pin, Right_L_PWM );      
      }

    if (Left_R_PWM >= 0) {
      analogWrite(Left_L_PWM_Pin, 0);
      analogWrite(Left_R_PWM_Pin, Left_R_PWM );

      }
     if (Left_R_PWM < 0) {
      analogWrite(Left_R_PWM_Pin, 0);
      analogWrite(Left_L_PWM_Pin, Left_L_PWM );
      }
    
}
