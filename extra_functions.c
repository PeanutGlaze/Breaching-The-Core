#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "header.h"

int compare_Strings(char* pStr1, char* pStr2)
{
  pStr1[strcspn(pStr1, "\n")] = 0;
  pStr2[strcspn(pStr2, "\n")] = 0;
  int result = strcmp(pStr1, pStr2);

  return result;
}

int file_reader(char* path)
{
  FILE* file = fopen(path, "r");
  char line[256];
  if(file != NULL)
  {
    while(fgets(line, sizeof(line), file))
    {
      printf("%s\n", line);
      char i = getchar();
    }
    fclose(file);
  } else{ printf("No file"); }
  
  return 0;
}

char* read_input()
{
    char buffer[1024];  // Buffer to temporarily hold the input
    printf("Enter your input: ");
    if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
        // Allocate memory for the string <-- to complicated for now
        size_t length = strlen(buffer);
        char* input = (char*)malloc(length + 1);
        if (input != NULL) {
            strncpy(input, buffer, length);
            input[length] = '\0';  // Null-terminate the string
            return input;
        }
    }
    return NULL;  // Return NULL if there's an error
}
