void update_station()
{
  for (w = 0; w < 8; w++)
  {

    if (read_id[w] == s_1[w])
    {
      b_11++;
      if (b_11 >= 8)
      {
        read_station  = 1;
        b_11 = 0;
//         Serial.print("read_station..................................");
//        Serial.println(read_station);
      }
    }
    else
    {
      b_11 = 0;
    }


    if (read_id[w] == s_2[w])
    {
      b_12++;
      if (b_12 >= 8)
      {
        read_station  = 2;
        b_12 = 0;
//        Serial.print("read_station..................................");
        Serial.println(read_station);
      }
    }
    else
    {
      b_12 = 0;
    }

    if (read_id[w] == s_3[w])
    {
      b_13++;
      if (b_13 >= 8)
      {
        read_station  = 3;
        b_13 = 0;
//         Serial.print("read_station..................................");
        Serial.println(read_station);
      }
    }
    else
    {
      b_13 = 0;
    }


    if (read_id[w] == s_4[w])
    {
      b_14++;
      if (b_14 >= 8)
      {
        read_station  = 4;
        b_14 = 0;
//         Serial.print("read_station..................................");
        Serial.println(read_station);
      }
    }
    else
    {
      b_14 = 0;
    }

    if (read_id[w] == s_5[w])
    {
      b_15++;
      if (b_15 >= 8)
      {
        read_station  = 5;
        b_15 = 0;
//         Serial.print("read_station..................................");
        Serial.println(read_station);
      }
    }
    else
    {
      b_15 = 0;
    }
     if (read_id[w] == s_6[w])
    {
      b_6++;
      if (b_6 >= 8)
      {
        read_station  = 6;
        b_6 = 0;
//         Serial.print("read_station..................................");
        Serial.println(read_station);
      }
    }
    else
    {
      b_6 = 0;
    }
     if (read_id[w] == s_7[w])
    {
      b_7++;
      if (b_7 >= 8)
      {
        read_station  = 7;
        b_7 = 0;
//         Serial.print("read_station..................................");
        Serial.println(read_station);
      }
    }
    else
    {
      b_7 = 0;
    }
     if (read_id[w] == s_8[w])
    {
      b_8++;
      if (b_8 >= 8)
      {
        read_station  = 8;
        b_8 = 0;
//         Serial.print("read_station..................................");
        Serial.println(read_station);
      }
    }
    else
    {
      b_8 = 0;
    }
     if (read_id[w] == s_9[w])
    {
      b_9++;
      if (b_9 >= 8)
      {
        read_station  = 9;
        b_9 = 0;
//         Serial.print("read_station..................................");
        Serial.println(read_station); 
      }
    }
    else
    {
      b_9 = 0;
    }
        if (read_id[w] == s_10[w])
    {
      b_10++;
      if (b_10 >= 8)
      {
        read_station  = 10;
        b_10 = 0;
//         Serial.print("read_station..................................");
        Serial.println(read_station); 
      }
    }
    else
    {
      b_10 = 0;
    }
  }
}
