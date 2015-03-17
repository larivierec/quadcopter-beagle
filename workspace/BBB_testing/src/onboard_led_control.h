/*
 * onboard_led_control.h
 *
 *  Created on: Feb 21, 2015
 *      Author: tony
 */

#ifndef ONBOARD_LED_CONTROL_H_
#define ONBOARD_LED_CONTROL_H_

#include <stdio.h>

#define SUCCESS 1
#define FAILED 0
#define ON_BOARD_LED_COUNT 4
#define STRING_OB_LED_PATH_LENGTH 100

extern char *ob_led_brightness_path[];
extern char *ob_led_trigger_path[];

void remove_trigger(int led);
//bbb onboard LED on
int on_board_led_on(int led);
//bbb onboard LED off
int on_board_led_off(int led);
//bbb onboard LED toggle
int on_board_led_toggle(int led);


#endif /* ONBOARD_LED_CONTROL_H_ */
