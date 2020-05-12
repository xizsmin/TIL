#include <stdio.h>

int check_power_of_two(unsigned int x)
{
	return (x && ((x & (x - 1)) ==0));
}

int kth(unsigned int x, int lev)
{
	if (x == 1) return lev;
	if (check_power_of_two(x)) {
		int l=0;
		while( x >>= 1) ++l;
		return lev+l;
	}
	if (!(x & 1)) return kth(x/2, lev+1);
	else return kth(3*x+1, lev+1);

}


int main(int argc, char **argv)
{

	for(int i=1; i<1000; ++i) \
		printf("[%d]%d\n", i, kth((unsigned int)i, 0));

	return 0;
}

