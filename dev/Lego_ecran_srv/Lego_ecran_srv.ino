

/*
Lego Marc

Ecran Nokia 5110
15/11/2016: implantation code, graphique, rotation, attaque
24/11/2016: rajout Servomoteur + led 13

*/
#include "U8glib.h"


U8GLIB_PCD8544 u8g(3, 4, 7, 5, 6);  // CLK=3, DIN=4, CE=7, DC=5, RST=6, light=11, VCC=+3,3

#include <Servo.h>
Servo myservo;  // create servo object to control a servo
int pos = 0;    // variable to store the servo position
int sense =0; // 0 sense aiguille 1 inverse
int compt = 0; //compteur srv

#define backlight_pin 11

byte Menu = 0; //menu pour défilement

#define LED 13       //patte led

//nasa

const uint8_t brainy_bitmap[] PROGMEM ={ //logo Nasa
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3D, 0xE0,
0x00, 0x00, 0x00, 0x00, 0xFD, 0xF8, 0x00, 0x00, 0x00, 0x03, 0xFF, 0xDE, 0x00, 0x00, 0x00, 0x07,
0xFA, 0xDF, 0x00, 0x00, 0x00, 0x0F, 0xFE, 0xDF, 0xC0, 0x00, 0x00, 0x1F, 0xC9, 0xFF, 0xE0, 0x00,
0x00, 0x3E, 0x66, 0xFF, 0xE0, 0x00, 0x00, 0x7C, 0x0F, 0xFF, 0xF0, 0x00, 0x00, 0x79, 0xC7, 0xDF,
0xF8, 0x20, 0x00, 0xF8, 0xA3, 0xDF, 0xF8, 0x40, 0x01, 0xFA, 0x19, 0xFF, 0xFD, 0x80, 0x01, 0xFB,
0x3C, 0xFF, 0xFF, 0x00, 0x01, 0xFB, 0xFE, 0x7F, 0xFE, 0x00, 0x03, 0xFB, 0xFF, 0x3F, 0xFE, 0x00,
0x03, 0xF9, 0xFF, 0x1F, 0xFE, 0x00, 0x03, 0xF9, 0xFF, 0x8F, 0xFF, 0x00, 0x07, 0xF9, 0xFF, 0xCF,
0xFF, 0x00, 0x04, 0x30, 0x87, 0xC1, 0x87, 0x00, 0x04, 0x10, 0x87, 0x81, 0x87, 0x00, 0x06, 0x10,
0x83, 0x01, 0x83, 0x00, 0x06, 0x02, 0x03, 0x01, 0x83, 0x80, 0x06, 0x02, 0x03, 0x01, 0x03, 0x80,
0x06, 0x03, 0x01, 0x01, 0x03, 0x80, 0x06, 0x03, 0x01, 0x80, 0x01, 0x80, 0x06, 0x03, 0x01, 0x20,
0x01, 0x80, 0x06, 0x43, 0x00, 0x00, 0x21, 0x00, 0x04, 0x00, 0x00, 0x00, 0x20, 0x00, 0x07, 0xFE,
0x47, 0x06, 0x7F, 0x00, 0x07, 0xFF, 0xE7, 0xFF, 0x5F, 0x00, 0x03, 0xFF, 0xE3, 0xFF, 0x43, 0x00,
0x03, 0xFF, 0xF1, 0xFF, 0x02, 0x00, 0x03, 0xFE, 0x78, 0xFC, 0x32, 0x00, 0x01, 0xCE, 0x78, 0xFF,
0x36, 0x00, 0x01, 0x0F, 0xFF, 0xFD, 0x0C, 0x00, 0x01, 0xC9, 0xFF, 0xCC, 0x44, 0x00, 0x00, 0xEF,
0x3F, 0x80, 0x40, 0x00, 0x00, 0x7E, 0xFB, 0xF0, 0xF8, 0x00, 0x00, 0x7E, 0xBB, 0xFF, 0xF0, 0x00,
0x00, 0x3F, 0xFF, 0xFF, 0xE0, 0x00, 0x00, 0x3E, 0x7F, 0xFE, 0xE0, 0x00, 0x00, 0x0E, 0x7F, 0xFF,
0xC0, 0x00, 0x00, 0x07, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x03, 0xFF, 0xFE, 0x00, 0x00, 0x00, 0x00,
0xFF, 0xF8, 0x00, 0x00, 0x00, 0x00, 0x3F, 0xE0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xFF, 0x42, 0x42, 0x42, 0xFF, 0x45, 0x45, 0x45, 0xFF,
0x46, 0x46, 
};
 
