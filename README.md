# Shell402

My take on a shell program that was given to me as a homework assignment in my Systems Programming class. 

This is just a repository to finish the project, since I did not submit the full version on time, just about 80% of it.

## The Basic Assigment

Create a "simplified" version of a command line prompt using parent and child processes, and other relevant header files that C has so gracefully provided for us.

## The Commands

In this assignment, I was supposed to implement a certain number of commands that the user can type and execute certain processes.

**wd --- Displays the current working directory**

**chwd pathname --- Changes the current working directory to the one specified in the second argument.**

**-------------------**

**list --- Displays all non-hidden files in the current directory**

**list pathname -- Same as above, but with a specified pathname.**

**list -i --- Displays all files in the current directory, their size (in bytes), permissions, and inode numbers.**

**list -i pathname --- Same as above, but with a specified pathname.**

**list -h --- Displays all hidden files in the current directory.**

**list -h pathname --- Same as above, but with a specified pathname.**

**-------------------**

**create -f filepath --- Create a new file with a specified pathname.**

**create -d dirpath --- Create a new directory with specified pathname.**

**create -h oldname newname --- Create a hard link with a specified old name and a specified new name.**

**create -s oldname newname --- Create a symbolic (soft) link with a specified old name and a specified new name.**

**-------------------**

**help -- Displays this information.**

**quit --- Exits out of the program.**

**Note:** This program will only work on a cygwin64 terminal, as the executable files that will be called will have ./executable.exe as their format. You can change the format of the executable file in the **macros.h** file.

**Note:** The **list** and **create** executable files can actually be run on their own without the use of running the **shell402** executable file.

The full list of commands can also be viewed under the command **help**.
