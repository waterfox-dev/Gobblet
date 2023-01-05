#include "board.c"
#include "structure.c" // struct gui
#include "utilities.c" // mini function
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h> // For the usleep()

#define Large_1 "◆"
#define Medium_1 "■"
#define Small_1 "●"

#define Large_2 "◊"
#define Medium_2 "□"
#define Small_2 "○"

#define MAXINPUT 40

// return a gui from a board
struct gui gui_from_board(board game, char pseudo1[MAXINPUT], char pseudo2[MAXINPUT])
{
  FILE *file = fopen("save.txt", "r");
  char c;
  int line = 0;
  while (fscanf(file, "%c", &c) != EOF || line < 2)
  {
    if (c == '\n')
    {
      line++;
    }
    else if (line == 0)
    {
      strcat(pseudo1, &c);
    }
    else if (line == 1)
    {
      strcat(pseudo2, &c);
    }
  }
  // printf("[%s], [%s]\n",pseudo1, pseudo2);
  // usleep(1000000000);
  struct gui continue_gui;
  for (int i = 0; i < DIMENSIONS; i++)
  {
    for (int j = 0; j < DIMENSIONS; j++)
    {
      int cell_player = 0;
      for (int c = 1; c < DIMENSIONS + 1; c++)
      {
        if (game->array_players[i][j][c] != NO_PLAYER)
        {
          cell_player++;
        }
      }
      if (game->array_players[i][j][cell_player] > 0)
      {
        continue_gui.cases[i][j].occuped = true;
      }
      else
      {
        continue_gui.cases[i][j].occuped = false;
      }
      continue_gui.cases[i][j].color = game->array_players[i][j][cell_player];
    }
  }
  return continue_gui;
}

void display(struct gui *c_gui, board game)
{
  /* This function is the principal function of this program, it permits to
   * display the board. c_gui is the current gui, game is the current board and
   * c_player the current_player*/
  system("clear");
  for (int i = 0; i < 3; i++)
  {
    for (int j = 0; j < 3; j++)
    {
      if (i == 0 && j == 0)
      {
        printf("     1  2  3\n");
        printf("   ┌─────────┐   			      "
               "\x1b[36mRules\033[0;37m\n");
      }
      if (j == 0)
      {
        printf(" %d │", i + 1);
      }
      if (c_gui->cases[i][j].occuped == true)
      {
        if (c_gui->cases[i][j].color == 1)
        {
          if (get_piece_size(game, i, j) == SMALL)
          {
            printf("\033[0;93m %s \033[0;37m", Small_1);
          }
          else if (get_piece_size(game, i, j) == MEDIUM)
          {
            printf("\033[0;93m %s \033[0;37m", Medium_1);
          }
          else if (get_piece_size(game, i, j) == LARGE)
          {
            printf("\033[0;93m %s \033[0;37m", Large_1);
          }
        }
        else if (c_gui->cases[i][j].color == 2)
        {
          if (get_piece_size(game, i, j) == SMALL)
          {
            printf("\033[0;32m %s \033[0;37m", Small_2);
          }
          else if (get_piece_size(game, i, j) == MEDIUM)
          {
            printf("\033[0;32m %s \033[0;37m", Medium_2);
          }
          else if (get_piece_size(game, i, j) == LARGE)
          {
            printf("\033[0;32m %s \033[0;37m", Large_2);
          }
        }
      }
      else
      {
        printf(" · ");
      }
      if (j == 2)
      {
        printf("│");
      }
    }
    if (i == 0)
    {
      printf("\x1b[36m 		                  ╔═══════════╗\033[0;37m");
    }
    if (i == 1)
    {
      printf("\x1b[36m 		                  ║ %s < %s < %s ║\033[0;37m",
             Small_1, Medium_1, Large_1);
    }
    if (i == 2)
    {
      printf("\x1b[36m 		                  ╚═══════════╝\033[0;37m");
    }
    printf("\n");
  }
  printf("   └─────────┘\n");
}

