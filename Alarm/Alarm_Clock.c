#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

int main()
{
	time_t test;
	struct tm *info;
	int wake_hour;
	int wake_minute;
	int repeat_boolean;
	FILE *sound;
	FILE *hour;
	FILE *minute;
	FILE *repeat;
	char sound_check[100];

	while(1)
	{
		hour = fopen("hour.txt", "r");
		minute = fopen("minute.txt", "r");
		fscanf(hour, "%d", &wake_hour);
		fscanf(minute, "%d", &wake_minute);
		fclose(hour);
		fclose(minute);
		test = time(NULL);
		info = localtime(&test);
		if(info->tm_hour==wake_hour && info->tm_min==wake_minute)
		{
			do{
				system("mpc stop");
				sleep(1);
				system("mpc play");
				sleep(5);
				sound = fopen("/proc/asound/card0/pcm0p/sub0/status", "r");
				fscanf(sound, "%s", sound_check);
				fclose(sound);
			}while(strcmp(sound_check, "closed") == 0);
			repeat = fopen("repeat.txt", "r");
			fscanf(repeat, "%d", &repeat_boolean);
			if(!repeat_boolean)
				break;
		}
		sleep(5);
	}
	return(0);
}
