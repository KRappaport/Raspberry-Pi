#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

/* typedef struct alarm_profile
{
	int name_length;
	char alarm_name[50];
	short on_off;
	short hour;
	short minute;
}ALARM */

void mpd_play(void);

int main()
{
	time_t test;
	struct tm *info;
	int on_off, alarm_time[2], rpt;
	FILE *alarm_profile;

	while(1)
	{
		alarm_profile = fopen("/home/pi/Raspberry-Pi/Alarm/Profiles/wake_up.alrm", "rb");
		fread(&on_off, sizeof(short), 1, alarm_profile);
		fread(alarm_time, sizeof(short), 2, alarm_profile);
		fread(&rpt, sizeof(short), 1, alarm_profile);
		fclose(alarm_profile);
		test = time(NULL);
		info = localtime(&test);
		if(info->tm_hour==alarm_time[0] && info->tm_min==alarm_time[1])
		{
			mpd_play();
			if(!rpt)
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
		sleep(15);
		sound = fopen("/proc/asound/card0/pcm0p/sub0/status", "r");
		fscanf(sound, "%s", sound_check);
		fclose(sound);
	}while(strcmp(sound_check, "closed") == 0);

}
