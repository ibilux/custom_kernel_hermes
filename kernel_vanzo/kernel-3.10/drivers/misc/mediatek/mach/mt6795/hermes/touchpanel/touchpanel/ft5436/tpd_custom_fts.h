#ifndef TOUCHPANEL_H__
#define TOUCHPANEL_H__

#include <linux/hrtimer.h>
#include <linux/string.h>
#include <linux/vmalloc.h>
//#include <linux/io.h>

#include <linux/init.h>
#include <linux/module.h>
#include <linux/delay.h>
#include <linux/i2c.h>
#include <linux/input.h>
#include <linux/slab.h>
#include <linux/gpio.h>
#include <linux/sched.h>
#include <linux/kthread.h>
#include <linux/bitops.h>
#include <linux/kernel.h>
#include <linux/delay.h>
#include <linux/byteorder/generic.h>
#ifdef CONFIG_HAS_EARLYSUSPEND
#include <linux/earlysuspend.h>
#endif
#include <linux/interrupt.h>
#include <linux/time.h>
#include <linux/rtpm_prio.h>

#include <linux/proc_fs.h>
#include <asm/uaccess.h>

#include <mach/mt_pm_ldo.h>
#include <mach/mt_typedefs.h>
#include <mach/mt_boot.h>

#include <cust_eint.h>
#include <linux/jiffies.h>
#include <pmic_drv.h>

struct Upgrade_Info {
        u8 CHIP_ID;
        u8 FTS_NAME[20];
        u8 TPD_MAX_POINTS;
        u8 AUTO_CLB;
	u16 delay_aa;		/*delay of write FT_UPGRADE_AA */
	u16 delay_55;		/*delay of write FT_UPGRADE_55 */
	u8 upgrade_id_1;	/*upgrade id 1 */
	u8 upgrade_id_2;	/*upgrade id 2 */
	u16 delay_readid;	/*delay of read id */
	u16 delay_earse_flash; /*delay of earse flash*/
};


//extern Upgrade_Info fts_updateinfo_curr;

/**********************Custom define begin**********************************************/


#define TPD_POWER_SOURCE_CUSTOM        PMIC_APP_CAP_TOUCH_VDD //MT6323_POWER_LDO_VGP1


/*
///// ***** virtual key  definition  ***** /////

Below are the recommend  virtual key definition for different resolution TPM. 

HVGA  320x480    2key ( (80,530);(240,530) )           3key  ( (80,530);(160;530);(240,530) )          4key   ( (40,530);(120;530);(200,530);(280,530)  ) 
WVGA  480x800   2key ( (80,900);(400,900) )           3key  ( (80,900);(240,900);(400,900) )          4key   ( (60,900);(180;900);(300,900);(420,900)  ) 
FWVGA 480x854  2key ( (80,900);(400,900) )           3key  ( (80,900);(240,900);(400,900) )          4key   ( (60,900);(180;900);(300,900);(420,900)  ) 
QHD  540x960     2key ( (90,1080);(450,1080) )           3key  ( (90,1080);(270,1080);(450,1080) )          4key   ( (90,1080);(180;1080);(360,1080);(450,1080)  ) 
HD    1280x720    2key ( (120,1350);(600,1350) )           3key  ( (120,1350);(360,1350);(600,1350) )          4key   ( (120,1080);(240;1080);(480,1080);(600,1080)  )
FHD   1920x1080  2key ( (160,2100);(920,2100) )           3key  ( (160,2100);(540,2100);(920,2100) )          4key   ( (160,2100);(320;1080);(600,1080);(920,2100)  )
*/
#define TPD_HAVE_BUTTON	// if have virtual key,need define the MACRO
#define TPD_BUTTON_HEIGH        (40)  //100
#define TPD_KEY_COUNT           3    //  4
#define TPD_KEYS                {KEY_MENU,KEY_HOMEPAGE,KEY_BACK}
#define TPD_KEYS_FACTORY         {KEY_MENU,KEY_HOMEPAGE,KEY_BACK} //addb by major for factory test 
#define TPD_KEYS_DIM            	{{160,2010,20,TPD_BUTTON_HEIGH}, {540,2010,20,TPD_BUTTON_HEIGH}, {920,2010,20,TPD_BUTTON_HEIGH}}

/*********************Custom Define end*************************************************/

#define TPD_NAME    "FT"

/* Pre-defined definition */
#define TPD_TYPE_CAPACITIVE
#define TPD_TYPE_RESISTIVE
#define TPD_POWER_SOURCE         
#define TPD_I2C_NUMBER           		2
#define TPD_WAKEUP_TRIAL         		60
#define TPD_WAKEUP_DELAY         		100

#define TPD_VELOCITY_CUSTOM_X 			15
#define TPD_VELOCITY_CUSTOM_Y 			20

