// 200420 misc.
// take an ip address of string type
// then convert it to hexadecimal.
//
// cf. To check whether your system is Little or Big endian:
// $ echo -n I | od -to2 | head -n1 | cut -f2 -d" " | cut -c6 
// 1: Little, 0: Big

/**
 * Apr 20th, 2020:
 * A simple api which converts an IP addr of type string into hex
 * Assuming the input follows IPv4 format(x.x.x.x) correctly:
 * the api must be used at one's own risk.
 */

#include <stdio.h>

unsigned int ip2hex(char *ip)
{
	unsigned char ipblock[4] = {0,}; 
	unsigned int x = 0;
	char *p = ip;
	int i=0;
	unsigned int ret = 0;

	if (p == NULL) return 0;

	while (*p != '\0') {
		if (*p == '.') {
			ipblock[i++] = x;
			x=0, p++;
			continue;
		}
		x = 10*x + (*p) - '0';
		p++;
	}

	ipblock[i++] = x;

	for(i=0; i<4; ++i) {
		ret <<= 8;
		ret |= ipblock[i];
	}

	return ret;
}

int main(int argc, char **argv)
{
	if (argc != 2)
	{
		printf("Usage: ./ip2hex.o <x.x.x.x>\n");
		goto _OUT;
	}

	char *ip = argv[1];

	unsigned int hex = ip2hex(ip);
	printf("ret: 0x%x\n", hex);

_OUT:
	return 0;
}
