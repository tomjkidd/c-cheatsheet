#include <stdlib.h>
#include <stdio.h>

typedef struct node {
  int value;
  struct node *next;
} node;

node* create(int v) {
  node *cur = malloc(sizeof(node));
  (*cur).value = v; // can also use ptr->value
  (*cur).next = NULL;
  return cur;
}

void release(node* cur) {
  node *next = NULL;
  for (; cur != NULL; cur = next) {
    next = (*cur).next; // Get a reference to the next node, before freeing current node!
    free(cur); // NOTE: If node allocated more memory as part of it's data, that would also need to be cleared here!
  }
}

void display(node* cur) {
  node *next = NULL;
  for (; cur != NULL; cur = next) {
    printf("Node value is %i\n", (*cur).value);
    next = (*cur).next;
  }
}

/*
try something like this at the command line...
printf "12\n13\n14\n15\n" | ./memory
*/

int main() {
  node *start = NULL;
  node *i = NULL;
  node *next = NULL;
  char input[80];

  for(; fgets(input, 80, stdin) != NULL; i = next) { // Get input until a Ctrl-D
    next = create(atoi(input)); // Allocate memory for a new node
    if (start == NULL)
      start = next; // Capture the start of the list
    if (i != NULL)
      (*i).next = next; // Associate the next node with the current node to extend the list
  }

  display(start);
  
  release(start);
}
