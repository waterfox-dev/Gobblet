#include <stdio.h>
#include <string.h>

#define MAXINPUT 40

#define Large_1 "◆"
#define Medium_1 "■"
#define Small_1 "●"

#define Large_2 "◊"
#define Medium_2 "□"
#define Small_2 "○"

//------------------------------------VERIFICATION OF
// SCANF---------------------------------------

int powInt(int x, int y) {
  /*This function take x and y parameters and return x^y*/
  for (int i = 0; i < y; i++) {
    x *= 10;
  }
  return x;
}

int parseInt(char *chars) {
  /*This function take a number composed string and make the sum of it. *chars
   * is the string*/
  int sum = 0;
  int len = strlen(chars);
  for (int x = 0; x < len; x++) {
    int n = chars[len - (x + 1)] - '0';
    sum = sum + powInt(n, x);
  }
  return sum;
}

int scanf_digit_between_min_max_included(int min, int max, int *line) {
  /* This function take a integer min and a integer max as parameters and check
   * if the value of a scanf is between their*/
  char input[40] = "";
  int length, i;
  int test_valide = 0;
  int inputfinal;
  while (test_valide != 1) {
    test_valide = 1;
    scanf("%s", input);
    length = strlen(input);
    for (i = 0; i < length; i++) {
      if (!isdigit(input[i])) {
        test_valide = 0;
      }
    }
    inputfinal = parseInt(input);
    if (inputfinal < min || inputfinal > max) {
      *line = inputfinal;
      return 0;
    }
  }
  *line = inputfinal;
  return 1;
}

int line_have_free_space(struct gui *gui, board game, int line) {
  int test = 3;
  for (int i = 0; i < 3; i++) {
    if (get_piece_size(game, line, i) != LARGE){
      test--;
    }
  }
  if (test == 3) {
    return 0;
  }
  return 1;
}

int column_have_free_space(struct gui *gui, board game, int column) {
  int test = 3;
  for (int i = 0; i < 3; i++) {
    if (get_piece_size(game, i, column) != LARGE){
      test--;
    }
  }
  if (test == 3) {
    return 0;
  }
  return 1;
}

int size_is_available(struct gui *gui, board game, int size, int SMALL,
                      int MEDIUM, int LARGE) {
  if (size == 1 && SMALL > 0) {
    return 1;
  }
  if (size == 2 && MEDIUM > 0) {
    return 1;
  }
  if (size == 3 && LARGE > 0) {
    return 1;
  }
  return 0;
}

int read_and_count(char fichier[], int score) {
  FILE *f = fopen(fichier, "r");
  int cmptL = 1;
  if (f != NULL) {
    char c;
    while (fscanf(f, "%c", &c) != EOF) {
      if (c == '\n') {
        cmptL++;
      }
    }
  }
  return cmptL;
}

int line_has_pieces_of_player(struct gui *gui, board game, player PLAYER,
                              int source_line) {
  for (int i = 0; i < 3; i++) {
    if (gui->cases[source_line][i].color == PLAYER) {
      return 1;
    }
  }
  return 0;
}

int column_has_pieces_of_player(struct gui *gui, board game, player PLAYER,
                                int source_column) {
  for (int i = 0; i < 3; i++) {
    if (gui->cases[i][source_column].color == PLAYER) {
      return 1;
    }
  }
  return 0;
}
//------------------------------------END OF VERIFICATION OF
// SCANF---------------------------------------

//------------------------------------PLACE SCORE INTO
// FILE---------------------------------------

#define FILENAME_SIZE 1024
#define MAX_LINE 1000

void extract(int from, int to, char *chaine, char *sousChaine) {
  int i = 0, j = 0;
  // récupérer la longueur de la chaîne
  int length = strlen(chaine);

  if (from > length || from < 0) {
    printf("L'index 'from' est invalide\n");
  }
  if (to > length) {
    printf("L'index 'to' est invalide\n");
  }
  for (i = from, j = 0; i <= to; i++, j++) {
    sousChaine[j] = chaine[i];
  }
  sousChaine[j] = '\0';
}

void copy_str(char str[], char str_copy[]) {
  int cmpt = 0;
  for (cmpt = 0; str[cmpt] != '\0'; cmpt++) {
    str_copy[cmpt] = str[cmpt];
  }
  str_copy[cmpt] = '\0';
}

int pos_of_char_in_str(char a, char string[]) {
  for (int i = 0; i < strlen(string); i++) {
    if (string[i] == a) {
      return i;
    }
  }
  return 0;
}

void name_from_str(char a[]) {
  int start = 0;
  int end = 0;
  int i = 0;
  int good = 0;
  while (good != 1) {
    if (i == strlen(a) || end != 0) {
      good = 1;
    }
    if (a[i] == '.' && a[i + 1] == ' ') {
      start = i + 2;
    }
    if (a[i] == ' ' && a[i + 1] == ':') {
      end = i - 1;
    }
    i++;
  }
  char b[100];
  extract(start, end, a, b);
  for (i = 0; i < strlen(b); i++) {
    a[i] = b[i];
  }
  a[i] = '\0';
}

