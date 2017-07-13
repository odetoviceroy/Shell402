// George Juarez - Project shell402
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <limits.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <unistd.h> // need this for cygwin64 terminal

#include "shell402functs.h"
#include "input.h"

#define BUFFERSIZE 255

int main(int argc, char * argv[]){
  DIR * dir;
  struct dirent * ent;
  //------------ time to open the current directory ---------------
  if((dir = opendir(".")) == NULL){ printf("Cannot open current directory.\n"); exit(1); }
  //------------ time to check for correct argc ------------------
  if(argc > 2){ printf("Wrong number of command line arguments. Usage: \n\tshell402\n\tshell402 scriptfile\n"); exit(1); }
  //--------------------------------------------------------------
  //------------ Case 1: shell402 scriptfile ----------------
  if(argc == 2){
    FILE * finp = fopen(argv[1], "r");
    int counter = 0;
    if(finp == NULL) { printf("Error in opening file.\n"); exit(1); }
    while(!feof(finp)){
      if(feof(finp)) break;
      char * buffer = getLine(finp);
      if(counter % 2 == 0){
        printf("LINE READ: %s WITH SIZE %d\n", buffer, strlen(buffer));
        dir = processShellCommand(buffer, dir);
      }
      buffer[0] = '\0';
      free(buffer);
      counter += 1;
    }
  }
  //--------------------------------------------------------------
  //------------ Case 2: argv is just "shell402" -----------------
  else{
    printf("Welcome to Shell402!\nIf you have any questions as to what commands you may use on this program, type help.\n");
    char * buffer; // buffer string to hold the next command
    printf("Please enter a command: ");
    buffer = (char *)malloc(sizeof(char) * BUFFERSIZE);
    while(fgets(buffer, BUFFERSIZE, stdin) != NULL){
      dir = processShellCommand(buffer, dir);
      buffer[0] = '\0'; // flush buffer for next command
      printf("Please enter a command: "); // ready for next command
    }
  }
  closedir(dir); return 0;
}
