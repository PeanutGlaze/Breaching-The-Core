#include "header.h"

void file_reader(const char* path, const char* flag)
{
  FILE *file = fopen(path, "r");
  char line[256];
  if(file != NULL)
  {
    bool flag_reached = false;

    while(fgets(line, sizeof(line), file))
    {
      //Skipping lines, as long as the reader hasn't found the flag:
      if(!flag_reached)
      {
        if (strncmp(line, flag, strlen(flag)) == 0)
        { save_game(path, flag); flag_reached = true;  }
        // ^ Saving the game when the player reaches a new part of the game

        continue;
      }

      //Skipping empty lines:
      if(strncmp(line, "\n", 1) == 0) { continue; }

      //Stopping the reader if there's another flag detected:
      else if(strncmp(line, "@FLAG", 5) == 0) { break; }
      // ^ Realistically this line will only be reached during testing

      //Making the reader jump to another flag
      else if(strncmp(line, "@JUMP", 5) == 0)
      {
        char new_path[128];
        char new_flag[128];
        sscanf(line, "@JUMP %s %s", new_path, new_flag);

        file_reader(new_path, new_flag);
      }

      //Handling a yes/no decision if it comes up:
      else if(strncmp(line, "@CHOICE", 7) == 0)
      {
        //Copying the @YES and @NO lines:
        char yes_no_lines[2][128];
        for(char i = 0; i < 2; i++)
        { strcpy(yes_no_lines[i], fgets(line, sizeof(line), file)); }
        // 0 --> Yes || 1 --> No

        choice_handler(yes_no_lines);
        break;
      }

      //Handling a decision with up to four cardinal directions:
      else if(strncmp(line, "@DIRECTION", 10) == 0)
      {
        //Copying the lines including the directions:
        char directions[4][128];
        for(char i = 0; i < 4; i++)
        { strcpy(directions[i], fgets(line, sizeof(line), file)); }
        // 0 --> North || 1 --> East || 2 --> South || 3 --> West

        direction_handler(directions);
        break;
      }

      //Reading out a normal line
      else { printf("%s\n", line); char placeholder = getchar(); }
      //The getchar(); function is only there to ensure the player presses enter
    }

    fclose(file);

  //When there's no file correlating to the path:
  } else { printf("No file"); }
}

void choice_handler(const char pYes_no_lines[2][128])
{
  //Getting the path and the flag of the yes-choice:
  char yes_path[128];
  char yes_flag[128];
  sscanf(pYes_no_lines[0], "@YES %s %s", yes_path, yes_flag);

  //Getting the path and the flag of the no-choice:
  char no_path[128];
  char no_flag[128];
  sscanf(pYes_no_lines[1], "@NO %s %s", no_path, no_flag);

  //Handling the player's input:
  bool valid_answer = false;
  while(!valid_answer)
  {
    char* choice = read_input();
    puts("");

    if(strncmp(choice, "Yes", 3) == 0)
    { valid_answer = true; file_reader(yes_path, yes_flag); }

    else if(strncmp(choice, "No", 2) == 0)
    { valid_answer = true; file_reader(no_path, no_flag); }

    else
    { printf("Your answer was invalid, please try again.\n\n"); }
  }
}

void direction_handler(const char pDirections[4][128])
{
  //Getting the paths and the flags of the different directions:
  char north_path[128];
  char north_flag[128];
  sscanf(pDirections[0], "@NORTH %s %s", north_path, north_flag);

  char east_path[128];
  char east_flag[128];
  sscanf(pDirections[1], "@EAST %s %s", east_path, east_flag);

  char south_path[128];
  char south_flag[128];
  sscanf(pDirections[2], "@SOUTH %s %s", south_path, south_flag);

  char west_path[128];
  char west_flag[128];
  sscanf(pDirections[3], "@WEST %s %s", west_path, west_flag);

  //Handling the player's input:
  bool valid_answer = false;
  while(!valid_answer)
  {
    char* choice = read_input();
    puts("");

    if(strncmp(choice, "North", 5) == 0 && strncmp(north_path, "n/a", 3) != 0)
    { valid_answer = true; file_reader(north_path, north_flag); }

    else if(strncmp(choice, "East", 4) == 0 && strncmp(east_path, "n/a", 3) != 0)
    { valid_answer = true; file_reader(east_path, east_flag); }

    else if(strncmp(choice, "South", 5) == 0 && strncmp(south_path, "n/a", 3) != 0)
    { valid_answer = true; file_reader(south_path, south_flag); }

    else if(strncmp(choice, "West", 4) == 0 && strncmp(west_path, "n/a", 3) != 0)
    { valid_answer = true; file_reader(west_path, west_flag); }

    else
    { printf("Your answer was invalid, please try again.\n\n"); }
  }
}

char* read_input()
{
  char buffer[256];  // Buffer to temporarily hold the input
  printf("Enter your input: ");
  if (fgets(buffer, sizeof(buffer), stdin) != NULL)
  {
    // Allocate memory for the string
    size_t length = strlen(buffer);
    char* input = (char*)malloc(length + 1);
    if (input != NULL)
    {
      strncpy(input, buffer, length);
      input[length] = '\0';  // Null-terminate the string
      return input;
    }
  }
  return NULL;  // Return NULL if there's an error
}
