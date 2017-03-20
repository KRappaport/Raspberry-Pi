#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "prfl_fncs.h"


int main(int argc, char const *argv[])
{

    FILE *profile_list;
    ALARM profile;
    char path[55];
    int i=1;

    if (argc <= 1) {
        printf("Please provide alarm name:\n");
        exit(1);
    }

    strcpy(profile.alarm_name, argv[i]);
    argc--;
    while (argc > 1) {
        i++;
        strcat(profile.alarm_name, " ");
        strcat(profile.alarm_name, argv[i]);
        argc--;
    }
    profile.name_length = strlen(profile.alarm_name);

	create_path(path, profile.alarm_name);

    profile_list = fopen("/home/pi/Raspberry-Pi/Alarm/profile_list.txt", "a");
    fputs(path, profile_list);
    fputc('\n', profile_list);

    printf("Turn alarm on or off (1 = on, 0 = off): ");
    scanf("%hd", &profile.on_off);
    putchar('\n');

    printf("Enter alarm hour (0-23): ");
    scanf("%hd", &profile.alarm_time[0]);
    putchar('\n');
    printf("Enter alarm minute (0-59): ");
    scanf("%hd", &profile.alarm_time[1]);
    putchar('\n');

	printf("Enter alarm volume (0-100): ");
    scanf("%hd", &profile.volume);
    putchar('\n');

    printf("Choose if alarm should repeat (1 = repeat, 0 = don't repeat): ");
    scanf("%hd", &profile.rpt);

	write_profile(path, profile);

    printf("OK alarm is set.\n");

    return(0);
}
