#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#define MINUTE 60
#define HOUR 3600

int main(int argc, char const *argv[]) {

    int hour, minute;
    long unsigned int sleep_time;
    FILE *sound;
    char sound_check[100];

    printf("Input sleep time: ", );
    scanf("%d", &hour);
    scanf("%d", &minute);

    sleep_time = (hour*HOUR) + (minute*MINUTE);

    do{
        system("mpc stop");
        sleep(1);
        system("mpc play");
        sleep(6);
        sound = fopen("/proc/asound/card0/pcm0p/sub0/status", "r");
        fscanf(sound, "%s", sound_check);
        fclose(sound);
    }while(strcmp(sound_check, "closed") == 0);

    sleep(sleep_time);

    system("mpc stop");

    return(0);
}
