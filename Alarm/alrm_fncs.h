#ifndef ALRM_FNCS
#define ALRM_FNCS 1

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <unistd.h>
#include "prfl_fncs.h"


#define MIN_SEC 60
#define HOUR_SEC 3600
#define HOUR_MULTIPLIER 100
#define DAY_SEC 86400


typedef struct alarm_heap{
	ALARM *heap;
	int size;
}HEAP;

void heapify_down(HEAP *alarm_heap, int i) {
    int left, right, minimum=i;
	ALARM temp;
    left = (2*i) + 1;
    right = 2*(i + 1);

	if ((left < (alarm_heap->size -1)) && (alarm_heap->heap[left].priority < alarm_heap->heap[minimum].priority)) {
		minimum = left;
	}
	if ((right < (alarm_heap->size -1)) && (alarm_heap->heap[right].priority < alarm_heap->heap[minimum].priority)) {
		minimum = right;
	}
	if (i < minimum) {
		temp = alarm_heap->heap[i];
		alarm_heap->heap[i] = alarm_heap->heap[minimum];
		alarm_heap->heap[minimum] = temp;
		heapify_down(alarm_heap, minimum);
	}

}

void heapify(HEAP *notheap) {
	int i=0;

    for (i = parent(notheap->size); i >= 0; i--) {
    	heapify_down(notheap, i);
    }
}

void init_load(HEAP *main_heap, HEAP *reheap) {
	int current_priority, i, status;
	time_t test;
	struct tm *info;
	FILE *profile_list;
	char path[55];
	ALARM profile;
	main_heap->size = 0;
	reheap->size = 0;

	main_heap->heap = (ALARM*)malloc(sizeof(ALARM)*5);
	reheap->heap = (ALARM*)malloc(sizeof(ALARM)*5);

	if (main_heap->heap == NULL || reheap->heap == NULL) {
		perror("Oh No!");
		exit(1);
	}

	test = time(NULL);
	info = localtime(&test);
	current_priority = (info->tm_hour * HOUR_MULTIPLIER) + (info->tm_min);

	profile_list = fopen("/home/pi/Raspberry-Pi/Alarm/profile_list.txt", "r");
	for (i = 0; i <= 4; i++) {
		status = fscanf(profile_list, "%s", path);
		if (status == EOF) {
			break;
		}
		profile = read_profile(path);
		if (profile.priority < current_priority) {
			main_heap->heap[main_heap->size] = profile;
			main_heap->size++;
		}
	/*else if (profile.priority == current_priority) {
			/* code */
		//}
		else {
			reheap->heap[reheap->size] = profile;
			reheap->size++;
		}
	}

	heapify(main_heap);
	heapify(reheap);

}

int parent(int child) {
	int par;
	par = (child - 2)/2;
	return(par);
}

void insert_to_heap(HEAP *addto, ALARM toadd) {
	int i;

	addto->heap[addto->size] = toadd;
	addto->size++;
	i = addto->size;

	while ((i>1) && (addto->heap[i].priority < addto->heap[parent(i)].priority)) {
		toadd = addto->heap[parent(i)];
		addto->heap[parent(i)] = addto->heap[i];
		addto->heap[i] = toadd;
		i = parent(i) + 1;
	}
}

void mpd_play(void){

	FILE *sound;
	char sound_check[100];

	do{
		system("mpc stop");
		sleep(1);
		system("mpc play");
		sleep(15);
		sound = fopen("/proc/asound/card0/pcm0p/sub0/status", "r");
		fscanf(sound, "%s", sound_check);
		fclose(sound);
	}while(strcmp(sound_check, "closed") == 0);

}

void heap_swap(HEAP *main_heap, HEAP *reheap) {
	free(main_heap->heap);
	*main_heap = *reheap;
	reheap->heap = (ALARM*)malloc(sizeof(ALARM)*5);

	if (reheap->heap == NULL) {
		perror("Oh No!");
		exit(1);
	}

	reheap->size = 0;
}

#endif
