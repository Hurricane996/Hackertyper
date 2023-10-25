#include "hackertyper.h"

FILE* file;


char chars_per_nl = 1;

int main(int argc, char* argv[]){
  const char* path = DEFAULT_PATH;
  
  parse_args(argc, argv, &path);

  if(open_file(path) == -1){

    return -1;
  }
  
  init();

  int clear_msg_flag = 0;

  nc_color_green();

  int running = 1;
  
  while(running) {
    // buffer here so that buffering happens before clear_msg
    int input_ch  = getch();  
    // message was drawn last time and we need to clear it
    if(clear_msg_flag) {
      clear_msg_flag = 0;
      clear_msg();
    }

    switch(input_ch){
    //C-c
    case 3:
      running = 0;
      break;
    //C-d
    case 4:
      clear();
      nc_color_red();
      draw_msg("ACCESS DENIED");
      clear_msg_flag = 1;
      break;
    // C-g
    case 7:
      clear();
      nc_color_green();
      draw_msg("ACCESS GRANTED");

      clear_msg_flag = 1;

      break;
    case KEY_BACKSPACE:
      backspace();
      break;
    default:
      for(int i = 0; i < 5; i++) {
        int output_ch = fgetc(file);

        if(output_ch == EOF) {
          rewind(file);

          output_ch = fgetc(file);
        }

        if(output_ch != '\r')
          addch(output_ch);
      }

      refresh();
      break;
    }
  }

  end();
}

void parse_args(int argc, char* argv[], const char** path) {
  if(argc > 1) {
    for(int i = 0; i < argc; i++) {
      if(strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0) {
        printf(HELP_TEXT);

        exit(0);
      }

      else if(strcmp(argv[i], "-v") == 0 || strcmp(argv[i], "--version") == 0) {
        printf(VERSION_TEXT);

        exit(0);
      }

      else if(strcmp(argv[i], "-f") == 0) {
        if(i+1 >= argc) {
          fprintf(stderr, HELP_TEXT);

          exit(-1);
        }

        *path = argv[++ i];
      }
      else {
        fprintf(stderr, HELP_TEXT);
      }
    }
  }
}

int open_file(const char* path) {
  file     = fopen(path, "r");

  return file == NULL ? -1 : 0;
}

void init(){
  initscr();
  raw();
  noecho();
  scrollok(stdscr, true);
  keypad(stdscr, true);

  // check line endings
  // TODO: expand this to work with endings besides \n and \r\n
  
  char ch = 0;

  while(ch !='\n' && ch !='\r'){
    ch = fgetc(file);
  }

  if (ch == '\r') {
    chars_per_nl = 2;
  }

  rewind(file); 
  
  if(has_colors()){
    start_color();
    init_pair(1, COLOR_GREEN, COLOR_BLACK);
    init_pair(2, COLOR_RED, COLOR_BLACK);
  }
}

void nc_color_green(){
  if(has_colors()){
    attroff(COLOR_PAIR(2));
    attron(COLOR_PAIR(1));
  }
}

void nc_color_red(){
  if(has_colors()){
    attroff(COLOR_PAIR(1));
    attron(COLOR_PAIR(2));
  }
}

void nc_color_default(){
  if(has_colors()){
    attroff(COLOR_PAIR(1));
    attroff(COLOR_PAIR(2));
  }
}

void backspace(){
  fseek(file,-1 ,SEEK_CUR);

  int x,y;
  getyx(stdscr,y,x);
  
  if(x == 0) {

    if( y == 0 ) {
      
      return;
    }
    
    x = getmaxx(stdscr) - 1;
    move(--y,x);

    char ch = ' ';

    while(ch == ' ' && x != 0){
      move(y,--x);
      ch=inch();
    }

    fseek(file, -chars_per_nl, SEEK_CUR);
  } else {
    move(y,x-1);

  }


  delch();
}

void draw_msg(char* msg) {
  int len             = strlen(msg);

  int w;
  int h;

  getmaxyx(stdscr, h, w);

  move(h/2 - 2, w/2 - len/2 - 3);

  for(int i = 0; i < len + 6; i ++)
    addch('#');

  move(h/2 - 1, w/2 - len/2 - 3);

  addch('#');

  for(int i = 0; i < len + 4; i ++)
    addch(' ');

  addch('#');

  move(h/2, w/2 - len/2 - 3);
  printw("#  %s  #", msg);

  move(h/2 + 1, w/2 - len/2 - 3);
  addch('#');

  for(int i = 0; i < len + 4; i ++)
    addch(' ');

  addch('#');

  move(h/2 + 2, w/2 - len/2 - 3);

  for(int i = 0; i < len + 6; i ++)
    addch('#');
  
  move(0,0);
}

void clear_msg(){
      nc_color_green();
      clear();
      move(0, 0);
      // seek file to next line   

      while(fgetc(file) != '\n');
}

void end(){
  endwin();
  fclose(file);
}
