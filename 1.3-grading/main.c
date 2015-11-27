#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "grading.h"
#include "appsupport.h"

void tryFree(char **ptr);
void printHeader();
void printUsage();
void startRepl();
void printPrompt();
bool isCommand(const char *commmand, const char *commandType);
void processCommand(char *command);
void unknownCommand();

int main() {
  printHeader();
  printUsage();
  startRepl();
  return 0;
}

void printHeader() {
  printf("--------------------------------------------\n");
  printf("----Welcome to the Simple Grading Module----\n");
  printf("--------------------------------------------\n");
  printf("\n");
}

void printUsage() {
  printf("add (student|class) <name> [class=<class_id> student=<student_id>]\n");
  printf("list (students|classes|enrollments) [class=<class_id>]\n");
  printf("count (students|classes|enrollments) [class=<class_id> student=<student_id>]\n");
  printf("report (student|class) <id>\n");
  printf("help\n");
  printf("quit\n");
}

void startRepl() {
  size_t size = 0;
  char *line = NULL;
  while(true) {
    tryFree(&line);
    printPrompt();
    if (getline(&line, &size, stdin) == -1) {
      break;
    }
    if (isCommand(line, "quit")) {
      break;
    }
  }
  tryFree(&line);
}

void tryFree(char **str) {
  if (*str) {
    free(*str);
    *str = NULL;
  }
}

void printPrompt() {
  printf("> ");
}

void processCommand(char *command) {
  /*
  if (commandIs(command, "help")) {
    printUsage();
  } else {
    unknownCommand();
  }
  */
}

void unknownCommand(char *command) {
  printf("Unknown Command: %s", command);
}
