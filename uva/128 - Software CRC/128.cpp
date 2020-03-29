#include <stdio.h>
#include <string.h>

#define G 34943

unsigned char line[1030];
int len;

unsigned short crc()
{
	int i;
	unsigned int d = 0;
	if(len == 0)
		return 0;
	for(i = 1; i < len; i += 2)
	{
		d = (d<<16)+(line[i-1]<<8)+line[i];
		d %= G;
	}
	if(i == len)
	{
		d = (d<<8)+line[len-1];
		d %= G;
	}
	d <<= 16;
	d %= G;
	return d == 0 ? 0 : G-d;
}

int main()
{
	unsigned short res;
	while(fgets((char *)line, sizeof(line), stdin))
	{
		if(line[0] == '#')
			break;
		len = strlen((char *)line)-1;
		line[len] = '\0';
		res = crc();
		printf("%02X %02X\n", (res & 0xff00)>>8, res & 0xff);
	}
	return 0;
}
