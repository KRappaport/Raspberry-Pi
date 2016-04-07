#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
int main()
{

	time_t test;
        struct tm *info;
        int wake_hour = 6;
        int wake_minute = 0;
	FILE *fp;
        char c[100];

        while(1)
        {
                test = time(NULL);
                info = localtime(&test);
                if(info->tm_hour==wake_hour && info->tm_min==wake_minute)
		{
			do{
				system("mpc stop");
				sleep(1);
				system("mpc play");
				sleep(3);
				fp = fopen("/proc/asound/card0/pcm0p/sub0/status", "r");
				fscanf(fp, "%s", c);
			}while(strcmp(c, "closed") == 0);
			break;
		}
		sleep(5);
	}
	return(0);
}