void place_score_into_file(char name_winner[]) {
  FILE *file, *temp;
  char filename[FILENAME_SIZE] = "score.txt";
  char temp_filename[FILENAME_SIZE];
  char buffer[MAX_LINE];

  strcpy(temp_filename, "temp____");
  strcat(temp_filename, filename);

  fflush(stdin);

  file = fopen(filename, "r");
  temp = fopen(temp_filename, "w");

  bool keep_reading = true;
  int file_has_name = 0;

  while (keep_reading) {
    fgets(buffer, MAX_LINE, file);
    char name[100];
    memcpy(name, buffer, strlen(buffer)); // copy buffer dans str
    name_from_str(name);

    if (feof(file)) {
      keep_reading = false;
    } else if (strcmp(name, name_winner) == 0) {
      file_has_name = 1;
      char replace[strlen(buffer)]; // char de la meme taille que la ligne lue
      copy_str(buffer, replace);
      int a = (int)replace[strlen(replace) - 2];
      a = a - 47;
      char c = a + '0';
      replace[strlen(replace) - 2] = c;
      replace[strlen(replace) - 1] = '\n';
      replace[strlen(replace)] = '\0';
      fputs(replace, temp);
    } else {
      fputs(buffer, temp);
    }
  }

  fclose(file);
  fclose(temp);

  remove(filename);
  rename(temp_filename, filename);
  if (file_has_name == 0) {
    int cmptL = read_and_count(filename, 1);
    FILE *f = fopen(filename, "a");
    if (f == NULL) {
      fprintf(f, "1. %s : 1\n", name_winner);
    } else {
      fprintf(f, "%d. %s : 1\n", cmptL, name_winner);
    }
    fclose(f);
  }
}
//------------------------------------END OF PLACE SCORE INTO
// FILE---------------------------------------

bool check_diagonal(struct gui *gui, int line, int column, player p)
{
    gui->cases[line][column].occuped = true;
    gui->cases[line][column].color = p;

    for (int c_line = 0; c_line < 3; c_line++)
    {
        for (int c_column = 0; c_column < 3; c_column++)
        {
            if (c_line == c_column)
            {
                if ((gui->cases[c_line][column].occuped == false) || (gui->cases[c_line][column].color != p))
                {
                    gui->cases[line][column].occuped = false;
                    gui->cases[line][column].color = NO_PLAYER;
                    return false;
                }
            }
        }
    }

    gui->cases[line][column].occuped = false;
    gui->cases[line][column].color = NO_PLAYER;

    return true;
}
bool check_line(struct gui *gui, int line, int column, player p)
{
    gui->cases[line][column].occuped = true;
    gui->cases[line][column].color =
        p; // Warning : change this if the bot is not mandatory player 2

    for (int c_line = 0; c_line < 3; c_line++)
    {

        if ((gui->cases[c_line][column].occuped == false) ||
            (gui->cases[c_line][column].color != p))
        {
            gui->cases[line][column].occuped = false;
            gui->cases[line][column].color = NO_PLAYER;
            return false;
        }
    }

    gui->cases[line][column].occuped = false;
    gui->cases[line][column].color = NO_PLAYER;

    return true;
}

bool check_column(struct gui *gui, int line, int column, player p)
{
    gui->cases[line][column].occuped = true;
    gui->cases[line][column].color =
        p; // Warning : change this if the bot is not mandatory player 2

    for (int c_line = 0; c_line < 3; c_line++)
    {
        for (int c_column = 0; c_column < 3; c_column++)
        {
            if (c_column == column)
            {
                if ((gui->cases[c_line][c_column].occuped == false) ||
                    (gui->cases[c_line][c_column].color != p))
                {
                    gui->cases[line][column].occuped = false;
                    gui->cases[line][column].color = NO_PLAYER;
                    return false;
                }
            }
        }
    }

    gui->cases[line][column].occuped = false;
    gui->cases[line][column].color = NO_PLAYER;

    return true;
}

bool is_a_winnning_place(
    struct gui *gui, int line, int column,
    player p) // Check if the place is empty then check if it is a winning place
{
    if (gui->cases[line][column].occuped == 1   )
    {
        return false;
    }
    else
    {
        if (check_line(gui, line, column, p) == true)
        {
            return true;
        }
        if (check_column(gui, line, column, p) == true)
        {
            return true;
        }
        if (check_diagonal(gui, line, column, p) == true)
        {
            return true;
        }
    }
    return false;
}

// Print win with size of player's name
void print_win(char pseudo_player[]) {
  printf("\n╔");
  for (int i = 0; i < strlen(pseudo_player); i++) {
    printf("═");
  }
  printf("════════════════════╗");
  printf("\n║\033[0;33m Player \033[0;93m\e[5m %s\e[0m\033[0;33m has win  "
         "\033[0;37m ║",
         pseudo_player);
  printf("\n╚");
  for (int i = 0; i < strlen(pseudo_player); i++) {
    printf("═");
  }
  printf("════════════════════╝\n");
}