void draw4(void) {
  u8g.drawBitmapP( 37, 0, 6, 50, brainy_bitmap);  // put bitmap
  u8g.setFont(u8g_font_profont11);  // select font
  u8g.drawStr(0, 15, "Marc ");  // put string of display at position X, Y
  u8g.drawStr(0, 35, "Attaque: ");
  u8g.setPrintPos(15, 15);  // set position
  
  delay(2000);

}

//Rotation
uint8_t offset = 0;

void draw2(void) {
  // graphic commands to redraw the complete screen should be placed here  
  u8g.setFont(u8g_font_unifont);
  u8g.drawStr( 0+0, 20+0, "Marc!");
  u8g.drawStr( 0+2, 20+16, "Attaque!");
  
  u8g.drawBox(0, 0, 3, 3);
  u8g.drawBox(u8g.getWidth()-6, 0, 6, 6);
  u8g.drawBox(u8g.getWidth()-9, u8g.getHeight()-9, 9, 9);
  u8g.drawBox(0, u8g.getHeight()-12, 12, 12);  
}

void rotate(void) {
  static  uint8_t dir = 0;
  static  unsigned long next_rotation = 0;
  
  if ( next_rotation < millis() )
  {
    switch(dir) {
      case 0: u8g.undoRotation(); break;
      case 1: u8g.setRot90(); break;
      case 2: u8g.setRot180(); break;
      case 3: u8g.setRot270(); offset = ( offset + 1 ) & 0x0f; Menu=100; u8g.undoRotation(); break;
          }
    
    dir++;
    dir &= 3;
    next_rotation = millis();
    next_rotation += 1000;
  }
}

//Graphique
void u8g_prepare(void) {
  u8g.setFont(u8g_font_6x10);
  u8g.setFontRefHeightExtendedText();
  u8g.setDefaultForegroundColor();
  u8g.setFontPosTop();
}

void u8g_box_frame(uint8_t a) {
  u8g.drawStr( 0, 0, "MarcBox");
  u8g.drawBox(5,10,20,10);
  u8g.drawBox(10+a,15,30,7);
  u8g.drawStr( 0, 30, "MarcFrame");
  u8g.drawFrame(5,10+30,20,10);
  u8g.drawFrame(10+a,15+30,30,7);
}

void u8g_disc_circle(uint8_t a) {
  u8g.drawStr( 0, 0, "MarcDisc");
  u8g.drawDisc(10,18,9);
  u8g.drawDisc(24+a,16,7);
  u8g.drawStr( 0, 30, "MarcCircle");
  u8g.drawCircle(10,18+30,9);
  u8g.drawCircle(24+a,16+30,7);
}

void u8g_r_frame(uint8_t a) {
  u8g.drawStr( 0, 0, "MarcRFrame/Box");
  u8g.drawRFrame(5, 10,40,30, a+1);
  u8g.drawRBox(50, 10,25,40, a+1);
}

void u8g_string(uint8_t a) {
  u8g.drawStr(30+a,31, " 0");
  u8g.drawStr90(30,31+a, " 90");
  u8g.drawStr180(30-a,31, " 180");
  u8g.drawStr270(30,31-a, " 270");
}

void u8g_line(uint8_t a) {
  u8g.drawStr( 0, 0, "MarcLine");
  u8g.drawLine(7+a, 10, 40, 55);
  u8g.drawLine(7+a*2, 10, 60, 55);
  u8g.drawLine(7+a*3, 10, 80, 55);
  u8g.drawLine(7+a*4, 10, 100, 55);
}

void u8g_triangle(uint8_t a) {
  uint16_t offset = a;
  u8g.drawStr( 0, 0, "MarcTriangle");
  u8g.drawTriangle(14,7, 45,30, 10,40);
  u8g.drawTriangle(14+offset,7-offset, 45+offset,30-offset, 57+offset,10-offset);
  u8g.drawTriangle(57+offset*2,10, 45+offset*2,30, 86+offset*2,53);
  u8g.drawTriangle(10+offset,40+offset, 45+offset,30+offset, 86+offset,53+offset);
}

void u8g_ascii_1() {
  char s[2] = " ";
  uint8_t x, y;
  u8g.drawStr( 0, 0, "ASCII Marc1");
  for( y = 0; y < 6; y++ ) {
    for( x = 0; x < 16; x++ ) {
      s[0] = y*16 + x + 32;
      u8g.drawStr(x*7, y*10+10, s);
    }
  }
}

