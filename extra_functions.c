#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <stdbool.h>

#include "header.h"

void file_reader(const char* path, const char* flag)
{
  FILE* file = fopen(path, "r");
  char line[256];
  if(file != NULL)
  {
    bool flag_reached = false;

    while(fgets(line, sizeof(line), file))
    {
      //Skipping lines, as long as the reader hasn't found the flag:
      if(!flag_reached)
      {
        if (strncmp(line, flag, strlen(flag)) == 0) { flag_reached = true; }
        continue;
      }

      //Skipping empty lines:
      if(strncmp(line, "\n", 1) == 0) { continue; }

      //Stopping the reader if there's another flag detected:
      else if(strncmp(line, "@FLAG", 5) == 0) { break; }
      // ^ Technically this line should never be used though

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
        //Getting the path and the flag of the yes-choice:
        char yes_path[128];
        char yes_flag[128];
        fgets(line, sizeof(line), file);
        sscanf(line, "@YES %s %s", yes_path, yes_flag);

        //Getting the path and the flag of the no-choice:
        char no_path[128];
        char no_flag[128];
        fgets(line, sizeof(line), file);
        sscanf(line, "@NO %s %s", no_path, no_flag);

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
        break;
      }

      //Handling a decision with up to four cardinal directions:
      else if(strncmp(line, "@DIRECTION", 10) == 0)
      {
        //Getting the paths and the flags of the different directions:
        char north_path[128];
        char north_flag[128];
        fgets(line, sizeof(line), file);
        sscanf(line, "@NORTH %s %s", north_path, north_flag);

        char east_path[128];
        char east_flag[128];
        fgets(line, sizeof(line), file);
        sscanf(line, "@EAST %s %s", east_path, east_flag);

        char south_path[128];
        char south_flag[128];
        fgets(line, sizeof(line), file);
        sscanf(line, "@SOUTH %s %s", south_path, south_flag);

        char west_path[128];
        char west_flag[128];
        fgets(line, sizeof(line), file);
        sscanf(line, "@WEST %s %s", west_path, west_flag);

        //Handling the player's input:
        bool valid_answer = false;
        while(!valid_answer)
        {
          char* choice = read_input();
          puts("");

          if(strncmp(choice, "North", 5) == 0 && strncmp(north_path, "NULL", 4) != 0)
          { file_reader(north_path, north_flag); valid_answer = true; }

          else if(strncmp(choice, "East", 4) == 0 && strncmp(east_path, "NULL", 4) != 0)
          { file_reader(east_path, east_flag); valid_answer = true; }

          else if(strncmp(choice, "South", 5) == 0 && strncmp(south_path, "NULL", 4) != 0)
          { file_reader(south_path, south_flag); valid_answer = true; }

          else if(strncmp(choice, "West", 4) == 0 && strncmp(west_path, "NULL", 4) != 0)
          { file_reader(west_path, west_flag); valid_answer = true; }

          else
          { printf("Your answer was invalid, please try again.\n\n"); }
        }
        break;
      }

      //Reading out a normal line
      else
      {
        printf("%s\n", line);
        char placeholder = getchar();
      }
    }

    fclose(file);

  //When there's no file correlating to the path:
  } else { printf("No file"); }
}

char* read_input()
{
  char buffer[256];  // Buffer to temporarily hold the input
  printf("Enter your input: ");
  if (fgets(buffer, sizeof(buffer), stdin) != NULL)
  {
    // Allocate memory for the string <-- to complicated for now
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
