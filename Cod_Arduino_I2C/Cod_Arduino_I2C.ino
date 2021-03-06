#include <TimerOne.h>

#include <Wire.h>
#include "U8glib.h"


U8GLIB_ST7920_128X64_1X u8g(6,5,4,7);
char charAux[30];
String aux;
 int c=0;
  const char com [9] = ""; //variable Ema/tono
   char pul[9] = "";        //variable leo/ema/tono
  const char res[9]="";    //variable hector 

  float pulso = 0;


//Cronometro.

float segundos = -2;
const char seg [9]=""; //constante cronometro

float cpmm=0;
const int timeThreshold = 20;
const int intPin = 3;
volatile int ISRCounter = 0;
float counter = 0;
long startTime = 0;
  //respiraciones
  volatile int Contador=0; //variable que cuenta los pulsos
  int PinSensor = 2;    // pin donde se conecta  el sensor
  float respiracion=0;
 
  void pulso2 (){
    Contador++;
    //delay(440);
  }// función a ejecutarse en cada interrupción
  
 unsigned int Tm = 0,T=20000,cpm=0; //Tm->tiempo Maximo en la que guira en motor, T un minuto en miliseg/1000, s->
unsigned int Tm1;
 
long funcion(void){
  long cantidad;
  Contador = 0;  
  interrupts();
  delay(100);  //Se inician las interrupciones y se cuentan los pulsos
  noInterrupts();//se suspenden las interrupciones
  cantidad=10*Contador; // pulsos por segundo
  return cantidad;
}

