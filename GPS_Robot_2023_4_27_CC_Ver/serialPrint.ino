void serialPrint(){
  
    if(millis() >=Time+5000){

        Serial.print("Received Characters: ");
        Serial.println(receivedChars);
       
        Serial.print("Distance (m) to Way Point: ");
        Serial.println(MetersToWP);
        
        Serial.print("Course to Way Point: ");
        Serial.println(courseToWP);
        
        Serial.print("WP Number: ");
        Serial.println(WPNumber);
        
        Serial.print("Heading: ");
        Serial.println(headingDeg);
        
        Serial.print("offHeading: ");
        Serial.println(offHeading);
        
        Serial.print("Right Motor:" );
        Serial.println(Right_R_PWM);
        
        Serial.print("Left Motor: ");
        Serial.println(Left_R_PWM);          
           
        Serial.print("Right Motor Rev: ");
        Serial.println(Right_L_PWM); 

        Serial.print("Left Motor Rev: ");
        Serial.println(Left_L_PWM); 
        
        Serial.println();

        Serial1.print("Distance (m) to Way Point: ");
        Serial1.println(MetersToWP);
        
        Serial1.print("Course to Way Point: ");
        Serial1.println(courseToWP);
        
        Serial1.print("WP Number: ");
        Serial1.println(WPNumber);
        
        Serial1.print("Heading: ");
        Serial1.println(headingDeg);
        
        Serial1.print("offHeading: ");
        Serial1.println(offHeading); 

        Serial1.print("Right_R_PWM: ");
        Serial1.println(Right_R_PWM); 

        Serial1.print("Left_L_PWM: ");
        Serial1.println(Left_R_PWM); 

        Serial1.print("Right_L_PWM: ");
        Serial1.println(Right_L_PWM); 

        Serial1.print("Left_L_PWM: ");
        Serial1.println(Left_L_PWM); 

        Serial1.print("PID_P: ");
        Serial1.println(PID_P); 

        Serial1.print("PID_I: ");
        Serial1.println(PID_I);                 
        Serial1.println();
        
        Time = millis();
  }
}
