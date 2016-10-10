#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

void mpd_play(void);

int main()
{
	time_t test;
	struct tm *info;
	int wake_hour;
	int wake_minute;
	int repeat_boolean;
	FILE *hour;
	FILE *minute;
	FILE *repeat;

	while(1)
	{
		hour = fopen("/home/pi/Raspberry-Pi/Alarm/hour.txt", "r");
		minute = fopen("/home/pi/Raspberry-Pi/Alarm/minute.txt", "r");
		fscanf(hour, "%d", &wake_hour);
		fscanf(minute, "%d", &wake_minute);
		fclose(hour);
		fclose(minute);
		test = time(NULL);
		info = localtime(&test);
		if(info->tm_hour==wake_hour && info->tm_min==wake_minute)
		{
			mpd_play();
			repeat = fopen("/home/pi/Raspberry-Pi/Alarm/repeat.txt", "r");
			fscanf(repeat, "%d", &repeat_boolean);
			fclose(repeat);
			if(!repeat_boolean)
				break;
		}
		sleep(5);
	}
	return(0);
}

void mpd_play(void){

	FILE *sound;
	char sound_check[100];

	do{
		system("mpc stop");
		sleep(1);
		system("mpc play");
		sleep(10);
		sound = fopen("/proc/asound/card0/pcm0p/sub0/status", "r");
		fscanf(sound, "%s", sound_check);
		fclose(sound);
	}while(strcmp(sound_check, "closed") == 0);

}