void display_player_pseudo(player PLAYER, char pseudo[])
{
  if (PLAYER == 1)
  {
    printf("\n┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈\033[0;93m PLAYER %s "
           "\033[0;"
           "37m┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈\n",
           pseudo);
  }
  else
  {
    printf("\n┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈\033[0;32m PLAYER %s "
           "\033[0;"
           "37m┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈\n",
           pseudo);
  }
}

void print_line_piece(player PLAYER, int SMALL, int MEDIUM, int LARGE)
{
  if (SMALL == 2 && PLAYER == PLAYER_1)
  {
    printf("║\033[0;93m     %s    %s      \033[0;37m", Small_1, Small_1);
  }
  else if (SMALL == 1 && PLAYER == PLAYER_1)
  {
    printf("║\033[0;93m       %s         \033[0;37m", Small_1);
  }
  else if (SMALL == 0 && PLAYER == PLAYER_1)
  {
    printf("║                 ");
  }
  if (MEDIUM == 2 && PLAYER == PLAYER_1)
  {
    printf("║\033[0;93m     %s     %s     \033[0;37m", Medium_1, Medium_1);
  }
  else if (MEDIUM == 1 && PLAYER == PLAYER_1)
  {
    printf("║\033[0;93m       %s         \033[0;37m", Medium_1);
  }
  else if (MEDIUM == 0 && PLAYER == PLAYER_1)
  {
    printf("║                 ");
  }
  if (LARGE == 2 && PLAYER == PLAYER_1)
  {
    printf("║\033[0;93m    %s    %s     \033[0;37m║\n", Large_1, Large_1);
  }
  else if (LARGE == 1 && PLAYER == PLAYER_1)
  {
    printf("║\033[0;93m       %s       \033[0;37m║\n", Large_1);
  }
  else if (LARGE == 0 && PLAYER == PLAYER_1)
  {
    printf("║               ║\n");
  }

  if (SMALL == 2 && PLAYER == PLAYER_2)
  {
    printf("║\033[0;32m     %s     %s     \033[0;37m", Small_2, Small_2);
  }
  else if (SMALL == 1 && PLAYER == PLAYER_2)
  {
    printf("║\033[0;32m       %s         \033[0;37m", Small_2);
  }
  else if (SMALL == 0 && PLAYER == PLAYER_2)
  {
    printf("║                 ");
  }
  if (MEDIUM == 2 && PLAYER == PLAYER_2)
  {
    printf("║\033[0;32m     %s     %s     \033[0;37m", Medium_2, Medium_2);
  }
  else if (MEDIUM == 1 && PLAYER == PLAYER_2)
  {
    printf("║\033[0;32m       %s         \033[0;37m", Medium_2);
  }
  else if (MEDIUM == 0 && PLAYER == PLAYER_2)
  {
    printf("║                 ");
  }
  if (LARGE == 2 && PLAYER == PLAYER_2)
  {
    printf("║\033[0;32m     %s     %s   \033[0;37m║\n", Large_2, Large_2);
  }
  else if (LARGE == 1 && PLAYER == PLAYER_2)
  {
    printf("║\033[0;32m       %s       \033[0;37m║\n", Large_2);
  }
  else if (LARGE == 0 && PLAYER == PLAYER_2)
  {
    printf("║              ║\n");
  }
}

void print_inventory(player PLAYER, int SMALL, int MEDIUM, int LARGE)
{
  printf(
      "\n\e[36m                        \e[1m\e[4mINVENTORY\e[0m\033[0;37m\n");
  printf("╔═════════════════╦═════════════════╦═══════════════╗");
  printf(
      "\n║\033[0;37m    SMALL : %d    ║    MEDIUM : %d   ║   LARGE : %d   ║ \n",
      SMALL, MEDIUM, LARGE);

  print_line_piece(PLAYER, SMALL, MEDIUM, LARGE);

  printf("╚═════════════════╩═════════════════╩═══════════════╝\n");
}

