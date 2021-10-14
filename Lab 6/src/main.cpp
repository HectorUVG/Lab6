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
#define en 16
#define rs 0

#define pot1 36


#define Boton1 14

//*****************************************************************************
// Prototipos de función
//*****************************************************************************
void separarvariables1(void);
//*****************************************************************************
// Variables Globales
//*****************************************************************************
// Create An LCD Object. Signals: [ RS, EN, D4, D5, D6, D7 ]
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
int centenas = 0;
int decenas = 0;
int unidades = 0;
int adcRaw;
float voltaje1;
int volt1;

//*****************************************************************************
//ISR
//*****************************************************************************

//*****************************************************************************
// Configuración
//*****************************************************************************

void setup() {
 
 // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("Pot1:");
  lcd.setCursor(6, 0);
}

//*****************************************************************************
// Loop principal
//*****************************************************************************

void loop() {
  separarvariables1();

  lcd.setCursor(0, 1);
  // print the number of seconds since reset:
  lcd.print(voltaje1);
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