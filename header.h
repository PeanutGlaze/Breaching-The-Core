#ifndef HEADER_H
#define HEADER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>

void file_reader(const char* path, const char* flag);
void choice_handler(const char pYes_no_lines[2][128]);
void direction_handler(const char pDirections[4][128]);
char* read_input();

void save_game(const char* path, const char* flag);
void load_game();

#endif
