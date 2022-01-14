  #include <IRremote.h>
  #include <LiquidCrystal.h>
  #include <EEPROM.h>

  uint8_t EEPROMpirates = 100;
  uint8_t EEPROMbirthday = 200;
  uint8_t EEPROMjingle = 300;
  uint8_t EEPROMgame = 400;
  
  
  int buzzer_pin = 9;
  float half = 0.5;
  float one = 1.0;
  float one_half = 1.5;
  float two = 2.0;
  float two_half = 2.5;
  int tempo;
  int Length;
  int currentPos = 0;
  int button_pin = 2;
  String songName;
  volatile int count=1;
  volatile int state = 0;
  int IR = 13;
  IRrecv irrec(IR);
  decode_results results;
  LiquidCrystal lcd(12, 11, 5, 4, 1, 0);

  #define CHD 0x40BF906F
  #define CHU 0x40BF0AF5
  #define VOLD 0x40BF58A7
  #define VOLU 0x40BF8A75
  #define OK 0x40BFF807
  #define ZERO 0x40BF18E7
  #define ICHI 0x40BF8877
  #define NI 0x40BF48B7
  #define SAN 0x40BFC837
  #define YON 0x40BFD22D
  #define GO 0x40BF28D7

void ON_OFF(){
  if(state == 0){
    state =1;
    lcd.setCursor(0,1);
    lcd.print("o");
  }else if(state == 1 ){
    state = 0;
    count = 1;
    lcd.setCursor(0,1);
    lcd.print("x");
  }
  
}


void setup() {
  // put your setup code here, to run once:
  pinMode(buzzer_pin, OUTPUT);
  pinMode(button_pin, INPUT);
  attachInterrupt(0,ON_OFF,FALLING);
  irrec.enableIRIn();
  lcd.begin(16, 2); 
  lcd.clear();     
}

void loop() {
  // put your main code here, to run repeatedly:
  if(state == 0){
    if(count == 1){
    lcd.clear();
    lcd.setCursor(2,0);
    lcd.print("Push Button");
    lcd.setCursor(3,1);
    lcd.print("to Continue");
    count--;
    }
  }if(state == 1){
   if(irrec.decode(&results)){
    
    if(results.value == ICHI){
      currentPos=0;
      
    }else if(results.value == NI){
      currentPos=1;
      
    }else if(results.value == SAN){
      currentPos=2;
      
    }else if (results.value == YON){
      currentPos=3;
      
    }else if(results.value == GO){
      currentPos=4;
      
    }else if(results.value == CHD){
      currentPos--;
      
    }else if(results.value == CHU){
      currentPos++;
    }

  if(currentPos == 0){
    playHP();
 }else if(currentPos == 1){
    playBirthday();
  }else if(currentPos == 2){
    playJingle();
  }else if(currentPos == 3){
    playGameOfThrones();
  }
  irrec.resume();
  }
}
}

void setTone(int pin, int note, int duration) {
  tone(pin, note, duration);
  delay(duration);
  noTone(pin);
}

void playHP(){
  unsigned long startTime = millis();
  lcd.clear();
  lcd.setCursor(2,0);
  lcd.print("Harry Potter");
  lcd.setCursor(2,1);
  lcd.print("Theme Song");
  int hA = 550;
  int hAs = 582;
  int hB = 617;
  int hC = 654;
  int hCs = 693;
  int hD = 734;
  int hDs = 777;
  int hE = 824;
  int hF = 873;
  int hFs = 925;
  int hG = 980;
  int hGs = 1003;
  int hA2 = 1100;
  int hA2s = 1165;
  int hB2 = 1234;
  int hC3 = 1308;
  int hC3s = 1385;
  int hD3 = 1555;
  tempo = 400;
  setTone(buzzer_pin, hB, tempo * one);
  setTone(buzzer_pin, hE, tempo * one_half);
  setTone(buzzer_pin, hG, tempo * half);
  setTone(buzzer_pin, hF, tempo * one);
  setTone(buzzer_pin, hE, tempo * two);
  setTone(buzzer_pin, hB2, tempo * one);
  setTone(buzzer_pin, hA2, tempo * two_half);
  setTone(buzzer_pin, hFs, tempo * two_half);
  
  setTone(buzzer_pin, hE, tempo * one_half);
  setTone(buzzer_pin, hG, tempo * half);
  setTone(buzzer_pin, hF, tempo * one);
  setTone(buzzer_pin, hDs, tempo * two);
  setTone(buzzer_pin, hF, tempo * one);
  setTone(buzzer_pin, hB, tempo * two_half);
  unsigned long endTime = millis();
  unsigned long elapsedTime = endTime-startTime;
  float songDuration = elapsedTime / 1000.0;
  EEPROM.put(EEPROMpirates, songDuration);
  lcd.setCursor(13,1);
  lcd.print(EEPROM.get(EEPROMpirates,songDuration));
}

