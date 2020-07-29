#include <LiquidCrystal.h>
#include<string>
#include <SPI.h>
#include <SD.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
const int analogInPin = A0;
const int analogOutPin = 9;
int sensorValue = 0;
int outputValue = 0;
int steps = 0;
const int SDCardPin = 10;
File myFile;
File logs;

void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  // pinMode(LED_BUILTIN, OUTPUT);
  
  lcd.begin(16, 2);
  
  Serial.begin(9600);
  Serial.println("Initializing SD card... Wait for a 'meter' second");
  
  myFile = SD.open("data.csv", FILE_WRITE);
  logs = SD.open("logs.txt", FILE_WRITE);
  
  if(logs){
    logs.println("---------------- LOGS BEGIN ------------------------");  
    logs.close();
  }
  else{
    Serial.println("But a brand new SD card at ... https://amzn.to/30PYZ2O");
    delay(10);
    Serial.println("Or Your Inserted SD Card is damaged/curropted/burned/unreadable/notFormatted/BAD/has Wrong Data Type/Etc. ");
    delay(10);
    Serial.println("Or Is it? - Vsacue");
  }
  
  if(myFile){
    myFile.println("Step, Val");
    Serial.println("SD card Initialized... and File Writeable ");
  }else{
    Serial.println("But a brand new SD card at ... https://amzn.to/30PYZ2O");
    delay(10);
    Serial.println("Your Inserted SD Card is damaged");
    delay(10);
    Serial.println("Or Is it? - Vsacue");
    
  }
  // myFile.close();
  // logs.close();
  myFile.flush();
  logs.flush();
}
int prevData= 0;
// the loop function runs over and over again forever
void loop() {
  if(!logs){
    exit(0);
  }
  if(!myFile){
    myFile = SD.open("data.csv", O_APPEND);
  }
  if(!myFile){
    exit(0);
  }
  // myFile = SD.open("data.txt", O_APPEND);
  // logs = SD.open("logs.txt", O_APPEND);
  stepFile = SD.open("data"+to_string(i)+".txt", FILE_WRITE);
  step++;
  sensorValue = analogRead(analogInPin);
  Serial.println(sensorValue);
  Serial.print(" ");
  lcd.clear();
  lcd.print(sensorValue - prevData);
  prevData = sensorValue;
  stepFile.println(sensorValue);
  stepFile.close();
  logs.println("stepFile "+to_string(i)+" Flushed and Closed");
  if(steps%2==0){
    return;
  }
  // Basically I am saving data in 2 files
  // One file is the file where all the data is stored
  // The other file, actually a folder where the data is stored in numbered file names
  // Since if the data is stored in the SDCard in any format and type, we can read the data from the computer.
  // Easily:- We only have to get the Data, And we have the DATA for the long time/as much as we want we can decrypt/retrieve the Data to the computer
  // I will also be creating a Logs.txt, to keep logs.
  
  if(myFile){
    myFile.println(to_string(i)+","+to_string(sensorValue));
    logs.println("Added Value for "+to_string(i));
    myFile.flush();
    // FLUSH:- When you call the println or print of the file, it stores them in a buffur/memory and writed only when you call the close() which closes the file and you cannot further write
    // or you can use the flush function which writes to the data in the buffer/memory to the file without closing the file system
    // the File in SDCARD is not curropted after force shutdown/forcefull disconnecting the power supply.
  }else{
    logs.println("MainFile Error");
    logs.println("Created New File");
    myFile = SD.open("data.csv", O_APPEND);
    // exit(0);
  }
  //Serial.print("Sensor = ");
  //Serial.print(sensorValue);
  //Serial.print("\t Output = ");
  //Serial.print(outputValue);
  //Serial.print("\n");
  delay(2500);
}
