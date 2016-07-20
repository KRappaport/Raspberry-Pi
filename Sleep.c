#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#define MINUTE 60
#define HOUR 3600

void mpd_play(void);

int main(int argc, char const *argv[]) {

    int hour=0, minute=0, i;
    long unsigned int sleep_time;

    printf("%d\n", argc);

    if(argc > 1){
        while(--argc>0 && (*++argv)[0] == '-'){
            switch ((*argv)[1]) {
                case 'h':
                    hour = atoi((*++argv));
                    break;
                case 'm':
                    minute = atoi((*++argv));
                    break;
                default:
                    printf("'\'%s\' is an invalid :\n", (*argv)[1]);
                    argc = 0;
                    break;
            }
        }
    }
    if(minute == 0 && hour == 0){
        printf("Input sleep time: ");
        scanf("%d", &hour);
        scanf("%d", &minute);
    }

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
		sleep(10);
		sound = fopen("/proc/asound/card0/pcm0p/sub0/status", "r");
		fscanf(sound, "%s", sound_check);
		fclose(sound);
	}while(strcmp(sound_check, "closed") == 0);

}
