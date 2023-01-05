#define _BOARD_H_

#include <stdbool.h>

/**
 * \file board.h
 *
 * \brief Gobblet game engine functions.
 *
 * In this file, all the functions for having a game of gobblets or of
 * gobblet-gobblers run are defined.
 *
 * \author Dorbec
 *
 */

/**
 * \mainpage SAE 1.1 and 1.2 for IUT Grand Ouest Normandie, computer science
 * department \section descritpion Description of the project This project is
 * aimed to implement a two player game, close to the Tic-Tac-Toe game. The
 * rules of the games are described below.
 *
 * The project is divided into various files. Mostly, the engine of the game,
 * implementing the detailed rules, is provided in the files board.c and board.h
 *
 * \section rules Detailed rules of the game.
 *
 * The game is played by two players on a three by three squares board,
 * though variants may be played on larger boards
 * (in particular on a four by four board for gobblets).
 * Each player has control of aplace_piece(game, size, line, column) set of six
 * pieces whose owner is easily identifiable, for example by the shape or the
 * color of the piece. The pieces are of three different sizes (big, medium,
 * small), each player having two of each size.
 *
 * During the course of the game, players alternately make a move that consists
 * in either:
 * - adding a piece from their collection on the board.
 * - moving one of his visible pieces already on the board to another square.
 *
 * A piece can be placed either on an empty square,
 * or on a square containing only smaller pieces,
 * independently of who owns the piece.
 * In that latter case, the piece covers and hides the smaller pieces.
 * When a piece placed over other pieces is moved from a square,
 * the largest piece covered is revealed and can be played in a later turn.
 *
 * The game is won by the first player who manages to make a visible line of
 * his pieces across the board (on a line, a column,
 * or a diagonal, like for Tic-Tac-Toe.)
 *
 */

/**
 * @brief Game dimension.
 *
 * For being general in terms of dimensions,
 * they are defined in a general parameter.
 * In the following, all indices are given from 0 to DIMENSIONS - 1.
 */
#define DIMENSIONS 3

/**
 * @brief the different sizes of pieces.
 *
 * This set includes references to an 'empty' size, for representing no piece at
 * all. They are ordered by increasing size, so that they can be compared with <
 * or >.
 */
enum sizes_e
{
  NONE,
  SMALL,
  MEDIUM,
  LARGE
};

typedef enum sizes_e size;

/**
 * @brief the different players for further reference.
 * NO_PLAYER is used when informing that a square is empty.
 */
enum players_e
{
  NO_PLAYER,
  PLAYER_1,
  PLAYER_2
};

typedef enum players_e player;

/**
 * @brief number of players in the game.
 */
#define NB_PLAYERS 2

enum return_code
{
  OK,
  POSITION,
  SOURCE,
  TARGET
};

/**
 * @brief number of sizes for robustness if the enumeration is modified.
 */
#define NB_SIZE 3

/**
 * @brief number of pieces of each size per player at the beginning.
 */
#define NB_INITIAL_PIECES 2

/**
 * @brief Pointer to the structure that holds the game.
 *
 * Details of the content are not necessary for its use, so the structure is not
 * included here.
 */
// typedef struct board_s * board;

struct board_s
{
  enum sizes_e array_sizes[DIMENSIONS][DIMENSIONS][DIMENSIONS + 1];
  enum players_e array_players[DIMENSIONS][DIMENSIONS][DIMENSIONS + 1];
  // TODO: choisir une structure adaptee
};

typedef struct board_s *board;

/**@{
 * \name Game creation/deletion functionalities.
 */

/**
 * @brief Defines a new empty board for starting a game of gobblet-gobblers.
 *
 * The first player is always PLAYER_1
 * @return the newly created board
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> // For the usleep()
void print3D_array(board game_board)
{
  for (int i = 0; i < DIMENSIONS; i++)
  {
    for (int j = 0; j < DIMENSIONS; j++)
    {
      for (int c = 0; c < DIMENSIONS + 1; c++)
      {
        printf("size : %d, ", game_board->array_sizes[i][j][c]);
        printf("player : %d \n",
               game_board->array_players[i][j][c]);
      }
    }
  }
  usleep(10000000);
}
board new_game()
{
  board game_board = malloc(sizeof(struct board_s));

  for (int i = 0; i < DIMENSIONS; i++)
  {
    for (int j = 0; j < DIMENSIONS; j++)
    {
      for (int c = 0; c < DIMENSIONS + 1; c++)
      {
        game_board->array_sizes[i][j][c] = NONE;
        game_board->array_players[i][j][c] = NO_PLAYER;
      }
    }
  }
  // print3D_array(game_board);
  return game_board;
}

/**
 * @brief Makes a deep copy of the game.
 * @param original_game the game to copy.
 * @return a new copy fully independent of the original game.
 */
