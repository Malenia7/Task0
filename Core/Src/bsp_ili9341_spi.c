#include "bsp_ili9341_spi.h"
#include "spi.h"
#include "tim.h"




/****************************** SPI communication ******************************/
/**
 * @brief host writes commands to ILI9341.
 * @note If the D/CX bit is low, the transmission byte is interpreted as a command byte. 
 * 		 If the D/CX bit is high, the transmission byte is stored as the display data RAM
 */
inline void spi_write_cmd(uint8_t cmd) {
	HAL_GPIO_WritePin(LCD_DCX_GPIO_Port, LCD_DCX_Pin, GPIO_PIN_RESET);
	HAL_SPI_Transmit(&hspi1, &cmd, 1, HAL_MAX_DELAY);
	HAL_GPIO_WritePin(LCD_DCX_GPIO_Port, LCD_DCX_Pin, GPIO_PIN_SET);
}

//  host writes data to ILI9341.
inline void spi_write_data(uint8_t data) {
	HAL_SPI_Transmit(&hspi1, &data, 1, HAL_MAX_DELAY);
}

//  host writes cmd and data to ILI9341.
inline void spi_write_reg(uint8_t cmd, uint8_t data) {
	spi_write_cmd(cmd);
	spi_write_data(data);
}
	
/****************************** SPI communication ******************************/
void ili9341_init(void) {
/* HW RESET
 * 1. LCD_RST_Pin defaults to HIGH.
 * 2. valid reset requires RST held LOW for tRW ≥ 10 µs.
 * 3. HW reset cancel time (tRT) within 5 ms after a rising edge of RST,	
 *    After setting RST HIGH, wait ≥120 ms before issuing commands.
 */	
	HAL_GPIO_WritePin(LCD_RST_GPIO_Port, LCD_RST_Pin, GPIO_PIN_RESET);
	HAL_Delay(1);
	HAL_GPIO_WritePin(LCD_RST_GPIO_Port, LCD_RST_Pin, GPIO_PIN_SET);
	HAL_Delay(120);

// ILI9341 manufacturer-recommended initialization command sequence
	// Power Control Sequences
	spi_write_cmd(0xCF);
    spi_write_data(0x00);
    spi_write_data(0xC1);
    spi_write_data(0x30);	// Power control B

    spi_write_cmd(0xED);
    spi_write_data(0x64);
    spi_write_data(0x03);
    spi_write_data(0x12);
    spi_write_data(0x81);	// Power on sequence control

    spi_write_cmd(0xE8);    // Driver timing control A
    spi_write_data(0x85);
    spi_write_data(0x10);
    spi_write_data(0x7A);

    spi_write_cmd(0xCB);	// Power control A
    spi_write_data(0x39);
    spi_write_data(0x2C);
    spi_write_data(0x00);
    spi_write_data(0x34);
    spi_write_data(0x02);

    spi_write_cmd(0xF7);
    spi_write_data(0x20);	// Pump ratio control

    spi_write_cmd(0xEA);	// Driver timing control B
    spi_write_data(0x00);
    spi_write_data(0x00);

    // VCOM and Power Configuration
    spi_write_cmd(0xC0);    // Power control 1
    spi_write_data(0x1B);   // VRH[5:0]       
    spi_write_cmd(0xC1);    // Power control 2
    spi_write_data(0x01);   // SAP[2:0]; BT[3:0]

    spi_write_cmd(0xC5);    // VCOM control 1
    spi_write_data(0x30);   
    spi_write_data(0x30);	
    spi_write_cmd(0xC7);    // VCOM control 2
    spi_write_data(0xB7);
    
	
    // Memory Access Control & Pixel Format
    spi_write_cmd(0x36);    // Memory access control
    spi_write_data(0x08);   // Landscape, RGB order => 0x01001000
    spi_write_cmd(0x3A);	// Pixel format set
    spi_write_data(0x55);   // 16-bit/pixel (RGB565)

    spi_write_cmd(0xB1);	// Frame ratlcd_clear(BLACK);e control (normal mode)
    spi_write_data(0x00);	
    spi_write_data(0x1B);   // ~60 Hz
    
    spi_write_cmd(0xB6);	// Display function control
    spi_write_data(0x0A);
    spi_write_data(0xA2);
	
	
	// Gamma Correction
    spi_write_cmd(0xF2);	// 3Gamma function disable
    spi_write_data(0x00);

    spi_write_cmd(0x26);	// Gamma curve selected
    spi_write_data(0x01);	// Gamma set = curve 1

    spi_write_cmd(0xE0);	// Positive Gamma Correction
    spi_write_data(0x0F); spi_write_data(0x2A); spi_write_data(0x28); 
    spi_write_data(0x08); spi_write_data(0x0E); spi_write_data(0x08);
    spi_write_data(0x54); spi_write_data(0XA9); spi_write_data(0x43);
    spi_write_data(0x0A); spi_write_data(0x0F); spi_write_data(0x00);
    spi_write_data(0x00); spi_write_data(0x00); spi_write_data(0x00);
    
    spi_write_cmd(0XE1);	// Negative Gamma Correction
    spi_write_data(0x00); spi_write_data(0x15); spi_write_data(0x17);
    spi_write_data(0x07); spi_write_data(0x11); spi_write_data(0x06);
    spi_write_data(0x2B); spi_write_data(0x56); spi_write_data(0x3C);
    spi_write_data(0x05); spi_write_data(0x10); spi_write_data(0x0F);
    spi_write_data(0x3F); spi_write_data(0x3F); spi_write_data(0x0F);
   
   
    // Column / Page Address Setting
    spi_write_cmd(ili9341_t.cmd_setx);	// Column Address Set (X-axis)
    spi_write_data(0x00);
    spi_write_data(0x00);
    spi_write_data(0x00);
    spi_write_data(0xEF);   // End column = 239

	spi_write_cmd(ili9341_t.cmd_sety);	// Page Address Set (Y-axis)
    spi_write_data(0x00);   
    spi_write_data(0x00);   // Start row
    spi_write_data(0x01);   
    spi_write_data(0x3F);   // End row = 0x013F = 319
    
	
	// Display Commands
    spi_write_cmd(0x35);	// Tearing effect line ON
    spi_write_data(0x00);
    
    spi_write_cmd(0x11);	// Exit Sleep mode
    spi_write_cmd(0x21);	// Display inversion ON
    HAL_Delay(120);		// Wait for display to stabilize
    spi_write_cmd(0x29);	// Display ON
	
	
	// test
	lcd_clear(RED);
	//HAL_Delay(2000);
	//lcd_clear(GREEN);
	//HAL_Delay(2000);
	//lcd_clear(BLUE);
}

