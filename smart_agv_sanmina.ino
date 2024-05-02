//signature 1 - speed - green
//signature 2 - red - u turn
//siganture 3 - slow - yellow


#include <TimerOne.h>
#include <Arduino.h>
#include <Pixy2.h>
Pixy2 pixy;


//PID CONTROL//
float Kp = 0.08;
float Ki = 0.0002;
float Kd = 1;
float Kp_1 = 0.08;
float Ki_1 = 0.0002;
float Kd_1 = 1;
int P;
int I;
int D;
int lastError = 0;

const uint8_t maxspeeda = 60;
const uint8_t maxspeedb = 60;
const uint8_t basespeeda = 30;
const uint8_t basespeedb = 30;
const uint8_t maxspeeda_1 = 30;
const uint8_t maxspeedb_1 = 30;
const uint8_t basespeeda_1 = 10;
const uint8_t basespeedb_1 = 10;

// input output//

int Start_pb = 2;
int Emergency = 3;
int motor1_on = 4;
int motor1_dir = 5;
int motor2_on = 9;
int motor2_dir = 10;
int mot1_brake = 6;
int mot2_brake = 11;
int motor1_speed = 7;
int motor2_speed = 8;
int red = A5;
int green = A4;
int buzzer = A3;
int voltage_input = A0;
int scanner = 12;

// input output//


// variables//

byte position_ = 0;
String indata = "";
String nul = "0";
bool off_path = false;
bool battery_low = false;
bool lidar_out = false;
bool auto_start = false;
bool rfid = false;
bool branch = false;
bool rev = false;
bool emg = false;
bool left_turn = false;
bool rightturn = false;
bool rightturn_1 = false;
bool safety_off = false;
bool op_ack = false;
bool normal_operation = false;
bool pause = false;
bool process_complete = false;
bool fg_1, fg_2 = true;

int rotate_count = 0;
char station_id[] = "000000000000";
int map_1, map_2 = 0;

int high_spd = 45;
int high_spd_high = 50;
int high_spd_low = 40;

int med_spd = 30;
int med_spd_high = 35;
int med_spd_low = 20;

int slow_spd = 15;
int slow_spd_high = 20;
int slow_spd_low = 6;



int station_1[8];
int station_2[8];
int station_3[8];
int station_4[8];
int station_5[8];

int s_1[8] = {224, 4, 1, 8, 51, 29, 98, 167};
int s_2[8] = {224, 4, 1, 8, 33, 45, 213, 231}; // s-1
int s_3[8] = {224, 4, 1, 8, 33, 45, 195, 108}; //s-12
int s_4[8] = {224, 4, 1, 8, 33, 45, 221, 134}; // s-3
int s_5[8] = {224, 4, 1, 8, 33, 45, 238, 31}; //s-4
int s_6[8] = {224, 4, 1, 8, 33, 45, 193, 53}; //s-5
int s_7[8] = {224, 4, 1, 8, 51, 29, 187, 180}; //s-6
int s_8[8] = {224, 4, 1, 8, 51, 29, 61, 24}; //s-7
int s_9[8] = {224, 4, 1, 8, 33, 45, 195, 108}; //s-8
int s_10[8] = {224, 4, 1, 8, 51, 29, 199, 73}; //s-2
int s_11[8] = {224, 4, 1, 8, 51, 29, 54, 56}; //s-9
int s_12[8] = {224, 4, 1, 8, 51, 29, 121, 138}; //s-10
int s_13[8] = {224, 4, 1, 8, 51, 29, 181, 12}; //s-11
int s_14[8] = {224, 4, 1, 8, 51, 29, 180, 234}; //
int s_15[8] = {224, 4, 1, 8, 51, 29, 193, 217}; //


int rot_count_1 = 30;
int rot_count_2 = rot_count_1 + 60;
int rot_count_3 = rot_count_1 + 300;

int rfid_count = 0;
int volt = 0;
int slow_count = 0;
int move_slow = 0;
double seqValue = 0;
int a_1, a_2, a_3, a_4, a_5 = 0;
int a, b, c, d, e, f, g, h, j, k, l, m, n, o, p, r, s, t, u, v, w, z = 0;
int b_1, b_2, b_3, b_4, b_5, b_6, b_7, b_8, b_9, b_10, b_11, b_12, b_13, b_14, b_15, b_16, b_17, b_18, b_19, b_20, b_21, b_22, b_23, b_24, b_25 = 0;
int station_count = 0;
int destination_station, read_station = 0;
String inputString = "";         // a String to hold incoming data
bool stringComplete = false;  // whether the string is complete
char char_array[5];
// variables//

// camera variables//

int i = 0;
int signature = 0;
int x = 0;                      //positon x axis
int y = 0;                      //position y axis
unsigned int width_1 = 0;         //object's width
unsigned int height_1 = 0;        //object's height
int last_value[10];
int q = 0;
int cameraerror = 0;
uint16_t blocks;
// camera variables//


// rfid variables//
byte input[50];
int read_id[8];
int count = 0;

// rfid variables//




