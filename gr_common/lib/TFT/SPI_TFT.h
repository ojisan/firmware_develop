/* GR-CITRUS SPI_TFT Library
 * Copyright (C) 2009 by William Greiman
 *
 * * You should have received a copy of the GNU General Public License
 * <http://www.gnu.org/licenses/>.
 */

#ifndef SPI_TFT_h
#define SPI_TFT_h

// define software SPI pins so Mega can use unmodified GPS Shield
/** SPI chip select pin */
uint8_t const TFT_CHIP_SELECT_PIN = 10;
/** SPI Master Out Slave In pin */
uint8_t const SPI_MOSI_PIN = 11;
/** SPI Master In Slave Out pin */
uint8_t const SPI_MISO_PIN = 12;
/** SPI Clock pin */
uint8_t const SPI_SCK_PIN = 13;
/** SPI RES pin */
uint8_t const TFT_RES_PIN = 4;
/** SPI RS pin */
uint8_t const TFT_RS_PIN = 3;

//------------------------------------------------------------------------------
/** nop to tune soft SPI timing */
#define __NOP() asm volatile ("nop\n\t")

#define sdi_High()	digitalWrite(SPI_MOSI_PIN, HIGH)
#define sdi_Low()	digitalWrite(SPI_MOSI_PIN, LOW)
#define sck_High()	digitalWrite(SPI_SCK_PIN, HIGH)
#define sck_Low()	digitalWrite(SPI_SCK_PIN, LOW)
#define res_High()	digitalWrite(TFT_RES_PIN, HIGH)
#define res_Low()	digitalWrite(TFT_RES_PIN, LOW)
#define rs_High()	digitalWrite(TFT_RS_PIN, HIGH)
#define rs_Low()	digitalWrite(TFT_RS_PIN, LOW)
#define CLK_OUT()	sck_Low();__NOP();__NOP();\
					sck_High();__NOP();__NOP();

#define sendSPI(x)							\
		(0x80 & x) ? sdi_High() : sdi_Low();	\
		CLK_OUT();							\
		(0x40 & x) ? sdi_High() : sdi_Low();	\
		CLK_OUT();							\
		(0x20 & x) ? sdi_High() : sdi_Low();	\
		CLK_OUT();							\
		(0x10 & x) ? sdi_High() : sdi_Low();	\
		CLK_OUT();							\
		(0x08 & x) ? sdi_High() : sdi_Low();	\
		CLK_OUT();							\
		(0x04 & x) ? sdi_High() : sdi_Low();	\
		CLK_OUT();							\
		(0x02 & x) ? sdi_High() : sdi_Low();	\
		CLK_OUT();							\
		(0x01 & x) ? sdi_High() : sdi_Low();	\
		CLK_OUT();
/* Send 16-bit Data Macro */
#define sendSPI16(x)						\
		(0x8000 & x) ? sdi_High() : sdi_Low();	\
		CLK_OUT();							\
		(0x4000 & x) ? sdi_High() : sdi_Low();	\
		CLK_OUT();							\
		(0x2000 & x) ? sdi_High() : sdi_Low();	\
		CLK_OUT();							\
		(0x1000 & x) ? sdi_High() : sdi_Low();	\
		CLK_OUT();							\
		(0x0800 & x) ? sdi_High() : sdi_Low();	\
		CLK_OUT();							\
		(0x0400 & x) ? sdi_High() : sdi_Low();	\
		CLK_OUT();							\
		(0x0200 & x) ? sdi_High() : sdi_Low();	\
		CLK_OUT();							\
		(0x0100 & x) ? sdi_High() : sdi_Low();	\
		CLK_OUT();							\
		(0x0080 & x) ? sdi_High() : sdi_Low();	\
		CLK_OUT();							\
		(0x0040 & x) ? sdi_High() : sdi_Low();	\
		CLK_OUT();							\
		(0x0020 & x) ? sdi_High() : sdi_Low();	\
		CLK_OUT();							\
		(0x0010 & x) ? sdi_High() : sdi_Low();	\
		CLK_OUT();							\
		(0x0008 & x) ? sdi_High() : sdi_Low();	\
		CLK_OUT();							\
		(0x0004 & x) ? sdi_High() : sdi_Low();	\
		CLK_OUT();							\
		(0x0002 & x) ? sdi_High() : sdi_Low();	\
		CLK_OUT();							\
		(0x0001 & x) ? sdi_High() : sdi_Low();	\
		CLK_OUT();

#define MADCTL_MY  0x80
#define MADCTL_MX  0x40
#define MADCTL_MV  0x20
#define MADCTL_ML  0x10
#define MADCTL_RGB 0x00
#define MADCTL_BGR 0x08
#define MADCTL_MH  0x04
#define ILI9341_MADCTL  0x36
#define MAX_X				320
#define MAX_Y				240

#define RGB(r,g,b)	(uint16_t)((b >> 3) |((g >> 2) << 5) |((r >> 3) << 11))
#define ABS(x) ((x) >= 0 ? (x) : -(x))
/*
 * LCD Colours
 */
#define COL_WHITE          0xFFFF
#define COL_BLACK          0x0000
#define COL_GREY           0xF7DE
#define COL_LGRAY          0xC618
#define COL_DGRAY          0x7BEF
#define COL_DGREEN         0x03E0
#define COL_DCYAN          0x03EF
#define COL_MAROON         0x7800
#define COL_PURPLE         0x780F
#define COL_OLIVE          0x7BE0
#define COL_BLUE           0x001F
#define COL_BLUE2          0x051F
#define COL_NAVY           0x000F
#define COL_RED            0xF800
#define COL_MAGENTA        0xF81F
#define COL_GREEN          0x07E0
#define COL_CYAN           0x7FFF
#define COL_YELLOW         0xFFE0

  //public function	 
int TFT_init();
void TFT_setRotation(uint8_t m);
void TFT_clear(uint16_t color); 
void TFT_fillRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color);   
void TFT_setPixel(uint16_t col, uint16_t row);
void TFT_drawPixel(uint16_t col, uint16_t row, uint16_t colour);
int TFT_puts(uint16_t col, uint16_t row, char *pch, uint16_t fg, uint16_t bg, uint16_t scale);
void TFT_drawLine(int16_t xs,int16_t ys,int16_t xe,int16_t ye, uint16_t colour);
void TFT_drawVLine(int16_t x, int16_t y, int16_t h, uint16_t color);
void TFT_drawHLine(int16_t x, int16_t y, int16_t w, uint16_t color);

  // private functions
  void TFT_chipSelectHigh(void);
  void TFT_chipSelectLow(void);
  void TFT_cmd(uint8_t cmd);
  void TFT_dat(uint8_t data);
  void TFT_dat16(uint16_t data);
  void TFT_gram(uint16_t gram);
  void TFT_rect(uint16_t x,  uint16_t width, uint16_t y,  uint16_t height);
  uint8_t TFT_spiinit();
  void TFT_reset();
  void TFT_setDisplayWindow(int16_t x0, int16_t y0, int16_t x1, int16_t y1);
  void TFT_drawChar(int16_t col, int16_t row, char c, uint16_t fg, uint16_t bg, uint16_t scale);
#endif  // SPI_TFT_h
