#include "header.h"

int main()
{
  //The access function checks if a file exists if you enter a path with F_OK
  if (access("script/save_file.txt", F_OK) == 0) { load_game(); }

  //The else-part acts as a "New Game" function
  else { file_reader("script/start.txt", "@FLAG1"); }

  return 0;
}

void save_game(const char* path, const char* flag)
{
  FILE *save_file = fopen("script/save_file.txt", "w");

  if(save_file != NULL)
  { fprintf(save_file, "@JUMP %s %s", path, flag); }

  fclose(save_file);
}

void load_game()
{
  FILE *save_file = fopen("script/save_file.txt", "r");

  if(save_file != NULL)
  {
    char line[256];
    fgets(line, sizeof(line), save_file);

    char load_path[128];
    char load_flag[128];
    sscanf(line, "@JUMP %s %s", load_path, load_flag);

    file_reader(load_path, load_flag);
  }

  fclose(save_file);
}
