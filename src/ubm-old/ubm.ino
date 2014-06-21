 /*
  * TODO
  *
  * - EEPROM:
  *   + curve (cd, ni, pb, li)
  *   + nominal voltage
  *   + selectionable divider
  * - auto mode
  * - algorithm
  * - menu
  * - al inicio monitorizar 1/100
  * - correction factor adc / mux
  */
  

#define RANGE_UPPER_LIMIT 0.85
#define RANGE_LOWER_LIMIT 0.15

//user param
#define BATT_TYPE BATT_PB
#define BATT_CELLS 12
#define LPF_SIZE 32    //min 4 max 240

void loop() {
  Check();
  //PrintMenu();
  //DebugMenu();
//  do {
//    BattMeasure();
//    delay(100);
//  } while(1);
}

void Check() {
  byte C_yLoop = 0;
  
  for (C_yLoop = 0; C_yLoop < 11; C_yLoop++) {
    bDisplay[C_yLoop] = true;
  }
  delay(500);
  for (C_yLoop = 0; C_yLoop < 11; C_yLoop++) {
    bDisplay[C_yLoop] = false;
  }
}

void BattMeasure() {
  byte BM_yLoop = 0;
  const float fCurve[6][11] = {
    {1.2, 1.2, 1.2, 1.2, 1.2, 1.2, 1.2, 1.2, 1.2, 1.2, 1.2}, //nicd
    {1.2, 1.2, 1.2, 1.2, 1.2, 1.2, 1.2, 1.2, 1.2, 1.2, 1.2}, //nimh
    {1.75, 1.89, 1.93, 1.96, 1.98, 2.01, 2.03, 2.05, 2.07, 2.08, 2.12}, //pb
    {3.6, 3.6, 3.6, 3.6, 3.6, 3.6, 3.6, 3.6, 3.6, 3.6, 3.6}, //liion
    {3.7, 3.7, 3.7, 3.7, 3.7, 3.7, 3.7, 3.7, 3.7, 3.7, 3.7}, //lipo
    {3.6, 3.6, 3.6, 3.6, 3.6, 3.6, 3.6, 3.6, 3.6, 3.6, 3.6} //life
  };
  float BM_fCellVoltage = 0;
  
  BM_fCellVoltage = fmap(AnalogLPF(analogRead(A6)), 0.0, 1023.0, 0.0, 40.0) / BATT_CELLS;
  if (BM_fCellVoltage > fCurve[BATT_TYPE][10]) {
    bDisplay[9] = true;
    bDspAni[9] = true;
    for (BM_yLoop = 0; BM_yLoop < 9; BM_yLoop++) {
      bDisplay[BM_yLoop] = false;
      bDspAni[BM_yLoop] = false;
    }
  }
  else if (BM_fCellVoltage < fCurve[BATT_TYPE][0]) {
    bDisplay[0] = true;
    bDspAni[0] = true;
    for (BM_yLoop = 1; BM_yLoop < 10; BM_yLoop++) {
      bDisplay[BM_yLoop] = false;
      bDspAni[BM_yLoop] = false;
    }
  }
  else {
    for (BM_yLoop = 0; BM_yLoop < 9; BM_yLoop++) {
      if (BM_fCellVoltage > fCurve[BATT_TYPE][BM_yLoop + 1]) bDisplay[BM_yLoop] = true;
      else bDisplay[BM_yLoop] = false;
    }
  }
}

/*
void PrintMenu() {
  unsigned long PM_lTimeOut = 0;
  byte PM_yLoop = 0;
  
  PM_lTimeOut = millis();
  for (PM_yLoop = 0; PM_yLoop < 10; PM_yLoop++) {
    bDisplay[PM_yLoop] = true;
    bDspAni[PM_yLoop] = true;
  }
  Serial.println("Welcome to **Universal Battery Meter** version 0.1");
  Serial.println("Select an option, the default one is selected within 10 seconds:");
  Serial.println("[1] Show current input");
  Serial.println("[2] Show configuration");
  Serial.println("[3] Edit configuration");
  Serial.println("[4] Exit (default)");
  Serial.println("Write option number [1-4]:");
  while (millis() < (PM_lTimeOut + 10000));
  for (PM_yLoop = 0; PM_yLoop < 10; PM_yLoop++) {
    bDisplay[PM_yLoop] = false;
    bDspAni[PM_yLoop] = false;
  }
}
*/

unsigned int AnalogLPF(unsigned int ALPF_iValue) {
  static unsigned int ALPF_iBuffer[LPF_SIZE];
  unsigned long ALPF_lAve;
  byte ALPF_yLoop = 0;
  
  for (ALPF_yLoop = (LPF_SIZE - 2); ALPF_yLoop < LPF_SIZE; ALPF_yLoop--) {
    ALPF_iBuffer[ALPF_yLoop + 1] = ALPF_iBuffer[ALPF_yLoop];
  }
  ALPF_iBuffer[0] = ALPF_iValue;
  ALPF_lAve = 0;
  for (ALPF_yLoop = 0; ALPF_yLoop < LPF_SIZE; ALPF_yLoop++) {
    ALPF_lAve += ALPF_iBuffer[ALPF_yLoop];
  }
  ALPF_lAve /= LPF_SIZE;
  return ALPF_lAve;
}

float fmap(float x, float in_min, float in_max, float out_min, float out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

/*
void DebugMenu() {
  byte yChar = 0;
  
  do {
    if (Serial.available() > 0) {
      yChar = Serial.read();
      switch (yChar) {
        case 'r':
          digitalWrite(13, LOW);
          break;
        case 'R':
          digitalWrite(13, HIGH);
          break;
        case 'a':
          digitalWrite(A0, LOW);
          break;
        case 'A':
          digitalWrite(A0, HIGH);
          break;
        case 's':
          digitalWrite(A1, LOW);
          break;
        case 'S':
          digitalWrite(A1, HIGH);
          break;
        case 'd':
          digitalWrite(A2, LOW);
          break;
        case 'D':
          digitalWrite(A2, HIGH);
          break;
        case 'f':
          digitalWrite(A3, LOW);
          break;
        case 'F':
          digitalWrite(A3, HIGH);
          break;
        case 'g':
          digitalWrite(A4, LOW);
          break;
        case 'G':
          digitalWrite(A4, HIGH);
          break;
        case 'h':
          digitalWrite(A5, LOW);
          break;
        case 'H':
          digitalWrite(A5, HIGH);
          break;
      }
    }
  } while(1);
}
*/
