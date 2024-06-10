#include <assert.h>
#include <stdio.h>

#include "max_gap.h"

int maxGap(int * array, int start, int end) {
	// printf("end=%d", end);
	if(end-start==2) return array[end-1] - array[start];
	if(end-start==1) return 0;

	int sx = maxGap(array, start, (end+start)/2);
	int dx = maxGap(array, (end+start)/2, end);

	return (sx>dx)? sx:dx;
}
