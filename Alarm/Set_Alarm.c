#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct alarm_profile
{
	int name_length;
	char alarm_name[15];
	short int on_off;
	short int alarm_time[2];
	short int volume;
	short int rpt;
}ALARM;

int main(int argc, char const *argv[])
{

    FILE *alarm_profile, *profile_list;
    ALARM profile;
    char path[55];
    int i=1;

    if (argc <= 1) {
        printf("Please provide alarm name:\n");
        exit(1);
    }

    sprintf(path, "/home/pi/Raspberry-Pi/Alarm/Profiles/%s", argv[i]);
    strcpy(profile.alarm_name, argv[i]);
    argc--;
    while (argc > 1) {
        i++;
        strcat(profile.alarm_name, " ");
        strcat(profile.alarm_name, argv[i]);
        strcat(path, "_");
        strcat(path, argv[i]);
        argc--;
    }
    strcat(path, ".alrm");
    profile.name_length = strlen(profile.alarm_name);

    profile_list = fopen("/home/pi/Raspberry-Pi/Alarm/profile_list.txt", "a");
    fputs(path, profile_list);
    fputc('\n', profile_list);

    alarm_profile = fopen(path, "wb");

    fwrite(&profile.name_length, sizeof(int), 1, alarm_profile);
    fwrite(profile.alarm_name, sizeof(char), profile.name_length, alarm_profile);


    printf("Turn alarm on or off (1 = on, 0 = off): ");
    scanf("%hd", &profile.on_off);
    fwrite(&profile.on_off, sizeof(short), 1, alarm_profile);
    putchar('\n');

    printf("Enter alarm hour (0-23): ");
    scanf("%hd", &profile.alarm_time[0]);
    putchar('\n');
    printf("Enter alarm minute (0-59): ");
    scanf("%hd", &profile.alarm_time[1]);
    putchar('\n');
    fwrite(profile.alarm_time, sizeof(short), 2, alarm_profile);

    printf("Enter alarm volume (0-100): ");
    scanf("%hd", &profile.volume);
    putchar('\n');
    fwrite(&profile.volume, sizeof(short), 1, alarm_profile);

    printf("Choose if alarm should repeat (1 = repeat, 0 = don't repeat): ");
    scanf("%hd", &profile.rpt);
    fwrite(&profile.rpt, sizeof(short), 1, alarm_profile);

    printf("OK alarm is set.\n");


    fclose(alarm_profile);

    return(0);
}
