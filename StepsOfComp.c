#include <stdio.h>

#define MAX_VALUES	10
#define SETBITINBYTE(t, pos) (t |= 1 << pos -1 )
#define UNSETBITINBYTE(t, pos) (t &= ~( 1 << pos -1 ))
#define FLIPBITINBYTE(t, pos) ( t = t ^ (1 << pos -1))
typedef struct NoElem
{
};
printbits(unsigned char ch)
{
        unsigned char a = 128;
        int i =0;
        printf("[%d]:\t", ch);
        for( i = 0 ; i < 8; i++)
        {
                if(ch & a )
                        printf("1 ");
                else
                        printf("0 ");
                a = a >> 1;
        }
        printf("\n");
}
volatile int VolMem;
int GlobalMem;
int main()
{
	register char ch = MAX_VALUES;
	char c = 'a';
	int LocalMem;
	printf("address of volatile[%x] Global[%x]Local[%x]\n", &VolMem, &GlobalMem, &LocalMem);
	printf("Sizeof empty stru[%d]\n", sizeof(struct NoElem));
	printf("Cannot print address of registry variiables \n"); 
	printf("value is [%d]add[%p][%c]\n",ch, &c,c);
	printf("Compilatoin steps: \n");
	printf("1. Preprocessor option: gcc -E file.c >> file.I \n");
	printf("2. Compiler option: gcc -S file.c output: file.s \n");
	printf("3. Assembler optoin gcc-c file.c output: file.o \n");
	printf("4. Linker optoin gcc file.c output: file.o \n");
	printf("5. exe outpu: gcc -o file file.c \n");
	printbits(ch);
	FLIPBITINBYTE(ch, 2);	
	printbits(ch);
	SETBITINBYTE(ch, 3);
	printbits(ch);
	UNSETBITINBYTE(ch,3);
	printbits(ch);
	return 0;
}

