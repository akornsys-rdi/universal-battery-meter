/*
 * RELAY      D13
 * BUZZER     D12
 *  _
 * |_| RED    D11
 * |_| GREEN  D10
 * |_| GREEN  D9
 * |_| GREEN  D8
 * |_| GREEN  D7
 * |_| YELLOW D6
 * |_| YELLOW D5
 * |_| YELLOW D4
 * |_| RED    D3
 * |_| RED    D2
 *
 * RESISTOR DIVIDER NETWORK (82k primary resistor)
 *
 * ANALOG IN  A6	1/1
 *
 * -/\/\- k82 A5	1/100
 * -/\/\- 2k7 A4	1/32
 * -/\/\- 5k6 A3	1/16
 * -/\/\- 12k A2	1/8
 * -/\/\- 27k A1	1/4
 * -/\/\- 82k A0	1/2
 *
 */

/*
 *
 * DIV	MIN	MINCUT	NOM	MAXCUT	MAX	RES/STEP
 * 1	4.9	-/750	2500	4250	5000	4.8875855327
 * 2	9.8	1500	5000	8500	10000	9.7751710654
 * 4	19.6	3000	10000	17000	20000	19.5503421309
 * 8	39.1	6000	20000	34000	40000	39.1006842619
 * 16	78.2	12000	40000	68000	80000	78.2013685239
 * 32	156.4	24000	80000	136000	160000	156.4027370478
 * 100	488.8	-	250000	-	500000	488.7585532746
 *
 */

#include <MsTimer2.h>

//constant
#define BATT_NONE 0
//nickel
#define BATT_NICD 11 //nickel-cadmium
#define BATT_NIMH 12 //nickel metal hydride
#define BATT_NIZN 13 //nickel-zinc
//lead
#define BATT_PB 2 
//lithium
#define BATT_LIION 31 //lithium-ion
#define BATT_LIPO 32 //lithium polymer
#define BATT_LIFE 33 //lithium iron phosphate

#define	DIV_100	100
#define DIV_32	32
#define DIV_16	16
#define DIV_8	8
#define DIV_4	4
#define DIV_2	2
#define DIV_1	1

//display & buzzer
boolean Display[12] = {false, false, false, false, false, false, false, false, false, false, false};
boolean DspAni[12] = {false, false, false, false, false, false, false, false, false, false, false};

//isr timer2 every 10ms
void isrtmr2() {
  static byte isr_BlinkFlag = 0; //uses bit 5 for blink (~640ms )
  byte isr_yLoop = 0;
  
  isr_BlinkFlag++; //increment 
  for (isr_yLoop = 0; isr_yLoop < 12; isr_yLoop++) {
    digitalWrite(isr_yLoop + 2, (Display[isr_yLoop] && (!DspAni[isr_yLoop] || (isr_BlinkFlag & 0x20))));
  }
  autovolts();
}

void setup() {
  byte yLoop = 0;
  
  Serial.begin(9600);
  for (yLoop = 2; yLoop < (A5 + 1); yLoop++) {
    pinMode(yLoop, OUTPUT);
    digitalWrite(yLoop, LOW);
  }
  MsTimer2::set(10, isrtmr2);
  MsTimer2::start();
  analogReference(DEFAULT);
}

void loop() {

}

//return readed volt value in mV with autoscale
unsigned long autovolts() {
  static byte mode = 0; //0 off; 1 autoscale; 2 protection
  static unsigned long prevvalue = 0;
  
  if (mode) {
    
  }
  else {
    setdivider(100);
    mode = 2;
  }
}

void setdivider(int div) {
  //activar 100, desconectar rango actual, activar rango correspondiente, desactivar 100
}

/*
si no esta activo, activar y meter en proteccion
si esta en proteccion esperar tiempo antes de volver a autoscale
en autoscale, si el slewrate es muy alto, pasar a proteccion
en caso contrario ir desde la mayor division al la menor, buscando el valor centrado
si el valor supera el 85% subir de escala
si el valor baja del 15% bajar de escala
*/