#if (defined MT8389)
#define TPD_POWER_SOURCE_CUSTOM         PMIC_APP_CAP_TOUCH_VDD//MT65XX_POWER_LDO_VGP4
#define CUST_EINT_TOUCH_PANEL_NUM 		6
#endif

#define TPD_POWER_SOURCE_CUSTOM         PMIC_APP_CAP_TOUCH_VDD//MT6325_POWER_LDO_VGP1//wangmeixia
#define MTK_I2C_NEED_DMA_TRANSFER		// for MT6589/MT8389/MT6572,pls anbel this MACRO

#define TPD_DELAY                		(2*HZ/100)
//#define TPD_RES_X                		480
//#define TPD_RES_Y                		800
#define TPD_CALIBRATION_MATRIX  		{962,0,0,0,1600,0,0,0};

#define USB_CHARGE_DETECT				// if need usb charger detection notify,enable this MACRO
//#if (defined HQ_CTP_PROXIMITY)   //add by zhangkun 14.04.18
//#define TPD_PROXIMITY					// if need the PS funtion,enable this MACRO
//#endif
//#define TPD_HAVE_BUTTON					// if have virtual key,need define the MACRO,and modified the below parameter according the TP resultion parameter
//#define TPD_BUTTON_HEIGH        		(60)
//#define TPD_KEY_COUNT           		3
//#define TPD_KEYS                		{ KEY_MENU, KEY_HOMEPAGE ,KEY_BACK}
//#define TPD_KEYS_DIM            		{{80,900,60,TPD_BUTTON_HEIGH},{240,900,60,TPD_BUTTON_HEIGH},{400,900,60,TPD_BUTTON_HEIGH}}

/******************************************************************************/
/*Chip Device Type*/
#define IC_FT5X06						0	/*x=2,3,4*/
#define IC_FT5606						1	/*ft5506/FT5606/FT5816*/
#define IC_FT5316						2	/*ft5x16*/
#define IC_FT6208						3  	/*ft6208*/
#define IC_FT6x06     					       4	/*ft6206/FT6306*/
#define IC_FT5x06i     					5	/*ft5306i*/
#define IC_FT5x36     					       6	/*ft5336/ft5436/FT5436i*/


/*register address*/
#define FT_REG_CHIP_ID				0xA3    //chip ID 
#define FT_REG_FW_VER				0xA6   //FW  version 
#define FT_REG_VENDOR_ID			0xA8   // TP vendor ID 


#define TPD_MAX_POINTS_2                        2
#define TPD_MAX_POINTS_5                        5
#define TPD_MAXPOINTS_10                        10
#define AUTO_CLB_NEED                              1
#define AUTO_CLB_NONEED                          0

//#endif
#define TPD_SYSFS_DEBUG
#define FTS_CTL_IIC
#define FTS_APK_DEBUG
#ifdef TPD_SYSFS_DEBUG
//#define TPD_AUTO_UPGRADE				// if need upgrade CTP FW when POWER ON,pls enable this MACRO
#endif


#define FTS_DBG
#ifdef FTS_DBG
#define DBG(fmt, args...) 				printk("[FTS]" fmt, ## args)
#else
#define DBG(fmt, args...) 				do{}while(0)
#endif

//add by major 
//#define FTS_GESTRUE

#ifdef FTS_GESTRUE
#define GESTURE_LEFT		0x20
#define GESTURE_RIGHT		0x21
#define GESTURE_UP		    0x22
#define GESTURE_DOWN		0x23
#define GESTURE_DOUBLECLICK	0x24
#define GESTURE_O		    0x30
#define GESTURE_W		    0x31
#define GESTURE_M		    0x32
#define GESTURE_E		    0x33
#define GESTURE_L		    0x44
//#define GESTURE_S		    0x46
//#define GESTURE_V		    0x54
//#define GESTURE_Z		    0x41


#include "ft_gesture_lib.h"



#define FTS_GESTRUE_POINTS 255
#define FTS_GESTRUE_POINTS_ONETIME  62
#define FTS_GESTRUE_POINTS_HEADER 8
#define FTS_GESTURE_OUTPUT_ADRESS 0xD3
#define FTS_GESTURE_OUTPUT_UNIT_LENGTH 4

//suspend_state_t get_suspend_state(void);

extern short pointnum ;

extern unsigned short coordinate_x[255] ;
extern unsigned short coordinate_y[255] ;
#endif
#define RGK_SAMPLE_VERSION 0x14
#define MODULE_MAX_LEN 40
#define MODULE_ID0 0x67
#define MODULE_ID1 0x5f
#define MODULE_ID2 0x73
#define MODULE_ID3 0x74
#define MODULE_ID4 0x75
static char tp_modules_name[][MODULE_MAX_LEN] ={
	[0]="dijing",
	[1]="yushun",
	[2]="dijing",
	[3]="dijing",
	[4]="dijing",
	[5]="dijing",
	[6]="dijing",
	[7]="dijing",
	[8]="yushun",
};

#endif /* TOUCHPANEL_H__ */
