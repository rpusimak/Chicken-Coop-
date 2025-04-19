
void GPSHeading(){
/*************************************
* void GPSHeading()
*************************************/

  double targetLat; 
  double targetLong; 
  
  switch (WPNumber) {
    case 1:                                
    targetLat = 44.67374292264353;
    targetLong = -88.14361151815835;
    break;


    case 2:                 
    targetLat = 44.67391444242195;
    targetLong = -88.1431520001651;
    break;

    case 3:                 
    targetLat = 44.674285978974694;
    targetLong = -88.14330627134717;
    break;

    case 4:                 
    targetLat = 44.67417487519212;
    targetLong = -88.14353560022984;
    break;

    case 5:                 
    targetLat = 44.673918508720654;
    targetLong = -88.14405984577104;
    break;

  }  
  
  while (Serial2.available() > 0)
  {
    if (gps.encode(Serial2.read()))
    {
      if (gps.location.isUpdated())
      {
          MetersToWP =
          TinyGPSPlus::distanceBetween(
            gpsLatFunction(gps.location.lat()),
            gpsLngFunction(gps.location.lng()),
            targetLat,
            targetLong);
            
        courseToWP =
          TinyGPSPlus::courseTo(
            gpsLatFunction(gps.location.lat()),
            gpsLngFunction(gps.location.lng()),
            targetLat,
            targetLong);         
        }          
      }
    }
}

float gpsLatFunction(float x){
  gpsLatArray[gpsLatIndex] = x;
  gpsLatIndex ++;
  if (gpsLatIndex == (arraySize)){gpsLatIndex = 0;}
  
    float s = 0;
    for (int i=0; i< arraySize; i++)
    {
        s += gpsLatArray[i];
    }
    averageLat = s/arraySize; 

   return averageLat;
}

float gpsLngFunction(float x){  
  gpsLngArray[gpsLngIndex] = x;
  gpsLngIndex ++;
  if (gpsLngIndex == (arraySize)){gpsLngIndex = 0;}
  
    float s = 0;
    for (int i=0; i< arraySize; i++)
    {
        s += gpsLngArray[i];
    }
    averageLng = s/arraySize; 
  
  return averageLng;
}
