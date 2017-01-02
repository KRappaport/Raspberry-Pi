#include <stdio.h>

int main(int argc, char const *argv[])
{

    FILE *alarm_profile;
    short int alarm_time[2], rpt, on-off, i=1;
    int name_length;
    char alarm_name[50], path[100];

    if (argc <= 1) {
        printf("Please provide alarm name:\n");
        exit(1);
    }
    sprintf(path, "/home/pi/Raspberry-Pi/Alarm/Profiles/%s", argv[i]);
    argc--;
    while (argc > 1) {
        i++;
        strcat(path, "_");
        strcat(path, argv[i]);
        argc--;
    }
    strcat(path, ".alrm");

    alarm_profile = fopen(path, "wb");

    printf("Turn alarm on or off (1 = on, 0 = off): ");
    scanf("%d", &on-off);
    fwrite(&on-off, sizeof(short), 1, alarm_profile);
    putchar('\n');

    printf("Enter alarm hour (0-23): ");
    scanf("%d", &alarm_time[0]);
    putchar('\n');
    printf("Enter alarm minute (0-59): ");
    scanf("%d", &alarm_time[1]);
    putchar('\n');
    fwrite(alarm_time, sizeof(short), 2, alarm_profile);
    printf("Choose if alarm should repeat (1 = repeat, 0 = don't repeat): ");
    scanf("%d", &rpt);
    fwrite(rpt, sizeof(short), 1, alarm_profile);
    printf("OK alarm is set.\n");


    fclose(alarm_profile);

    return(0);
}
