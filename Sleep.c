#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#define MINUTE 60
#define HOUR 3600

void mpd_play(void);

int main(int argc, char const *argv[]) {

    int hour, minute;
    long unsigned int sleep_time;

    printf("Input sleep time: ");
    scanf("%d", &hour);
    scanf("%d", &minute);

    sleep_time = (hour*HOUR) + (minute*MINUTE);

    mpd_play();

    sleep(sleep_time);

    system("mpc stop");

    return(0);
}

void mpd_play(void){

	FILE *sound;
	char sound_check[100];

	do{
		system("mpc stop");
		sleep(1);
		system("mpc play");
		sleep(6);
		sound = fopen("/proc/asound/card0/pcm0p/sub0/status", "r");
		fscanf(sound, "%s", sound_check);
		fclose(sound);
	}while(strcmp(sound_check, "closed") == 0);

}
