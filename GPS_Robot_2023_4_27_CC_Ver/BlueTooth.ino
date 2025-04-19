

void recvWithStartEndMarkers() {
/*************************************
* void recvWithStartEndMarkers() 
* Function reads serial input for new bluetooth input.  If new data is received it writes it to receivedChars.
* There is a cycle timer at the bottom.  If there is no new data received for 10 scans then it resets the receive function
**************************************/   
    static boolean recvInProgress = false;
    static byte ndx = 0;
    char startMarker = '<';
    char endMarker = '>';
    char rc;
 
    while (Serial1.available() > 0 && newData == false) {
        rc = Serial1.read();
        

        if (recvInProgress == true) {                         
            if (rc != endMarker) {
                receivedChars[ndx] = rc;
                Serial.print(rc);
                ndx++;
                if (ndx >= numChars) {
                    ndx = numChars - 1;
                }
            }
            else {
                receivedChars[ndx] = '\0'; // terminate the string
                recvInProgress = false;
                ndx = 0;
                newData = true;

            }
        }

        else if (rc == startMarker) {
            recvInProgress = true;
            Serial.println("R");
        }
    }


    if (newData == true ){
        newDataTimer ++;
    }
    else if (newData == false){
        newDataTimer = 0;
    }
    if(newDataTimer >= 10){
        newData = false;
    }
    
    
}


 
