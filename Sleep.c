#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#define MINUTE 60
#define HOUR 3600

void mpd_play(void);

int main(int argc, char const *argv[]) {

    int hour=0, minute=0, volume, vol_bool=0, i;
    long unsigned int sleep_time;
    FILE *sound;
    char sound_check[100], vol_change[14];

//  Checks command-line arguements.
    if(argc > 1){
        while(--argc>0 && (*++argv)[0] == '-'){
            switch ((*argv)[1]) {
                case 'h':
                    hour = atoi((*++argv));
                    argc--;
                    break;
                case 'm':
                    minute = atoi((*++argv));
                    argc--;
                    break;
                case 'v':
                    volume = atoi((*++argv));
                    argc--;
                    vol_bool = 1;
                    break;
                default:
                    printf("'\'%s\' is an invalid :\n", (*argv)[1]);
                    argc = 0;
                    break;
            }
        }
    }
//  Asks for user input in the event that either no or invalid command-line arguements are supplied.
    if(minute == 0 && hour == 0){
        printf("Input sleep time: ");
        scanf("%d", &hour);
        scanf("%d", &minute);
    }

//  Converts inputed hours and minutes to seconds.
    sleep_time = (hour*HOUR) + (minute*MINUTE);

//  Checks if music is already playing.
    sound = fopen("/proc/asound/card0/pcm0p/sub0/status", "r");
    fscanf(sound, "%s", sound_check);
    fclose(sound);

    //Change Volume.
    if (vol_bool) {
        sprintf(vol_change, "mpc volume %d", volume);
        system(vol_change);
    }
//  Calls mpd_play to turn on music if not already playing.
    if (strcmp(sound_check, "closed") == 0) {
        mpd_play();
    }

//  Pauses the program for the amount of time inputed by user.
    sleep(sleep_time);
//  After which music is stopped.
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
		sleep(10);
		sound = fopen("/proc/asound/card0/pcm0p/sub0/status", "r");
		fscanf(sound, "%s", sound_check);
		fclose(sound);
	}while(strcmp(sound_check, "closed") == 0);

}