int scanf_line_or_column_or_size(struct gui *gui, board game, player PLAYER,
                                 char pseudo[], char line_or_column_or_size[],
                                 int array[], int SMALL, int MEDIUM,
                                 int LARGE)
{
  /* scanf a integer to put as line */
  int min = 1;
  int max;
  if (array[0] == 1)
  {
    printf("\n\x1b[36mYou can only place a new piece because its your first "
           "round\033[0;37m\n");
  }
  if (array[0] == 3 || array[0] == 1)
  { // place piece turn
    print_inventory(PLAYER, SMALL, MEDIUM, LARGE);
  }
  char input_choice[MAXINPUT];
  if (strcmp("form", line_or_column_or_size) ==
      0)
  { // string non equals mean form turn
    strncpy(input_choice, "(Circle = 1, Squared = 2, Diamond = 3)", MAXINPUT);
  }
  else
  { // choice of column or line turn
    strncpy(input_choice, "(between 1 and 3 included)", MAXINPUT);
  }
  if (array[0] == 1)
  {
    printf("\nEnter a %s %s:\n", line_or_column_or_size, input_choice);
    max = 3;
  }
  else
  {
    printf("\nEnter a %s %s Or enter 4 to go into the choice menu:\n",
           line_or_column_or_size, input_choice);
    max = 4;
  }
  int line = 0;
  int good = scanf_digit_between_min_max_included(min, max, &line);
  while (good != 1)
  {
    display(gui, game);
    display_player_pseudo(PLAYER, pseudo);
    if (array[0] == 1)
    {
      printf("\n\x1b[36mYou can only place a new piece because its your first "
             "round\033[0;37m\n");
    }
    printf("\n\e[31mEntered input \e[1m%d\e[0m \e[31mis not a number between "
           "%d and %d included\033[0;37m\n",
           line, min, max);
    if (strcmp("line of source", line_or_column_or_size) == 0)
    {
      printf("\n┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈Source "
             "line┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈");
    }
    if (strcmp("column of source", line_or_column_or_size) == 0)
    {
      printf("\n\e[36mSource line input : %d\033[0;37m", array[1]);
      printf("\n┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈Source "
             "column┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈");
    }
    if (strcmp("line for target", line_or_column_or_size) == 0)
    {
      printf("\n\e[36mSource : [%d,%d]\033[0;37m", array[1], array[2]);
      printf("\n┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈Target "
             "line┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈");
    }
    if (strcmp("column for target", line_or_column_or_size) == 0)
    {
      printf("\n\e[36m┈┈┈┈┈┈┈┈┈┈┈┈┈Source : [%d,%d], Target line input : "
             "%d┈┈┈┈┈┈┈┈┈┈┈┈┈\e[0;37m\n",
             array[1], array[2], array[3]);
      printf("\n┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈Target "
             "column┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈");
    }
    if (array[0] == 3 || array[0] == 1)
    { // place piece turn
      print_inventory(PLAYER, SMALL, MEDIUM, LARGE);
    }
    if (array[0] == 1)
    {
      printf("\nEnter a %s %s:\n", line_or_column_or_size, input_choice);
    }
    else
    {
      printf("\nEnter a %s %s Or enter 4 to go into the choice menu:\n",
             line_or_column_or_size, input_choice);
    }
    good = scanf_digit_between_min_max_included(min, max, &line);
  }
  if (strcmp("form", line_or_column_or_size) != 0)
  {
    return line - 1;
  }
  return line;
}

