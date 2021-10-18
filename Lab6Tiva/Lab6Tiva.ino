


//***********************************************************************
//definicion de pines
//***********************************************************************

#define pot2 A7
#define boton1 PF_4
#define boton2 PF_0

#define Rx1 RX(1)
#define Tx1 TX(1)

#define Rx2 RX(2)
#define Tx2 TX(2)

//***********************************************************************
//Prototipos de funciones
//***********************************************************************
void contBitsSuma(void);
void comunicacionESP(void);
//*****************************************************************************
// Variables Globales
//*****************************************************************************
float voltajePot = 0;
float voltaje1 = 0;
int contador = 0;
String mensaje = "";
//***********************************************************************
//CONFIGURACION
//***********************************************************************

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial1.begin(115200);
  Serial2.begin(115200);
  
  pinMode(boton1, INPUT_PULLUP);
  pinMode(boton2, INPUT_PULLUP);
}

void loop() {
  // put your main code here, to run repeatedly:
  voltajePot = ((analogRead(pot2))*0.008);
  contBitsSuma(); 
  comunicacionESP();
  
  Serial1.write(voltajePot);
  Serial2.write(33);
  
  Serial.print(voltajePot);
  Serial.print("  ");
  Serial.print(contador);
  Serial.print("  ");
  Serial.println(voltaje1);

  delay(150);
}

//*****************************************************************************
//Funcion para realizar la suma y resta con los botones
//*****************************************************************************
void contBitsSuma() {
  if ( digitalRead(boton1) == LOW && contador < 255) {
    contador = contador + 1 ;
    mensaje = "";

  }

  if ( digitalRead(boton1) == LOW && contador >= 255) {
    contador = 0 ;

    mensaje = "";

  }

  if (digitalRead(boton2) == LOW && contador > 0) {
    contador = contador - 1 ;
    mensaje = "";

  }
  if ( digitalRead(boton2) == LOW && contador <= 0) {
    contador = 254 ;
    mensaje = "";

  }
}

//*****************************************************************************
//Funcion para recibir datos de esp
//*****************************************************************************
void comunicacionESP(){
  if(Serial2.available()){//si hay algun dato esperando a ser leido...
    voltaje1 = Serial2.read();//el dato es guardado en la variable
    
  }
}
