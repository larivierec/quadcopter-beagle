/*
 * onboard_led_control.h
 *
 *  Created on: Feb 21, 2015
 *      Author: tony
 */

#ifndef ONBOARD_LED_CONTROL_H_
#define ONBOARD_LED_CONTROL_H_

#include <stdio.h>
 #include <stdlib.h>

#define SUCCESS 1
#define FAILED 0
#define ON_BOARD_LED_COUNT 4
#define STRING_OB_LED_PATH_LENGTH 100

typedef enum
{ 
	NONE = 0, NAND_DISK, MMC0, MMC1, TIMER, ONESHOT, HEARTBEAT, BACKLIGHT, GPIO, CPU0, DEFAULT_ON, TRANSIENT
}Trigger_Mode;

typedef struct ob_bbb_led{
	char **brightness;
	char **trigger;
}ob_bbb_led;

//For Paths
extern ob_bbb_led ob_led_path;

//Init locations for other functions, pass as reference
void init_ob_leb_paths();

//send NONE to remove default trigger with chosen led
void modify_trigger(Trigger_Mode mode, int led);

//bbb onboard LED on
int on_board_led_on(int led);

//bbb onboard LED off
int on_board_led_off(int led);

//bbb onboard LED toggle
int on_board_led_toggle(int led);

//clearsob_bbb_led struct
void clean_ob_bbb_led_path();


#endif /* ONBOARD_LED_CONTROL_H_ */
