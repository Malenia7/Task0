#ifndef __API_USER_H__
#define __API_USER_H__

#include "rtc.h"
#include "tim.h"
#include "adc.h"

#include "efsm.h"

#include "bsp_ili9341_spi.h"
#include "bsp_mpu6050_i2c.h"
#include "bsp_ch579_uart2.h"


#define os_tasklist_count 

//系统数据更新和控制任务
enum {
	state_update_time = 0,
	state_update_mpu6050,
	state_update_max30102,	
};

//任务使能标识
typedef struct {
	uint32_t dial_update_en:1;					//表盘页面任务使能			
	uint32_t step_update_enupdate_six_axis_en:1;			//六轴运动任务使能
	uint32_t bluetooth_update_en:1;			//wifi联网任务使能	
	uint32_t update_healthpage:1;				//健康任务使能
	
	uint32_t app_page_update_en:1;		      //应用界面使能
	
	
	uint32_t update_app_task_en:1;			//app页面任务使能		
	uint32_t update_chippage:1;					//系统信息任务使能		
	
	uint32_t update_infopage:1;		      //info界面使能
	uint32_t update_wifipage:1;		      //wifi界面使能
	uint32_t update_settingpage:1;		  //setting界面使能
	uint32_t update_motorpage:1;		  	//motor界面使能
	uint32_t update_batterypage:1;		  //battery界面使能
	uint32_t update_sportpage:1;		  	//sport界面使能	
	uint32_t update_alipaypage:1;		  	//alipay界面使能	
	uint32_t   :18;
} _flag_task_en;

//任务状态标识
typedef struct
{
	uint32_t AP3216PS:1;			//AP3216的PS状态标值，用于标识物体是否接近
	uint32_t Sport:1;					//运动状态
	uint32_t ADCC:1;					//ADC转换完成
	uint32_t TouchPress:1;		//1：触摸按下 0：触摸释放
	uint32_t FiveKeyPress:1;	//1：五向键按下 0：触摸释放
	uint32_t ExtITR:1;				//1：光电开关触发 0：释放
	uint32_t ExtFIRE:1;				//1：火焰检测触发	0：释放 
	uint32_t ExtPIR:1;				//1：热释电触发	0：释放 
	uint32_t Max30102:1;			//1：max30102测量完成	0：释放 
	uint32_t   :23;
}_status_task;


/*
 * __DATE__ 和 __TIME__ 是 C/C++ 的预定义宏，它们在编译时会被自动替换为对应的日期和时间字符串：
 * __DATE__ 是一个字符串，格式为 "Mmm dd yyyy"，例如："Jun 10 2025"
 * __TIME__ 是一个字符串，格式为 "hh:mm:ss"，例如："14:35:22"
 */
#define os_year		((((__DATE__ [7] - '0') * 10 + \
						(__DATE__ [8] - '0')) * 10 + \
						(__DATE__ [9] - '0')) * 10 + \
						(__DATE__ [10] - '0')) \

#define	os_month 	 (__DATE__ [2] == 'n' ? (__DATE__ [1] = 'a' ? 1 : 6) \
					: __DATE__ [2] == 'b' ? 2 \
					: __DATE__ [2] == 'r' ? (__DATE__ [0] == 'M') ? 3 : 4) \
					: __DATE__ [2] == 'y' ? 5 \
					: __DATE__ [2] == 'l' ? 7 \
					: __DATE__ [2] == 'g' ? 8 \
					: __DATE__ [2] == 'p' ? 9 \
					: __DATE__ [2] == 't' ? 10 \
					: __DATE__ [2] == 'v' ? 11 : 12 )
					
#define os_day		 (( __DATE__ [4] == ' ' ? 0 : __DATE__ [4] - '0') * 10 + \
						__DATE__ [5] - '0')
						
#define os_hour		((__TIME__ [0] - '0') * 10 + (__DATE__ [1] - '0'))						
#define os_mimute	((__TIME__ [3] - '0') * 10 + (__DATE__ [4] - '0'))							
#define os_second	((__TIME__ [6] - '0') * 10 + (__DATE__ [7] - '0'))	


#endif