#ifndef GAME_OF_LIFE
#define GAME_OF_LIFE

// Field size
#define FIELD_SIZE_X 80
#define FIELD_SIZE_Y 25

// Cell status
#define ALIVE 1
#define DEAD 0

// Game control
#define UP_SPEED_BUTTON 'W'
#define DOWN_SPEED_BUTTON 'S'
#define EXIT_BUTTON_CODE 27

// Speed settings
#define SPEED_MAX 20
#define SPEED_MIN 100
#define SPEED_STEP 5
#define START_SPEED 80

// Others
#define NUM_OF_NEIBORS 8

void initCurses();

void renderField(int field[FIELD_SIZE_Y][FIELD_SIZE_X]);

int** newGeneration(int gen[FIELD_SIZE_Y][FIELD_SIZE_X], int past_gen[FIELD_SIZE_Y][FIELD_SIZE_X]);

int isGameOver(int num_of_live, int num_of_change);

void validateUserInput(int user_input, int *game_speed, int *exit_flag);

void upSpeed(int *game_speed);

void downSpeed(int *game_speed);

int isChangeStatus(int game_field[FIELD_SIZE_Y][FIELD_SIZE_X], int y_index, int x_index); 

void getColumnsIndexes(int columns_indexes[NUM_OF_NEIBORS], int x_index);

void getRowsIndexes(int rows_indexes[NUM_OF_NEIBORS], int y_index);

#endif