void push_button()
{
  //  Serial.println("entered pb");
  if (digitalRead(Emergency) == HIGH && digitalRead(Start_pb) == LOW && auto_start == false && a_1 > 0)
  {
    //    Serial.println("entered auto start");
    move_slow = 1;
    count = 0;      // Reset the counter to zero
    station_count = 0;
    auto_start = true;
    left_turn = false;
    rightturn = false;
    rfid = false;
    normal_operation = true;
    op_ack = false;
    tower();
    String sendThis = ""; //Declare and initialise the string we will send
    //    sendThis = "n8.val="; //Build the part of the string that we know
    //    sendThis.concat(0); //Add the variable we want to send
    //    writeString(sendThis);
    sendThis = "n1.val="; //Build the part of the string that we know
    sendThis.concat(1); //Add the variable we want to send
    writeString(sendThis);
    sendThis = "n7.val="; //Build the part of the string that we know
    sendThis.concat(0); //Add the variable we want to send
    writeString(sendThis);
    station_count++;
    //    Serial.println(a_1);
    //    Serial.print("..........................................");
    if (station_count == 1)
    {
      destination_station = a_1;
      //      Serial.println("sttttttttttttttion_1");
    }
    else if (station_count == 0)
    {
      //      Serial.println("no station");
      auto_start = false;
      destination_station = 0;
      //      digitalWrite(serial_output, HIGH);
    }

    //    Serial.print("destination");
    Serial.println("1");
    //    String sendThis = ""; //Declare and initialise the string we will send
    sendThis = "n3.val="; //Build the part of the string that we know
    sendThis.concat(volt); //Add the variable we want to send
    writeString(sendThis);
  }

  else if  ((digitalRead(Emergency) == HIGH) && (auto_start == true) && (digitalRead(Start_pb) == LOW) && (pause == true) && (lidar_out == false) && (op_ack == false) && read_station == 4)
  {
    op_ack = true;
    normal_operation = true;
    rightturn = false;
    pause = false;
    digitalWrite(motor1_on, HIGH);
    digitalWrite(motor2_on, HIGH);
    String sendThis = ""; //Declare and initialise the string we will send
    sendThis = "n6.val="; //Build the part of the string that we know
    sendThis.concat(0); //Add the variable we want to send
    writeString(sendThis);
    tower();
  }
  else if  ((digitalRead(Emergency) == HIGH) && (auto_start == true) && (digitalRead(Start_pb) == LOW) && (pause == true) && (lidar_out == false) && (op_ack == false) && read_station == 5)
  {

    op_ack = true;
    normal_operation = true;
    rightturn = false;
    pause = false;
    digitalWrite(motor1_on, HIGH);
    digitalWrite(motor2_on, HIGH);
    String sendThis = ""; //Declare and initialise the string we will send
    sendThis = "n6.val="; //Build the part of the string that we know
    sendThis.concat(0); //Add the variable we want to send
    writeString(sendThis);
    tower();
  }
  else if  ((digitalRead(Emergency) == HIGH) && (auto_start == true) && (digitalRead(Start_pb) == LOW) && (pause == true) && (lidar_out == false) && (op_ack == false) && read_station == 6)
  {
    station_count++;
    op_ack = true;
    normal_operation = true;
    rightturn = false;
    pause = false;
    digitalWrite(motor1_on, HIGH);
    digitalWrite(motor2_on, HIGH);
    String sendThis = ""; //Declare and initialise the string we will send
    sendThis = "n6.val="; //Build the part of the string that we know
    sendThis.concat(0); //Add the variable we want to send
    writeString(sendThis);
    tower();
  }
  else if  ((digitalRead(Emergency) == HIGH) && (auto_start == true) && (digitalRead(Start_pb) == LOW) && (pause == true) && (lidar_out == false) && (op_ack == false) && read_station == 9)
  {
    station_count++;
    op_ack = true;
    normal_operation = false;
    left_turn = true;
    pause = false;
    String sendThis = ""; //Declare and initialise the string we will send
    sendThis = "n6.val="; //Build the part of the string that we know
    sendThis.concat(0); //Add the variable we want to send
    writeString(sendThis);
    rev = true;
    tower();
  }

  else if  ((digitalRead(Emergency) == HIGH) && (auto_start == true) && (digitalRead(Start_pb) == LOW) && (pause == true) && (lidar_out == false) && (op_ack == false) && read_station == 10 && fg_1 == true)
  {
    op_ack = true;
    normal_operation = true;
    rightturn = false;
    pause = false;
    digitalWrite(motor1_on, HIGH);
    digitalWrite(motor2_on, HIGH);
    fg_1 = false;
    String sendThis = ""; //Declare and initialise the string we will send
    sendThis = "n6.val="; //Build the part of the string that we know
    sendThis.concat(0); //Add the variable we want to send
    writeString(sendThis);
    tower();
  }

  else if  ((digitalRead(Emergency) == HIGH) && (digitalRead(Start_pb) == LOW) && (pause == true) && (auto_start == false))
  {
    op_ack = true;
    tower();
    String sendThis = ""; //Declare and initialise the string we will send
    //    delay(300); //Probably unneccessary, but I give the screen some time to respond
    sendThis = "n7.val="; //Build the part of the string that we know
    sendThis.concat(0); //Add the variable we want to send
    writeString(sendThis);
  }

  else if  ((digitalRead(Emergency) == HIGH) && (digitalRead(Start_pb) == LOW) && (emg == true))
  {
    emg = false;
    digitalWrite(motor1_on, HIGH);
    digitalWrite(motor2_on, HIGH);
    normal_operation = true;
    String sendThis = ""; //Declare and initialise the string we will send
    //    delay(300); //Probably unneccessary, but I give the screen some time to respond
    sendThis = "n2.val="; //Build the part of the string that we know
    sendThis.concat(0); //Add the variable we want to send
    writeString(sendThis);
    tower();
  }
  else if  (((digitalRead(Emergency) == HIGH) && (digitalRead(Start_pb) == LOW)  && auto_start == true) || ((digitalRead(Emergency) == HIGH) && (digitalRead(Start_pb) == LOW) && battery_low == true))
  {
    emg = false;
    digitalWrite(motor1_on, HIGH);
    digitalWrite(motor2_on, HIGH);
    String sendThis = ""; //Declare and initialise the string we will send
    //    delay(300); //Probably unneccessary, but I give the screen some time to respond
    sendThis = "n2.val="; //Build the part of the string that we know
    sendThis.concat(0); //Add the variable we want to send
    writeString(sendThis);
    tower();
    Serial.println("21");
  }

  else if (digitalRead(Emergency) == LOW)
  {
    emg = true;
    normal_operation = false;
    left_turn = false;
    rightturn = false;
    digitalWrite(motor1_on, LOW);
    digitalWrite(motor2_on, LOW);
    String sendThis = ""; //Declare and initialise the string we will send
    delay(300); //Probably unneccessary, but I give the screen some time to respond
    sendThis = "n2.val="; //Build the part of the string that we know
    sendThis.concat(1); //Add the variable we want to send
    writeString(sendThis);
    tower();
    Serial.println("20");
  }

}


