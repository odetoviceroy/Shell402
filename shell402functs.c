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

#include "shell402functs.h"
#include "macros.h"

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
  printf("LIST COMMAND %s OF SIZE %d\n", buffer, strlen(buffer));
  if((child = fork()) == 0){
    if(strcmp(buffer, "list") == 0){  // command is "list"
      execlp(listExec, "list", NULL);
    }
    if(strcmp(buffer, "list -i") == 0){  // command is "list -i"
      execlp(listExec, "list", "-i", NULL);
    }
    if(strcmp(buffer, "list -h") == 0){  // command is "list -h"
      execlp(listExec, "list", "-h", NULL);
    }
    char * flagDetect = malloc(sizeof(char) * 2); // string to hold the possible flags the list command might have
    char * pathName = malloc(sizeof(char) * (strlen(buffer) - 8));
    strncpy(flagDetect, buffer + 5, 2); // copy the flag name
    strncpy(pathName, buffer + 8, strlen(buffer) -7); // copy the pathname
    if(strcmp(flagDetect,"-i") == 0){ // command is "list -i pathname"
      printf("FLAG DETECTED: %s WITH PATHNAME %s\n", flagDetect, pathName);
      execlp(listExec, "list", "-i", pathName, NULL); // TODO: SWITCH TO LIST INSTEAD OF ./LIST.EXE PLEASEEES
      free(pathName); free(flagDetect);
    }
    if(strcmp(flagDetect,"-h") == 0){ // command is "list -h pathname"
      printf("FLAG DETECTED: %s WITH PATHNAME %s\n", flagDetect, pathName);
      execlp(listExec, "list", "-h", pathName, NULL); // TODO: SWITCH TO LIST INSTEAD OF ./LIST.EXE PLEASEEES
      free(pathName); free(flagDetect);
    }
    else{ // command is just "list pathname"
      free(pathName); free(flagDetect);   // free them, then reallocate pathName
      pathName = malloc(sizeof(char) * (strlen(buffer) - 5));
      strncpy(pathName, buffer + 5, strlen(buffer) - 5);
      printf("SOLE PATHNAME: %s\n", pathName);
      execlp(listExec, "list", pathName, NULL); // TODO: SWITCH TO LIST INSTEAD OF ./LIST.EXE PLEASEEES
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
  printf("LIST COMMAND %s OF SIZE %d\n", buffer, strlen(buffer));
  if((child = fork()) == 0){
    char * flagDetect = malloc(sizeof(char) * 2); // string to hold the possible flags the create command might have
    char * pathName = malloc(sizeof(char) * (strlen(buffer) - 10));
    strncpy(flagDetect, buffer + 7, 2); // copy the flag name
    strncpy(pathName, buffer + 10, strlen(buffer) -10); // copy the pathname
    if(strcmp(flagDetect,"-f") == 0){ // command is "create -f filepath"
      printf("FLAG DETECTED: %s WITH PATHNAME %s\n", flagDetect, pathName);
      execlp(createExec, "create", "-f", pathName, NULL); // TODO: SWITCH TO CREATE INSTEAD OF ./CREATE.EXE PLEASEEES
      free(pathName); free(flagDetect);
    }
    if(strcmp(flagDetect,"-d") == 0){ // command is "create -d dirpath"
      printf("FLAG DETECTED: %s WITH PATHNAME %s\n", flagDetect, pathName);
      execlp("./create.exe", "create", "-d", pathName, NULL); // TODO: SWITCH TO CREATE INSTEAD OF ./CREATE.EXE PLEASEEES
      free(pathName); free(flagDetect);
    }
    char * oldName = strtok(pathName, " "); // split the pathName into oldName and linkName for -h, -s options
    char * newName = strtok(NULL, " ");
    printf("PATHNAME %s NEWNAME: %s\n", oldName, newName);
    if(strcmp(flagDetect,"-h") == 0){ // command is "create -h oldname linkname"
      printf("FLAG DETECTED: %s WITH PATHNAME %s\n", flagDetect, pathName);
      execlp("./create.exe", "create", "-h", oldName, newName, NULL); // TODO: SWITCH TO CREATE INSTEAD OF ./CREATE.EXE PLEASEEES
      free(pathName); free(flagDetect);
    }
    if(strcmp(flagDetect,"-h") == 0){ // command is "create -s oldname linkname"
      printf("FLAG DETECTED: %s WITH PATHNAME %s\n", flagDetect, pathName);
      execlp("./create.exe", "create", "-s", oldName, newName, NULL); // TODO: SWITCH TO CREATE INSTEAD OF ./CREATE.EXE PLEASEEES
      free(pathName); free(flagDetect);
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

void printHelp(){
  printf("This is Shell402. You may able to use several commands on this program. Here is a complete list of them:\n\n"
          "wd --- Displays the current working directory\nchwd pathname --- Changes the current working directory"
          " to the one specified in the second argument.\n"
          "----------------------------------\n"
          "list --- Displays all non-hidden files in the current directory\n"
          "list pathname -- Same as above, but with a specified pathname.\n"
          "list -i --- Displays all files in the current directory, their size (in bytes), permissions, and inode numbers.\n"
          "list -i pathname --- Same as above, but with a specified pathname.\n"
          "list -h --- Displays all hidden files in the current directory.\nlist -h pathname --- Same as above, but with a specified pathname.\n"
          "----------------------------------\n"
          "create -f filepath --- Create a new file with a specified pathname.\ncreate -d dirpath --- Create a new directory with specified pathname."
          "create -h oldname newname --- Create a hard link with a specified old name and a specified new name.\n"
          "create -s oldname newname --- Create a symbolic (soft) link with a specified old name and a specified new name.\n"
          "----------------------------------\nquit --- Exits out of the program.\n\n");
  return;
}

DIR * processShellCommand(char * buffer, DIR * dir){
  char * currDir; // char pointer to hold the current directory
  int isValid = 0; // flag to determine if the command given is a valid command
  //strcpy(temp, buffer); temp[strlen(buffer)] = '\0';
  buffer[strcspn(buffer, "\n")] = '\0';
  //----------- Case 1: handle the quit command --------------
  if(strcmp(buffer, "quit") == 0){
    isValid = 1; free(buffer); closedir(dir);
    quit(); // call the quit() function in shell402functs.c
  }
  //----------------------------------------------------------
  //----------- Case 2: handle the wd command ----------------
  if(strcmp(buffer, "wd") == 0){
    isValid = 1; currDir = wd(); // call the wd() function in shell402functs.c
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
    isValid = 1; nextDir = buffer + 5;
    printf("NEXT DIRECTORY: %s WITH SIZE %d\n", nextDir, strlen(nextDir));
    dir = chwd(nextDir, dir);
  }
  //----------------------------------------------------------
  //-------- Case 4: handle the list-related commands --------
  if(strcmp(keyWord, "list") == 0){
    isValid = 1; forkListProcess(buffer);
  }
  //----------------------------------------------------------
  char createWord[7]; // char array to hold the "create" keyword
  //-------- Case 5: handle the create-related commands ------
  strncpy(createWord, buffer, 6);
  createWord[6] = '\0';
  if(strcmp(createWord, "create") == 0){
    isValid = 1; forkCreateProcess(buffer);
  }
  //----------------------------------------------------------
  //-------- Case 6: handle the "help" command ---------------
  if(strcmp(keyWord,"help") == 0){
    isValid = 1; printHelp();
  }
  //----------------------------------------------------------
  if(isValid == 0){ printf("Not a valid command.\n"); }
  keyWord[0] = '\0'; // flush keyWord
  return dir;
}