const uint8_t meso[] U8G_PROGMEM = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0,
   0x05, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x30, 0x0e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1c, 0x18, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02,
   0x60, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x03, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xc0, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00,
   0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x80, 0xff, 0xff, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x78, 0x00, 0x00, 0x3f, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x7f, 0x00,
   0x00, 0xff, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x01, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0xf0, 0xff, 0x3f, 0xc0, 0x03, 0xfc, 0xff, 0x0f,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfe, 0xff, 0x1f, 0xc0,
   0x03, 0xf8, 0xff, 0x7f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80,
   0xff, 0x1f, 0x1e, 0x00, 0x00, 0x78, 0xfc, 0xff, 0x03, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0xf0, 0xff, 0x01, 0xfe, 0xbc, 0x1d, 0x7f, 0x80, 0xff,
   0x1f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfc, 0x3f, 0xc0, 0xff, 0xbc,
   0x3d, 0xff, 0x01, 0xfc, 0x7f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff,
   0x07, 0xc0, 0xbf, 0xbc, 0xbd, 0xfc, 0x01, 0xe0, 0xff, 0x01, 0x00, 0x00,
   0x00, 0x00, 0xc0, 0xff, 0x00, 0xf0, 0xbf, 0xbd, 0xbd, 0xfd, 0x0f, 0x00,
   0xff, 0x07, 0x00, 0x00, 0x00, 0x00, 0xf0, 0x3f, 0x00, 0xf0, 0xc7, 0xbc,
   0xbd, 0xe1, 0x0f, 0x00, 0xfc, 0x0f, 0x00, 0x00, 0x00, 0x00, 0xf8, 0x0f,
   0x00, 0xf8, 0xf7, 0xbc, 0xbd, 0xf7, 0x0f, 0x00, 0xf0, 0x3f, 0x00, 0x00,
   0x00, 0x00, 0xfc, 0x03, 0x00, 0xfe, 0xf7, 0xbc, 0xbd, 0xe7, 0x7f, 0x00,
   0xc0, 0x7f, 0x00, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0xfe, 0xfb, 0xbe,
   0x3d, 0xdf, 0x3f, 0x00, 0x80, 0xff, 0x00, 0x00, 0x00, 0x80, 0x7f, 0x00,
   0xc0, 0xff, 0xfb, 0xbe, 0x3d, 0xdf, 0xff, 0x03, 0x00, 0xfe, 0x01, 0x00,
   0x00, 0xc0, 0x1f, 0x00, 0xc0, 0xff, 0xf8, 0xbe, 0x3d, 0x1f, 0xff, 0x03,
   0x00, 0xfc, 0x03, 0x00, 0x00, 0xe0, 0x0f, 0x00, 0xf8, 0xff, 0x7e, 0xbe,
   0x3d, 0x3f, 0xff, 0x1f, 0x00, 0xf0, 0x07, 0x00, 0x00, 0xf0, 0x07, 0x00,
   0xf8, 0xff, 0xfe, 0xbe, 0x3f, 0x3f, 0xff, 0x1f, 0x00, 0xe0, 0x0f, 0x00,
   0x00, 0xf0, 0x03, 0x00, 0xf8, 0x1f, 0x7f, 0xbe, 0x3f, 0xfe, 0xfc, 0x0f,
   0x00, 0xc0, 0x1f, 0x00, 0x00, 0xf8, 0x01, 0x00, 0xff, 0x3f, 0x7f, 0xbe,
   0x7f, 0xfe, 0xfc, 0xff, 0x00, 0x80, 0x3f, 0x00, 0x00, 0xfc, 0x00, 0x00,
   0xff, 0x8f, 0x7f, 0xbe, 0x7f, 0xfe, 0xf0, 0xff, 0x00, 0x00, 0x3f, 0x00,
   0x00, 0x7c, 0x00, 0x00, 0xff, 0x8f, 0x7f, 0xbe, 0x7f, 0xfe, 0xf1, 0xff,
   0x00, 0x00, 0x7e, 0x00, 0x00, 0x3e, 0x00, 0xe0, 0xff, 0x8f, 0x7f, 0xbe,
   0x7f, 0xfe, 0xf1, 0xff, 0x07, 0x00, 0x7e, 0x00, 0x00, 0x3e, 0x00, 0xe0,
   0xff, 0xf3, 0x7f, 0xbe, 0x7f, 0xfe, 0xe7, 0xff, 0x07, 0x00, 0xfc, 0x00,
   0x00, 0x1f, 0x00, 0xe0, 0xff, 0xf3, 0x7f, 0xbe, 0x7f, 0xfe, 0xe7, 0xff,
   0x07, 0x00, 0xf8, 0x00, 0x00, 0x1f, 0x00, 0xf8, 0xff, 0xf3, 0x7f, 0xbf,
   0xff, 0xfe, 0xe7, 0xff, 0x1f, 0x00, 0xf8, 0x00, 0x00, 0x0f, 0x00, 0xf8,
   0xff, 0xf0, 0x3f, 0xbf, 0xff, 0xfe, 0x8f, 0xff, 0x1f, 0x00, 0xf0, 0x01,
   0x00, 0x0f, 0x00, 0xf8, 0xff, 0xfc, 0x3f, 0xbf, 0xff, 0xfc, 0x9f, 0xff,
   0x1f, 0x00, 0xf0, 0x01, 0x00, 0x07, 0x00, 0xff, 0x7f, 0xfc, 0x3f, 0xbf,
   0xff, 0xfc, 0x1f, 0xfe, 0xff, 0x00, 0xf0, 0x01, 0x00, 0x07, 0x00, 0xff,
   0x3f, 0xfe, 0x1f, 0xff, 0xff, 0xf8, 0x7f, 0xfe, 0xff, 0x00, 0xe0, 0x01,
   0x00, 0x07, 0x00, 0xff, 0x3f, 0xfe, 0xdf, 0xff, 0xff, 0xf9, 0x7f, 0xfe,
   0xff, 0x00, 0xe0, 0x01, 0x00, 0x07, 0x00, 0xff, 0x3f, 0xfe, 0xdf, 0xff,
   0xff, 0xfd, 0x7f, 0xfe, 0xff, 0x00, 0xe0, 0x00, 0x00, 0x07, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x00,
   0x00, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0xe0, 0x00, 0x00, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x00, 0x00, 0x06, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x60, 0x00,
   0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x60, 0x00, 0x00, 0x0c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x60, 0x00, 0x00, 0x08, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 0x00,
   0x00, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x10, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00,
   0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00
  };

 const uint8_t planti[] U8G_PROGMEM = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff,
   0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
   0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
   0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3e, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x80, 0x0f, 0x63, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00,
   0x00, 0x00, 0x00, 0x00, 0xe0, 0x18, 0xc1, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 0x10, 0x81, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x10, 0x18, 0x91, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0x03, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x10, 0x0a, 0x91, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x06, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 0x0b, 0x9f, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x87, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00,
   0xe0, 0x09, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x85, 0x02, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x0c, 0x60, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x8d, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf8, 0xf3, 0x3f, 0x00,
   0x00, 0x00, 0x00, 0x00, 0xc0, 0x89, 0x3a, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0xf8, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf8, 0x0a, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x0c, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x18, 0x0a, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x02, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x0e, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x04, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x06, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x24, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x18, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3c, 0x02, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x3f, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00 };

  void logo(void){
  u8g.drawXBMP( 0, 0, 128, 64, meso);
  }

  void ISR_crono(){
    unsigned long antes=millis();
    despliegue();
    segundos = segundos +1;
    if (segundos >= 130 && counter >=150&& counter <=155 & &respiracion >= 10 && respiracion <= 15){
        segundos = 0;
      }
    if (segundos >= 130 && counter >=300&& counter <=305 & &respiracion >= 20 && respiracion <= 25){
        segundos = 0;
      }
      if (segundos >= 130 && counter >=450&& counter <=455 & &respiracion >= 30 && respiracion <= 35){
        segundos = 0;
      }
      if (segundos >= 130 && counter >=600&& counter <=605 & &respiracion >= 40 && respiracion <= 45){
        segundos = 0;
      }
      if (segundos >= 130 && counter >=750&& counter <=755 & &respiracion >= 50 && respiracion <= 55){
        segundos = 0;
      }
      unsigned long despues=millis();
    unsigned long transcurridos= despues-antes;
    Tm = Tm + transcurridos;
    }
  
  void despliegue(){ 
       dtostrf(segundos, 2, 0, seg);
       dtostrf(counter, 2, 0, com);//convierte float a char
       dtostrf(cpmm, 2, 1, pul);
       dtostrf(respiracion, 2, 0, res);
       u8g.firstPage();
        do{
          plantilla();
          u8g.drawStr(90, 25, seg);   //segundos
          u8g.drawStr( 20, 25, com);  //compresiones
          u8g.drawStr( 26, 50, pul);   //pulso
           u8g.drawStr( 95, 50, res); //respiraciones
         }while(u8g.nextPage());
    
    }
  
  void plantilla(void){
  u8g.drawXBMP( 0, 0, 128, 64, planti);
  u8g.setFont(u8g_font_unifont);
  u8g.drawStr( 8, 10, "Comp: ");
  u8g.drawStr(75, 10, "Crono: ");
  }
  void comienzo (){
     u8g.setFont(u8g_font_unifont);
  //u8g.setFont(u8g_font_osb21);
  u8g.drawStr( 30, 35, "Comienza");
    }

