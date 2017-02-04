/*
 * SPI TFT関連
 *
 * Copyright (c) 2016 Wakayama.rb Ruby Board developers
 *
 * This software is released under the MIT License.
 * https://github.com/wakayamarb/wrbb-v2lib-firm/blob/master/MITL
 *
 */
#define PROGMEM
#include <Arduino.h>
#include <SPI.h>
#include "SPI_TFT.h"
#include "font.h"
#include <avr/pgmspace.h>

static SPISettings settings;
static uint8_t chip_select_asserted = 0;
void spiSend(uint8_t b) {
  SPI.transfer(b);
}

void TFT_chipSelectHigh(void) {
  digitalWrite(TFT_CHIP_SELECT_PIN, HIGH);
}
void TFT_chipSelectLow(void) {
  digitalWrite(TFT_CHIP_SELECT_PIN, LOW);
}
void TFT_cmd(uint8_t cmd) {
  rs_Low();
  // select card
  TFT_chipSelectLow();
  spiSend(cmd);
  // send argument
  TFT_chipSelectHigh();
  rs_High();
}
void TFT_dat(uint8_t data) {
  rs_High(); 
  // select card
  TFT_chipSelectLow();
  spiSend(data);
  // send argument
  TFT_chipSelectHigh();
}
void TFT_dat16(uint16_t data) {
  rs_High(); 
  // select card
  TFT_chipSelectLow();
  spiSend((uint8_t)(data>>8));
  spiSend((uint8_t)data);
  // send argument
  TFT_chipSelectHigh();
}
void TFT_gram(uint16_t gram) {
  // select card
  TFT_chipSelectLow();
  spiSend((uint8_t)(gram>>8));
  spiSend((uint8_t)gram);
  // send argument
  TFT_chipSelectHigh();
}
void TFT_rect(uint16_t x,  uint16_t width, uint16_t y,  uint16_t height)
{

	TFT_cmd(0x2A);				/* Horizontal RAM Start ADDR */
	TFT_dat(( x)>>8);
	TFT_dat( x);
	TFT_dat((width)>>8);
	TFT_dat( width);

	TFT_cmd(0x2B);				/* Horizontal RAM Start ADDR */
	TFT_dat(( y)>>8);
	TFT_dat( y);
	TFT_dat((height)>>8);
	TFT_dat( height);

	TFT_cmd(0x2C);				/* Write Data to GRAM */

}
uint8_t TFT_spiinit() {
//  uint8_t sckRateID = 1;
  // set pin modes
  pinMode(TFT_CHIP_SELECT_PIN, OUTPUT);
  digitalWrite(TFT_CHIP_SELECT_PIN, HIGH);

  pinMode(SPI_MISO_PIN, INPUT);
  pinMode(SPI_MOSI_PIN, OUTPUT);
  pinMode(SPI_SCK_PIN, OUTPUT);
  pinMode(TFT_RES_PIN, OUTPUT);
  pinMode(TFT_RS_PIN, OUTPUT);
  SPI.begin();
  settings = SPISettings(400000, MSBFIRST, SPI_MODE0);
  SPI.beginTransaction(settings);
  return true; //

}
void TFT_reset(){

	res_High();
	TFT_chipSelectHigh();
	sck_High();
	delay(10);
	res_Low();
	delay(10);
	res_High();
 	delay(125);
 }
