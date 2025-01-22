#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <stdbool.h>

#include "header.h"

void file_reader(char* path, char* flag)
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

          if(strncmp(choice, "Yes", 3) == 0 || strncmp(choice, "yes", 3) == 0)
          { valid_answer = true; file_reader(yes_path, yes_flag); }

          else if(strncmp(choice, "No", 2) == 0 && strncmp(choice, "no", 2) == 0)
          { valid_answer = true; file_reader(no_path, no_flag); }

          else
          { printf("Your answer was invalid, please try again.\n\n"); }
        }
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

int compare_Strings(char* pStr1, char* pStr2)
{
  pStr1[strcspn(pStr1, "\n")] = 0;
  pStr2[strcspn(pStr2, "\n")] = 0;
  int result = strcmp(pStr1, pStr2);

  return result;
}
