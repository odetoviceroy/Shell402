// this file is to contain all functions related to list.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

void readNonHiddenFiles(DIR * dir, struct dirent * ent){
  while((ent = readdir(dir)) != NULL){  // simple reading of all filenames in specified directory
    if(ent->d_name[0] != '.')
      printf("%s\n",ent->d_name);
  }
  return;
}

void printExtraInfo(DIR * dir, struct dirent * ent){
  FILE * finp;
  struct stat buf;
  struct stat file_s;
  int size, chMod, fint, inode;
  while((ent = readdir(dir)) != NULL){
      finp = fopen(ent->d_name, "r"); // read file for reviewing size of file using finp
      fseek(finp, 0L, SEEK_END);
      size = ftell(finp);
      rewind(finp);
      fclose(finp); // close file pointer
      stat(ent->d_name, &buf); // next, get permissions of the file using ent->d_name
      chMod = buf.st_mode & (S_IRWXU | S_IRWXG | S_IRWXO);
      inode = buf.st_ino;
      printf("%s has size of %d bytes, permissions 0x%o, and inode number of 0d%d\n", ent->d_name, size, chMod, inode);
    }
  return;
}

void readHiddenFiles(DIR * dir, struct dirent * ent){
  while((ent = readdir(dir)) != NULL){  // simple reading of all filenames in specified directory
    if(ent->d_name[0] == '.')
      printf("%s\n",ent->d_name);
  }
  return;
}
