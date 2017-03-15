#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

#define MIN_SEC 60
#define HOUR_SEC 3600
#define DAY_SEC 86400

typedef struct alarm_profile
{
	int name_length;
	char alarm_name[15];
	short int on_off;
	short int alarm_time[2];
	short int volume;
	short int rpt;
	int priority;
}ALARM;

ALARM read_profile(char *path);
void mpd_play(void);

int main()
{
	time_t test;
	struct tm *info;
	ALARM profile;
	FILE *profile_list;
	char path[55], vol_change[14];
	int current_psec, alarm_psec;

	profile_list = fopen("/home/pi/Raspberry-Pi/Alarm/profile_list.txt", "r");
	fscanf(profile_list, "%s", path);

	profile = read_profile(path);
	alarm_psec = ((profile.alarm_time[0])*HOUR_SEC) + (profile.alarm_time[1]*MIN_SEC);

	while(1)
	{
		test = time(NULL);
		info = localtime(&test);
		current_psec = (info->tm_hour * HOUR_SEC) + (info->tm_min * MIN_SEC);
		if(alarm_psec == current_psec)
		{
			sprintf(vol_change, "mpc volume %d", profile.volume);
	        system(vol_change);
			mpd_play();
			if(!profile.rpt)
				break;
		}
		else if (alarm_psec < current_psec) {
			sleep(((DAY_SEC + alarm_psec) - current_psec)/2);
		}
		else {
			sleep((alarm_psec - current_psec)/2);
		}
	}
	return(0);
}

ALARM read_profile(char *path){
	ALARM profile;
	FILE *fp;

	fp = fopen(path, "rb");

	fread(&profile.name_length, sizeof(int), 1, fp);
	fread(profile.alarm_name, sizeof(char), profile.name_length, fp);
	fread(&profile.on_off, sizeof(short), 1, fp);
	fread(profile.alarm_time, sizeof(short), 2, fp);
	fread(&profile.volume, sizeof(short), 1, fp);
	fread(&profile.rpt, sizeof(short), 1, fp);

	profile.priority = ((int)profile.alarm_time[0] * 100) + (int)profile.alarm_time[1];

	return(profile);
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
