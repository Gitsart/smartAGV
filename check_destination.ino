void destination()
{
//  Serial.print("entered....................................... dest");
//  Serial.print(destination_station);
//  Serial.print(branch);
//  Serial.print(rev);
//  Serial.println(read_station);

  if (destination_station == 1 && branch == false && rev == false && read_station == 2)
  {
//    Serial.println("station2 ....................................detected");
    normal_operation = false;
    left_turn = true;
    rightturn = false;
    branch = true;
    rev = false;
  }
  else if (destination_station == 1 && branch == true && rev == false && read_station == 10)
  {
    normal_operation = true;
    left_turn = false;
    rightturn = false;
  }
  else if (destination_station == 1 && branch == true && rev == false && pause == false && read_station == 4)
  {
//    Serial.println("station4 ......................................detected");
    String sendThis = ""; //Declare and initialise the string we will send
    sendThis = "n6.val="; //Build the part of the string that we know
    sendThis.concat(1); //Add the variable we want to send
    writeString(sendThis);
    normal_operation = false;
    left_turn = false;
    rightturn = false;
    pause = true;
  }
  else if (destination_station == 3 && branch == true && rev == false && pause == false && read_station == 5)
  {
//    Serial.println("station5 .....................................detected");
    String sendThis = ""; //Declare and initialise the string we will send
    sendThis = "n6.val="; //Build the part of the string that we know
    sendThis.concat(1); //Add the variable we want to send
    writeString(sendThis);
    normal_operation = false;
    left_turn = false;
    rightturn = false;
    pause = true;
    fg_1 = true;
    // IF ACKNOWLEDGED IS PRESSED HERE WE NEED TO TURN U TURN //
  }
  else if ((destination_station == 1) && (branch == true) && rev == false && pause == false && read_station == 6)
  {
//    Serial.println("station5 .....................................detected");
    String sendThis = ""; //Declare and initialise the string we will send
    sendThis = "n6.val="; //Build the part of the string that we know
    sendThis.concat(1); //Add the variable we want to send
    writeString(sendThis);
    normal_operation = false;
    left_turn = false;
    rightturn = false;
    pause = true;

    // IF ACKNOWLEDGED IS PRESSED HERE WE NEED TO TURN U TURN //
  }

  else if (destination_station == 1 && branch == true && rev == true && pause == false && read_station == 4)
  {
//    Serial.println("station4 ......................................detected");
    String sendThis = ""; //Declare and initialise the string we will send
    sendThis = "n6.val="; //Build the part of the string that we know
    sendThis.concat(1); //Add the variable we want to send
    writeString(sendThis);
    normal_operation = false;
    left_turn = false;
    rightturn = false;
    pause = true;
  }
   else if (destination_station ==  1 && branch == true && rev == false && read_station == 5)
  {
    normal_operation = true;
    left_turn = false;
    rightturn = false;
  }
  
  else if (destination_station == 3 && branch == true && rev == true && pause == false && read_station == 5)
  {
//    Serial.println("station5 .....................................detected");
    String sendThis = ""; //Declare and initialise the string we will send
    sendThis = "n6.val="; //Build the part of the string that we know
    sendThis.concat(1); //Add the variable we want to send
    writeString(sendThis);
    normal_operation = false;
    left_turn = false;
    rightturn = false;
    pause = true;
    fg_1 = true;
    // IF ACKNOWLEDGED IS PRESSED HERE WE NEED TO TURN U TURN //
  }
  else if ((destination_station == 1) && (branch == true) && rev == true && pause == false && read_station == 6)
  {
//    Serial.println("station5 .....................................detected");
    String sendThis = ""; //Declare and initialise the string we will send
    sendThis = "n6.val="; //Build the part of the string that we know
    sendThis.concat(1); //Add the variable we want to send
    writeString(sendThis);
    normal_operation = false;
    left_turn = false;
    rightturn = false;
    pause = true;
    fg_1 = true;
    // IF ACKNOWLEDGED IS PRESSED HERE WE NEED TO TURN U TURN //
  }

  else if ((destination_station == 0) && (branch == true) && rev == true && pause == false && read_station == 6)
  {
    normal_operation = true;
    left_turn = false;
    rightturn = false;
    pause = false;
  }
  else if ((destination_station == 0) && (branch == true) && rev == true && pause == false && read_station == 4)
  {
    normal_operation = true;
    left_turn = false;
    rightturn = false;
    pause = false;
  }
  else if ((destination_station == 0) && (branch == true) && rev == true && pause == false && read_station == 5)
  {
    normal_operation = true;
    left_turn = false;
    rightturn = false;
    pause = false;
  }
  else if (destination_station == 0 && branch == true && rev == true && pause == false && read_station == 10 && fg_1 == true)
  {
    normal_operation = false;
    left_turn = false;
    rightturn = false;
    pause = true;
    String sendThis = ""; //Declare and initialise the string we will send
    sendThis = "n6.val="; //Build the part of the string that we know
    sendThis.concat(1); //Add the variable we want to send
    writeString(sendThis);
  }
  else if ((destination_station == 0) && (branch == true) && rev == true && pause == false && read_station == 2)
  {
    normal_operation = false;
    left_turn = false;
    rightturn = true;
    pause = false;
    branch = false;
  }
  else if (destination_station == 2 && branch == false && rev == false && read_station == 2)
  {
    normal_operation = false;
    left_turn = true;
    rightturn = false;
    branch = true;
  }
  else if (destination_station == 2 && branch == true && rev == false && read_station == 10)
  {
    normal_operation = true;
    left_turn = false;
    rightturn = false;
  }
  else if (destination_station == 2 && branch == true && rev == false && read_station == 4)
  {
    normal_operation = true;
    left_turn = false;
    rightturn = false;
  }
  else if (destination_station == 2 && branch == true && rev == false && read_station == 5)
  {
    normal_operation = true;
    left_turn = false;
    rightturn = false;
  }
  
  else if (destination_station == 2 && branch == true && rev == false && read_station == 6)
  {
    normal_operation = true;
    left_turn = false;
    rightturn = false;
    branch = true;
  }

  else if (destination_station == 2 && branch == true && rev == false && read_station == 7)
  {
    normal_operation = false;
    left_turn = false;
    rightturn = true;
    branch = false;
  }

  else if (destination_station == 2 && branch == false && rev == false && read_station == 8)
  {
    normal_operation = false;
    left_turn = false;
    rightturn = true;
    branch = true;
  }

  else if ((destination_station == 2) && (branch == true) && rev == false && pause == false && read_station == 9)
  {
//    Serial.println("station5 .....................................detected");
    String sendThis = ""; //Declare and initialise the string we will send
    sendThis = "n6.val="; //Build the part of the string that we know
    sendThis.concat(1); //Add the variable we want to send
    writeString(sendThis);
    normal_operation = false;
    left_turn = false;
    rightturn = false;
    pause = true;
    // IF ACKNOWLEDGED IS PRESSED HERE WE NEED TO TURN U TURN //
  }

  else if ((destination_station == 0) && (branch == true) && rev == true && pause == false && read_station == 8)
  {
    normal_operation = false;
    left_turn = true;
    rightturn = false;
    pause = false;
    branch = false;
  }
    else if ((destination_station == 1) && (branch == true) && rev == true && pause == false && read_station == 8)
  {
    normal_operation = false;
    left_turn = true;
    rightturn = false;
    pause = false;
    branch = false;
  }
  else if ((destination_station == 0) && (branch == false) && rev == true && pause == false && read_station == 7)
  {
    normal_operation = false;
    left_turn = true;
    rightturn = false;
    pause = false;
    branch = true;
  }
   else if ((destination_station == 1) && (branch == false) && rev == true && pause == false && read_station == 7)
  {
    normal_operation = false;
    left_turn = true;
    rightturn = false;
    pause = false;
    branch = true;
  }
  else if (destination_station == 0 && branch == true && rev == true && pause == false && read_station == 10 && fg_1 == false)
  {
    normal_operation = true;
    left_turn = false;
    rightturn = false;
  }
  rfid = false;
}