int place_piece_on_board(struct gui *gui, board game, player PLAYER,
                         char pseudo[], int choice)
{
  int SMALL = get_nb_piece_in_house(game, PLAYER, 1);
  int MEDIUM = get_nb_piece_in_house(game, PLAYER, 2);
  int LARGE = get_nb_piece_in_house(game, PLAYER, 3);

  int turn[1];
  turn[0] = 3;
  int b_test = 0;

  if (SMALL == 2 && MEDIUM == 2 && LARGE == 2)
  {
    turn[0] = 1;
  }

  int placement_piece_test = 0;

  while (placement_piece_test == 0)
  {
    int line = 0;
    int column = 0;
    int size = 0;

    int b_line = 0;
    int b_column = 0;
    int b_size = 0;

    int response_code;

    if (choice == 1 || PLAYER == PLAYER_1) // If this is PvP or that the turn of
                                           // player 1 in a case of PvE
    {
      int l_test = 0;
      int c_test = 0;
      int p_test = 0;

      while (l_test == 0)
      {
        line = scanf_line_or_column_or_size(gui, game, PLAYER, pseudo, "line",
                                            turn, SMALL, MEDIUM, LARGE);
        if (line == 3) // Case of exit to menu
        {
          return 0;
        }
        if (line_have_free_space(gui, game, line) == 1)
        {
          l_test = 1;
        }
        else
        {
          printf("\n\e[91mThat line has no free space\033[0;37m\n");
        }
      }

      while (c_test == 0)
      {
        display(gui, game);
        display_player_pseudo(PLAYER, pseudo);
        column = scanf_line_or_column_or_size(
            gui, game, PLAYER, pseudo, "column", turn, SMALL, MEDIUM, LARGE);
        if (column == 3)
        {
          return 0;
        }
        if (column_have_free_space(gui, game, column) == 1)
        {
          c_test = 1;
        }
        else
        {
          printf("\n\e[91mThat column has no free space\033[0;37m\n");
        }
      }

      while (p_test == 0)
      {
        display(gui, game);
        display_player_pseudo(PLAYER, pseudo);
        size = scanf_line_or_column_or_size(gui, game, PLAYER, pseudo, "form",
                                            turn, SMALL, MEDIUM, LARGE);
        if (size == 4)
        {
          return 0;
        }
        if (size_is_available(gui, game, size, SMALL, MEDIUM, LARGE) == 1)
        {
          p_test = 1;
        }
        else
        {
          printf("\n\e[91mThat size is not available\033[0;37m\n");
        }
      }
      response_code = place_piece(game, size, line, column);
    }
    else if (choice == 2) // If this a pvb and the turn of the dump bot
    {
      if (b_test == 0)
      {
        for (int l = 0; l < 3; l++)
        {
          for (int c = 0; c < 3; c++)
          {
            bool winning = is_a_winnning_place(gui, l, c, PLAYER_2);
            if (winning == true)
            {
              b_line = l + 1;
              b_column = c + 1;
            }
          }
        }
        b_test = 1;
      }
      if (b_line == 0)
      {
        b_line = (rand() % (3 - 1 + 1));
        b_column = (rand() % (3 - 1 + 1));
      }

      int test_size = 0;
      while (test_size == 0)
      {
        b_size = (rand() % (3 - 1 + 1) + 1);
        if (size_is_available(gui, game, b_size, SMALL, MEDIUM, LARGE) == 1)
        {
          test_size = 1;
        }
      }

      response_code = place_piece(game, b_size, b_line, b_column);
      printf("response_code : %d\n", response_code);
    }
    else if (choice == 3)
    {
      if (b_test == 0)
      {

        for (int l = 0; l < 3; l++)
        {
          for (int c = 0; c < 3; c++)
          {
            bool winning = is_a_winnning_place(gui, l, c, PLAYER_2);
            if (winning == true)
            {
              b_line = l + 1;
              b_column = c + 1;
            }
          }
        }
      }
      if (b_line == 0)
      {
        for (int l = 0; l < 3; l++)
        {
          for (int c = 0; c < 3; c++)
          {
            bool winning = is_a_winnning_place(gui, l, c, PLAYER_1);
            if (winning == true)
            {
              b_line = l + 1;
              b_column = c + 1;
            }
          }
        }
        b_test = 1;
      }
      if (b_line == 0)
      {
        b_line = (rand() % (3 - 1 + 1));
        b_column = (rand() % (3 - 1 + 1));
      }

      int test_size = 0;
      b_size = (rand() % (3 - 1 + 1) + 1);
      while (test_size == 0)
      {
        b_size = (rand() % (3 - 1 + 1) + 1);
        if (size_is_available(gui, game, b_size, SMALL, MEDIUM, LARGE) == 1)
        {
          test_size = 1;
        }
      }
      response_code = place_piece(game, b_size, b_line, b_column);
      printf("response_code : %d\n", response_code);
    }

    if (response_code != OK)
    {
      if (choice == 1)
      {
        printf("\n\e[31mThat place is already taken, please enter a new "
               "piece\033[0;37m\n");
      }
    }
    else
    {
      if (choice == 1 || PLAYER == PLAYER_1)
      {
        printf("\nPlacement for player %d \n", next_player(game));
        gui->cases[line][column].occuped = true;
        gui->cases[line][column].color = (int)PLAYER;
        display(gui, game);
        placement_piece_test = 1;
        return 1;
      }
      else
      {
        printf("\nPlacement for player %d \n", next_player(game));
        gui->cases[b_line][b_column].occuped = true;
        gui->cases[b_line][b_column].color = (int)PLAYER;
        display(gui, game);
        placement_piece_test = 1;
        return 1;
      }
    }
  }
  return 0;
}

