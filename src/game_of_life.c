#include <stdio.h>
#include <ncurses.h>

#include "game_of_life.h"

void run() {
    int game_field[FIELD_SIZE_Y][FIELD_SIZE_X];
    int past_game_field[FIELD_SIZE_Y][FIELD_SIZE_X];

    int speed = START_SPEED;
    int user_input;
    int exit_flag;

}
void initCurses() {
    initscr();
    raw();
    curs_set(0);
    noecho();
    nodelay(stdscr, true);
}

void renderField(int field[FIELD_SIZE_Y][FIELD_SIZE_X]) {
    for (int i = 0; i < FIELD_SIZE_Y; i++) {
        for (int j = 0; j < FIELD_SIZE_X; j++) {
            if (field[i][j] == ALIVE) printw("*");
            else printw(" ");
        }
        printw("\n");
    }
}

int** newGeneration(int gen[FIELD_SIZE_Y][FIELD_SIZE_X], int past_gen[FIELD_SIZE_Y][FIELD_SIZE_X]) {
    for (int i = 0; i < FIELD_SIZE_Y; i++) {
        for (int j = 0; j < FIELD_SIZE_X; j++) {
            if (isChangeStatus(past_gen, i, j)) gen[i][j] = !gen[i][j];
        }
    }
}

int isGameOver(int num_of_live, int num_of_change) {
    return num_of_live == 0 || num_of_change == 0;
}

void validateUserInput(int user_input, int *game_speed, int *exit_flag) {
    switch (user_input)
    {
    case UP_SPEED_BUTTON:
    case UP_SPEED_BUTTON + 32:
    case KEY_UP:
        upSpeed(game_speed);
        break;
    
    case DOWN_SPEED_BUTTON:
    case DOWN_SPEED_BUTTON + 32:
    case KEY_DOWN:
        downSpeed(game_speed);

    case EXIT_BUTTON_CODE:
        *exit_flag = true;
    }
}

void upSpeed(int *game_speed) {
    *game_speed = *game_speed - SPEED_STEP > SPEED_MAX ? *game_speed - SPEED_STEP : *game_speed;
}

void downSpeed(int *game_speed) {
    *game_speed = *game_speed + SPEED_STEP < SPEED_MIN ? *game_speed + SPEED_STEP : *game_speed;
}

int isChangeStatus(int game_field[FIELD_SIZE_Y][FIELD_SIZE_X], int y_index, int x_index) {
    int live_neibor = 0;
    int result = false;
    int rows_indexes[NUM_OF_NEIBORS];
    int columns_indexes[NUM_OF_NEIBORS];
    getRowsIndexes(rows_indexes, y_index);
    getColumnsIndexes(columns_indexes, x_index);

    for (int i = 0; i < NUM_OF_NEIBORS; i++) 
        live_neibor += game_field[rows_indexes[i]][columns_indexes[i]];
    
    if (game_field[y_index][x_index] && (live_neibor < 2 || live_neibor > 3) || 
        !game_field[y_index][x_index] && (live_neibor == 3))
        result = true;

    return result;
}   

void getRowsIndexes(int rows_indexes[NUM_OF_NEIBORS], int y_index) {
    int next = y_index + 1 != 25 ? y_index + 1 : 0;
    int prev = y_index - 1 != -1 ? y_index - 1 : 24;

    rows_indexes[0] = rows_indexes[1] = rows_indexes[2] = prev;
    rows_indexes[3] = rows_indexes[4] = rows_indexes[5] = y_index;
    rows_indexes[6] = rows_indexes[7] = rows_indexes[8] = next;

    return rows_indexes;
}

void getColumnsIndexes(int columns_indexes[NUM_OF_NEIBORS], int x_index) {
    int next = x_index + 1 != 80 ? x_index + 1 : 0;
    int prev = x_index - 1 != -1 ? x_index - 1 : 79;

    columns_indexes[0] = columns_indexes[3] = columns_indexes[6] = prev;
    columns_indexes[1] = columns_indexes[4] = columns_indexes[7] = x_index;
    columns_indexes[2] = columns_indexes[5] = columns_indexes[8] = next;

    return columns_indexes;
}