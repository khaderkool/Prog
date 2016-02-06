#define SETBITINBYTE(t, pos) (t |= 1 << pos -1 )
#define UNSETBITINBYTE(t, pos) (t &= ~( 1 << pos -1 ))
#define FLIPBITINBYTE(t, pos) ( t = t ^ (1 << pos -1))
#define ISBITSETINBYTE(t, pos) (t & (1 << pos-1))
printbits(unsigned char ch)
{
        int i =0;
        printf("[%d]:\t", ch);
        for( i = 8 ; i >= 1; i--)
        {
		if(ISBITSETINBYTE(ch, i))
                        printf("1 ");
                else
                        printf("0 ");
        }
        printf("\n");
}
int swapbit_inbytes(unsigned char ch, int p1, int p2)
{
	if(ISBITSETINBYTE(ch, p1) && ISBITSETINBYTE(ch, p2))
		return 0;
	if(!ISBITSETINBYTE(ch, p1) && !ISBITSETINBYTE(ch, p2))
		return 0;
	FLIPBITINBYTE(ch, p1);// ( t = t ^ (1 << pos -1))
	FLIPBITINBYTE(ch, p2);
	printf("bits are diff need to swap \n");
	printbits(ch);
	return 1;	
}
int main()
{
	char ch = 10;
	int p;
	printbits(ch);
	printf("after setting bit 1 : \n");
	SETBITINBYTE(ch, 1);
	printbits(ch);
	UNSETBITINBYTE(ch, 1);
	
	printf("after unsetting bit 1 : \n");
	printbits(ch);
	printf("Swap 1 & 2 \n");
	swapbit_inbytes(ch, 1,2);
}
