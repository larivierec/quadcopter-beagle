/*
 * onboard_led_control.c

 *
 *  Created on: Feb 21, 2015
 *      Author: tony
 */
#include "onboard_led_control.h"

FILE *led_file;
char old_value[1];


char *ob_led_brightness_path[] = {"/sys/class/leds/beaglebone\\:green\\:usr0/brightness",
								  "/sys/class/leds/beaglebone\\:green\\:usr1/brightness",
								  "/sys/class/leds/beaglebone\\:green\\:usr2/brightness",
								  "/sys/class/leds/beaglebone\\:green\\:usr3/brightness"};

char *ob_led_trigger_path[] =    {"/sys/class/leds/beaglebone\\:green\\:usr0/trigger",
	    						  "/sys/class/leds/beaglebone\\:green\\:usr1/trigger",
								  "/sys/class/leds/beaglebone\\:green\\:usr2/trigger",
								  "/sys/class/leds/beaglebone\\:green\\:usr0/trigger"};

void remove_trigger(int led)
{
	led_file = fopen(ob_led_trigger_path[led], "w+" );
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

	led_file = fopen(ob_led_brightness_path[led], "w+" );

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
	printf("LED (%s) on\n", ob_led_brightness_path[led]);
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

	if(old_value[0] == "0")
	{
		on_board_led_on(led);
		return SUCCESS;
	}
	else if(old_value[0] == "1")
	{
		on_board_led_on(led);
		return SUCCESS;
	}
	else
		return FAILED;
}

