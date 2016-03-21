#include <stdio.h>
#include <time.h>
#include <unistd.h>

int main()
{

	time_t test;
        struct tm *info;
        int wake_hour = 7;
        int wake_minute = 0;

        while(1)
        {
                test = time(NULL);
                info = localtime(&test);
                if(info->tm_hour==wake_hour && info->tm_min==wake_minute)
		{
			system("mpc play");
			break;
		}
		sleep(5);
	}
	return(0);
}