void writeString(String stringData)
{ // Used to serially push out a String with Serial.write()

  for (int i = 0; i < stringData.length(); i++)
  {
    Serial3.write(stringData[i]);   // Push each char 1 by 1 on each loop pass
  }

  Serial3.write(0xff); //We need to write the 3 ending bits to the Nextion as well
  Serial3.write(0xff); //it will tell the Nextion that this is the end of what we want to send.
  Serial3.write(0xff);
}



void left_u_turn()
{
  if (rotate_count <= 10)
  {
    digitalWrite(motor1_on, LOW);
    digitalWrite(motor2_on, LOW);
    rotate_count ++;
  }
  else if (((10 < rotate_count && rotate_count <= rot_count_1) && signature == 1) || ((10 < rotate_count && rotate_count <= rot_count_1) && signature == 3))
  {
    if (157 < x && x < 314)
    {
      map_2 = map(x, 157, 314, (slow_spd), slow_spd_low);
      map_1 = map(x, 157, 314, (slow_spd), slow_spd_high);
      analogWrite(motor1_speed, map_1);
      analogWrite(motor2_speed, map_2);
      digitalWrite(motor1_on, HIGH);
      digitalWrite(motor2_on, HIGH);
      digitalWrite(mot1_brake, HIGH);
      digitalWrite(mot2_brake, HIGH);
      digitalWrite(motor1_dir, HIGH);
      digitalWrite(motor2_dir, LOW);
    }

    else if ( 0 <= x && x <= 157)
    {
      map_2 = map(x, 157, 0, (slow_spd), slow_spd_high);
      map_1 = map(x, 157, 0, (slow_spd), slow_spd_low);;
      analogWrite(motor1_speed, map_1);
      analogWrite(motor2_speed, map_2);
      digitalWrite(motor1_on, HIGH);
      digitalWrite(motor2_on, HIGH);
      digitalWrite(mot1_brake, HIGH);
      digitalWrite(mot2_brake, HIGH);
      digitalWrite(motor1_dir, HIGH);
      digitalWrite(motor2_dir, LOW);
    }
    rotate_count ++;
  }

  else if (((rot_count_1 < rotate_count && rotate_count <= rot_count_2) && signature == 1) || ((rot_count_1 < rotate_count && rotate_count <= rot_count_2) && signature == 3))
  {
    digitalWrite(motor1_on, LOW);
    digitalWrite(motor2_on, LOW);
    rotate_count ++;
  }

  else if ((rotate_count > rot_count_2 ))
  {
    analogWrite(motor2_speed, 3);
    analogWrite(motor1_speed, 3);
    digitalWrite(motor1_on, HIGH);
    digitalWrite(motor2_on, HIGH);
    digitalWrite(mot1_brake, HIGH);
    digitalWrite(mot2_brake, HIGH);
    digitalWrite(motor1_dir, LOW);
    digitalWrite(motor2_dir, LOW);
    rotate_count ++;

    if (((signature == 1) && (x > 50) && (auto_start == true)  && (left_turn == true) && (rotate_count >= rot_count_3)) || ((signature == 3) && (x > 50) && (auto_start == true)  && (left_turn == true) && (rotate_count >= rot_count_3)))
    {
      left_turn = false;
      rightturn = false;
      rotate_count = 0;
      pause = false;
      op_ack = false;
      move_slow = 0;
      digitalWrite(motor1_on, LOW);
      digitalWrite(motor2_on, LOW);
      delay(1000);
      normal_operation = true;
      digitalWrite(motor1_on, HIGH);
      digitalWrite(motor2_on, HIGH);
    }

    else if (((signature == 1) && (width_1 > 50) && (auto_start == false) && (left_turn == true) && (rotate_count >= rot_count_3)) || ((signature == 3) && (width_1 > 50) && (auto_start == false)  && (left_turn == true) && (rotate_count >= rot_count_3)))
    {
      left_turn = false;
      rightturn = false;
      rotate_count = 0;
      pause = false;
      op_ack = false;
      move_slow = 0;
      digitalWrite(motor1_on, LOW);
      digitalWrite(motor2_on, LOW);
      delay(1000);
      normal_operation = true;
      digitalWrite(motor1_on, HIGH);
      digitalWrite(motor2_on, HIGH);
    }

  }
}
void right()
{
  if (rotate_count <= 10)
  {
    digitalWrite(motor1_on, LOW);
    digitalWrite(motor2_on, LOW);
    rotate_count ++;
  }

  else if (((10 < rotate_count && rotate_count <= rot_count_1) && signature == 1 && read_station != 6) || ((10 < rotate_count && rotate_count <= rot_count_1) && signature == 3 && read_station != 6))
  {
    if (157 < x && x < 314)
    {
      map_2 = map(x, 157, 314, (slow_spd), slow_spd_low);
      map_1 = map(x, 157, 314, (slow_spd), slow_spd_high);
      analogWrite(motor1_speed, map_1);
      analogWrite(motor2_speed, map_2);
      digitalWrite(motor1_on, HIGH);
      digitalWrite(motor2_on, HIGH);
      digitalWrite(mot1_brake, HIGH);
      digitalWrite(mot2_brake, HIGH);
      digitalWrite(motor1_dir, HIGH);
      digitalWrite(motor2_dir, LOW);
    }
    else if (( 0 <= x && x <= 157))
    {
      map_2 = map(x, 157, 0, (slow_spd), slow_spd_high);
      map_1 = map(x, 157, 0, (slow_spd), slow_spd_low);
      analogWrite(motor1_speed, map_1);
      analogWrite(motor2_speed, map_2);
      digitalWrite(motor1_on, HIGH);
      digitalWrite(motor2_on, HIGH);
      digitalWrite(mot1_brake, HIGH);
      digitalWrite(mot2_brake, HIGH);
      digitalWrite(motor1_dir, HIGH);
      digitalWrite(motor2_dir, LOW);
    }

    rotate_count ++;
  }


  else if (((rot_count_1 < rotate_count && rotate_count <= rot_count_2) && signature == 1 && read_station != 6) || ((rot_count_1 < rotate_count && rotate_count <= rot_count_2) && signature == 3 && read_station != 6))
  {
    digitalWrite(motor1_on, LOW);
    digitalWrite(motor2_on, LOW);
    rotate_count ++;
  }
  else if ((rotate_count > rot_count_2 && read_station != 6))
  {
    analogWrite(motor2_speed, 3);
    analogWrite(motor1_speed, 3);
    digitalWrite(motor1_on, HIGH);
    digitalWrite(motor2_on, HIGH);
    digitalWrite(mot1_brake, HIGH);
    digitalWrite(mot2_brake, HIGH);
    digitalWrite(motor1_dir, HIGH);
    digitalWrite(motor2_dir, HIGH);
    rotate_count ++;

    if (((signature == 1) && (x > 50) && (auto_start == true)  && (rightturn == true) && (rotate_count >= rot_count_3)) || ((signature == 3) && (x > 50) && (auto_start == true)  && (rightturn == true) && (rotate_count >= rot_count_3)))
    {
      left_turn = false;
      rightturn = false;
      rotate_count = 0;
      pause = false;
      op_ack = false;
      move_slow = 0;
      digitalWrite(motor1_on, LOW);
      digitalWrite(motor2_on, LOW);
      delay(1000);
      normal_operation = true;
      digitalWrite(motor1_on, HIGH);
      digitalWrite(motor2_on, HIGH);
    }

    else if (((signature == 1) && (x > 50) && (auto_start == false)  && (rightturn == true) && (rotate_count >= rot_count_3)) || ((signature == 3) && (x > 50) && (auto_start == false)  && (rightturn == true) && (rotate_count >= rot_count_3)))
    {
      left_turn = false;
      rightturn = false;
      rotate_count = 0;
      pause = false;
      op_ack = false;
      move_slow = 0;
      digitalWrite(motor1_on, LOW);
      digitalWrite(motor2_on, LOW);
      delay(1000);
      normal_operation = true;
      digitalWrite(motor1_on, HIGH);
      digitalWrite(motor2_on, HIGH);
    }
  }



  else if (((10 < rotate_count && rotate_count <= 1000) && signature == 1 && read_station == 6) || ((10 < rotate_count && rotate_count <= 1000) && signature == 3 && read_station == 6))
  {
    if (157 < x && x < 314)
    {
      map_2 = map(x, 157, 314, (slow_spd), slow_spd_low);
      map_1 = map(x, 157, 314, (slow_spd), slow_spd_high);
      analogWrite(motor1_speed, map_1);
      analogWrite(motor2_speed, map_2);
      digitalWrite(motor1_on, HIGH);
      digitalWrite(motor2_on, HIGH);
      digitalWrite(mot1_brake, HIGH);
      digitalWrite(mot2_brake, HIGH);
      digitalWrite(motor1_dir, HIGH);
      digitalWrite(motor2_dir, LOW);
    }
    else if ((signature == 1) && ( 0 <= x && x <= 157))
    {
      map_2 = map(x, 157, 0, (slow_spd), slow_spd_high);
      map_1 = map(x, 157, 0, (slow_spd), slow_spd_low);
      analogWrite(motor1_speed, map_1);
      analogWrite(motor2_speed, map_2);
      digitalWrite(motor1_on, HIGH);
      digitalWrite(motor2_on, HIGH);
      digitalWrite(mot1_brake, HIGH);
      digitalWrite(mot2_brake, HIGH);
      digitalWrite(motor1_dir, HIGH);
      digitalWrite(motor2_dir, LOW);
    }

    rotate_count ++;
  }


  else if (((1000 < rotate_count && rotate_count <= 1050) && signature == 1 && read_station == 6) || ((1000 < rotate_count && rotate_count <= 1050) && signature == 3 && read_station == 6))
  {
    digitalWrite(motor1_on, LOW);
    digitalWrite(motor2_on, LOW);
    rotate_count ++;
  }
  else if ((rotate_count > 1050 && read_station == 6))
  {
    analogWrite(motor2_speed, 3);
    analogWrite(motor1_speed, 3);
    digitalWrite(motor1_on, HIGH);
    digitalWrite(motor2_on, HIGH);
    digitalWrite(mot1_brake, HIGH);
    digitalWrite(mot2_brake, HIGH);
    digitalWrite(motor1_dir, HIGH);
    digitalWrite(motor2_dir, HIGH);
    rotate_count ++;

    if (((signature == 1) && (x > 150) && (auto_start == true)  && (rightturn == true) && (rotate_count >= 1180)) || ((signature == 3) && (x > 150) && (auto_start == true)  && (rightturn == true) && (rotate_count >= 1180)))
    {
      left_turn = false;
      rightturn = false;
      rotate_count = 0;
      pause = false;
      op_ack = false;
      move_slow = 0;
      digitalWrite(motor1_on, LOW);
      digitalWrite(motor2_on, LOW);
      delay(1000);
      normal_operation = true;
      digitalWrite(motor1_on, HIGH);
      digitalWrite(motor2_on, HIGH);
    }

    else if (((signature == 1) && (x > 150) && (auto_start == false)  && (rightturn == true) && (rotate_count >= 1180)) || ((signature == 3) && (x > 150) && (auto_start == false)  && (rightturn == true) && (rotate_count >= 1180)))
    {
      left_turn = false;
      rightturn = false;
      rotate_count = 0;
      pause = false;
      op_ack = false;
      move_slow = 0;
      digitalWrite(motor1_on, LOW);
      digitalWrite(motor2_on, LOW);
      delay(1000);
      normal_operation = true;
      digitalWrite(motor1_on, HIGH);
      digitalWrite(motor2_on, HIGH);
    }
  }
}



