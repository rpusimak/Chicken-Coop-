void setRunConditions(){

    if(strcmp(receivedChars, atm) == 0){
      strcpy(mode, atm);
      newData = false;
    }
    else if(strcmp(receivedChars, man) == 0){
      strcpy(mode,man);
      newData = false;
    }
    else{}
    


   
}
