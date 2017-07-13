// macros.h serves to hold the name of the 3 executable files that can be changed to shell402-list-create

pid_t child; // child pid returned by fork
int cStatus; // exit status of child
pid_t waitC; // pid of child to be returned by wait

// ./shell402.exe, ./list.exe, and ./create.exe work on a cygwin64 terminal
// whereas shell402, list, and create would work on another other terminal
char * shell402Exec = "./shell402.exe";
char * listExec = "./list.exe";
char * createExec = "./create.exe";