int move_piece_on_board(struct gui *gui, board game, player PLAYER,
                        char pseudo[])
{

  int SMALL = get_nb_piece_in_house(game, PLAYER, 1);
  int MEDIUM = get_nb_piece_in_house(game, PLAYER, 2);
  int LARGE = get_nb_piece_in_house(game, PLAYER, 3);

  int array[5];
  array[0] = 2;

  if (SMALL == 2 && MEDIUM == 2 && LARGE == 2)
  {
    array[0] = 1;
  }

  /* Move a piece on the board and communicate this to the gui system */
  int test_placement_piece = 0;
  while (test_placement_piece == 0)
  {
    display(gui, game);
    display_player_pseudo(PLAYER, pseudo);
    if (array[4] == 1)
    {
      printf("\n\e[91mThat place is already taken, please enter a new "
             "piece\033[0;37m\n");
    }
    printf("\n┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈Source "
           "line┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈");
    int test = 0;
    int source_line;
    int source_line_print;
    while (test == 0)
    {
      source_line = scanf_line_or_column_or_size(gui, game, PLAYER, pseudo,
                                                 "line of source", array, SMALL,
                                                 MEDIUM, LARGE);
      source_line_print = source_line + 1;
      if (source_line == 3)
      { // return to choice menu
        return 0;
      }
      if (line_has_pieces_of_player(gui, game, PLAYER, source_line) == 1)
      {
        test = 1;
      }
      else
      {
        display(gui, game);
        display_player_pseudo(PLAYER, pseudo);
        printf("\n\e[91mThat line contain none of your pieces\033[0;37m\n");
        printf("\n\e[36mLast input source line : %d\033[0;37m\n",
               source_line_print);
        printf("\n┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈Source "
               "line┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈");
      }
    }
    array[1] = source_line_print;
    display(gui, game);
    display_player_pseudo(PLAYER, pseudo);
    printf("\n\e[36mSource line input : %d\033[0;37m", source_line_print);
    printf("\n┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈Source "
           "column┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈");
    test = 0;
    int source_column;
    int source_column_print;
    while (test == 0)
    {
      source_column = scanf_line_or_column_or_size(gui, game, PLAYER, pseudo,
                                                   "column of source", array,
                                                   SMALL, MEDIUM, LARGE);
      source_column_print = source_column + 1;
      if (source_column == 3)
      {
        return 0;
      }
      if (column_has_pieces_of_player(gui, game, PLAYER, source_column) == 1)
      {
        if(get_place_holder(game, source_column, source_line) != PLAYER){
          display(gui, game);
          display_player_pseudo(PLAYER, pseudo);
          printf("\n\e[91mThat case contain none of your pieces\033[0;37m\n");
          printf("\n\e[36mSource line : %d, Last input source column : "
          "%d\033[0;37m\n",
          source_line_print, source_column_print);
          printf("\n┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈Source "
          "column┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈");
        }
        else{
          test = 1;
        }
      }
      else
      {
        display(gui, game);
        display_player_pseudo(PLAYER, pseudo);
        printf("\n\e[91mThat column contain none of your pieces\033[0;37m\n");
        printf("\n\e[36mSource line : %d, Last input source column : "
               "%d\033[0;37m\n",
               source_line_print, source_column_print);
        printf("\n┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈Source "
               "column┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈");
      }
    }
    array[2] = source_column_print;
    display(gui, game);
    display_player_pseudo(PLAYER, pseudo);
    printf("\n\e[36mSource : [%d,%d]\033[0;37m", source_line_print,
           source_column_print);
    printf("\n┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈Target "
           "line┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈");
    int target_line = scanf_line_or_column_or_size(gui, game, PLAYER, pseudo,
                                                   "line for target", array,
                                                   SMALL, MEDIUM, LARGE);
    if (target_line == 3)
    {
      return 0;
    }
    int target_line_print = target_line + 1;
    array[3] = target_line;
    display(gui, game);
    display_player_pseudo(PLAYER, pseudo);
    printf("\n\e[36m┈┈┈┈┈┈┈┈┈┈┈┈┈Source : [%d,%d], Target line input : "
           "%d┈┈┈┈┈┈┈┈┈┈┈┈┈\e[0;37m\n",
           source_line_print, source_column_print, target_line_print);
    printf("\n┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈Target "
           "column┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈");
    int target_column = scanf_line_or_column_or_size(gui, game, PLAYER, pseudo,
                                                     "column for target", array,
                                                     SMALL, MEDIUM, LARGE);
    if (target_column == 3)
    {
      return 0;
    }
    int result = move_piece(game, source_line, source_column, target_line,
                            target_column);
    if (result != 0)
    {
      array[4] = 1;
    }
    else
    {
      gui->cases[target_line][target_column].occuped = true;
      gui->cases[target_line][target_column].color = PLAYER;
      if (get_place_holder(game, source_line, source_column) == NO_PLAYER)
      {
        gui->cases[source_line][source_column].occuped = false;
      }
      display(gui, game);
      test_placement_piece = 1;
      return 1;
    }
  }
  return 0;
}

