
float compassHeading()  {
/**********************************
* float headingFunction()  
* Function returns the heading in degrees from the compass.
* Set declination angle on your location and fix heading
* You can find your declination on: http://magnetic-declination.com/
* (+) Positive or (-) for negative
* Formula: (deg + (min / 60.0)) / (180 / M_PI);
***********************************/   
    Vector norm = compass.readNormalize();          // Read a vector from the compass 
    float heading = atan2(norm.YAxis, norm.XAxis);  // Calculate heading
          heading = heading-1.57;                    // Compass is direction of travel.
    float declinationAngle = (-4.0 + (-7.0 / 60.0)) / (180 / M_PI);
    heading += declinationAngle;
    
    if (heading < 0)
    {                               // Correct for heading < 0deg
      heading += 2 * PI;
    }
  
    if (heading > 2 * PI)
    {                          // Correct for heading > 360deg
      heading -= 2 * PI;
    }
  
    headingDeg = heading * 180/M_PI;      // Convert to degrees   
    
}
