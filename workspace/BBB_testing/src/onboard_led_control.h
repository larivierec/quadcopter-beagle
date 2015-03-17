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

typedef struct ob_bbb_led{
	char *brightness;
	char *trigger;
}ob_bbb_led;

//Init locations for other functions, pass as reference
void init_ob_leb_paths(ob_bbb_led *ob_led_path);

//removes default trigger with chosen led
void remove_trigger(ob_bbb_led ob_led_path, int led);

//bbb onboard LED on
int on_board_led_on(ob_bbb_led ob_led_path, int led);

//bbb onboard LED off
int on_board_led_off(ob_bbb_led ob_led_path, int led);

//bbb onboard LED toggle
int on_board_led_toggle(ob_bbb_led ob_led_path, int led);


#endif /* ONBOARD_LED_CONTROL_H_ */
