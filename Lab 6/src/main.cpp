#include <Arduino.h>
#include <LiquidCrystal.h>


//*****************************************************************************
// Definición de pines
//*****************************************************************************
#define d4 19//los GPIO 1 y 3 se dejan libres porque son los que usa la 
//comnicacion serial
#define d5 21
#define d6 22
#define d7 23
#define en 18
#define rs 5

#define pot1 36

#define Boton1 14
//pines para la comunicacion uart
#define TX2 17
#define RX2 16

#define TX1 10
#define RX1 9

//*****************************************************************************
// Prototipos de función
//*****************************************************************************
void separarvariables1(void);
void comunicacionTiva(void);
void CentenasDecenasUnidades(void);
void comunicacionTivabtn(void);
//*****************************************************************************
// Variables Globales
//*****************************************************************************
// Create An LCD Object. Signals: [ RS, EN, D4, D5, D6, D7 ]
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
int centenas = 0;
int decenas = 0;
int unidades = 0;

float voltaje1;
int volt1;
//variables para la comunicacion usart
float uartESPTX = 0;
float uartESPRX = 0;

int uartESPTXbtn = 0;//comunicacion con los botones de la tiva
int uartESPRXbtn = 0;

float pot2 = 0;//para poder convertir lo de la tiva a un valor con el que pueda trabajar

//*****************************************************************************
//ISR
//*****************************************************************************

//*****************************************************************************
// Configuración
//*****************************************************************************

void setup() {
 Serial.begin(115200);//se inicia la comunicacion uart 1
 Serial1.begin(115200);
 Serial2.begin(115200);//se inicia la comunicacion uart 2, para comunicarme con la tiva
 // set up the LCD's number of columns and rows:
  lcd.begin(16, 4);
  // Print a message to the LCD.
  lcd.print("Pot1:");
  lcd.setCursor(6, 0);
  lcd.print("Pot2:");
  lcd.setCursor(12, 0);
  lcd.print("Tiva");
}

//*****************************************************************************
// Loop principal
//*****************************************************************************

void loop() {
  separarvariables1();
  comunicacionTiva();
  comunicacionTivabtn();
  CentenasDecenasUnidades();
  

  lcd.setCursor(0, 1);
  // print the number of seconds since reset:
  lcd.print(voltaje1);

  lcd.setCursor(6, 1);
  // print the number of seconds since reset:
  lcd.print(uartESPRX);

  lcd.setCursor(12, 1);
  // imprime el valir de la centena
  lcd.print(centenas);

  lcd.setCursor(13, 1);
   // imprime el valir de la decena
  lcd.print(decenas);

  lcd.setCursor(14, 1);
   // imprime el valir de la unidad
  lcd.print(unidades);
  Serial.println(uartESPRXbtn);
  Serial1.println(voltaje1);
}

//*****************************************************************************
//*****************************************************************************
// funciones
//*****************************************************************************
//*****************************************************************************

//*****************************************************************************
//Funcion para leer el voltaje del pot1
//*****************************************************************************
void separarvariables1(){
  voltaje1 = analogReadMilliVolts(pot1)/1000.0 ;//al dividirlo da el valor en 
  //volios
  //potLedR = (voltaje1/3.15)*255;//divide voltaje1 para obtener un valor entre
  //0 y 1 y lo multiplica por 255 para obtener valores entre 0 y 255 para el 
  //led 


}

//*****************************************************************************
//Comunicacion cn la tiva
//*****************************************************************************
void comunicacionTiva(){
  if(Serial2.available()>0){//si hay algun dato esperando a ser leido...
    uartESPRX = Serial2.read()/10.0;//el dato es guardado en la variable
  }
}

void comunicacionTivabtn(){
  if(Serial1.available()>0){//si hay algun dato esperando a ser leido...
    uartESPRXbtn = Serial1.read();//el dato es guardado en la variable
  }
}

//*****************************************************************************
// funcion para decenas centenas y unidades
//*****************************************************************************
void CentenasDecenasUnidades(){
  
  int temp = uartESPRXbtn;
  centenas = temp/100;
  temp = temp - (centenas*100);
  decenas = temp/10;
  temp = temp - (decenas*10);
  unidades = temp;


}