
#define BITCOUNT(x)    (((BX_(x)+(BX_(x)>>4)) & 0x0F0F0F0F) % 255)
#define BX_(x)         ((x) - (((x)>>1)&0x77777777) - (((x)>>2)&0x33333333) - (((x)>>3)&0x11111111))
int	main()
{
	int i =  0b111111111111111111111111;
	printf("%#d\n", BITCOUNT(i));
	return (0);
}