inline void lcd_set_cursor(uint16_t x, uint16_t y) {
	uint8_t x_buf[2] = {x >> 8, x & 0xFF};
	spi_write_cmd(ili9341_t.cmd_setx);
	HAL_SPI_Transmit(&hspi1, x_buf, 2, HAL_MAX_DELAY);
	
	uint8_t y_buf[2] = {y >> 8, y & 0xFF};
	spi_write_cmd(ili9341_t.cmd_sety);
	HAL_SPI_Transmit(&hspi1, y_buf, 2, HAL_MAX_DELAY);
}

void lcd_clear(uint16_t color) {
	lcd_set_cursor(0, 0);
	
	uint8_t color_buf[2] = {color >> 8, color & 0xFF};
	uint32_t pixel_count = ili9341_t.width * 
						   ili9341_t.height;	
	spi_write_cmd(0x2C);
	for (uint32_t i = 0; i < pixel_count; i++) {
		HAL_SPI_Transmit(&hspi1, color_buf, 2, HAL_MAX_DELAY);
	}
}

inline void lcd_setarea(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1) {	
	uint8_t xy_tmp[4];
	//行改变就重新设置行
	if (x0 != xy_prev.x0 || x1 != xy_prev.x1) {
		xy_tmp[0] = x0 >> 8;
		xy_tmp[1] = x0 &  0xFF;
		xy_tmp[2] = x1 >> 8;
		xy_tmp[3] = x1 &  0xFF;	
		spi_write_cmd(ili9341_t.cmd_setx);
		HAL_SPI_Transmit(&hspi1, xy_tmp, 4, HAL_MAX_DELAY);
		xy_prev.x0 = x0;
		xy_prev.x1 = x1;
	}
	//列改变就重新设置列
	if (y0 != xy_prev.y0 || y1 != xy_prev.y1) {
		xy_tmp[0] = y0 >> 8;
		xy_tmp[1] = y0 &  0xFF;
		xy_tmp[2] = y1 >> 8;
		xy_tmp[3] = y1 &  0xFF;	
		spi_write_cmd(ili9341_t.cmd_sety);
		HAL_SPI_Transmit(&hspi1, xy_tmp, 4, HAL_MAX_DELAY);
		xy_prev.y0 = y0;
		xy_prev.y1 = y1;
	}
}

/**
 * @brief 设置背光PWM占空比
 * @param pDutyRatio 输入范围5~100，对应占空比5%~100%（CCR = pDutyRatio * 10）
 */
void lcd_update_backlight(uint8_t duty_cycle) {
	if ( (duty_cycle < 5) || (duty_cycle > 100) ) {
		return;
	}
	HAL_TIM_PWM_Stop(&htim2, TIM_CHANNEL_3);
	__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_3, duty_cycle * 10);
	__HAL_TIM_SET_COUNTER(&htim2, 0);
	HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_3);
}





