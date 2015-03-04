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
#include "onboard_led_control.h"
#include "string.h"



int main(void) {

	int led;

	printf("Which LED to turn on?\n");
	scanf("%d", &led);

	printf("You chose: %d\n", led);

	on_board_led_on(led);
	//okay

	return EXIT_SUCCESS;
}
