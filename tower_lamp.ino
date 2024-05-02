void tower()
{
  if (((auto_start == true) && ((emg == true) || (lidar_out == true))) || ((auto_start == true) && ((signature != 1) && (signature != 2) && (signature != 3) && (left_turn == 0) && (rightturn == 0) && (op_ack == false))))
  {
    digitalWrite(red, HIGH);
    digitalWrite(green, LOW);
    digitalWrite(buzzer, HIGH);

  }
  else if (((auto_start == false) && (battery_low == true) && ((emg == true) || (lidar_out == true))) || ((auto_start == false) && (battery_low == true) && ((signature != 1) && (signature != 2) && (signature != 3) && (left_turn == 0) && (rightturn == 0) && (op_ack == false))))
  {
    digitalWrite(red, HIGH);
    digitalWrite(green, LOW);
    digitalWrite(buzzer, HIGH);
  }
  else if ((auto_start == true) && (emg == false) && (lidar_out == false) && (pause == false) && ((signature == 1) || (signature == 2) || (signature == 3)))
  {
    digitalWrite(red, LOW);
    digitalWrite(buzzer, LOW);
    digitalWrite(green, HIGH);
  }
  else if ((auto_start == true) && (signature == 2) && (pause == true))
  {
    digitalWrite(red, LOW );
    digitalWrite(green, HIGH);
    digitalWrite(buzzer, HIGH);

  }

  else if ((auto_start == false) && (signature == 1) && (battery_low == false) && (pause == false))
  {
    digitalWrite(red, LOW);
    digitalWrite(buzzer, LOW);
    digitalWrite(green, LOW);
    read_station = 0;
  }
  else if ((auto_start == false) && (signature == 3) && (battery_low == false) && (pause == false))
  {
    digitalWrite(red, LOW);
    digitalWrite(buzzer, LOW);
    digitalWrite(green, LOW);
    read_station = 0;
  }
}