struct gui create_gui()
{
  /* Create an empty gui with empty place */
  struct gui current_gui;
  for (int x = 0; x < 3; x++)
  {
    for (int y = 0; y < 3; y++)
    {
      struct gui_case current_case = {false, 0};
      current_gui.cases[x][y] = current_case;
    }
  }
  return current_gui;
}

int choice_turn(struct gui *gui, board game, player PLAYER, char pseudo[],
                char pseudo_other_player[], int choice)
{
  /* choose either if a player can do a move or not and display the options */
  display_player_pseudo(PLAYER, pseudo);

  int SMALL = get_nb_piece_in_house(game, PLAYER, 1);
  int MEDIUM = get_nb_piece_in_house(game, PLAYER, 2);
  int LARGE = get_nb_piece_in_house(game, PLAYER, 3);

  if (SMALL == 2 && MEDIUM == 2 && LARGE == 2)
  {
    int place_good = 0;
    while (place_good != 1)
    {
      place_good = place_piece_on_board(gui, game, PLAYER, pseudo, choice);
    }
  }
  else
  {
    if (PLAYER == PLAYER_2 && choice > 1)
    {
      place_piece_on_board(gui, game, PLAYER, pseudo, choice);
    }
    else
    {
      printf("\nWhat do you want to do (Place a new piece = 1 / Move a piece = "
             "2 / Save this game = 3)\n");
      int respond = 0;
      int good = 0;
      while (good != 1)
      {
        good = scanf_digit_between_min_max_included(1, 3, &respond);
      }
      if (respond == 1)
      {
        if (place_piece_on_board(gui, game, PLAYER, pseudo, choice) == 0)
        {
          display(gui, game);
          choice_turn(gui, game, PLAYER, pseudo, pseudo_other_player, choice);
        }
      }
      if (respond == 2)
      {
        if (move_piece_on_board(gui, game, PLAYER, pseudo) == 0)
        {
          display(gui, game);
          choice_turn(gui, game, PLAYER, pseudo, pseudo_other_player, choice);
        }
      }
      if (respond == 3)
      {
        FILE *f = fopen("save.txt", "w");
        if (f != NULL)
        {
          fprintf(f, "%s\n", pseudo);
          fprintf(f, "%s\n", pseudo_other_player);
        }
        fclose(f);
        save_game(game, "save.txt");
        destroy_game(game);
        return 0;
      }
    }
  }
  return 1;
}

