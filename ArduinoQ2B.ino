#include <OSM.h>
#define PINNUMBER ""

GSM gsmAccess;
GSM_SMS sms;

void setup(){
	Serial.println("SMS Messages Sender");
	boolean notConnected = true;

	while(notConnected){
		if(gsmAcess.begin(PINNUMBER)==GSM_READY){
			notConnected = false;
		}else{
			Serial.println("Not connected");
			delay(1000);
		}
	}
	Serial.println("GSM Initiated")
}
void loop(){
	Seral.print("Enter a mobile number: ");
	char remoteNum[20];
	readSerial(remoteNum);
	Seral.printIn(remoteNum);
	Serial.print("Now, enter SMS content");
	chat txtMsg[200];
	readSerial(txtMsg);
	Serial.println("SENDING");
	Serial.println(txtMsg);
	sms.beginSMS(remoteNum);
	sms.print(txtMsg);
	Serial.println("\nCOMPLETE!\n")
}
int readSerial(char result[]){
	int i=0;
	while(1){
		while(Serial.available() > 0){
			char inChar = Serial.read();
			if(inChar=="\n"){
				result[i]="\0";//Null
				Serial.flush();
				return 0;
			}
			if(inChar!='\r'){
				result[i]=inChar;
				i++;
			}
		}
	}
}