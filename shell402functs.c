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

void forkListProcess(char * buffer){
  pid_t child; // child pid returned by fork
  int cStatus; // exit status of child
  pid_t waitC; // pid of child to be returned by wait
  printf("LIST COMMAND %s OF SIZE %d\n", buffer, strlen(buffer));
  if((child = fork()) == 0){
    if(strcmp(buffer, "list") == 0){  // command is "list"
      execlp("./list.exe", "list", NULL); // TODO: SWITCH TO LIST INSTEAD OF ./LIST.EXE PLEASEEES
    }
    if(strcmp(buffer, "list -i") == 0){  // command is "list -i"
      execlp("./list.exe", "list", "-i", NULL); // TODO: SWITCH TO LIST INSTEAD OF ./LIST.EXE PLEASEEES
    }
    if(strcmp(buffer, "list -h") == 0){  // command is "list -h"
      execlp("./list.exe", "list", "-h", NULL); // TODO: SWITCH TO LIST INSTEAD OF ./LIST.EXE PLEASEEES
    }
    char * flagDetect = malloc(sizeof(char) * 2); // string to hold the possible flags the list command might have
    char * pathName = malloc(sizeof(char) * (strlen(buffer) - 8));
    strncpy(flagDetect, buffer + 5, 2); // copy the flag name
    strncpy(pathName, buffer + 8, strlen(buffer) -7); // copy the pathname
    if(strcmp(flagDetect,"-i") == 0){ // command is "list -i pathname"
      printf("FLAG DETECTED: %s WITH PATHNAME %s\n", flagDetect, pathName);
      execlp("./list.exe", "list", "-i", pathName, NULL); // TODO: SWITCH TO LIST INSTEAD OF ./LIST.EXE PLEASEEES
      free(pathName); free(flagDetect);
    }
    if(strcmp(flagDetect,"-h") == 0){ // command is "list -h pathname"
      printf("FLAG DETECTED: %s WITH PATHNAME %s\n", flagDetect, pathName);
      execlp("./list.exe", "list", "-h", pathName, NULL); // TODO: SWITCH TO LIST INSTEAD OF ./LIST.EXE PLEASEEES
      free(pathName); free(flagDetect);
    }
    else{ // command is just "list pathname"
      free(pathName); free(flagDetect);   // free them, then reallocate pathName
      pathName = malloc(sizeof(char) * (strlen(buffer) - 5));
      strncpy(pathName, buffer + 5, strlen(buffer) - 5);
      printf("SOLE PATHNAME: %s\n", pathName);
      execlp("./list.exe", "list", pathName, NULL); // TODO: SWITCH TO LIST INSTEAD OF ./LIST.EXE PLEASEEES
      free(pathName); // free all the mallocs!!!!! >:0
    }
    free(pathName); free(flagDetect);
    fprintf(stderr, "Child process could not do execlp.\n"); exit(1); // error detect
  }
  else {
    waitC = wait(&cStatus);
    printf("Parent: Child %ld exited with status = %d\n", (long)waitC, cStatus);
  }
  return;
}

void forkCreateProcess(char * buffer){
  return;
}

DIR * processShellCommand(char * buffer, DIR * dir){
  char * currDir; // char pointer to hold the current directory
  char * temp = malloc(sizeof(char) * strlen(buffer)); // char pointer to copy buffer
  //strcpy(temp, buffer); temp[strlen(buffer)] = '\0';
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
  char keyWord[5]; // char array to hold the "chwd" or "list" keyword
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
  //-------- Case 4: handle the list-related commands --------
  if(strcmp(keyWord, "list") == 0){
    forkListProcess(buffer);
  }
  //----------------------------------------------------------
  /*
  char * childWord; // char pointer to hold possible "list" or "create" related command
  strncpy(childWord, temp, 4);
  childWord[4] = '\0';
  */
  keyWord[0] = '\0'; // flush keyWord
  free(temp);
  return dir;
}
