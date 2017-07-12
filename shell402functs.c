// .c file serves to hold the utility functions of shell402.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <limits.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <unistd.h> // need this for cygwin64 terminal

char * wd(){
  char cDir[255];
  return getcwd(cDir, sizeof(cDir));
}

void quit(){
  printf("Goodbye, beautiful! :)\n");  // we finished!
  exit(0); return;
}

DIR * chwd(char * nextDir, DIR * dir){
    closedir(dir);
    if((dir = opendir(nextDir)) == NULL){ printf("Cannot open next working directory.\n"); }
    return dir;
}

DIR * processShellCommand(char * buffer, DIR * dir){
  char * currDir; // char pointer to hold the current directory
  buffer[strcspn(buffer, "\n")] = '\0';
  printf("BUFFER SCAN %s WITH SIZE %d\n", buffer, strlen(buffer));
  //----------- Case 1: handle the quit command --------------
  if(strcmp(buffer, "quit") == 0){
    free(buffer); closedir(dir);
    quit(); // call the quit() function in shell402functs.c
  }
  //----------------------------------------------------------
  //----------- Case 2: handle the wd command ----------------
  if(strcmp(buffer, "wd") == 0){
    currDir = wd(); // call the wd() function in shell402functs.c
    printf("FINAL DIRECTORY: %s\n", currDir);
    currDir[0] = '\0'; // flush currDir
  }
  //----------------------------------------------------------
  char keyWord[5]; // char array to hold the "chwd" keyword
  char * nextDir; // char pointer to hold the next working directory
  //----------- Case 3: handle the chwd command --------------
  strncpy(keyWord, buffer, 4);
  keyWord[4] = '\0';
  if(strcmp(keyWord, "chwd") == 0){
    nextDir = buffer + 5;
    printf("NEXT DIRECTORY: %s WITH SIZE %d\n", nextDir, strlen(nextDir));
    dir = chwd(nextDir, dir);
  }
  //----------------------------------------------------------
  keyWord[0] = '\0'; // flush keyWord
  return dir;
}
