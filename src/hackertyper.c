#include <termios.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "hackertyper.h"

int main(int argc, char ** argv){
  int num_chars=0;
  if(argc > 1){
    for(int i = 1; i < argc; i++){
        if (strcmp(argv[i], "-v") == 0 ||strcmp( argv[1], "--version")==0){
            printf(VERSION_STRING);
            return 0;
        }
        if(strcmp(argv[i] , "-h") == 0 || strcmp(argv[i], "--help") == 0){
            printf(HELP_STRING);
            return 0;
        }
        if(strcmp(argv[i],"-n") == 0 || strcmp(argv[i],"--num-chars") == 0) {
          if(i==argc-1){
            printf(HELP_STRING);
            return 1;
          }
          num_chars = atoi(argv[++i]);
          if(num_chars==0){
            printf(HELP_STRING);
            return 1;
          }
        }
    }
  }

  if(num_chars == 0) num_chars = DEFAULT_NUM_CHARS;
  struct termios orig_termios;
  
  tcgetattr(STDIN_FILENO, &orig_termios);

  struct termios raw = orig_termios;
  raw.c_lflag &= ~(ECHO | ICANON | ISIG);

  tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);

  write(STDOUT_FILENO,ANSI_GREEN,ANSI_GREEN_LEN);

  char c;
  int offset = 0;
  while (read(STDIN_FILENO, &c, 1) == 1 && c != '\x04' && c != '\x03'){

    for(int i = 0; i < num_chars; i ++){
      write(STDOUT_FILENO, &DATA_START + offset, 1);

      offset++;

      if (&DATA_START + offset == &DATA_END) offset = 0;
    };
  };

  write(STDOUT_FILENO,"\n",1);
  write(STDOUT_FILENO,ANSI_WHITE,ANSI_WHITE_LEN);
  
  tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios);
  
  return 0;
}
