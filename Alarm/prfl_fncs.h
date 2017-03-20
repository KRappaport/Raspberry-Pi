#ifndef PRFL_FNCS
#define PRFL_FNCS 1

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

typedef struct alarm_profile{
	int name_length;
	char alarm_name[15];
	short int on_off;
	short int alarm_time[2];
	short int volume;
	short int rpt;
	int priority;
}ALARM;

void create_path(char *path, const char *alarm_name) {
    char *location;
    sprintf(path, "/home/pi/Raspberry-Pi/Alarm/Profiles/%s", alarm_name);

    location = strchr(path, ' ');
    while (location != NULL) {
        *location = '_';
        location = strchr(path, ' ');
    }
    strcat(path, ".alrm");
}

void write_profile(char *path, ALARM profile) {
    FILE *alarm_profile;

    alarm_profile = fopen(path, "wb");
    fwrite(&profile.name_length, sizeof(int), 1, alarm_profile);
    fwrite(profile.alarm_name, sizeof(char), profile.name_length, alarm_profile);
    fwrite(&profile.on_off, sizeof(short), 1, alarm_profile);
    fwrite(profile.alarm_time, sizeof(short), 2, alarm_profile);
    fwrite(&profile.volume, sizeof(short), 1, alarm_profile);
    fwrite(&profile.rpt, sizeof(short), 1, alarm_profile);
    fclose(alarm_profile);
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

	fclose(fp);

	return(profile);
}

#endif
