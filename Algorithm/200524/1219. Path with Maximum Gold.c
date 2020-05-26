// NO NEED TO APPLY ANY OPTIMIZATION

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define H_MAX			15
#define W_MAX			15
#define MAX(x, y)		( (x) > (y) ? (x) : (y) )
#define MAGIC_NUM		0


int visited[H_MAX][W_MAX];

int H, W;

int ans = 0;

int out_of_bound(int y, int x)
{
	return (y == H || x == W || y <0 || x < 0) ;
}

void f(int **grid, int y, int x, int sum, int lev)
{
	if (y == H || x == W || y <0 || x < 0) {
		ans = MAX(ans, sum);
		return;
	}
	visited[y][x] = 1;
    
	if (y < H-1 && !visited[y+1][x] && grid[y+1][x] != MAGIC_NUM)
		f(grid, y+1, x, sum + grid[y][x], lev+1);
	if (y > 0 && !visited[y-1][x] && grid[y-1][x] != MAGIC_NUM)
		f(grid, y-1, x, sum + grid[y][x], lev+1);
	if (x < W-1 && !visited[y][x+1] && grid[y][x+1] != MAGIC_NUM)
		f(grid, y, x+1, sum + grid[y][x], lev+1);
	if (x > 0 && !visited[y][x-1] && grid[y][x-1] != MAGIC_NUM)
		f(grid, y, x-1, sum + grid[y][x], lev+1);
	visited[y][x] = 0;
	ans = MAX(ans, sum+grid[y][x]);
}


int getMaximumGold(int** grid, int gridSize, int* gridColSize){
    H=gridSize;
    W=gridColSize[0];
    ans = 0;
    
	for(int y=0; y<H; ++y) {
		for(int x=0; x<W; ++x) {
            
			if (0 == grid[y][x]) 
				continue;
            
			for(int h=0; h<H; ++h) \
				memset(visited[h], 0, sizeof(visited[h]));
			f(grid, y, x, 0, 0);  
        }
    }

    
    return ans;

}
