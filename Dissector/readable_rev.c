#include <stdio.h>
#include <stdlib.h>
void usage()
{
  printf("Usage: reverse: string\n");
  exit (0);
}
char *strrev(char *s, int l)
{
  int i =0;
  char c;
  for (i = 0; i < l/2; i++)
  {
     c = s[i];
     s[i] = s[l-1-i];
     s[l-1-i] = c;
  }
  return s;
}

char * readable_strrev(char *s)
{
  char *p = s;
  char *start = s;

  strrev( s, strlen(s));
  while ( *p )
  {
    if (*p == ' ' || *p == '\t')
    {
      strrev(start, p - start);
      p++; //skip ' '
      start = p;
    }
    p++;
  }
 //last word; dont forget
  strrev(start, p - start);

}


int main(int argc, char *argv[])
{
  char s[] = "hello world. How are you?";

  printf(" orig: [%s] \n", s);
  printf(" reve: [%s] \n",strrev( s, strlen(s)));
  strrev( s, strlen(s));
  printf(" orig: [%s] \n",s);

  readable_strrev(s);

  printf("read: [%s] \n",s);
  return 0;
}
