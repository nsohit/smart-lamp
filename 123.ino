#include <Password.h>
#include <Keypad.h>
Password password = Password( "45" ); //Ubah password
#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <Servo.h>
Servo myservo;
Servo myservo2;
#include <Ultrasonic.h>
#define ledHijau 6
#define ledMerah  7
Ultrasonic ultrasonic (12, 13) ;//trigger and echo pin ditace
Ultrasonic ultrasonic2(10, 11) ;//trigger and echo pin isi tong
int isitongpenuh = 5;
 int isitongada = 30; 
int distance;
int isitong;
int pos = 0; 
const byte baris = 3; //Baris
const byte kolom = 3; //Kolom

char keys[baris][kolom] = {
//{'1','2','3'},
{'4','5','6'},
{'7','8','9'},
{'*','0','#'}
};


byte barisPin[baris] = {0,1,2};
byte kolomPin[kolom]= {3,4,5};

// Buat objek keypad
Keypad keypad = Keypad( makeKeymap(keys), barisPin, kolomPin, baris, kolom );
LiquidCrystal_I2C lcd(0x27, 16, 2);  


void setup() {
  // put your setup code here, to run once:

  lcd.backlight();
  lcd.init(); 
  lcd.clear();
  //keypad.addEventListener(keypadEvent);
  Serial.begin(9600);
  myservo.attach(9); 
  myservo2.attach(8);
  myservo.write(0);
  myservo2.write(90);
  keypad.addEventListener(keypadEvent); //add an event listener for this keypad    
  pinMode(ledHijau,OUTPUT);
  pinMode(ledMerah,OUTPUT);

}
void loop() {

  lcd.setCursor(3,0); 
  lcd.print("Masukan PWD");
  Serial.println(keypad.getKey());
 
  
  distance = ultrasonic.read(); // untuk membuka tong
 // delay(1);
  isitong = ultrasonic2.read();// membaca isi
 // delay(1);
  Serial.print("Distance in CM: ");
  Serial.println(distance);
  delay(10);
  Serial.print("Isi_Tong in CM: ");
  Serial.println(isitong);
  delay(10);
  
 if (distance <= 30 ){

   // for (pos = 0; pos <= 90; pos += 1)  // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo.write(180);              // tell servo to go to position in variable 'pos'
    delay(1); 
  
 }

 if (distance > 30 ){

  // for (pos = 90; pos >= 0; pos -= 1)  // goes from 180 degrees to 0 degrees
   myservo.write(0);              // tell servo to go to position in variable 'pos'
   delay(1);   
 }

 int range = map (isitong,isitongpenuh,isitongada,0,3);
 switch(range){

  case 1:
   digitalWrite(ledMerah,HIGH);
  delay(10);
  digitalWrite(ledHijau,LOW);
  delay(10);
  myservo.write(0);
  delay(900); 
  break; 
  case 2: 
  digitalWrite(ledHijau,HIGH); 
  delay(10);
  digitalWrite(ledMerah,LOW);
  delay(10);
  break;

 }

}
void keypadEvent(KeypadEvent eKey){
 
  switch (keypad.getState()){
    case PRESSED:
  lcd.setCursor(3,1);
  lcd.print(eKey);
  switch (eKey){
    case '*': checkPassword(); break;
    case '0': password.reset();lcd.clear(); break;
    case '#':tutup();break;
    default: password.append(eKey);
     }
  }
}

void checkPassword(){
  if (password.evaluate()){
   Serial.println("Success");
   lcd.setCursor(3,1);
   lcd.print("Akses Diterima!");
   myservo2.write(0);              // tell servo to go to position in variable 'pos'
   delay(9000); 
    //Add code to run if it works
  }else{
    Serial.println("Wrong");
    lcd.setCursor(3,1);
    lcd.print("Akses Ditolak!");
    //add code to run if it did not work
  }
}
void tutup(){
    myservo2.write(90);
     delay (200);  
}

