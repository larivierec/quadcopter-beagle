/*
 ============================================================================
 Name        : BBB_testing.c
 Author      : Anthony & Chris
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>//sleep in seconds
#include "onboard_led_control.h"
#include "string.h"




int main(void) {

	int led, i;

	init_ob_leb_paths();

	modify_trigger(HEARTBEAT, 0);

	printf("%s\n", ob_led_path.brightness[0]);

	clean_ob_bbb_led_path();

	return EXIT_SUCCESS;
}