board copy_game(board original_game)
{
  board game_board = malloc(sizeof(struct board_s));
  for (int i = 0; i < DIMENSIONS; i++)
  {
    for (int j = 0; j < DIMENSIONS; j++)
    {
      for (int c = 0; c < DIMENSIONS + 1; c++)
      {
        game_board->array_sizes[i][j][c] = original_game->array_sizes[i][j][c];
        game_board->array_players[i][j][c] =
            original_game->array_players[i][j][c];
      }
    }
  }
  return game_board;
}

/**
 * @brief Delete the game and frees all associated memory.
 * @param game the game to destroy.
 */
void destroy_game(board game)
{
  free(game);
}

/**@}*/

/**@{
 * \name Accessing game data functionalities.
 */

/**
 * @brief return the player whose turn it is to play.
 *
 * @param game the game to consider
 * @return the next player in the game
 */
player next_player(board game)
{
  int cmpt_1 = 0;
  int cmpt_2 = 0;
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
      if (game->array_players[i][j][cell_player] == PLAYER_1)
      {
        cmpt_1++;
      }
      if (game->array_players[i][j][cell_player] == PLAYER_2)
      {
        cmpt_2++;
      }
    }
  }
  if (cmpt_1 > cmpt_2)
  {
    return PLAYER_2;
  }
  return PLAYER_1;
}

/**
 * @brief returns the player holding the indicated place.
 * @param game the game from which to collect information
 * @param line the line number
 * @param column the columne number
 * @return the player holding the biggest piece of that square,
 * NO_PLAYER if no player is holding the place
 * or if the request is misplaced.
 */
player get_place_holder(board game, int line, int column)
{
  int cell_player = 0;
  for (int c = 1; c < DIMENSIONS + 1; c++)
  {
    if (game->array_players[line][column][c] != NO_PLAYER)
    {
      cell_player++;
    }
  }
  return game->array_players[line][column][cell_player];
}

/**
 * @brief returns the visible piece size.
 * @param game the game from which to collect information.
 * @param line the line number of the square.
 * @param column the column number of the square.
 * @return the size of the holding piece,
 * or NONE if there is no piece on this square of the board
 * or is the request is misplaced.
 */
size get_piece_size(board game, int line, int column)
{
  int cell_player = 0;
  for (int c = 1; c < DIMENSIONS + 1; c++)
  {
    if (game->array_players[line][column][c] != NO_PLAYER)
    {
      cell_player++;
    }
  }
  return game->array_sizes[line][column][cell_player];
}

/**
 * @brief Checks whether the game has a winner already
 *
 * Recall that winning condition is to have a full row,
 * column or diagonal covered with visible pieces.
 * If both players fulfill the winning condition, this function returns
 * NO_PLAYER. One possible interpretation is that the game should continue until
 * only one player is winning.
 * @param game the game to test.
 * @return the winning player or NO_PLAYER if no player is winning.
 */
player get_winner(board game)
{
  int cmpt_line_1 = 0;
  int cmpt_line_2 = 0;
  int cmpt_column_1 = 0;
  int cmpt_column_2 = 0;
  int cmpt_diag_1 = 0;
  int cmpt_diag_2 = 0;
  int cmpt_diag2_1 = 0;
  int cmpt_diag2_2 = 0;
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
      if (game->array_players[i][j][cell_player] == PLAYER_1)
      {
        cmpt_line_1++;
      }
      if (game->array_players[i][j][cell_player] == PLAYER_2)
      {
        cmpt_line_2++;
      }
      if (game->array_players[j][i][cell_player] == PLAYER_1)
      {
        cmpt_column_1++;
      }
      if (game->array_players[j][i][cell_player] == PLAYER_2)
      {
        cmpt_column_2++;
      }
    }
    if (cmpt_line_1 == 3 || cmpt_column_1 == 3)
    {
      return PLAYER_1;
    }
    if (cmpt_line_2 == 3 || cmpt_column_2 == 3)
    {
      return PLAYER_2;
    }

    cmpt_line_1 = 0;
    cmpt_column_1 = 0;
    cmpt_line_2 = 0;
    cmpt_column_2 = 0;

    int cell_player_diag = 0;
    for (int c = 1; c < DIMENSIONS + 1; c++)
    {
      if (game->array_players[i][i][c] != NO_PLAYER)
      {
        cell_player_diag++;
      }
    }

    if (game->array_players[i][i][cell_player_diag] == PLAYER_1)
    {
      cmpt_diag_1++;
    }
    if (game->array_players[i][i][cell_player_diag] == PLAYER_2)
    {
      cmpt_diag_2++;
    }

    int cell_player_diag2 = 0;
    int diag2 = DIMENSIONS - (i + 1);
    for (int c = 1; c < DIMENSIONS + 1; c++)
    {
      if (game->array_players[diag2][diag2][c] != NO_PLAYER)
      {
        cell_player_diag2++;
      }
    }
    if (game->array_players[diag2][diag2][cell_player_diag2] == PLAYER_1)
    {
      cmpt_diag2_1++;
    }
    if (game->array_players[diag2][diag2][cell_player_diag2] == PLAYER_2)
    {
      cmpt_diag2_2++;
    }
    diag2--;
  }
  if (cmpt_diag_1 == 3 || cmpt_diag2_1 == 3)
  {
    return PLAYER_1;
  }
  if (cmpt_diag_2 == 3 || cmpt_diag2_2 == 3)
  {
    return PLAYER_2;
  }
  return NO_PLAYER;
}