void straight_motion()
{
  if (signature == 1 && move_slow == 0)
  {
    int error = 157 - x;
    P = error;
    I = I + error;
    D = error - lastError;
    lastError = error;
    int motorspeed = P * Kp + I * Ki + D * Kd;

    int motorspeeda = basespeeda + motorspeed;
    int motorspeedb = basespeedb - motorspeed;
    //  Serial.println("motorspeed: " + String(motorspeed) + " error" + String(error));
    //  Serial.println("camera x: " + String(x));
    //  Serial.println("mot speed a"+ String(motorspeeda)+ " mot speed b"+String(motorspeedb));
    cameraerror = 0;
    rotate_count = 0;
    op_ack = false;
    pause = false;
    digitalWrite(motor1_on, HIGH);
    digitalWrite(motor2_on, HIGH);
    digitalWrite(mot1_brake, HIGH);
    digitalWrite(mot2_brake, HIGH);
    digitalWrite(motor1_dir, HIGH);
    digitalWrite(motor2_dir, LOW);
    analogWrite(motor1_speed, motorspeedb);
    analogWrite(motor2_speed, motorspeeda);
  }

  else if (signature == 1  && move_slow == 1)
  {
    if (count <= 300)
    {
      if (0 <= x && x <= 157)
      {
        cameraerror = 0;
        rotate_count = 0;
        op_ack = false;
        pause = false;
        move_slow = 1;
        map_2 = map(x, 157, 37, (slow_spd), slow_spd_high);
        map_1 = map(x, 157, 37, (slow_spd), slow_spd_low);
        analogWrite(motor1_speed, map_1);
        analogWrite(motor2_speed, map_2);
        digitalWrite(motor1_on, HIGH);
        digitalWrite(motor2_on, HIGH);
        digitalWrite(mot1_brake, HIGH);
        digitalWrite(mot2_brake, HIGH);
        digitalWrite(motor1_dir, HIGH);
        digitalWrite(motor2_dir, LOW);
        count++;
      }
      else if (( 157 < x && x <= 314))
      {
        cameraerror = 0;
        rotate_count = 0;
        op_ack = false;
        pause = false;
        move_slow = 1;
        map_2 = map(x, 157, 277, (slow_spd), slow_spd_low);
        map_1 = map(x, 157, 277, (slow_spd), slow_spd_high);
        analogWrite(motor1_speed, map_1);
        analogWrite(motor2_speed, map_2);
        digitalWrite(motor1_on, HIGH);
        digitalWrite(motor2_on, HIGH);
        digitalWrite(mot1_brake, HIGH);
        digitalWrite(mot2_brake, HIGH);
        digitalWrite(motor1_dir, HIGH);
        digitalWrite(motor2_dir, LOW);
        count++;
      }
    }
    else if ( 300 < count && count <= 600)
    {
      if (0 <= x && x <= 157)
      {
        cameraerror = 0;
        rotate_count = 0;
        op_ack = false;
        pause = false;
        move_slow = 1;
        map_2 = map(x, 157, 37, (med_spd), med_spd_high);
        map_1 = map(x, 157, 37, (med_spd), med_spd_low);
        analogWrite(motor1_speed, map_1);
        analogWrite(motor2_speed, map_2);
        digitalWrite(motor1_on, HIGH);
        digitalWrite(motor2_on, HIGH);
        digitalWrite(mot1_brake, HIGH);
        digitalWrite(mot2_brake, HIGH);
        digitalWrite(motor1_dir, HIGH);
        digitalWrite(motor2_dir, LOW);
        count++;
      }
      else if (( 157 < x && x <= 314))
      {
        cameraerror = 0;
        rotate_count = 0;
        op_ack = false;
        pause = false;
        move_slow = 1;
        map_2 = map(x, 157, 277, (med_spd), med_spd_low);
        map_1 = map(x, 157, 277, (med_spd), med_spd_high);
        analogWrite(motor1_speed, map_1);
        analogWrite(motor2_speed, map_2);
        digitalWrite(motor1_on, HIGH);
        digitalWrite(motor2_on, HIGH);
        digitalWrite(mot1_brake, HIGH);
        digitalWrite(mot2_brake, HIGH);
        digitalWrite(motor1_dir, HIGH);
        digitalWrite(motor2_dir, LOW);
        count++;
      }
    }
    else  if (600 < count && count <= 1000)
    {
      if (0 <= x && x <= 157)
      {
        cameraerror = 0;
        rotate_count = 0;
        op_ack = false;
        pause = false;
        move_slow = 1;
        map_2 = map(x, 157, 37, (high_spd), high_spd_high);
        map_1 = map(x, 157, 37, (high_spd), high_spd_low);
        analogWrite(motor1_speed, map_1);
        analogWrite(motor2_speed, map_2);
        digitalWrite(motor1_on, HIGH);
        digitalWrite(motor2_on, HIGH);
        digitalWrite(mot1_brake, HIGH);
        digitalWrite(mot2_brake, HIGH);
        digitalWrite(motor1_dir, HIGH);
        digitalWrite(motor2_dir, LOW);
        count++;
      }
      else if (( 157 < x && x <= 314))
      {
        cameraerror = 0;
        rotate_count = 0;
        op_ack = false;
        pause = false;
        move_slow = 1;
        map_2 = map(x, 157, 277, (high_spd), high_spd_low);
        map_1 = map(x, 157, 277, (high_spd), high_spd_high);
        analogWrite(motor1_speed, map_1);
        analogWrite(motor2_speed, map_2);
        digitalWrite(motor1_on, HIGH);
        digitalWrite(motor2_on, HIGH);
        digitalWrite(mot1_brake, HIGH);
        digitalWrite(mot2_brake, HIGH);
        digitalWrite(motor1_dir, HIGH);
        digitalWrite(motor2_dir, LOW);
        count++;
      }
    }

    if (count >= 1000)
    {
      move_slow = 0;
      count = 0;
    }

  }

  else if ((signature == 3) && (157 < x && x < 314))
  {

    cameraerror = 0;
    rotate_count = 0;
    op_ack = false;
    pause = false;
    move_slow = 1;
    map_2 = map(x, 157, 277, (slow_spd), slow_spd_low);
    map_1 = map(x, 157, 277, (slow_spd), slow_spd_high);
    analogWrite(motor1_speed, map_1);
    analogWrite(motor2_speed, map_2);
    digitalWrite(motor1_on, HIGH);
    digitalWrite(motor2_on, HIGH);
    digitalWrite(mot1_brake, HIGH);
    digitalWrite(mot2_brake, HIGH);
    digitalWrite(motor1_dir, HIGH);
    digitalWrite(motor2_dir, LOW);
  }

  else if ((signature == 3) && ( 0 <= x && x <= 157))
  {

    cameraerror = 0;
    rotate_count = 0;
    op_ack = false;
    pause = false;
    move_slow = 1;
    map_2 = map(x, 157, 37, (slow_spd), slow_spd_high);
    map_1 = map(x, 157, 37, (slow_spd), slow_spd_low);
    analogWrite(motor1_speed, map_1);
    analogWrite(motor2_speed, map_2);
    digitalWrite(motor1_on, HIGH);
    digitalWrite(motor2_on, HIGH);
    digitalWrite(mot1_brake, HIGH);
    digitalWrite(mot2_brake, HIGH);
    digitalWrite(motor1_dir, HIGH);
    digitalWrite(motor2_dir, LOW);
  }


  //  if (rfid_count > 0)
  //  {
  //    rfid_count++;
  //    if (rfid_count > 50)
  //    {
  //      while (Serial2.available())
  //      {
  //        int rlen = Serial2.readBytes(input, 8);  // read the incoming bytes
  //        for (int i = 0; i < rlen; i++)
  //        {
  //          read_id[i] = int(input[i]); // convert bytre to integer
  //          Serial.println(read_id[i]);
  //        }
  //      }
  //      for (int i = 0; i < 8; i++)
  //      {
  //        read_id[i] = 0;
  //        input[i] = "0";
  //      }
  //      rfid_count = 0;
  //    }
  //  }

}

