// TBD: too slow - need to be optimized in any way

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MIN(x, y)			( (x) < (y) ? (x) : (y) )
#define MAX(x, y)			( (x) > (y) ? (x) : (y) )

struct data {
	int index;
	int val;
	int mark;
} typedef DATA;

DATA r_min[50];
int retarr[50];
int *luckyNumbers(int **matrix, int matrixSize, int* matrixColSize, int* returnSize)
{
    //memset(retarr, 0, sizeof(retarr));
    for(int i=0; i<50; ++i) {
        r_min[i].index = 0; r_min[i].val = 0; r_min[i].mark = 0;
    }
	int row = matrixSize;
	int col = *matrixColSize;
	int cnt=0;

	for(int r=0; r<row; ++r) {
		r_min[r].index = 0;
		r_min[r].val = matrix[r][0];
		for(int c=0; c<col; ++c) {
			if(r_min[r].val > matrix[r][c]) {
				r_min[r].val = matrix[r][c]; 
                r_min[r].index = c; 
                r_min[r].mark = 0;
			}
		}
	}


	for(int r=0; r<row; ++r) {
		for(int i=0; i<row; ++i) {
			if(r_min[r].val < matrix[i][r_min[r].index]) {
				r_min[r].mark = 1;
				break;
			}
		}
		if (r_min[r].mark == 0) {cnt = cnt+1;}
	}
    
	
	int j=0;
	for(int r=0; r<row; ++r) {
		if (r_min[r].mark == 0)
			retarr[j++] = r_min[r].val;
	}

    *returnSize = cnt;
	return retarr;
}
