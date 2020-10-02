
// https://leetcode.com/problems/count-all-possible-routes/
/*
You are given an array of distinct positive integers locations where locations[i] represents the position of city i. 
You are also given integers start, finish and fuel representing the starting city, ending city, and the initial amount of fuel you have, respectively.

At each step, if you are at city i, you can pick any city j such that j != i and 0 <= j < locations.length and move to city j. 
Moving from city i to city j reduces the amount of fuel you have by |locations[i] - locations[j]|. Please notice that |x| denotes the absolute value of x.

Notice that fuel cannot become negative at any point in time, and that you are allowed to visit any city more than once (including start and finish).

Return the count of all possible routes from start to finish.

Since the answer may be too large, return it modulo 10^9 + 7.
*/

/* STRATEGIES:
   - You may go ANYWHERE if fuel allows (except the current location)
   - 'start == finish' case also counts
   - The trip finishes ONLY when you're run out of fuel
   - You may continue your trip EVEN when you've visited the FINISHING point
*/
/* ALGORITHM:
   i the current location, x the leftover amount of fuel:
   f(i, x) = { SUM(f(j, x-|locations[i] - locations[j]|) + 1) if j == finish,
               SUM(f(j, x-|locations[i] - locations[j]|)) o.w. } for 0 <= j < N where N = locations.length
*/

#define MOD_NUM 1000000007
#define LOC_MAX 100
#define FUEL_MAX  200
int dp[LOC_MAX][FUEL_MAX+1];
int N;
int abs(int x) {
    return ( (x)>0 ? (x) : ((-1) * (x)) );
}

int f(int i, int x, int *arr, int N, int finish)
{
    if (dp[i][x] != -1) return dp[i][x];
    
    dp[i][x] = 0;
    int ret = 0;
   
    int j;
    for(j=0; j<N; ++j) {
        if (j == i) continue;
        if (x < abs(arr[i]-arr[j])) continue;
        if (j == finish) {
            ret += (f (j, x-abs(arr[i]-arr[j]), arr, N, finish)+1);
            ret %= MOD_NUM;
        } else {
            ret += f(j, x-abs(arr[i]-arr[j]), arr, N, finish);
            ret %= MOD_NUM;
        }
        
    }
    return (dp[i][x] = ret);

}

int countRoutes(int* locations, int locationsSize, int start, int finish, int fuel){
    int i, j;
    
    for(i=0; i<LOC_MAX; ++i) for(j=0; j<FUEL_MAX+1; ++j) dp[i][j] = -1;
    int ret = f(start, fuel, locations, locationsSize, finish);
    if (start == finish) ret += 1, ret %= MOD_NUM;
    return ret;

}