#define MAX_LEN 128

void print_image(FILE *fptr)
{
  char read_string[MAX_LEN];

  while (fgets(read_string, sizeof(read_string), fptr) != NULL)
  {
    printf("%s", read_string);
    usleep(200000);
  }
}

void display_start()
{
  int m = system("clear");
  m--;
  printf("\033[2J");
  char *filename = "ascii.txt";
  FILE *fptr = NULL;

  if ((fptr = fopen(filename, "r")) == NULL)
  {
    fprintf(stderr, "error opening %s\n", filename);
  }
  else
  {
    print_image(fptr);
    fclose(fptr);
  }
}

int one_turn(board game, struct gui *gui, char pseudo_player1[],
             char pseudo_player2[], int choice)
{
  player joueur = next_player(game);
  bool running = true;
  if (joueur == PLAYER_1)
  {
    running =
        choice_turn(gui, game, joueur, pseudo_player1, pseudo_player2, choice);
  }
  else if (joueur == PLAYER_2)
  {
    running =
        choice_turn(gui, game, joueur, pseudo_player2, pseudo_player1, choice);
  }
  if (get_winner(game) != NO_PLAYER)
  {
    if (PLAYER_1 == get_winner(game))
    {
      print_win(pseudo_player1);
      place_score_into_file(pseudo_player1);
    }
    else
    {
      print_win(pseudo_player2);
      place_score_into_file(pseudo_player2);
    }
    destroy_game(game);
    running = false;
  }
  return running;
}

void game()
{
  /* run a game until a winner is declared */
  srand(time(0));

  display_start(); // display our logo of gobbletsS

  board game = new_game();
  struct gui gui = create_gui();

  printf("\n\n┈┈┈┈┈┈┈┈┈┈┈┈┈┈Enter a game mode┈┈┈┈┈┈┈┈┈┈┈┈┈┈\n\n1.Player VS "
         "Player\n2.Bot easy VS Player\n3.Bot medium VS Player\n4.Continue a "
         "game\n\033[0;37m\n");
  int choice;
  int good = 0;
  while (good != 1)
  {
    good = scanf_digit_between_min_max_included(1, 4, &choice);
  }
  char pseudo_player1[MAXINPUT];
  char pseudo_player2[MAXINPUT];
  bool running = true;

  if (choice != 4)
  {
    printf("\n\nEnter a pseudo for the \033[0;93mplayer 1 \033[0;37m:\n");
    scanf("%s", pseudo_player1);
  }
  if (choice == 1)
  { // PvP
    printf("\nEnter a pseudo for the \033[0;32mplayer 2 \033[0;37m:\n");
    scanf("%s", pseudo_player2);
  }

  if (choice == 2)
  { // PvE
    copy_str("Dumbot", pseudo_player2);
  }

  if (choice == 3)
  {
    copy_str("Mediumbot", pseudo_player2);
  }

  if (choice == 4)
  { // Save and quit game
    game = load_game("save.txt");
    gui = gui_from_board(game, pseudo_player1, pseudo_player2);
  }
  display(&gui, game);
  // printf("[%s], [%s]\n",pseudo_player1, pseudo_player2);
  while (running == true)
  {
    running = one_turn(game, &gui, pseudo_player1, pseudo_player2, choice);
  }
}

/* Clément Baratin et Cyprien De la Poëze d'Harambure */