void u8g_ascii_2() {
  char s[2] = " ";
  uint8_t x, y;
  u8g.drawStr( 0, 0, "ASCII Marc2");
  for( y = 0; y < 6; y++ ) {
    for( x = 0; x < 16; x++ ) {
      s[0] = y*16 + x + 160;
      u8g.drawStr(x*7, y*10+10, s);
    }
  }
}

void u8g_extra_page(uint8_t a)
{
  if ( u8g.getMode() == U8G_MODE_HICOLOR || u8g.getMode() == U8G_MODE_R3G3B2) {
    /* draw background (area is 128x128) */
    u8g_uint_t r, g, b;
    b = a << 5;
    for( g = 0; g < 64; g++ )
    {
      for( r = 0; r < 64; r++ )
      {
	u8g.setRGB(r<<2, g<<2, b );
	u8g.drawPixel(g, r);
      }
    }
    u8g.setRGB(255,255,255);
    u8g.drawStr( 66, 0, "Color Marc");
  }
  else if ( u8g.getMode() == U8G_MODE_GRAY2BIT )
  {
    u8g.drawStr( 66, 0, "Gray Marc");
    u8g.setColorIndex(1);
    u8g.drawBox(0, 4, 64, 32);    
    u8g.drawBox(70, 20, 4, 12);
    u8g.setColorIndex(2);
    u8g.drawBox(0+1*a, 4+1*a, 64-2*a, 32-2*a);
    u8g.drawBox(74, 20, 4, 12);
    u8g.setColorIndex(3);
    u8g.drawBox(0+2*a, 4+2*a, 64-4*a, 32-4*a);
    u8g.drawBox(78, 20, 4, 12);
  }
  else
  {
    u8g.drawStr( 0, 12, "Marc2x2");
    u8g.setScale2x2();
    u8g.drawStr( 0, 6+a, "Marc2x2");
    u8g.undoScale();
    Menu= 100; //pour sortir de la boucle
   
  }
}


uint8_t draw_state = 0;

void draw(void) {
  u8g_prepare();
  switch(draw_state >> 3) {
    case 0: u8g_box_frame(draw_state&7); break;
    case 1: u8g_disc_circle(draw_state&7); break;
    case 2: u8g_r_frame(draw_state&7); break;
    case 3: u8g_string(draw_state&7); break;
    case 4: u8g_line(draw_state&7); break;
    case 5: u8g_triangle(draw_state&7); break;
    case 6: u8g_ascii_1(); break;
    case 7: u8g_ascii_2(); break;
    case 8: u8g_extra_page(draw_state&7); break;
    //case 9: Menu= Menu+1; Serial.println(Menu); break;
  }
}

void setup(void) {
 myservo.attach(9);  // attaches the servo on pin 9 to the servo object
  //clignotement led
   
   
   
  // flip screen, if required
  //u8g.setRot180();

  
//  pinMode(13, OUTPUT);           
//  digitalWrite(13, HIGH);  
  
  analogWrite(backlight_pin, 50);  /* Set the Backlight intensity */
  Serial.begin(9600);          //  setup serial

}

void loop(void) {
  digitalWrite(LED,-(digitalRead(LED)));
  
  //Servo moteur
  compt += 1; //compteur nb cycle
  
  if (compt < 3){
 if (sense == 0){
 pos += 10; 
    // in steps of 1 degree
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    
    
    if (pos == 180){sense = 1;} 
   
  }
  }
  else
  compt = 0; //raz compteur
  
  if (compt < 3){
 if (sense == 1){
 pos -= 10; 
    // in steps of 1 degree
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    if (pos == 0){sense = 0;} 
   
  }
  }
  else
  compt = 0; //raz compteur
  
  
  // picture loop  
  u8g.firstPage();  

 if (Menu==0){Menu = 1;}
  
  if (Menu == 1){
  do {
    draw();
  } while( u8g.nextPage() );
  
  // increase the state
  draw_state++;
  if ( draw_state >= 9*8 )
    draw_state = 0;
  
  // rebuild the picture after some delay
  delay(150);
}

if(Menu == 2){ //rotate attaque
   rotate();
  u8g.firstPage();  
  do {
    draw2();
  } while( u8g.nextPage() );
  
  // rebuild the picture after some delay
  delay(100);
  }
 
if(Menu == 3){  //Nasa
  
  u8g.firstPage();  
  do {
    draw4();
  } while( u8g.nextPage() );
  
  
  
  Menu = 100;
  }

if( Menu == 100){ //sortir boucle + nb aleatoire
 
 Menu = random(0,4);
 Serial.print("Menu =");
 Serial.println(Menu);
  }



}


