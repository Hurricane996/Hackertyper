#include "hackertyper.h"

char* filename;
FILE* file;

int main(int argc, char* argv[]) {
  parse_args(argc, argv);

  if(open_file(filename) == -1){
    fprintf(stderr, "Could not open file\n");

    return -1;
  }

  nc_init();

  int clear_msg_flag = 0;

  nc_color_green();

  for(;;) {
    int input_ch = getch();

    if(input_ch == 3)
      break;

    // C-d
    if(input_ch == 4) {
      clear();
      nc_color_red();
      draw_msg("ACCESS DENIED");

      clear_msg_flag = 1;

      continue;
    }

    // C-g
    if(input_ch == 7) {
      clear();
      nc_color_green();
      draw_msg("ACCESS GRANTED");

      clear_msg_flag = 1;

      continue;
    }

    // message was drawn last time and we need to clear it
    if(clear_msg_flag == 1) {
      nc_color_green();
      clear();
      move(0, 0);

      clear_msg_flag = 0;

      // to prevent issues where you start typing from middle of line.
      rewind(file);
    }

    for(int i = 0; i < 5; i++) {
      int output_ch = fgetc(file);

      if(output_ch == EOF) {
        rewind(file);

        output_ch = fgetc(file);
      }

      addch(output_ch);
    }

    refresh();
  }

  nc_color_default();
  end();
}

void parse_args(int argc, char* argv[]) {
  if(argc > 1) {
    for(int i = 0; i < argc; i++) {
      if(strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0) {
        printf(HELP_TEXT);

        exit(0);
      }

      if(strcmp(argv[i], "-v") == 0 || strcmp(argv[i], "--version") == 0) {
        printf(VERSION_TEXT);

        exit(0);
      }

      if(strcmp(argv[i], "-f") == 0) {
        if(i+1 >= argc) {
          fprintf(stderr, HELP_TEXT);

          exit(-1);
        }

        filename = argv[i+1];
      }
    }
  }
}

int open_file(char* filename) {
  filename = filename ? filename : default_filename;
  file     = fopen(filename, "r");

  return file == NULL ? -1 : 0;
}

void nc_init(){
  initscr();
  raw();
  noecho();
  scrollok(stdscr, true);

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

// TODO: fix this shit
void draw_msg(char* msg) {
  int len   = strlen(msg);
  int hash  = atoi("#");
  int space = atoi(" ");

  WINDOW* stdscr;

  int w;
  int h;

  getmaxyx(stdscr, h, w);

  move(h/2 - 2, w/2 - len/2 - 3);

  for(int i = 0; i < len + 6; i ++)
    addch(hash);

  move(h/2 - 1, w/2 - len/2 - 3);

  addch(hash);

  for(int i = 0; i < len + 4; i ++)
    addch(space);

  addch(hash);

  move(h/2, w/2 - len/2 - 3);
  printw("%s  %s  %s", hash, msg, hash);

  move(h/2 + 1, w/2 - len/2 - 3);
  addch(hash);

  for(int i = 0; i < len + 4; i ++)
    addch(space);

  addch(hash);

  move(h/2 + 2, w/2 - len/2 - 3);

  for(int i = 0; i < len + 6; i ++)
    addch(hash);
}

void end(){
  endwin();

  fclose(file);
}
