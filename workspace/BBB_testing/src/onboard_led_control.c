/*
 * onboard_led_control.c

 *
 *  Created on: Feb 21, 2015
 *      Author: tony
 */
#include "onboard_led_control.h"
#include <stdio.h>
#include <string.h>

 ob_bbb_led ob_led_path;

void init_ob_leb_paths()
{
	int i;

	ob_led_path.brightness = (char **)malloc(ON_BOARD_LED_COUNT*(sizeof(char *)));
	ob_led_path.trigger = (char **)malloc(ON_BOARD_LED_COUNT*(sizeof(char *)));

	for(i = 0; i < ON_BOARD_LED_COUNT; i++)
	{
		ob_led_path.brightness[i] = (char *)malloc(strlen("/sys/class/leds/beaglebone:green:usr0/brightness")*(sizeof(char)));
		ob_led_path.trigger[i] = (char *)malloc(strlen("/sys/class/leds/beaglebone:green:usr0/trigger")*(sizeof(char)));

		switch(i)
		{
			case (0):
				strcpy(ob_led_path.brightness[i],"/sys/class/leds/beaglebone:green:usr0/brightness");
				strcpy(ob_led_path.trigger[i], "/sys/class/leds/beaglebone:green:usr0/trigger");
			break;
			case (1):
				strcpy(ob_led_path.brightness[i],"/sys/class/leds/beaglebone:green:usr1/brightness");
				strcpy(ob_led_path.trigger[i], "/sys/class/leds/beaglebone:green:usr1/trigger");
			break;
			case (2):
				strcpy(ob_led_path.brightness[i],"/sys/class/leds/beaglebone:green:usr2/brightness");
				strcpy(ob_led_path.trigger[i], "/sys/class/leds/beaglebone:green:usr2/trigger");
			break;
			case (3):
				strcpy(ob_led_path.brightness[i],"/sys/class/leds/beaglebone:green:usr3/brightness");
				strcpy(ob_led_path.trigger[i], "/sys/class/leds/beaglebone:green:usr3/trigger");
			break;
		}
	}
}

void modify_trigger(Trigger_Mode mode, int led)
{
	FILE *led_file;
	char buffer[15];

	printf("Opening: %s\n", ob_led_path.trigger[led]);
	led_file = fopen(ob_led_path.trigger[led], "w" );


	switch(mode)
	{
		case NONE:
			strcpy(buffer, "none");
		break;
		case NAND_DISK:
			strcpy(buffer, "nand-disk");
		break;
		case MMC0:
			strcpy(buffer, "mmc0");
		break;
		case MMC1:
			strcpy(buffer, "mmc1");
		break;
		case TIMER:
			strcpy(buffer, "timer");
		break;
		case ONESHOT:
			strcpy(buffer, "oneshot");
		break;
		case HEARTBEAT:
			strcpy(buffer, "heartbeat");
		break;
		case BACKLIGHT:
			strcpy(buffer, "backlight");
		break;
		case GPIO:
			strcpy(buffer, "gpio");
		break;
		case CPU0:
			strcpy(buffer, "cpu0");
		break;
		case DEFAULT_ON:
			strcpy(buffer, "default-on");
		break;
		case TRANSIENT:
			strcpy(buffer, "transient");
		break;
		default:
			printf("Please enter a TRIGGER_MODE enum type\n");
			exit(1);
		break;
	}

	printf("Changing Trigger to %s\n", buffer);
	fwrite(buffer, 1, sizeof(buffer), led_file);
	fclose(led_file);
}


/*--------------LED switch ON-----------*/
int on_board_led_on(int led)
{
	FILE *led_file;

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
int on_board_led_off(int led)
{
	FILE *led_file;
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
	fprintf(led_file, "%d", 0);
	fclose(led_file);
	printf("LED (%s) on\n", ob_led_path.brightness[led]);
	return SUCCESS;
	}
}
/*--------------LED Toggle--------------*/
int on_board_led_toggle(int led)
{
	int old_value;
	FILE *led_file;

	led_file = fopen(ob_led_path.brightness[led], "r+" );
	fscanf(led_file, "%d", &old_value);
	fclose(led_file);

	printf("This is init value: %d\n", old_value);

	if(!old_value)
	{
		on_board_led_on(led);
		return SUCCESS;
	}
	else if(old_value)
	{
		on_board_led_off(led);
		return SUCCESS;
	}
	else
		return FAILED;
}

void clean_ob_bbb_led_path()
{
	int i;
		//free columns
		for(i = 0; i < ON_BOARD_LED_COUNT; i++)
	{
		free(ob_led_path.brightness[i]);
		free(ob_led_path.trigger[i]);
	}
		//free rows
		free(ob_led_path.brightness);
		free(ob_led_path.trigger);
}

