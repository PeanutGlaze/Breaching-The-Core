#ifndef HEADER_H
#define HEADER_H

void file_reader(const char* path, const char* flag);
void choice_handler(const char pYes_no_lines[2][128]);
void direction_handler(const char pDirections[4][128]);
char* read_input();

#endif
