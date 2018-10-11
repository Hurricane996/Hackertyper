#include <signal.h>
#include <termios.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include "data.h"


#define PROGRAM_NAME "hackertyper"
#define VERSION "1.0"
#define COPYRIGHT "2018 Lani Willrich"
#define AUTHOR "Lani Willrich"

struct termios orig_termios;
char c;
int offset;


int main(int argc, char ** argv){
  if(argc > 1){
    printf("%s\n",argv[1]);
    if (strcmp(argv[1], "-v") == 0 ||strcmp( argv[1], "--version")==0){
      printf("\
%s %s\n\
Copyright (C) %s\n\
License GPLv3+: GNU GPL version 3 or later <https://gnu.org/licenses/gpl.html>\n\
This is free software: you are free to change and redistribute it.\n\
There is NO WARRANTY, to the extent permitted by law.\n\
Written by %s\n",
             PROGRAM_NAME,VERSION,COPYRIGHT,AUTHOR);
      return 0;
    }
  }
  signal(SIGINT, SIG_IGN);
  tcgetattr(STDIN_FILENO, &orig_termios);

  struct termios raw = orig_termios;
  raw.c_lflag &= ~(ECHO | ICANON);

  tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);

  write(STDOUT_FILENO,"\x1b[32m",5);
  
  while (read(STDIN_FILENO, &c, 1) == 1 && c != '\x04'){

    for(int i = 0; i < 4; i ++){
      write(STDOUT_FILENO,data_txt+offset,1);

      offset++;

      if (offset > data_txt_len - 1) offset = 0;
    };
  };

  write(STDOUT_FILENO,"\n\x1b[0m",5);
  tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios);
  
  return 0;
}
