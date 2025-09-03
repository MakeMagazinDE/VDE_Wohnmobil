// *********************************************************************************
// Automatic Phase Corrector for Caravans
// *********************************************************************************

//definitions
int AI1=0;                          //Analogeingang L' (nach Umpolung)
int AI2=0;                          //Analogeingang N  (Eingang)
int AI3=0;                          //Analogeingang N' (nach Umpolung)
bool DQ5=false;                     //Ausgang Invertierung
bool DQ6=false;                     //Ausgang Einschaltung
bool DQ7=false;                     //Ausgang Fehler-LED
bool LED13=false;                   //Ausgang LED Heartbeat

// --------------------------------------------------------------------------------------------------
void setup() {
pinMode  (5, OUTPUT);               // Pin 5 als Ausgang fuer Umpolrelais K1/K2 definieren
pinMode  (6, OUTPUT);               // Pin 6 als Ausgang fuer Einschaltrelais definieren
pinMode  (7, OUTPUT);               // Pin 7 als Ausgang fuer Stör-LED definieren
pinMode (13, OUTPUT);               // Pin 13 Heartbeat
}

// --------------------------------------------------------------------------------------------------
void loop() {
//Analogeingänge lesen
AI1=analogRead(A1);
AI2=analogRead(A2);
AI3=analogRead(A3);

//Umpolen falls AI2>250 (N hat Spannung gegen PE)
if(AI2>=350) DQ5=true;
else DQ5=false;
digitalWrite(5, DQ5);              //Umpolrelais ansteuern

//Einschalten wenn Bedingungen o.k. (L' hat Spannung, N' nicht)
if(AI1>=350 && AI3<=50) {
  DQ6=true;
  DQ7=false;
}
else {
  DQ6=false;
  DQ7=true;
}
digitalWrite(6, DQ6);             //Einschaltrelais ansteuern
digitalWrite(7, DQ7);             //Fehler-LED ansteuern

//LED H13 invertieren
LED13= !LED13;
digitalWrite(13, LED13);          //Heartbeat (falls vorhanden)
delay(100);

}