#include "DigiKeyboard.h"

#define KEY_A_DOWN 254//Code \ Код: 254 | Remote button \ Кнопка на пульте: - | Action \ Действие: VOL - 
#define KEY_A_UP 250//Code \ Код: 250 | Remote button \ Кнопка на пульте: + | Action \ Действие: VOL +
#define KEY_PAGE_UP 242//Code \ Код: 242 | Remote button \ Кнопка на пульте: << | Action \ Действие: PageUp
#define KEY_PAGE_DOWN 240//Code \ Код: 240 | Remote button \ Кнопка на пульте: >> | Action \ Действие: pageDown
#define KEY_SPACEBAR 252//Code \ Код: 252 | Remote button \ Кнопка на пульте: >= | Action \ Действие: SPACE  
#define KEY_MUTE 246//Code \ Код: 246 | Remote button \ Кнопка на пульте: ch  | Action \ Действие: Mute Ctr + M
#define KEY_POWER 249//Code \ Код: 249 | Remote button \ Кнопка на пульте: EQ | Action \ Действие: On\Off
#define KEY_F11K 251//Code \ Код: 251 | Remote button \ Кнопка на пульте: 200+ | Action \ Действие: F11
#define KEY_ESC 243//Code \ Код: 243 | Remote button \ Кнопка на пульте: 1 | Action \ Действие: ESC
#define KEY_EXIT 241//Code \ Код: 241 | Remote button \ Кнопка на пульте: 2 | Action \ Действие: EXIT  ALT + X
#define KEY_TAB 247//Code \ Код: 247 | Remote button \ Кнопка на пульте: 3 | Action \ Действие: TAB  TAB
#define KEY_ENTER 245//Code \ Код: 245 | Remote button \ Кнопка на пульте: 6 | Action \ Действие: ENTER  ENTER
#define KEY_BACK 244//Code \ Код: 244 | Remote button \ Кнопка на пульте: 7 | Action \ Действие: Backspace 

#define REL_PIN 0
#define IR_PIN 2
#define DATA_SIZE 20
#define START_BIT 4000
int i, s, data[DATA_SIZE];

void setup() {
  pinMode(IR_PIN, INPUT);
  pinMode(REL_PIN, OUTPUT); 
  digitalWrite(REL_PIN, HIGH);
}
void loop() {
  DigiKeyboard.update();
  DigiKeyboard.sendKeyStroke(0);

  
  s = pulseIn(IR_PIN, HIGH);
  if(s > START_BIT)
  {
    for(i = 0; i < DATA_SIZE; i++)
      data[i] = pulseIn(IR_PIN, HIGH);
    
    int result = 0;
    for(i = 12; i < DATA_SIZE; i++)
      if(data[i] > 1000)
        result |= (1 << (DATA_SIZE - 1 - i));


switch(result){
      case KEY_A_DOWN: DigiKeyboard.sendKeyStroke(KEY_ARROW_DOWN); break; //254 Кнопка -  VOL -
      case KEY_A_UP: DigiKeyboard.sendKeyStroke(KEY_ARROW_UP); break; //250 Кнопка +  VOL +
      case KEY_PAGE_UP: DigiKeyboard.sendKeyStroke(75); break; //242 Кнопка << PageUp
      case KEY_PAGE_DOWN: DigiKeyboard.sendKeyStroke(78); break; //240 Кнопка >> pageDown
      case KEY_SPACEBAR: DigiKeyboard.sendKeyStroke(KEY_SPACE); break; //252 Кнопка пауза пробел  SPACE >= 
      case KEY_MUTE: DigiKeyboard.sendKeyStroke(KEY_M , MOD_CONTROL_LEFT); break; //246 Кнопка Mute  ch
      case KEY_POWER: 
           digitalWrite(REL_PIN, LOW);
           delay(200);
           digitalWrite(REL_PIN, HIGH);
      break; //249 Кнопка Включения/Выключения  EQ
      case KEY_F11K: DigiKeyboard.sendKeyStroke(KEY_F11); break; //251  F11  display 200+
      case KEY_ESC: DigiKeyboard.sendKeyStroke(41); break; //243  ESC 1
      case KEY_EXIT: DigiKeyboard.sendKeyStroke(KEY_X , MOD_ALT_LEFT); break; //241  EXIT  ALT + X 2

      case KEY_TAB: DigiKeyboard.sendKeyStroke(43); break; //247  TAB  TAB 43 3
      case KEY_ENTER: DigiKeyboard.sendKeyStroke(40); break;//245  ENTER  ENTER 40 6
      case KEY_BACK: DigiKeyboard.sendKeyStroke(42); break;//244 Backspace  40 7
}
          //DigiKeyboard.print(result,'\n'); //For Debug
          //DigiKeyboard.delay(100);
  }
   delay(100);
}
