# Filemover

## Description
This is an application to automatically move files meeting specific criteria from one directory to another.

## Configuration
Depending on whether you define `cli` in [ConsoleApplication1.cpp](https://github.com/SlaynAndKorpil/Filemover/blob/master/ConsoleApplication1/ConsoleApplication1.cpp) you will either get a cli (Command Line Interface) when starting the application or it will read its parameters from the configuration file. By default it is not set. If you work with the cli it will lead you through the settings. For the configuration file you should first take a look at the next section.

## Configuration file
The file has to be named `filemover.conf` and needs to be located in the same directory as the executable.
It contains information in the following order (every parameter needs to be in its own line, no empty lines allowed)
 1. directory to move files out of
 1. directory to move files into
 1. prefix to filter files for
 1. extension that all files need to have in order to be moved
 1. extension that all files should have after being moved
 1. time (in milliseconds) which determines the time the program waits between trying to move files

Example:
>C:\Users\user\Desktop\background  
C:\Users\user\Desktop\foreground  
00  
.jpg  
.png  
60000
