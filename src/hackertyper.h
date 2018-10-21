#define PROGRAM_NAME "hackertyper"
#define VERSION "1.1"
#define COPYRIGHT "2018 Lani Willrich"
#define AUTHOR "Lani Willrich"

#define VERSION_STRING "\
hackertyper 1.0\n\
Copyright (C) 2018 Lani Willrich\n\
License GPLv3+: GNU GPL version 3 or later <https://gnu.org/licenses/gpl.html>\n\
This is free software: you are free to change and redistribute it.\n\
There is NO WARRANTY, to the extent permitted by law.\n\
Written by Lani Willrich\n\
"

#define HELP_STRING "\
Usage:\n\
hackertyper [options]\n\
Options:\n\
  -h,--help       Print this help string\n\
  -v,--version    Print version info\n\
  -n,--num-chars  Customize number of chars outputted per button press\n\
"

extern const char _binary_program_data_start;
extern const char _binary_program_data_end;

#define DATA_START _binary_program_data_start
#define DATA_END   _binary_program_data_end

#define STRLEN(s) sizeof(s)

#define ANSI_GREEN "\x1b[32m"
#define ANSI_WHITE "\x1b[0m"
#define ANSI_RED   "\x1b[31m"
#define ANSI_TOP_LEFT "\x1b[H"

#define ANSI_GREEN_LEN    sizeof(ANSI_GREEN)
#define ANSI_WHITE_LEN    sizeof(ANSI_RED)
#define ANSI_RED_LEN      sizeof(ANSI_WHITE)
#define ANSI_TOP_LEFT_LEN sizeof(ANSI_TOP_LEFT)

#define ACCESS_GRANTED "\
######################\n\
#                    #\n\
#   ACCESS GRANTED   #\n\
#                    #\n\
######################\n\
"
#define ACCESS_GRANTED_LEN sizeof(ACCESS_GRANTED)

#define ACCESS_DENIED "\
#####################\n\
#                   #\n\
#   ACCESS DENIED   #\n\
#                   #\n\
#####################\n\
"
#define ACCESS_DENIED_LEN sizeof(ACCESS_DENIED)

#define DEFAULT_NUM_CHARS 7