void TFT_clear(uint16_t color){
	volatile uint32_t n;
	TFT_rect(0,  MAX_X-1,0, MAX_Y-1);
	n = (uint32_t)(MAX_X) * (MAX_Y);

	do {
		TFT_gram(color);
	} while (--n);	
}
int TFT_init(){
	
	TFT_spiinit();
	delay(100);
	TFT_reset();
	/* Initialize ILI9341 */
	TFT_cmd(0x11);					/* Sleep out */
	delay(120); 

	TFT_cmd(0xCB); 					/*  ILI9341 Internal Timings Fine Adjustments */
    TFT_dat(0x01);
	
	TFT_cmd(0xEF);
	TFT_dat(0x03);
	TFT_dat(0x80);
	TFT_dat(0x02);
		
	TFT_cmd(0xCF);
	TFT_dat(0x00);
	TFT_dat(0xAA);
	TFT_dat(0xB0);

	TFT_cmd(0xED);
	TFT_dat(0x67);
	TFT_dat(0x03);
	TFT_dat(0x12);
	TFT_dat(0x81);

	TFT_cmd(0xE8);
	TFT_dat(0x85); 
	TFT_dat(0x00);
	TFT_dat(0x7A);

	TFT_cmd(0x3A); 					/* RGB & CPU 18bit 0x66 / 16bit 0x55 */
    TFT_dat(0x55);
		
	TFT_cmd(0xF6);					/* Interface control */
    TFT_dat(0x01);
    TFT_dat(0x30);
    TFT_dat(0x00);

	TFT_cmd(0xCB);
	TFT_dat(0x39);
	TFT_dat(0x2C);
	TFT_dat(0x00);
	TFT_dat(0x34);
	TFT_dat(0x02);

	TFT_cmd(0xF7);
	TFT_dat(0x20);

	TFT_cmd(0xEA);
	TFT_dat(0x00);
	TFT_dat(0x00);

	TFT_cmd(0xC0);					/* Power control */
	TFT_dat(0x21);					/* VRH[5:0] */

	TFT_cmd(0xC1);					/* Power control */
	TFT_dat(0x11);					/* SAP[2:0];BT[3:0] */

	TFT_cmd(0xC5);					/* Vcomh & Vcoml control */
	TFT_dat(0x20);
	TFT_dat(0x3C);

	TFT_cmd(0xC7);					/* vcom adjust control */
	TFT_dat(0xC1);

	TFT_cmd(0x3A);
	TFT_dat(0x55);

	TFT_cmd(0x36);					/* Memory Access Control */
	TFT_dat(0xE8);   

	TFT_cmd(0xB1);           
	TFT_dat(0x00);
	TFT_dat(0x12);
	TFT_cmd(0xB4);           
	TFT_dat(0x00);
	TFT_dat(0x00);
	TFT_cmd(0xB6);           
	TFT_dat(0x0A);
	TFT_dat(0x82);					/* 0x02 background black,0x82 background white */
	TFT_dat(0x27);
	TFT_dat(0x00);

	TFT_cmd(0xF2);					/* 3Gamma Function Disable */ 
    TFT_dat(0x00);

	TFT_cmd(0x26); 					/* Gamma select G2.2 */
	TFT_dat(0x01);

	TFT_cmd(0xE0);					/* Positive  gamma */
	TFT_dat(0x0F);
	TFT_dat(0x17);
	TFT_dat(0x16);
	TFT_dat(0x0C);
	TFT_dat(0x10);
	TFT_dat(0x09);
	TFT_dat(0x45);
	TFT_dat(0xA9);
	TFT_dat(0x33);
	TFT_dat(0x08);
	TFT_dat(0x0D);
	TFT_dat(0x03);
	TFT_dat(0x00);
	TFT_dat(0x00);
	TFT_dat(0x00);
		
	TFT_cmd(0xE1);					/* Negative  gamma */
	TFT_dat(0x00);
	TFT_dat(0x28);
	TFT_dat(0x29);
	TFT_dat(0x03);
	TFT_dat(0x0F);
	TFT_dat(0x06);
	TFT_dat(0x3A);
	TFT_dat(0x56);
	TFT_dat(0x4C);
	TFT_dat(0x07);
	TFT_dat(0x12);
	TFT_dat(0x0C);
	TFT_dat(0x3F);
	TFT_dat(0x3F);
	TFT_dat(0x0F);

	TFT_cmd(0x29);					/* Display on */

	TFT_setRotation(1);
//	TFT_fillRect(0,0, 320-1, 240-1, COL_BLUE);
	TFT_clear(COL_BLACK);
	return 1;

}

