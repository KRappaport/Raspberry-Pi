#include <stdio.h>

int main(int argc, char const *argv[])
{

    FILE *hour;
    FILE *minute;
    FILE *repeat;
    int hr, min, rpt;

    hour = fopen("~/Raspberry-Pi/Alarm/hour.txt", "w");
    minute = fopen("~/Raspberry-Pi/Alarm/minute.txt", "w");
    repeat = fopen("~/Raspberry-Pi/Alarm/repeat.txt", "w");

    printf("Enter alarm time: ");
    scanf("%d", &hr);
    scanf("%d", &min);
    printf("Choose if alarm should repeat (1 = repeat, 0 = don't repeat): ");
    scanf("%d", &rpt);
    printf("OK alarm is set.\n");

    fprintf(hour, "%d", hr);
    fprintf(minute, "%d", min);
    fprintf(repeat, "%d", rpt);

    fclose(hour);
    fclose(minute);
    fclose(repeat);

    return(0);
}