float playBirthday(){
  unsigned long startTime = millis();
  lcd.clear();
  lcd.setCursor(1,0);
  lcd.print("Happy Birthday");
  lcd.setCursor(2,1); 
  lcd.print("to You!");
  Length = 28;
  char notes[] = "GGAGcB GGAGdc GGxecBA yyecdc";
  int beats[] = { 2, 2, 8, 8, 8, 16, 1, 2, 2, 8, 8,8, 16, 1, 2,2,8,8,8,8,16, 1,2,2,8,8,8,16 };
  tempo = 150;
  for (int i = 0; i < Length; i++) {
   if (notes[i] == ' ') {
     delay(beats[i] * tempo);
   } else {
     playNote(notes[i], beats[i] * tempo);
   }
   delay(tempo);
}
  unsigned long endTime = millis();
  unsigned long elapsedTime = endTime-startTime;
  float songDuration = elapsedTime / 1000.0;
  EEPROM.put(EEPROMbirthday, songDuration);
  lcd.setCursor(11,1);
  lcd.print(EEPROM.get(EEPROMbirthday, songDuration));
}

void playJingle(){
  unsigned long startTime = millis();
  lcd.clear();
  lcd.setCursor(2,0);
  lcd.print("Jingle Bells");
  Length = 26;
  char notes[] = "eeeeeeegcde fffffeeeeddedg";
  int beats[] = { 1, 1, 2, 1, 1, 2, 1, 1, 1, 1, 4, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2};
  tempo = 300;
  for (int i = 0; i < Length; i++) {
    if (notes[i] == ' ') {
      delay(beats[i] * tempo);
    } else {
      playNote2(notes[i], beats[i] * tempo);
    }
    delay(tempo / 2); 
  } 
  unsigned long endTime = millis();
  unsigned long elapsedTime = endTime-startTime;
  float songDuration = elapsedTime / 1000.0;
  EEPROM.put(EEPROMjingle, songDuration);
  lcd.setCursor(5,1);
  lcd.print(EEPROM.get(EEPROMjingle,songDuration));
}

void playTone(int tone, int duration) {

  for (long i = 0; i < duration * 1000L; i += tone * 2) {    
    digitalWrite(buzzer_pin, HIGH);
    delayMicroseconds(tone);
    digitalWrite(buzzer_pin, LOW);
    delayMicroseconds(tone);
  }
}

void playNote(char note, int duration) {

  char names[] = {'C', 'D', 'E', 'F', 'G', 'A', 'B',           

                 'c', 'd', 'e', 'f', 'g', 'a', 'b',

                 'x', 'y' };

  int tones[] = { 1915, 1700, 1519, 1432, 1275, 1136, 1014,

                 956,  834,  765,  593,  468,  346,  224,

                 655 , 715 };

  int SPEE = 5;

  for (int i = 0; i < 17; i++) {
     if (names[i] == note) {
     int newduration = duration/SPEE;
     playTone(tones[i], newduration);
   }
  }
}

void playNote2(char note, int duration) {
  char names[] = { 'c', 'd', 'e', 'f', 'g', 'a', 'b', 'C' };
  int tones[] = { 1915, 1700, 1519, 1432, 1275, 1136, 1014, 956 };
  for (int i = 0; i < 8; i++) {
    if (names[i] == note) {
      playTone(tones[i], duration);
    }
  }
}

