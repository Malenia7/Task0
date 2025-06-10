//2.8-inch ILI9341 LCD driver (4-wire SPI)
#ifndef __BSP_ILI9341_SPI_H__
#define __BSP_ILI9341_SPI_H__

#include "main.h"


//屏幕长宽和常用cmd
typedef struct {
    uint16_t	width,height;	
	uint8_t		cmd_setx, cmd_sety, cmd_gram;
} _ili9341_t;

static _ili9341_t ili9341_t = {320, 240, 0x2A, 0x2B};

// 缓存上一次的坐标值
static struct {
	uint16_t x0, x1, y0, y1;
} xy_prev = { 0 };






//扫描方向
typedef enum {
	L2R_U2D = 0U,	//从左到右，从上到下
	L2R_D2U,
	R2L_U2D,
	R2L_D2U,
	U2D_L2R,
	U2D_R2L,
	D2U_L2R,
	D2U_R2L
} _scan_direction;

//显示的长宽比
typedef enum {
	SCAN_VERTICAL = 0U,		//竖屏
	SCAM_HORIZONTAL
} _screen_direction;

//颜色
#define	BLACK     0x0000  // 00000 000000 00000
#define	WHITE     0xFFFF  // 11111 111111 11111
#define	RED       0xF800  // 11111 000000 00000
#define	GREEN     0x07E0  // 00000 111111 00000
#define	BLUE      0x001F  // 00000 000000 11111
#define YELLOW    0xFFE0  // 11111 111111 00000
#define CYAN      0x07FF  // 00000 111111 11111
#define MAGENTA   0xF81F  // 11111 000000 11111
#define GRAY      0x8410  // 10000 100000 10000

	
void ili9341_init(void);
inline void lcd_set_cursor(uint16_t x, uint16_t y);
void lcd_clear(uint16_t color);
void lcd_update_backlight(uint8_t duty_cycle);


#endif
