// .h file serves to hold prototypes for shell402functs.c, or like constants, structs, etc.

char * wd();  // function that handles the "wd" command: that is, display the current working directory

void quit(); // function that handles the "quit" command: that is, exits the program

DIR * chwd(); // function that handles the "chwd" command: that is, changes the current working directory

DIR * processShellCommand(char *, DIR *); // function that handles the wd, chwd, quit commands
