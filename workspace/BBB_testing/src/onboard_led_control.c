/*
 * onboard_led_control.c

 *
 *  Created on: Feb 21, 2015
 *      Author: tony
 */
#include "onboard_led_control.h"
#include <stdio.h>
#include <string.h>

FILE *led_file;



void init_ob_leb_paths(ob_bbb_led *ob_led_path)
{
	int i;

	for(i = 0; i < ON_BOARD_LED_COUNT; i++)
	{
		*ob_led.brightness = (char *)malloc(ON_BOARD_LED_COUNT*(sizeof(char)));
		*ob_led.trigger = (char *)malloc(ON_BOARD_LED_COUNT*(sizeof(char)));
		switch(i)
		{
			case (0):
				strcpy(*ob_led_path.brightness[i],"/sys/class/leds/beaglebone\\:green\\:usr0/brightness");
				strcpy(*ob_led_path.trigger[i], "/sys/class/leds/beaglebone\\:green\\:usr0/trigger");
			break;
			case (1):
				strcpy(*ob_led_path.brightness[i],"/sys/class/leds/beaglebone\\:green\\:usr1/brightness");
				strcpy(*ob_led_path.trigger[i], "/sys/class/leds/beaglebone\\:green\\:usr1/trigger");
			break;
			case (2):
				strcpy(*ob_led_path.brightness[i],"/sys/class/leds/beaglebone\\:green\\:usr2/brightness");
				strcpy(*ob_led_path.trigger[i], "/sys/class/leds/beaglebone\\:green\\:usr2/trigger");
			break;
			case (3):
				strcpy(*ob_led_path.brightness[i],"/sys/class/leds/beaglebone\\:green\\:usr3/brightness");
				strcpy(*ob_led_path.trigger[i], "/sys/class/leds/beaglebone\\:green\\:usr3/trigger");
			break;
		}
	}
}

void remove_trigger(ob_bbb_led ob_led_path, int led)
{
	led_file = fopen(ob_led_path.trigger[led], "w" );
	fprintf(led_file, "none");
	fclose(led_file);
}


/*--------------LED switch ON-----------*/
int on_board_led_on(ob_bbb_led ob_led_path, int led)
{

	if(led > 3)
	{
		printf("Chose between 0 and 3\n");
		return FAILED;
	}

	led_file = fopen(ob_led_path.brightness[led], "w+" );

	if (!led_file)
	{
		printf("File not found\n");
		fclose(led_file);
		return FAILED;
	}
	else
	{
	fprintf(led_file, "%d", 1);
	fclose(led_file);
	printf("LED (%s) on\n", ob_led_path.brightness[led]);
	return SUCCESS;
	}

}
/*--------------LED switch off----------*/
int on_board_led_off(ob_bbb_led ob_led_path, int led)
{

	if(led > 3)
	{
		printf("Chose between 0 and 3\n");
		return FAILED;
	}

	led_file = fopen(ob_led_brightness_path[led], "w+" );

	if (!led_file)
	{
		printf("File not found\n");
		fclose(led_file);
		return FAILED;
	}
	else
	{
	fprintf(led_file, "%d", 0);
	fclose(led_file);
	printf("LED (%s) on\n", ob_led_path.brightness[led]);
	return SUCCESS;
	}
}
/*--------------LED Toggle--------------*/
int on_board_led_toggle(ob_bbb_led ob_led_path, int led)
{
	char old_value;

	led_file = fopen(ob_led_path.brightness[led], "r+" );
	fscanf(led_file, "%c", old_value);
	fclose(led_file);

	printf("This is init value: %c\n", old_value);

	if(!strcmp(old_value, "0"))
	{
		on_board_led_on(ob_led_path, led);
		return SUCCESS;
	}
	else if(strcmp(old_value, "0"))
	{
		on_board_led_off(ob_led_path, led);
		return SUCCESS;
	}
	else
		return FAILED;
}