void playGameOfThrones(){
  unsigned long startTime = millis();
  lcd.clear();
  lcd.setCursor(4,0);
  lcd.print("Game of");
  lcd.setCursor(2,1);
  lcd.print("Thrones");
  int NOTE_B0  = 31;
  int NOTE_C1  = 33;
  int NOTE_CS1 = 35;
  int NOTE_D1  = 37;
  int NOTE_DS1 = 39;
  int NOTE_E1  = 41;
  int NOTE_F1  = 44;
  int NOTE_FS1 = 46;
  int NOTE_G1  = 49;
  int NOTE_GS1 = 52;
  int NOTE_A1  = 55;
  int NOTE_AS1 = 58;
  int NOTE_B1  = 62;
  int NOTE_C2  = 65;
  int NOTE_CS2 = 69;
  int NOTE_D2  = 73;
  int NOTE_DS2 = 78;
  int NOTE_E2  = 82;
  int NOTE_F2  = 87;
  int NOTE_FS2 = 93;
  int NOTE_G2  = 98;
  int NOTE_GS2 = 104;
  int NOTE_A2  = 110;
  int NOTE_AS2 = 117;
  int NOTE_B2  = 123;
  int NOTE_C3  = 131;
  int NOTE_CS3 = 139;
  int NOTE_D3  = 147;
  int NOTE_DS3 = 156;
  int NOTE_E3  = 165;
  int NOTE_F3  = 175;
  int NOTE_FS3 = 185;
  int NOTE_G3  = 196;
  int NOTE_GS3 = 208;
  int NOTE_A3  = 220;
  int NOTE_AS3 = 233;
  int NOTE_B3  = 247;
  int NOTE_C4  = 262;
  int NOTE_CS4 = 277;
  int NOTE_D4  = 294;
  int NOTE_DS4 = 311;
  int NOTE_E4  = 330;
  int NOTE_F4  = 349;
  int NOTE_FS4 = 370;
  int NOTE_G4  = 392;
  int NOTE_GS4 = 415;
  int NOTE_A4  = 440;
  int NOTE_AS4 = 466;
  int NOTE_B4  = 494;
  int NOTE_C5  = 523;
  int NOTE_CS5 = 554;
  int NOTE_D5  = 587;
  int NOTE_DS5 = 622;
  int NOTE_E5  = 659;
  int NOTE_F5  = 698;
  int NOTE_FS5 = 740;
  int NOTE_G5  = 784;
  int NOTE_GS5 = 831;
  int NOTE_A5  = 880;
  int NOTE_AS5 = 932;
  int NOTE_B5  = 988;
  int NOTE_C6  = 1047;
  int NOTE_CS6 = 1109;
  int NOTE_D6  = 1175;
  int NOTE_DS6 = 1245;
  int NOTE_E6  = 1319;
  int NOTE_F6  = 1397;
  int NOTE_FS6 = 1480;
  int NOTE_G6  = 1568;
  int NOTE_GS6 = 1661;
  int NOTE_A6  = 1760;
  int NOTE_AS6 = 1865;
  int NOTE_B6  = 1976;
  int NOTE_C7  = 2093;
  int NOTE_CS7 = 2217;
  int NOTE_D7  = 2349;
  int NOTE_DS7 = 2489;
  int NOTE_E7  = 2637;
  int NOTE_F7  = 2794;
  int NOTE_FS7 = 2960;
  int NOTE_G7  = 3136;
  int NOTE_GS7 = 3322;
  int NOTE_A7  = 3520;
  int NOTE_AS7 = 3729;
  int NOTE_B7  = 3951;
  int NOTE_C8  = 4186;
  int NOTE_CS8 = 4435;
  int NOTE_D8  = 4699;
  int NOTE_DS8 = 4978;
  for(int i=0; i<4; i++)
    {
    tone(buzzer_pin, NOTE_G4);
    delay(500);
    noTone(buzzer_pin);
    tone(buzzer_pin, NOTE_C4);
    delay(500);
    noTone(buzzer_pin);
    tone(buzzer_pin, NOTE_DS4);
    delay(250);
    noTone(buzzer_pin);
    tone(buzzer_pin, NOTE_F4);
    delay(250);
    noTone(buzzer_pin);
    }
    for(int i=0; i<4; i++)
    {
    tone(buzzer_pin, NOTE_G4);
    delay(500);
    noTone(buzzer_pin);
    tone(buzzer_pin, NOTE_C4);
    delay(500);
    noTone(buzzer_pin);
    tone(buzzer_pin, NOTE_E4);
    delay(250);
    noTone(buzzer_pin);
    tone(buzzer_pin, NOTE_F4);
    delay(250);
    noTone(buzzer_pin);
    }
        tone(buzzer_pin, NOTE_G4);
        delay(500);
        noTone(buzzer_pin);
        tone(buzzer_pin, NOTE_C4);
        delay(500);
        tone(buzzer_pin, NOTE_DS4);
        delay(250);
        noTone(buzzer_pin);
        tone(buzzer_pin, NOTE_F4);
        delay(250);
        noTone(buzzer_pin);
        tone(buzzer_pin, NOTE_D4);
        delay(500);
        noTone(buzzer_pin);
    for(int i=0; i<3; i++)
    {
    tone(buzzer_pin, NOTE_G3);
    delay(500);
    noTone(buzzer_pin);
    tone(buzzer_pin, NOTE_AS3);
    delay(250);
    noTone(buzzer_pin);
    tone(buzzer_pin, NOTE_C4);
    delay(250);
    noTone(buzzer_pin);
    tone(buzzer_pin, NOTE_D4);
    delay(500);
    noTone(buzzer_pin);
    }//
        tone(buzzer_pin, NOTE_G3);
        delay(500);
        noTone(buzzer_pin);
        tone(buzzer_pin, NOTE_AS3);
        delay(250);
        noTone(buzzer_pin);
        tone(buzzer_pin, NOTE_C4);
        delay(250);
        noTone(buzzer_pin);
        tone(buzzer_pin, NOTE_D4);
        delay(1000);
        noTone(buzzer_pin);
         
        tone(buzzer_pin, NOTE_F4);
        delay(1000);
        noTone(buzzer_pin);
        tone(buzzer_pin, NOTE_AS3);
        delay(1000);
        noTone(buzzer_pin);
        tone(buzzer_pin, NOTE_DS4);
        delay(250);
        noTone(buzzer_pin);
        tone(buzzer_pin, NOTE_D4);
        delay(250);
        noTone(buzzer_pin);
        tone(buzzer_pin, NOTE_F4);
        delay(1000);
        noTone(buzzer_pin);
        tone(buzzer_pin, NOTE_AS3);
        delay(1000);
        noTone(buzzer_pin);
        tone(buzzer_pin, NOTE_DS4);
        delay(250);
        noTone(buzzer_pin);
        tone(buzzer_pin, NOTE_D4);
        delay(250);
        noTone(buzzer_pin);
        tone(buzzer_pin, NOTE_C4);
        delay(500);
        noTone(buzzer_pin);
    for(int i=0; i<3; i++)
    {
    tone(buzzer_pin, NOTE_GS3);
    delay(250);
    noTone(buzzer_pin);
    tone(buzzer_pin, NOTE_AS3);
    delay(250);
    noTone(buzzer_pin);
    tone(buzzer_pin, NOTE_C4);
    delay(500);
    noTone(buzzer_pin);
    tone(buzzer_pin, NOTE_F3);
    delay(500);
    noTone(buzzer_pin);
    }
          tone(buzzer_pin, NOTE_G4);
          delay(1000);
          noTone(buzzer_pin);
          tone(buzzer_pin, NOTE_C4);
          delay(1000);
          noTone(buzzer_pin);
          tone(buzzer_pin, NOTE_DS4);
          delay(250);
          noTone(buzzer_pin);
          tone(buzzer_pin, NOTE_F4);
          delay(250);
          noTone(buzzer_pin);
          tone(buzzer_pin, NOTE_G4);
          delay(1000);
          noTone(buzzer_pin);
          tone(buzzer_pin, NOTE_C4);
          delay(1000);
          noTone(buzzer_pin);
          tone(buzzer_pin, NOTE_DS4);
          delay(250);
          noTone(buzzer_pin);
          tone(buzzer_pin, NOTE_F4);
          delay(250);
          noTone(buzzer_pin);
          tone(buzzer_pin, NOTE_D4);
          delay(500);
          noTone(buzzer_pin);
    for(int i=0; i<4; i++)
    {
    tone(buzzer_pin, NOTE_G3);
    delay(500);
    noTone(buzzer_pin);
    tone(buzzer_pin, NOTE_AS3);
    delay(250);
    noTone(buzzer_pin);
    tone(buzzer_pin, NOTE_C4);
    delay(250);
    noTone(buzzer_pin);
    tone(buzzer_pin, NOTE_D4);
    delay(500);
    noTone(buzzer_pin);
    }
    unsigned long endTime = millis();
    unsigned long elapsedTime = endTime-startTime;
    float songDuration = elapsedTime / 1000.0;
    EEPROM.put(EEPROMgame, songDuration);
    lcd.setCursor(11,1);
    lcd.print(EEPROM.get(EEPROMgame,songDuration));
}
