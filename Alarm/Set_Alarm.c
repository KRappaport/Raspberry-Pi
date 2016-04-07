#include <stdio.h>

int main(int argc, char const *argv[])
{

    FILE *hour;
    FILE *minute;
    int hr, min;

    hour = fopen("hour.txt", "w");
    minute = fopen("minute.txt", "w");

    printf("Enter alarm time: ");
    scanf("%d", &hr);
    scanf("%d", &min);
    printf("ok\n");

    fprintf(hour, "%d", hr);
    fprintf(minute, "%d", min);

    fclose(hour);
    fclose(minute);

    return(0);
}
