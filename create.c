// C exec file holds all functions for "create"-related functions
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

#include "createfuncts.h"

int main(int argc, char * argv[]){
  int res;
  //------- Case 1: command is "create -f filepath" --------------
  if(argc == 3 && strcmp(argv[1], "-f") == 0){
    res = createNewFile(argv[2]);
    if(res == -1) { printf("Failed to create new file.\n"); }
  }
  //--------------------------------------------------------------
  //------- Case 2: command is "create -d dirpath" ---------------
  if(argc == 3 && strcmp(argv[1], "-d") == 0){
    createNewDirectory(argv[2]);
  }
  //--------------------------------------------------------------
  //----- Case 3: command is "create -h oldname linkname" ----------
  if(argc == 4 && strcmp(argv[1], "-h") == 0){
    printf("-h option with oldname %s and linkname %s\n", argv[2], argv[3]);
    res = createHardLink(argv[2], argv[3]);
    if(res == 0) { printf("Hard link created successfully.\n"); }
    if(res == -1) { printf("Failed to create hard link.\n"); }
  }
  //--------------------------------------------------------------
  //----- Case 4: command is "create -s oldname linkname" ----------
  if(argc == 4 && strcmp(argv[1], "-s") == 0){
    printf("-s option with oldname %s and linkname %s\n", argv[2], argv[3]);
    res = createSoftLink(argv[2], argv[3]);
    if(res == 0) { printf("Symbolic link created successfully.\n"); }
    if(res == -1) { printf("Failed to create soft link.\n"); }
  }
  //--------------------------------------------------------------
  return 0;
}
