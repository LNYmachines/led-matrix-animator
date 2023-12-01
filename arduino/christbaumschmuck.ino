#define latchPin 2
#define clockPin 3
#define dataPin 4
#define myTimeout 100
const byte PROGMEM led_lookup[] = {
    0b01111000, //A1
    0b01110100, //A2
    0b01110010, //A3
    0b01110001, //A4
    0b10111000, //B1
    0b10110100, //B2
    0b10110010, //B3
    0b10110001, //B4
    0b11011000, //C1
    0b11010100, //C2
    0b11010010, //C3
    0b11010001, //C4
    0b11101000, //D1
    0b11100100, //D2
    0b11100010, //D3
    0b11100001, //D4
};

//animation goes here

const byte animation_size = sizeof(animation)/sizeof(animation[0]);
void setup() {
  // put your setup code here, to run once:
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  digitalWrite(dataPin, LOW);
  digitalWrite(clockPin, LOW);
  digitalWrite(latchPin, LOW);
}

byte led_bitmask(byte index, byte state){
  byte bitmask = 0;
  if (state){
    //bitmask = pgm_read_byte(&led_lookup[index]);
    bitmask = pgm_read_byte(&led_lookup[index]);
  } else {
      bitmask = 0b11110000;
    }
  return bitmask;
}

void loop() {
  for (byte frame=0; frame < animation_size ; frame++){
    long myTimer = millis();
    while (millis() < myTimer + myTimeout){
      for (byte j=0; j <16; j++){
        // each frame is now a hex value, read word from PROGMEM and check bit
        byte currentBit = (pgm_read_word(&animation[frame]) >> j) & 1;
        byte bitmask = led_bitmask(j, currentBit);
        digitalWrite(latchPin, LOW);
        for (byte i=0; i<8; i++){

          digitalWrite(dataPin, (bitmask >> i) & 1);
          digitalWrite(clockPin, HIGH);
          digitalWrite(clockPin, LOW);
        }
        digitalWrite(latchPin, HIGH);
      }
    }
  }
}