/**
 * @brief Collect data about the pieces in a player's house.
 *
 * Returns the number of pieces of the given size there are left
 * in the given player's house.
 *
 * @param game the game to check
 * @param checked_player whose player house is to check
 * @param piece_size which piece size is to check
 * @return the number of pieces in the house, 0 if anything is wrong.
 */

int get_nb_piece_in_house(board game, player checked_player, size piece_size)
{
  int nb_pieces = 2;
  for (int i = 0; i < DIMENSIONS; i++)
  {
    for (int j = 0; j < DIMENSIONS; j++)
    {
      for (int c = 0; c < DIMENSIONS; c++)
      {
        if (game->array_players[i][j][c] == checked_player &&
            game->array_sizes[i][j][c] == piece_size)
        {
          nb_pieces--;
        }
      }
    }
  }
  return nb_pieces;
}

/**@}*/

/**@{
 * \name Playing functionalities
 */

/**
 * @brief Adds a piece on the board if possible.
 *
 * The piece is taken from the player's house.
 * Whether the piece is available is tested.
 * The piece is then placed on the board,
 * provided all the pieces on that place are smaller than the current piece,
 * covering any existing smaller piece.
 *
 * If placing the piece is not possible, this returns a positive return_code
 * encoding the problem identified:
 *   0. OK: if everything went smoothly.
 *   1. POSITION: line or column do not correspond to a valid position.
 *   2. SOURCE: the chosen piece is not available in the player's house.
 *   3. TARGET: the chosen piece is available but to small to be put at the
 * target place.
 *
 * @param game the game where to add a piece.
 * @param current_player the player whose piece is to be added.
 * @param piece_size the size of the piece to add.
 * @param line the line number of where to place the piece.
 * @param column the column number of where to place the piece.
 * @return a return_code, positive if the operation fails.
 */

enum return_code place_piece(board game, size piece_size, int line,
                             int column)
{
  enum return_code r;

  if (line < 0 || line > DIMENSIONS - 1 || column < 0 ||
      column > DIMENSIONS + 1)
  {
    return r = 1;
  }

  int cell_player = 1;
  for (int c = 1; c < DIMENSIONS + 1; c++)
  {
    if (game->array_players[line][column][c] != NO_PLAYER)
    {
      cell_player++;
    }
  }
  if (game->array_sizes[line][column][cell_player - 1] >= piece_size ||
      cell_player > DIMENSIONS)
  {
    return r = 3;
  }
  game->array_sizes[line][column][cell_player] = piece_size;
  game->array_players[line][column][cell_player] = next_player(game);
  return r = 0;
}

/**
 * @brief Moves a piece from a place to another, if possible.
 *
 * If placing the piece is not possible, this returns a positive return_code
 * encoding the problem identified:
 *   0. SUCCESS: the move is successful
 *   1. POSITION: line or column do not correspond to a valid position.
 *   2. SOURCE: there is no visible piece belonging to the player on the
 * corresponding place
 *   3. TARGET: a piece was available, but too small to be put at the target
 * place.
 *
 * @param game the game where to move a piece.
 * @param source_line the line number of where to move the piece from.
 * @param source_column the column number of where to move the piece from.
 * @param target_line the line number of where to move the piece to.
 * @param target_column the column number of where to move the piece to.
 * @return an integer encoding the result of the placement, positive if the move
 * failed.
 */
