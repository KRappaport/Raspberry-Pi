#include <stdio.h>
#include <time.h>

int main()
{
	time_t test;
	char c[] = "07:00";
	while(1)
	{
		test = time(NULL);
		if(strncmp(c,ctime(&test)+11,5)==0)
		{
			system("mpc play");
			break;
		}
	}
	return(0);
}

