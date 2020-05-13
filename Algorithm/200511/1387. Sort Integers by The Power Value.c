#include <stdio.h>
#include <stdlib.h>

struct pow {
	int num;
	int power;
};

int check_power_of_two(unsigned int x)
{
	return (x && ((x & (x - 1)) ==0));
}

int kth(struct pow x, int lev)
{
	if (x.power == 1) return lev;
	if (check_power_of_two(x.power)) {
		int l=0;
		while( x.power >>= 1) ++l;
		return lev+l;
	}

	if (!(x.power & 1)) {
		x.power >>= 1;
		return kth(x, lev+1);
	}
	else {
		x.power = x.power * 3 + 1;
		return kth(x, lev+1);
	}

}

int static compare (const void* first, const void* second)
{
	struct pow *_first = (struct pow *)first;
	struct pow *_second = (struct pow *)second;

	if (_first->power > _second->power)
        return 1;
 
    else if (_first->power < _second->power)
        return -1;
    else
        return 0;
}

int getKth(int lo, int hi, int k)
{
	struct pow *tmp = (struct pow *)malloc(sizeof(struct pow) * (hi-lo+1) );
	for(int i=lo; i<=hi; ++i) {
		tmp[i-lo].num = i;
		tmp[i-lo].power = i;
		tmp[i-lo].power = kth(tmp[i-lo], 0);
	}
	qsort(tmp, hi-lo+1, sizeof(struct pow), compare);
	return tmp[k-1].num;
}

int main(int argc, char **argv)
{
    printf("%d\n", getKth(7,11,4));
	return 0;
}

