#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>
#include <locale.h>
#include <wchar.h>
#include <ctype.h>

//Stolen from stackoverflow
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_BRIGHTBLUE "\x1b[94m"
#define ANSI_COLOR_BRIGHTMAGENTA "\x1b[95m"
#define ANSI_COLOR_WHITE "\x1b[97m"
#define ANSI_COLOR_RESET   "\x1b[0m"

//Insane macro trick that actually works
#define PRINTC(c,f,s) printf ("\x1b[%dm" f "\x1b[0m", c, s)