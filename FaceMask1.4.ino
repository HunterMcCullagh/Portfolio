//August 11/2020
//Hunter McCullagh
//Mask Version 1.4
//Turns Modes Into Procedures


#include <Adafruit_NeoMatrix.h>
#include <gamma.h>
#include <Adafruit_NeoPixel.h>

#define lengthof(A) ((sizeof((A))/sizeof((A)[0])))

const PROGMEM uint8_t mouth_0[8][8] = {
    {1,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0},
    {6,6,6,6,6,6,6,6},
    {6,6,6,6,6,6,6,6},
    {0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0}
};

const PROGMEM uint8_t mouth_4[8][8] = {
    {1,0,6,6,6,6,0,0},
    {0,6,0,0,0,0,6,0},
    {6,0,0,0,0,0,0,6},
    {6,0,0,0,0,0,0,6},
    {6,0,0,0,0,0,0,6},
    {6,0,0,0,0,0,0,6},
    {0,6,0,0,0,0,6,0},
    {0,0,6,6,6,6,0,0}
};

const PROGMEM uint8_t mouth_3[8][8] = {
    {1,0,0,0,0,0,0,0},
    {0,0,6,6,6,6,0,0},
    {0,6,0,0,0,0,6,0},
    {6,0,0,0,0,0,0,6},
    {6,0,0,0,0,0,0,6},
    {0,6,0,0,0,0,6,0},
    {0,0,6,6,6,6,0,0},
    {0,0,0,0,0,0,0,0}
};

const PROGMEM uint8_t mouth_2[8][8] = {
    {1,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0},
    {0,6,6,6,6,6,6,0},
    {6,0,0,0,0,0,0,6},
    {6,0,0,0,0,0,0,6},
    {0,6,6,6,6,6,6,0},
    {0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0}
};

const PROGMEM uint8_t mouth_1[8][8] = {
    {1,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0},
    {0,0,0,6,6,0,0,0},
    {6,6,6,0,0,6,6,6},
    {6,6,6,0,0,6,6,6},
    {0,0,0,6,6,0,0,0},
    {0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0}
};

const PROGMEM uint8_t mouth_smile[8][8] = {
    {1,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0},
    {6,0,0,0,0,0,0,6},
    {6,6,0,0,0,0,6,6},
    {0,6,6,6,6,6,6,0},
    {0,0,6,6,6,6,0,0},
    {0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0}
};

const PROGMEM uint8_t love1[8][8] = {
    {9,9,9,9,9,9,9,9},
    {9,9,9,9,9,9,9,9},
    {0,0,0,9,9,0,0,0},
    {0,0,0,9,9,0,0,0},
    {0,0,0,9,9,0,0,0},
    {0,0,0,9,9,0,0,0},
    {9,9,9,9,9,9,9,9},
    {9,9,9,9,9,9,9,9}
};

const PROGMEM uint8_t love2[8][8] = {
    {9,0,0,0,0,0,0,0},
    {0,9,9,0,0,9,9,0},
    {9,0,0,9,9,0,0,9},
    {9,0,0,0,0,0,0,9},
    {9,0,0,0,0,0,0,9},
    {0,9,0,0,0,0,9,0},
    {0,0,9,0,0,9,0,0},
    {0,0,0,9,9,0,0,0}
};

const PROGMEM uint8_t love3[8][8] = {
    {9,9,0,0,0,0,9,9},
    {9,9,0,0,0,0,9,9},
    {9,9,0,0,0,0,9,9},
    {9,9,0,0,0,0,9,9},
    {9,9,0,0,0,0,9,9},
    {9,9,0,0,0,0,9,9},
    {9,9,9,9,9,9,9,9},
    {9,9,9,9,9,9,9,9}
};

const PROGMEM uint8_t example[8][8] = {
    {3,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0}
};

short emotions[5] = {(short)mouth_1,(short)mouth_2,(short)mouth_3,(short)mouth_4 ,(short)mouth_smile};
short love[3] = {(short)love1,(short)love2,(short)love3};

uint16_t palette[10] = {};
Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(8, 8, 6,
  NEO_MATRIX_BOTTOM     + NEO_MATRIX_RIGHT +
  NEO_MATRIX_ROWS    + NEO_MATRIX_ZIGZAG,
  NEO_GRB            + NEO_KHZ800);


void drawImage(short image_addr){
    for(int x = 0; x<8; x++){
        for(int y = 0; y<8; y++){
            uint8_t index = pgm_read_byte(image_addr+x+y*8);
            matrix.drawPixel(x, y, palette[index]); 
        }
    }

    matrix.show();
}

int buttonPin = 8;


void setup() {
    matrix.begin();

    palette[0] = matrix.Color(0,0,0);
    palette[1] = matrix.Color(255,0,0);
    palette[2] = matrix.Color(0,255,0);
    palette[3] = matrix.Color(0,0,255);
    palette[4] = matrix.Color(0,255,255);
    palette[5] = matrix.Color(255,0,255);
    palette[6] = matrix.Color(50,255,255);
    palette[7] = matrix.Color(255,255,255);
    palette[8] = matrix.Color(64,64,64);
    palette[9] = matrix.Color(255,8,127);

    pinMode(buttonPin, INPUT_PULLUP);  
    Serial.begin(9600);
}


int i = 0; // mode counter
int j = 0; //emotions counter
int k = 0; //♥ Counter


void loop() {
    
     if(i==0)
    {
      smile();
    }

    else if(i==1)
    {
      loving();
    }

    
    else if(i==2)
    {
       talk();
    }
   

    if(digitalRead(buttonPin)==LOW)
    {
      Serial.print("here"); 
      i++;
      j=0;
      k=0;

      if (i>=3)
      i-=3;
      delay(200);
    }
   
}

void smile()
{
  drawImage(emotions[j]);
      delay(500);
      j++;
      if (j>=5)
        j-=5;

}

void talk()
{
  float vol = 0;
  const uint16_t samples = 128;
  float nvol = 0;
  int previous_peak = -1;
  int pop_detection = 0;
  bool smiling = false;
  unsigned long smiletimer = 0;
  unsigned long last_face = 0;
  
  for (int i = 0; i<samples; i++){
          auto analog = analogRead(A1);
          auto micline = abs(analog - 512);

          nvol = max(micline, nvol);
      }

        vol = (nvol + 1.0*vol)/2.0;

        if(nvol > 200){
            pop_detection += 1;
            if(pop_detection > 2) {
                smiling = false;
                last_face = millis();
            }
        } 
        else {
          if(pop_detection > 0 && pop_detection <= 2) {
              if(millis() > last_face + 500){
                  smiling = true;
                  smiletimer = millis() + 2000;
              }
          }
          pop_detection = 0;
      }

      if(millis() > smiletimer) smiling = false;

      if(smiling){
          drawImage((short)example);//blank face
      } else if(vol < 200){
          drawImage((short)mouth_0);
      } else if(vol < 250){
          drawImage((short)mouth_1);
      } else if(vol < 350){
          drawImage((short)mouth_2);
      } else if(vol < 450){
          drawImage((short)mouth_3);
      }  else {
          drawImage((short)mouth_4);
      }

}

 void loving()
{
  drawImage(love[k]);
      delay(500);
      k++;
      if (k>=3)
        k-=3;

}
