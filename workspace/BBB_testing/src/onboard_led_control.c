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
char old_value;

typedef struct bbb_led{
	char *brightness;
	char *trigger;
}bbb_led;


bbb_led ob_led[ON_BOARD_LED_COUNT];

void remove_trigger(int led)
{
	int i;

	for(i = 0; i < ON_BOARD_LED_COUNT; i++)
	{
		ob_led[i].brightness = (char *)malloc(STRING_OB_LED_PATH_LENGTH*(sizeof(char)));
		ob_led[i].trigger = (char *)malloc(STRING_OB_LED_PATH_LENGTH*(sizeof(char)));
		switch(i)
		{
			case (0):
				strcpy(ob_led[i].brightness,"/sys/class/leds/beaglebone\\:green\\:usr0/brightness");
				strcpy(ob_led[i].trigger, "/sys/class/leds/beaglebone\\:green\\:usr0/trigger");
			break;
			case (1):
				strcpy(ob_led[i].brightness,"/sys/class/leds/beaglebone\\:green\\:usr1/brightness");
				strcpy(ob_led[i].trigger, "/sys/class/leds/beaglebone\\:green\\:usr1/trigger");
			break;
			case (2):
				strcpy(ob_led[i].brightness,"/sys/class/leds/beaglebone\\:green\\:usr2/brightness");
				strcpy(ob_led[i].trigger, "/sys/class/leds/beaglebone\\:green\\:usr2/trigger");
			break;
			case (3):
				strcpy(ob_led[i].brightness,"/sys/class/leds/beaglebone\\:green\\:usr3/brightness");
				strcpy(ob_led[i].trigger, "/sys/class/leds/beaglebone\\:green\\:usr3/trigger");
			break;
		}
	}

	led_file = fopen(ob_led[led].trigger, "w" );
	fprintf(led_file, "none");
	fclose(led_file);
}


/*--------------LED switch ON-----------*/
int on_board_led_on(int led)
{

	if(led > 3)
	{
		printf("Chose between 0 and 3\n");
		return FAILED;
	}

	led_file = fopen(ob_led[led].brightness, "w+" );

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
	printf("LED (%s) on\n", ob_led[led].brightness);
	return SUCCESS;
	}

}
/*--------------LED switch off----------*/
int on_board_led_off(int led)
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
	printf("LED (%s) on\n", ob_led_brightness_path[led]);
	return SUCCESS;
	}
}
/*--------------LED Toggle--------------*/
int on_board_led_toggle(int led)
{
	led_file = fopen(ob_led_brightness_path[led], "r+" );
	fscanf(led_file, "%s", old_value);
	fclose(led_file);

	printf("This is init value: %c\n", old_value[0]);

	if(!strcmp(old_value, "0"))
	{
		on_board_led_on(led);
		return SUCCESS;
	}
	else if(!strcmp(old_value, "1"))
	{
		on_board_led_on(led);
		return SUCCESS;
	}
	else
		return FAILED;
}

