// C exec file holds all functions for "list"-related functions
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "listfuncts.h"

int main(int argc, char * argv[]){
  DIR * dir;
  struct dirent * ent;

  //----------- Case 1: command is "list" --------------------
  if(argc == 1){
    if((dir = opendir(".")) == NULL){
      printf("Cannot open current directory.\n"); exit(1);
    }
    readNonHiddenFiles(dir, ent);
    closedir(dir);
  }
  //----------------------------------------------------------
  //----------- Case 2: command is "list -i" -----------------
  if(argc == 2 && strcmp(argv[1], "-i") == 0){
    if((dir = opendir(".")) == NULL){
      printf("Cannot open current directory.\n"); exit(1);
    }
    printExtraInfo(dir, ent);
    closedir(dir);
  }
  //----------------------------------------------------------
  //----------- Case 3: command is "list -h" -----------------
  if(argc == 2 && strcmp(argv[1], "-h") == 0){
    if((dir = opendir(".")) == NULL){
      printf("Cannot open current directory.\n"); exit(1);
    }
    readHiddenFiles(dir, ent);
    closedir(dir);
  }
  //----------------------------------------------------------
  //--------- Case 4: command is "list -i pathname" ----------
  if(argc == 3 && strcmp(argv[1], "-i") == 0){
    if((dir = opendir(argv[2])) == NULL){
      printf("Cannot open current directory.\n"); exit(1);
    }
    printExtraInfo(dir, ent);
    closedir(dir);
  }
  //----------------------------------------------------------
  //--------- Case 5: command is "list -h pathname" ----------
  if(argc == 3 && strcmp(argv[1], "-h") == 0){
    if((dir = opendir(argv[2])) == NULL){
      printf("Cannot open current directory.\n"); exit(1);
    }
    readHiddenFiles(dir, ent);
    closedir(dir);
  }
  //----------------------------------------------------------
  //--------- Case 6: command is "list pathname" -------------
  if(argc == 2 && strcmp(argv[1], "-h") != 0 && strcmp(argv[1],"-i") !=0){
    if((dir = opendir(argv[1])) == NULL){
      printf("Cannot open current directory.\n"); exit(1);
    }
    readNonHiddenFiles(dir, ent);
    closedir(dir);
  }
  //----------------------------------------------------------
  return 0;
}