enum return_code move_piece(board game, int source_line, int source_column,
                            int target_line, int target_column)
{
  enum return_code r = 0;

  if (source_line < 0 || source_line > DIMENSIONS - 1 || source_column < 0 ||
      source_column > DIMENSIONS + 1)
  {
    return r = 1;
  }
  if (target_line < 0 || target_line > DIMENSIONS - 1 || target_column < 0 ||
      target_column > DIMENSIONS + 1)
  {
    return r = 1;
  }

  int cell_player = 0;
  for (int c = 1; c < DIMENSIONS + 1; c++)
  {
    if (game->array_players[source_line][source_column][c] != NO_PLAYER)
    {
      cell_player++;
    }
  }
  if (game->array_players[source_line][source_column][cell_player] !=
      next_player(game))
  {
    return r = 2;
  }

  int cell_player_target = 0;
  for (int c = 1; c < DIMENSIONS + 1; c++)
  {
    if (game->array_players[target_line][target_column][c] != NO_PLAYER)
    {
      cell_player_target++;
    }
  }

  if (game->array_sizes[source_line][source_column][cell_player] <=
      game->array_sizes[target_line][target_column][cell_player_target])
  {
    return r = 3;
  }
  place_piece(game, game->array_sizes[source_line][source_column][cell_player],
              target_line, target_column);
  game->array_sizes[source_line][source_column][cell_player] = NONE;
  game->array_players[source_line][source_column][cell_player] = NO_PLAYER;
  return r = 0;
}

/**
 * loads the game saved in filename and returns the loaded game.
 * Returns NULL if the load fails.
 * @param filename the filename to load the game from.
 * @return a new game containing the loaded game.
 **/
board load_game(char *filename)
{
  FILE *file = fopen(filename, "r");
  char c_char;
  int line_cmpt = -2;
  int type_cmpt = 0;
  int cmpt_line_game = 0;
  int column = 0;
  board board_c = malloc(sizeof(struct board_s));

  while (fscanf(file, "%c", &c_char) != EOF)
  {
    int c_char_int;
    if (c_char == '\n')
    {
      line_cmpt++;
      type_cmpt = 0;
      // printf("\n%d", line_cmpt);
    }
    if (c_char == ':')
    {
      type_cmpt++;
    }
    else
    {
      // printf("%c", c_char);
      c_char_int = c_char - 48;
      if (c_char_int >= 0 && c_char_int <= 3)
      {
        // printf("c = [%d]\n", c_char_int);
        //printf("cmpt = %d\n", line_cmpt);
        if (line_cmpt == 12 )
        {
          cmpt_line_game = 1;
        }
        if(line_cmpt == 24){
          cmpt_line_game = 2;
        }
        int layer = line_cmpt%4;
        if(line_cmpt == 4 || line_cmpt == 16 || line_cmpt == 28){
          column = 1;
        }
        if(line_cmpt == 8 || line_cmpt == 20 || line_cmpt == 32){
          column = 2;
        }
        if(line_cmpt == 12 || line_cmpt == 24 || line_cmpt == 36){
          column = 3;
        }
        //printf("[%d][%d][%d] = %d\n", cmpt_line_game, column, layer, c_char_int);
        if (type_cmpt == 0)
        {
          //printf("[%d][%d][%d] = %d\n", cmpt_line_game, column, layer, c_char_int);
          board_c->array_sizes[cmpt_line_game][column][layer] = c_char_int;
        }
        else
        {
          board_c->array_players[cmpt_line_game][column][layer] = c_char_int;
        }
      }
    }
  }
  //print3D_array(board_c);
  //usleep(100000000);
  return board_c;
}

/**
 * saves the game in the corresponding filename.
 * @param filename the filename to save the game to, extension .sav is suggested.
 **/
void save_game(board game, char *filename)
{
  int good = 0;
  while (good != 1)
  {
    FILE *f = fopen(filename, "a");
    if (f != NULL)
    {
      good = 1;
      for (int i = 0; i < DIMENSIONS; i++)
      {
        // fprintf(f, "Line : %d\n", i);
        for (int j = 0; j < DIMENSIONS; j++)
        {
          for (int c = 0; c < DIMENSIONS + 1; c++)
          {
            fprintf(f, "%d", game->array_sizes[i][j][c]);
            fprintf(f, ":");
            fprintf(f, "%d\n", game->array_players[i][j][c]);
          }
          // fprintf(f, "Column : %d\n", j);
        }
      }
    }
    fclose(f);
  }
}

// #endif /*_BOARD_H_*/