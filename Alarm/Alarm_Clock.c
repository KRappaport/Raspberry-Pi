#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include "alrm_fncs.h"
#include "prfl_fncs.h"


int main()
{
	time_t test;
	struct tm *info;
	HEAP main_heap, reheap;
	ALARM current;
	char vol_change[14], path[55];
	int current_psec, alarm_psec, done;

	init_load(&main_heap, &reheap);

	if (main_heap.size == 0) {
		heap_swap(&main_heap, &reheap);
	}

	while (1) {
		current = main_heap.heap[0];
		main_heap.size--;

		if (current.on_off) {
			alarm_psec = ((current.alarm_time[0])*HOUR_SEC) + (current.alarm_time[1]*MIN_SEC);

			done = 0;
			while (!done) {
				test = time(NULL);
				info = localtime(&test);
				current_psec = (info->tm_hour * HOUR_SEC) + (info->tm_min * MIN_SEC);
				if(alarm_psec == current_psec) {
					sprintf(vol_change, "mpc volume %d", current.volume);
			        system(vol_change);
					mpd_play();

					if (!current.rpt) {
						current.on_off = 0;
						create_path(path, current.alarm_name);
						write_profile(path, current);
					}

					done = 1;
				}
				else if (alarm_psec < current_psec) {
					sleep(((DAY_SEC + alarm_psec) - current_psec)/2);
				}
				else {
					sleep((alarm_psec - current_psec)/2);
				}
			}
		}

		insert_to_heap(&reheap, current);

		if (main_heap.size == 0) {
			heap_swap(&main_heap, &reheap);
		} else {
			main_heap.heap[0] = main_heap.heap[main_heap.size];
			heapify_down(&main_heap, 0);
		}

	}


	return(0);
}
