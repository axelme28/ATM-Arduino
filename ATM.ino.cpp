#include <Arduino.h>
#line 1 "C:\\Users\\Axel\\Documents\\Arduino\\ATM\\ATM.ino"
#include <Password.h>
#include <Keypad.h>
#include <LiquidCrystal.h>

const byte filas = 4;
const byte columnas = 3;

Password password = Password("1234");  //Definimos el Password
int dlugosc = 4;                        //Largo del Password
int buzzer = 4  ; //Creamos las Variables de salida

int ilosc; //Numero de Clicks
void checkPassword();

LiquidCrystal lcd(9, 8, 10, 11, 12, 13); //Definimos los pines del LCD
char hexakeys[filas][columnas] = {
{'1','2','3'},
{'4','5','6'},
{'7','8','9'},
{'*','0','#'}
};

byte filasPins[filas] = {3,2,1,0};
byte columnasPins[columnas] = {7,6,5};


boolean valorActual = false;
Keypad keypad = Keypad( makeKeymap(hexakeys), filasPins, columnasPins, filas, columnas);

char tecla;
char clave[5];
char clave_maestra[5] = "1234";
byte indice = 0;

String monto;
char op;
boolean final = false;
byte cuenta;

int movimiento;
int cien=0,dos=0,quin = 0,mil = 0; 
int pulso = 0;
String leerMonto;

const int motorA = A0;
const int motorB = A1;
const int motorC = A2;
const int motorD = A3;


#line 51 "C:\\Users\\Axel\\Documents\\Arduino\\ATM\\ATM.ino"
void setup();
#line 75 "C:\\Users\\Axel\\Documents\\Arduino\\ATM\\ATM.ino"
void loop();
#line 112 "C:\\Users\\Axel\\Documents\\Arduino\\ATM\\ATM.ino"
void dinero(int monto);
#line 218 "C:\\Users\\Axel\\Documents\\Arduino\\ATM\\ATM.ino"
void retiro();
#line 51 "C:\\Users\\Axel\\Documents\\Arduino\\ATM\\ATM.ino"
void setup() {
  Serial.begin(9600);
  //lcd
  lcd.begin(16,2);
  lcd.setCursor(0,0);
  lcd.print("Bienvenido");
  lcd.setCursor(0,1);
  lcd.print("Digite su PIN");
  delay(2000);
  lcd.clear();
  //motores
  pinMode(motorA, OUTPUT);
  pinMode(motorB, OUTPUT);
  pinMode(motorC, OUTPUT);
  pinMode(motorD, OUTPUT);

  digitalWrite(motorA,LOW);
  digitalWrite(motorB,LOW);
  digitalWrite(motorC,LOW);
  digitalWrite(motorD,LOW);

  
}

void loop() {
 checkPassword();

}  
          




void checkPassword(){
      char key = keypad.getKey();
  if (key){
    clave[ilosc] = key;
    lcd.print(key);
    lcd.setCursor(++ilosc,0);
    
    if (ilosc==4){
      if(!strcmp(clave,clave_maestra)){
        lcd.setCursor(0,0);
        lcd.print("  <PIN CORRECTO>");
        delay(1500);
        lcd.clear();
        retiro();
        

      }
        /*else {
        lcd.setCursor(0,0);
        lcd.print("<PIN INCORRECTO>");  
        ilosc = 0;  
        }
    */
          
      }
    }
  }

    void dinero(int monto){
  lcd.clear();
  mil = monto/1000;
  monto = monto - (mil*1000);

  quin = monto/500;
  monto = monto - (quin*500);
  
  dos = monto/200;
  monto = monto - (dos*200);

  cien = monto/100;
  monto = monto - (cien*200);

  String milS = String(mil);
  String cienS = String(cien);
  String dosS = String(cien);
  String quinS = String(cien);
  if(mil>0){
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Billetes de 1000");
    lcd.setCursor(0,1);
    lcd.print(milS);
    delay(3000);
    mil*1000;
    digitalWrite(motorA,HIGH);
    delay(2000);
    
    }
    digitalWrite(motorA,LOW);
     if(quin>0){
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Billetes de 500: ");
    lcd.setCursor(0,1);
    lcd.print(quinS);
    delay(3000);
    quin*1000;
    digitalWrite(motorB,HIGH);
    delay(2000);
    
    }
   digitalWrite(motorB,LOW);
   if(dos>0){
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Billetes de 200: ");
    lcd.setCursor(0,1);
    lcd.print(dosS);
    delay(2000);
    dos*1000;
    digitalWrite(motorC,HIGH);
    delay(2000);
    
    }
    digitalWrite(motorC,LOW);
   if(cien>0){
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Billetes de 100: "+cienS);
    lcd.setCursor(0,1);
    lcd.print(cienS);
    delay(2000);
    cien*1000;
    digitalWrite(motorD,HIGH);
    delay(2000);
    
   }
   digitalWrite(motorD,LOW);

   digitalWrite(motorA,LOW);
   digitalWrite(motorB,LOW);
   digitalWrite(motorC,LOW);
   digitalWrite(motorD,LOW);
   lcd.clear();
   lcd.setCursor(0,0);
   lcd.print("RETIRE SU DINERO");
   delay(2000);
   lcd.clear();
   lcd.setCursor(0,0);
   lcd.print("Gracias");
}


  
 /* lcd.setCursor(0,0);
  lcd.print("Ingrese cantidad");
  lcd.setCursor(0,2);
  lcd.print("a retirar");
  delay(1500);
  lcd.clear();
  char monto2 = keypad.getKey();
    if (monto2){
    monto[pulso] = monto2;
    lcd.print(monto2);
    lcd.setCursor(++pulso,2);
    if (pulso==4){
      
      lcd.clear();
      int montoF = String(monto).toInt();
      dinero(montoF);
      
    }/*else if(ilosc==4){
      dinero(monto);
    }*/
void retiro(){
  lcd.setCursor(0,0);
  lcd.print("Ingrese cantidad");
  lcd.setCursor(0,2);
  lcd.print("a retirar");
  delay(1500);
  lcd.clear();
  
   char key = keypad.getKey();
  if (key != NO_KEY && (key=='1'||key=='2'||key=='3'||key=='4'||key=='5'||key=='6'||key=='7'||key=='8'||key=='9'||key=='0')){
    if (valorActual != true){
        monto = monto +key;
        lcd.print(monto);   
    }

}
    lcd.setCursor(0, 0);
        lcd.print("1");
        delay(700);
        lcd.setCursor(1, 0);
        lcd.print("8");
        delay(700);
        lcd.setCursor(2, 0);
        lcd.print("0");
        delay(700);
        lcd.setCursor(3, 0);
        lcd.print("0");
        delay(700);
        lcd.setCursor(4, 0);
        lcd.print("#");
        

dinero(1800);
}
/*if (key=='#'){
    lcd.clear();
    monto = leerMonto.toInt();
    dinero(100);
          }
        }*/
        
    /*else {
        num2 = num2 + key;
        int numLength = num2.length();
        lcd.setCursor(movimiento+1, 0);
        lcd.print(num2);
        final = true;
    }*/



  

