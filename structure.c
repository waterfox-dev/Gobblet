#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>

struct gui_location {
  int x;
  int y;
};

struct gui_case {
  bool occuped;
  int color;
};

struct gui {
  struct gui_case cases[3][3];
};
