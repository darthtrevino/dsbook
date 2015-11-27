#include "appsupport.h"
#include <stdio.h>
#include <string.h>

bool isCommand(char *command, const char *commandType) {
  int commandLength = strlen(command);
  char commandCopy[commandLength];
  strcpy(commandCopy, command);
  const char *delimeters = " \t\n";
  const char *token = strtok(commandCopy, delimeters);
  int result = strcmp(token, commandType);
  return result == 0;
}