void right_1()
{
  if (rotate_count <= 10)
  {
    digitalWrite(motor1_on, LOW);
    digitalWrite(motor2_on, LOW);
    rotate_count ++;
  }

  else if ((rotate_count > 10 ))
  {
    analogWrite(motor2_speed, 6);
    analogWrite(motor1_speed, 6);
    digitalWrite(motor1_on, HIGH);
    digitalWrite(motor2_on, HIGH);
    digitalWrite(mot1_brake, HIGH);
    digitalWrite(mot2_brake, HIGH);
    digitalWrite(motor1_dir, HIGH);
    digitalWrite(motor2_dir, HIGH);
    rotate_count ++;
    if ((signature == 1) && (x > 50) && (auto_start == false)  && (rightturn_1 == true) && (rotate_count >= 760))
    {
      rightturn_1 = false;
      rotate_count = 0;
      digitalWrite(motor1_on, LOW);
      digitalWrite(motor2_on, LOW);
    }
    else if ((signature == 3) && (x > 50) && (auto_start == false)  && (rightturn_1 == true) && (rotate_count >= 760))
    {
      rightturn_1 = false;
      rotate_count = 0;
      digitalWrite(motor1_on, LOW);
      digitalWrite(motor2_on, LOW);
    }
  }
}


void setup()
{
  //  Serial.begin(115200);
  pixy.init();
  Serial.begin(115200);// wifi
  Serial3.begin(9600);// DISPLAY
  Serial2.begin(115200);// RFID
  Timer1.initialize(30000);
  Timer1.attachInterrupt(camera);
  pinMode(motor1_on, OUTPUT);
  pinMode(motor2_on, OUTPUT);
  pinMode(motor1_dir, OUTPUT);
  pinMode(motor2_dir, OUTPUT);
  pinMode(motor1_speed, OUTPUT);
  pinMode(motor2_speed, OUTPUT);
  pinMode(red, OUTPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(green, OUTPUT);
  pinMode(Start_pb, INPUT_PULLUP);
  pinMode(Emergency, INPUT_PULLUP);
  pinMode(voltage_input, INPUT);
  pinMode(scanner, INPUT);
  digitalWrite(red, LOW);
  digitalWrite(green, LOW);
  digitalWrite(buzzer, LOW);
  pinMode(mot1_brake, OUTPUT);
  pinMode(mot2_brake, OUTPUT);
  digitalWrite(mot1_brake, HIGH);
  digitalWrite(mot2_brake, HIGH);
  volt = analogRead(voltage_input);
  delay(5000);
  volt = analogRead(voltage_input);
  String sendThis = ""; //Declare and initialise the string we will send
  sendThis = "n3.val="; //Build the part of the string that we know
  sendThis.concat(volt); //Add the variable we want to send
  writeString(sendThis);
}

void loop()
{
Serial.println(rotate_count);


    Serial.print(auto_start); Serial.print(rfid); Serial.print(normal_operation); Serial.print(rightturn); Serial.print(left_turn);  Serial.print(branch); Serial.print(rev); Serial.print(pause); Serial.print(digitalRead(Emergency)); Serial.print(digitalRead(Start_pb));
    Serial.print(station_count); Serial.print(destination_station); Serial.println(a_1);
  volt = analogRead(voltage_input);

  //  Serial.println(rotate_count);
  //  Serial.println(volt);
//    Serial.println(digitalRead(scanner));
  push_button();
  motion();
  tower(); 
  if ((volt < 430) && (auto_start == false) && ( battery_low == false) && signature == 1 && normal_operation == false && rightturn == false && op_ack == false)
  {
    battery_low = true;
    normal_operation = true;
    String sendThis = ""; //Declare and initialise the string we will send
    sendThis = "n3.val="; //Build the part of the string that we know
    sendThis.concat(volt); //Add the variable we want to send
    writeString(sendThis);
  }

  if (digitalRead(scanner) == true && auto_start == true)
  {
    lidar_out = false;
    String sendThis = ""; //Declare and initialise the string we will send
    sendThis = "n4.val=";
    sendThis.concat(0); //Add the variable we want to send
    writeString(sendThis);
  }
  else if (digitalRead(scanner) == false && auto_start == true)
  {
    lidar_out = true;
    digitalWrite(motor1_on, LOW);
    digitalWrite(motor2_on, LOW);
    String sendThis = ""; //Declare and initialise the string we will send
    sendThis = "n4.val=";
    sendThis.concat(1); //Add the variable we want to send
    writeString(sendThis);
    delay(1000);
    move_slow = 1;
  }
  if (Serial2.available() )  // CHECK FOR AVAILABILITY OF SERIAL DATA
  {
    // Reset the counter to zero
    int rlen = Serial2.readBytes(input, 8);  // read the incoming bytes
    for (int i = 0; i < rlen; i++)
    {
      read_id[i] = int(input[i]); // convert bytre to integer
      //      Serial.println(read_id[i]);
    }

    rfid = true;
    //    Serial.println("rfid.................................................................");
    update_station();
  }

  if (Serial3.available() && auto_start == false)
  {
    //    Serial.println("a_1:");
    //    Serial.print(a_1);
    reset_loop();
    indata = Serial3.readStringUntil('#');
    if (indata.indexOf("start") > -1)
    {
      position_ = indata.indexOf("start");
      seqValue = indata.substring(0, position_).toInt();
      if (position_ > 0)
      {
        if ((position_ - 1) >= 0) {
          a_1 = seqValue / pow(10, (position_ - 1));
        } else {
          a_1 = 0;
        }
        if ((position_ - 2) >= 0) {
          a_2 = (seqValue - (a_1 * pow(10, (position_ - 1)))) / pow(10, (position_ - 2));
        } else {
          a_2 = 0;
        }
        if ((position_ - 3) >= 0) {
          a_3 = (seqValue - ((a_1 * pow(10, (position_ - 1))) + (a_2 * pow(10, (position_ - 2))))) / pow(10, (position_ - 3));
        } else {
          a_3 = 0;
        }
        if ((position_ - 4) >= 0) {
          a_4 = (seqValue - ((a_1 * pow(10, (position_ - 1))) + (a_2 * pow(10, (position_ - 2))) + (a_3 * pow(10, (position_ - 3))))) / pow(10, (position_ - 4));
        } else {
          a_4 = 0;
        }
        if ((position_ - 5) >= 0) {
          a_5 = (seqValue - ((a_1 * pow(10, (position_ - 1))) + (a_2 * pow(10, (position_ - 2))) + (a_3 * pow(10, (position_ - 3))) + (a_4 * pow(10, (position_ - 4))))) / pow(10, (position_ - 5));
        } else {
          a_5 = 0;
        }
      }
      //      Serial.println("loop after a_1:");
      //      Serial.print(a_1);
    }
  }

  if ((signature != 1) && (signature != 2) && (signature != 3) && (left_turn == false) && (rightturn == false) && (rightturn_1 == false) && (op_ack == false))
  {
    digitalWrite(motor1_on, LOW);
    digitalWrite(motor2_on, LOW);
    //    String sendThis = ""; //Declare and initialise the string we will send
    //    sendThis = "n8.val="; //Build the part of the string that we know
    //    sendThis.concat(1); //Add the variable we want to send
    //    writeString(sendThis);
    //    off_path = true;
  }
  else if (cameraerror == true && (left_turn == false) && (rightturn == false) && (rightturn_1 == false) && (op_ack == false) )
  {
    digitalWrite(motor1_on, LOW);
    digitalWrite(motor2_on, LOW);
    //    String sendThis = ""; //Declare and initialise the string we will send
    //    sendThis = "n8.val="; //Build the part of the string that we know
    //    sendThis.concat(1); //Add the variable we want to send
    //    writeString(sendThis);
    //    off_path = true;
  }
  else if (cameraerror == false && pause == false && auto_start == true && normal_operation == true && lidar_out == false)
  {
    digitalWrite(motor1_on, HIGH);
    digitalWrite(motor2_on, HIGH);
  }
}
