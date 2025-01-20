#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "header.h"

int a1();
int a2();
int b1();

int main()
{
  a1();
  return 0;
}

int a1()
{
  file_reader("script/a1.txt");

  //Last Line: "What's your name?"

  char* name = read_input();
  printf("\n%s\n", name);
  char abc[] = {"Peggy"};

  if(compare_Strings(name,abc) == 0) { a2(); }
  else { b1(); }

  return 0;
}

int a2()
{
  file_reader("script/a2.txt");
  return 0;
}

int b1()
{
  file_reader("script/b1.txt");
  return 0;
}
