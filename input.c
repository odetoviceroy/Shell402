// .c file for supplementing the input functions for reading lines in shell402.c

#include <stdio.h>
#include <stdlib.h>

char * getLine(FILE * finp){
  char * buffer = (char *)malloc(sizeof(char) * 255);
  int i = 0;
  char c;
  c = fgetc(finp);
  while( c != '\n' && c != '\r' ){
    if(feof(finp)) break;
    buffer[i] = c;
    //printf("%c %d\n", c, i);
    i++;
    c = fgetc(finp);
  }
  buffer[i] = '\0';
  return buffer;
}