void clearLCD(){
    u8g.firstPage();
    do{
      }while(u8g.nextPage());
    }



void setup() {
  // put your setup code here, to run once:
  //Init comunication i2c
  Wire.begin(8);                // join i2c bus with address #8
  Wire.onRequest(requestEvent);


   
   if(u8g.getMode()== U8G_MODE_R3G3B2){
     u8g.setColorIndex(255);
    }
    else if(u8g.getMode() == U8G_MODE_GRAY2BIT){
      u8g.setColorIndex(3);
      }
      else if(u8g.getMode() == U8G_MODE_BW){
         u8g.setColorIndex(1);
        }
        else if(u8g.getMode() == U8G_MODE_HICOLOR){
          u8g.setHiColorByRGB(255, 255, 255);
          }
          u8g.firstPage();
  do{
    logo();
    }while(u8g.nextPage());
    delay(2000);
    clearLCD();
    
    u8g.firstPage();
      do{
    comienzo();
    }while(u8g.nextPage());
    delay(3000);
    clearLCD();

  Serial.begin(9600);  
  pinMode(intPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(intPin), debounceCount, FALLING);
  pinMode(PinSensor, INPUT);
  attachInterrupt(0,pulso2,RISING); // inicializamos las interupciones 
 

  Timer1.initialize(1000000); //1 segundo
  Timer1.attachInterrupt(ISR_crono);
}

int celsius, VarRan_L, Cpm_L, Res_L, Pul_L,Pul_Cor_L, Pul_Inc_L, Pul_Correctos, Pul_Incorrectos;

void loop() {
  unsigned long antes=millis();
  //Despues de Esto
  float frecuencia=funcion(); //frecuencia de los pulsos
  float Caudal=frecuencia/7.5; //calculamos el caudal en L/m
  Pul_Cor_L=20;
  Pul_Inc_L=34;
  
  if(Caudal > 1.33 && Caudal < 2){
    c+=1;
    respiracion+=1;
      celsius = c;
    despliegue();
    }
    
     if (counter != ISRCounter) {
      
      counter = ISRCounter;
      VarRan_L = counter;
      
      Serial.print("  tiempo:");
      Serial.println(Tm);
   
   }
    //Antes de Esto
    unsigned long despues=millis();
    unsigned long transcurridos= despues-antes;
    Tm = Tm + transcurridos;
 
   
}

void debounceCount()
{
  
   if (millis() - startTime > timeThreshold)
   {
    
      ISRCounter++;
      startTime = millis();
  
   cpm=T/Tm;
   if(Tm >= 200 && Tm < 500){
    cpm = 110;
   }
  if(Tm < 199){
    cpm = 150;
    Pul_Incorrectos++;
  }
  
//   cpm=Tm;
   cpmm=cpm;
   despliegue();
   Tm=0;
   
    }
}

//Function to send dato whit comunication
 void requestEvent() {
  Res_L = map(celsius, 0, 255, 100, 355);
  Cpm_L = map(cpm, 0, 255, 100, 355);
  Pul_L = map(VarRan_L, 0, 255, 100, 355);
  Pul_Incorrectos = map(Pul_Inc_L, 0, 255, 100, 355);
  Pul_Correctos = map(Pul_Cor_L, 0, 255, 100, 355);
  //Cpm_L = cpm;
  Wire.print(Res_L);
  Wire.print(Cpm_L);
  Wire.print(Pul_L);
  Wire.print(Pul_Incorrectos);
  Wire.print(Pul_Correctos);
}
