// C file to hold all create-related functions

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

#include "createfuncts.h"

int createNewFile(char * filePath){
  int fout = open(filePath, O_CREAT, 0640);
  printf("New file formed with filepath %s\n", filePath);
  return fout;
}

void createNewDirectory(char * dirPath){
  struct stat st = {0};
  if (stat(dirPath, &st) == -1) {
    mkdir(dirPath, 0750);
    printf("New directory formed with dirpath %s\n", dirPath);
  }
  return;
}

int createHardLink(char * oldName, char * newName){
  int ln = link(oldName, newName);
  return ln;
}

int createSoftLink(char * oldName, char * newName){
  int ln = symlink(oldName, newName);
  return ln;
}
