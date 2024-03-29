#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <string.h>

#ifndef DATADIR
#define DATADIR "data"
#endif 

#define DEFAULT_PATH DATADIR "/hackertyper.txt"

#define HELP_TEXT "\
Usage: hackertyper [-f file] [-h] [-v]\n\
Print text from file to stdout on pressing keys, similar to behavior of website https://www.hackertyper.org/\n\
\n\
Options:\n\
  -f FILE, --filename FILE  Print text from FILE rather than from default file\n\
  -h, --help                Print this help string\n\
  -v, --version             Print version information\n\
"

#define VERSION_TEXT "\
hackertyper 2.1.1\n\
Copyright (C) 2019-2023 Lani Willrich\n\
License GPLv3+: GNU GPL version 3 or later <https://gnu.org/licenses/gpl.html>\n\
This is free software: you are free to change and redistribute it.\n\
There is NO WARRANTY, to the extent permitted by law.\n\
Written by Lani Willrich\n\
"

void parse_args(int argc,char* argv[], const char** path);

int open_file(const char* path);

void init();
void nc_color_red();
void nc_color_green();
void nc_color_default();

void backspace();

void draw_msg(char* msg);
void clear_msg();

void end();