void TFT_setRotation(uint8_t m)
{
  uint8_t rotation=m%8;
  TFT_cmd(ILI9341_MADCTL);
  switch (rotation) {
   case 0:
     TFT_dat(MADCTL_MX | MADCTL_BGR);
     break;
   case 1:
     TFT_dat(MADCTL_MV | MADCTL_BGR);
     break;
   case 2:
    TFT_dat(MADCTL_MY | MADCTL_BGR);
     break;
   case 3:
     TFT_dat(MADCTL_MX | MADCTL_MY | MADCTL_MV | MADCTL_BGR);
     break;
   case 4:
     TFT_dat(MADCTL_MX | MADCTL_MY | MADCTL_BGR);
     break;
   case 5:
     TFT_dat(MADCTL_MV | MADCTL_MX | MADCTL_BGR);
     break;
   case 6:
    TFT_dat(MADCTL_BGR);
    break;
   case 7:
     TFT_dat(MADCTL_MY | MADCTL_MV | MADCTL_BGR);
     break;
  }
}
void TFT_fillRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color) 
{
	uint32_t n;

	if(!((x+w < x) || (y+h < y)) ) {
	
	TFT_rect(x,x+w,y,y+h);
	n = (w+1) * (h+1);
	
		do {
			TFT_dat16(color);
		} while (--n);
  	}	
}
void TFT_setPixel(uint16_t col, uint16_t row)
{
	TFT_rect(col,col,row,row);
}
void TFT_drawPixel(uint16_t col, uint16_t row,uint16_t color)
{
	TFT_setPixel(col,row);
	TFT_dat16(color);
}
void TFT_setDisplayWindow(int16_t x0, int16_t y0, int16_t x1, int16_t y1)
{

  TFT_cmd(0x2A); // Column addr setT
  TFT_dat(x0 >> 8);
  TFT_dat(x0 & 0xFF);     // XSTART 
  TFT_dat(x1 >> 8);
  TFT_dat(x1 & 0xFF);     // XEND

  TFT_cmd(0x2B); // Row addr set
  TFT_dat(y0>>8);
  TFT_dat(y0);     // YSTART
  TFT_dat(y1>>8);
  TFT_dat(y1);     // YEND

  TFT_cmd(0x2C); // write to RAM

}
/**************************************************************************/
/*! 
	DRAW Line Function(There is no cripper yet).
*/
/**************************************************************************/
void TFT_drawLine(int16_t xs,int16_t ys,int16_t xe,int16_t ye, uint16_t color)
{
	/* Bresenham Algorithum */
	int16_t  hhy,wwx,x,y,n,sx,sy;
	int16_t  e,x_ct,y_ct;
	
	hhy = ye - ys;
	wwx = xe - xs;
	x_ct  = ABS(wwx);
	y_ct  = ABS(hhy);
	
	if (wwx) sx = 1; else	 sx =-1;
	if (hhy) sy = 1; else	 sy =-1;

	x = xs;
	y = ys;

	if ( x_ct >= y_ct )
	{
		e=wwx;
		for(n=0; n<=x_ct;++n ){
			TFT_drawPixel(x,y,color);
			x +=sx;
			e += 2*hhy;
			if (e>=2*wwx){
				e -= 2*wwx;
				y +=sy;
			}
		}
	}
	else
	{
		e=hhy;
		for(n=0; n<=y_ct;++n ){
			TFT_drawPixel(x,y,color);
			y +=sy;
			e += 2*wwx;
			if (e>=2*hhy){
				e -= 2*hhy;
				x +=sx;
			}
		}
	}
}
void TFT_drawVLine(int16_t x, int16_t y, int16_t h, uint16_t color)
 {
  // Rudimentary clipping
  if(!((x >= MAX_X) || (y >= MAX_Y))){
  	if((y+h-1) >= MAX_X) 
    h = MAX_Y-y;
	TFT_setDisplayWindow(x, y, x, y+h-1);
  	uint8_t hi = color >> 8, lo = color;
  	TFT_chipSelectLow();			/* CS=L		     */
  	while (h--) {
	spiSend((uint8_t)color>>8);
	spiSend((uint8_t)color);
  	}
  	TFT_chipSelectHigh();			/* CS=H		     */
  }
}
void TFT_drawHLine(int16_t x, int16_t y, int16_t w, uint16_t color)
 {
  // Rudimentary clipping
  if(!((x >= MAX_X) || (y >= MAX_Y))){
  if((x+w-1) >= MAX_X)  w = MAX_X-x;
  
  TFT_setDisplayWindow(x, y, x+w-1, y);

  uint8_t hi = color >> 8, lo = color;
  TFT_chipSelectLow();			/* CS=L		     */
  while (w--) {
		spiSend((uint8_t)color>>8);
	spiSend((uint8_t)color);
  }
  TFT_chipSelectHigh();			/* CS=H		     */
  }
}


/**************************************************************************/
/*! 
	Put ANK Font With Occupy.
*/
/**************************************************************************/
void TFT_drawChar(int16_t col, int16_t row, char c, uint16_t fg, uint16_t bg, uint16_t scale) {
 	uint8_t x_s, y_s, x8, x, y, i, xbit, k,b;
	int size;
	if(scale == 1){
	x_s = pgm_read_byte(font1 + 14);		// font width
	y_s = pgm_read_byte(font1 + 15);		// font height
	}else{
	x_s = pgm_read_byte(font2 + 14);		// font width
	y_s = pgm_read_byte(font2 + 15);		// font height
	}
	x8 = x_s / 8;
	if(x_s % 8) {
		x8++;
	}
	size = x8 * y_s;

	TFT_rect(col, col + x_s - 1,
					row, row + y_s - 1);

	k = 0;
	for(y=0; y< y_s;y++)
	{
		for(i= x8; i >0;i--){
			if( i > 1) {
				xbit = 8;
			} else {
				xbit = x_s - (x8-1)*8;
			}
			if(scale == 1){
			b = pgm_read_byte(font1 + 17 + c * size + k);
			}else{
			b = pgm_read_byte(font2 + 17 + c * size + k);
			}
			k++;
			for(x = 0; x < xbit; x++ ){
				if (b & 0x80) {
					TFT_gram(fg);
				} else {
					TFT_gram(bg);
				}
				b <<=1;
			}	
		}
	}
}

/**************************************************************************/
/*! 
	Put ank Font2X.
*/
/**************************************************************************/
int TFT_puts(uint16_t col, uint16_t row, char *pch, uint16_t fg, uint16_t bg, uint16_t scale)
{
	
	uint8_t x_s;
	if(scale == 1){
	x_s = pgm_read_byte(font1 + 14);		// font width
	}else{
	x_s = pgm_read_byte(font2 + 14);		// font width
	}
	while(*pch){

		if(! (col >= MAX_X || row >= MAX_Y)){
		char ch = *pch;
		TFT_drawChar(col,row,ch,fg,bg,scale);
		pch +=1;
 		col += x_s;
 		}
	}
	return 1;
}



