#include <stdio.h>
#include "prfl_fncs.h"

int main() {
    ALARM profile;
    int status;
    FILE *profile_list;
    char path[55];

    profile_list = fopen("/home/pi/Raspberry-Pi/Alarm/profile_list.txt", "r");

    while (fscanf(profile_list, "%s", path) != EOF) {
        profile = read_profile(path);
        printf("%d\n%s\n%d\n%d\t%d\n%d\n%d\n%d\n", profile.name_length, profile.alarm_name, profile.on_off, profile.alarm_time[0], profile.alarm_time[1], profile.volume, profile.rpt, profile.priority);
    }

    return(0);
}
