extern uint8_t portion_hour_24, portion_min;
extern char this_time[9];

void convert_time(float this_portion) {
  portion_hour_24 = (int)(this_portion * 24);
  portion_min = (int)(60 * ((this_portion * 24) - portion_hour_24));
}

void format_time(uint8_t this_hour, uint8_t this_min) {
  // create a formatted text string and store in the global this_time[9] char array
  this_time[9] = "";
  uint8_t curr_index = 2;
  bool is_am = true;
  if (this_hour == 0) {
    this_time[0] = '1';
    this_time[1] = '2';
  } else if (this_hour == 1) {
    this_time[0] = '1';
    curr_index = 1;
  } else if (this_hour == 2) {
    this_time[0] = '2';
    curr_index = 1;
  } else if (this_hour == 3) {
    this_time[0] = '3';
    curr_index = 1;
  } else if (this_hour == 4) {
    this_time[0] = '4';
    curr_index = 1;
  } else if (this_hour == 5) {
    this_time[0] = '5';
    curr_index = 1;
  } else if (this_hour == 6) {
    this_time[0] = '6';
    curr_index = 1;
  } else if (this_hour == 7) {
    this_time[0] = '7';
    curr_index = 1;
  } else if (this_hour == 8) {
    this_time[0] = '8';
    curr_index = 1;
  } else if (this_hour == 9) {
    this_time[0] = '9';
    curr_index = 1;
  } else if (this_hour == 10) {
    this_time[0] = '1';
    this_time[1] = '0';
  } else if (this_hour == 11) {
    this_time[0] = '1';
    this_time[1] = '1';
  } else if (this_hour == 12) {
    this_time[0] = '1';
    this_time[1] = '2';
    is_am = false;
  } else if (this_hour == 13) {
    this_time[0] = '1';
    curr_index = 1;
    is_am = false;
  } else if (this_hour == 14) {
    this_time[0] = '2';
    curr_index = 1;
    is_am = false;
  } else if (this_hour == 15) {
    this_time[0] = '3';
    curr_index = 1;
    is_am = false;
  } else if (this_hour == 16) {
    this_time[0] = '4';
    curr_index = 1;
    is_am = false;
  } else if (this_hour == 17) {
    this_time[0] = '5';
    curr_index = 1;
    is_am = false;
  } else if (this_hour == 18) {
    this_time[0] = '6';
    curr_index = 1;
    is_am = false;
  } else if (this_hour == 19) {
    this_time[0] = '7';
    curr_index = 1;
    is_am = false;
  } else if (this_hour == 20) {
    this_time[0] = '8';
    curr_index = 1;
    is_am = false;
  } else if (this_hour == 21) {
    this_time[0] = '9';
    curr_index = 1;
    is_am = false;
  } else if (this_hour == 22) {
    this_time[0] = '1';
    this_time[1] = '0';
    is_am = false;
  } else if (this_hour == 23) {
    this_time[0] = '1';
    this_time[1] = '1';
    is_am = false;
  }
  this_time[curr_index] = ':';
  curr_index = curr_index + 1;
  if (this_min == 0) {
    this_time[curr_index] = '0';
    this_time[curr_index + 1] = '0';
  } else if (this_min == 1) {
    this_time[curr_index] = '0';
    this_time[curr_index + 1] = '1';
  } else if (this_min == 2) {
    this_time[curr_index] = '0';
    this_time[curr_index + 1] = '2';
  } else if (this_min == 3) {
    this_time[curr_index] = '0';
    this_time[curr_index + 1] = '3';
  } else if (this_min == 4) {
    this_time[curr_index] = '0';
    this_time[curr_index + 1] = '4';
  } else if (this_min == 5) {
    this_time[curr_index] = '0';
    this_time[curr_index + 1] = '5';
  } else if (this_min == 6) {
    this_time[curr_index] = '0';
    this_time[curr_index + 1] = '6';
  } else if (this_min == 7) {
    this_time[curr_index] = '0';
    this_time[curr_index + 1] = '7';
  } else if (this_min == 8) {
    this_time[curr_index] = '0';
    this_time[curr_index + 1] = '8';
  } else if (this_min == 9) {
    this_time[curr_index] = '0';
    this_time[curr_index + 1] = '9';
  } else if (this_min == 10) {
    this_time[curr_index] = '1';
    this_time[curr_index + 1] = '0';
  } else if (this_min == 11) {
    this_time[curr_index] = '1';
    this_time[curr_index + 1] = '1';
  } else if (this_min == 12) {
    this_time[curr_index] = '1';
    this_time[curr_index + 1] = '2';
  } else if (this_min == 13) {
    this_time[curr_index] = '1';
    this_time[curr_index + 1] = '3';
  } else if (this_min == 14) {
    this_time[curr_index] = '1';
    this_time[curr_index + 1] = '4';
  } else if (this_min == 15) {
    this_time[curr_index] = '1';
    this_time[curr_index + 1] = '5';
  } else if (this_min == 16) {
    this_time[curr_index] = '1';
    this_time[curr_index + 1] = '6';
  } else if (this_min == 17) {
    this_time[curr_index] = '1';
    this_time[curr_index + 1] = '7';
  } else if (this_min == 18) {
    this_time[curr_index] = '1';
    this_time[curr_index + 1] = '8';
  } else if (this_min == 19) {
    this_time[curr_index] = '1';
    this_time[curr_index + 1] = '9';
  } else if (this_min == 20) {
    this_time[curr_index] = '2';
    this_time[curr_index + 1] = '0';
  } else if (this_min == 21) {
    this_time[curr_index] = '2';
    this_time[curr_index + 1] = '1';
  } else if (this_min == 22) {
    this_time[curr_index] = '2';
    this_time[curr_index + 1] = '2';
  } else if (this_min == 23) {
    this_time[curr_index] = '2';
    this_time[curr_index + 1] = '3';
  } else if (this_min == 24) {
    this_time[curr_index] = '2';
    this_time[curr_index + 1] = '4';
  } else if (this_min == 25) {
    this_time[curr_index] = '2';
    this_time[curr_index + 1] = '5';
  } else if (this_min == 26) {
    this_time[curr_index] = '2';
    this_time[curr_index + 1] = '6';
  } else if (this_min == 27) {
    this_time[curr_index] = '2';
    this_time[curr_index + 1] = '7';
  } else if (this_min == 28) {
    this_time[curr_index] = '2';
    this_time[curr_index + 1] = '8';
  } else if (this_min == 29) {
    this_time[curr_index] = '2';
    this_time[curr_index + 1] = '9';
  } else if (this_min == 30) {
    this_time[curr_index] = '3';
    this_time[curr_index + 1] = '0';
  } else if (this_min == 31) {
    this_time[curr_index] = '3';
    this_time[curr_index + 1] = '1';
  } else if (this_min == 32) {
    this_time[curr_index] = '3';
    this_time[curr_index + 1] = '2';
  } else if (this_min == 33) {
    this_time[curr_index] = '3';
    this_time[curr_index + 1] = '3';
  } else if (this_min == 34) {
    this_time[curr_index] = '3';
    this_time[curr_index + 1] = '4';
  } else if (this_min == 35) {
    this_time[curr_index] = '3';
    this_time[curr_index + 1] = '5';
  } else if (this_min == 36) {
    this_time[curr_index] = '3';
    this_time[curr_index + 1] = '6';
  } else if (this_min == 37) {
    this_time[curr_index] = '3';
    this_time[curr_index + 1] = '7';
  } else if (this_min == 38) {
    this_time[curr_index] = '3';
    this_time[curr_index + 1] = '8';
  } else if (this_min == 39) {
    this_time[curr_index] = '3';
    this_time[curr_index + 1] = '9';
  } else if (this_min == 40) {
    this_time[curr_index] = '4';
    this_time[curr_index + 1] = '0';
  } else if (this_min == 41) {
    this_time[curr_index] = '4';
    this_time[curr_index + 1] = '1';
  } else if (this_min == 42) {
    this_time[curr_index] = '4';
    this_time[curr_index + 1] = '2';
  } else if (this_min == 43) {
    this_time[curr_index] = '4';
    this_time[curr_index + 1] = '3';
  } else if (this_min == 44) {
    this_time[curr_index] = '4';
    this_time[curr_index + 1] = '4';
  } else if (this_min == 45) {
    this_time[curr_index] = '4';
    this_time[curr_index + 1] = '5';
  } else if (this_min == 46) {
    this_time[curr_index] = '4';
    this_time[curr_index + 1] = '6';
  } else if (this_min == 47) {
    this_time[curr_index] = '4';
    this_time[curr_index + 1] = '7';
  } else if (this_min == 48) {
    this_time[curr_index] = '4';
    this_time[curr_index + 1] = '8';
  } else if (this_min == 49) {
    this_time[curr_index] = '4';
    this_time[curr_index + 1] = '9';
  } else if (this_min == 50) {
    this_time[curr_index] = '5';
    this_time[curr_index + 1] = '0';
  } else if (this_min == 51) {
    this_time[curr_index] = '5';
    this_time[curr_index + 1] = '1';
  } else if (this_min == 52) {
    this_time[curr_index] = '5';
    this_time[curr_index + 1] = '2';
  } else if (this_min == 53) {
    this_time[curr_index] = '5';
    this_time[curr_index + 1] = '3';
  } else if (this_min == 54) {
    this_time[curr_index] = '5';
    this_time[curr_index + 1] = '4';
  } else if (this_min == 55) {
    this_time[curr_index] = '5';
    this_time[curr_index + 1] = '5';
  } else if (this_min == 56) {
    this_time[curr_index] = '5';
    this_time[curr_index + 1] = '6';
  } else if (this_min == 57) {
    this_time[curr_index] = '5';
    this_time[curr_index + 1] = '7';
  } else if (this_min == 58) {
    this_time[curr_index] = '5';
    this_time[curr_index + 1] = '8';
  } else if (this_min == 59) {
    this_time[curr_index] = '5';
    this_time[curr_index + 1] = '9';
  }
  curr_index = curr_index + 2;
  if (is_am) {
    this_time[curr_index] = 'A';
  } else {
    this_time[curr_index] = 'P';
  }
  this_time[curr_index + 1] = 'M';
  
  // clear the trailing M if the current time only has a one digit hour
  if (curr_index == 4) {
    this_time[curr_index + 2] = '\0';
  }
}