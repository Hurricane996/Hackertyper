#define PROGRAM_NAME "hackertyper"
#define VERSION "1.1"
#define COPYRIGHT "2018 Lani Willrich"
#define AUTHOR "Lani Willrich"

#define VERSION_STRING "\
hackertyper 1.1\n\
Copyright (C) 2018 Lani Willrich\n\
License GPLv3+: GNU GPL version 3 or later <https://gnu.org/licenses/gpl.html>\n\
This is free software: you are free to change and redistribute it.\n\
There is NO WARRANTY, to the extent permitted by law.\n\
Written by Lani Willrich\n\
"

#define HELP_STRING "\
Write this later\n\
"

extern const char _binary_program_data_start;
extern const char _binary_program_data_end;

#define DATA_START _binary_program_data_start
#define DATA_END   _binary_program_data_end

#define ANSI_GREEN     "\x1b[32m"
#define ANSI_GREEN_LEN 5
#define ANSI_WHITE     "\x1b[0m"
#define ANSI_WHITE_LEN 4

#define DEFAULT_NUM_CHARS 7
