#include <stdio.h>
#include <stdlib.h>

int main() {
  char tmp[2];
  int i;
  char first_name[20];
  char last_name[20];

  printf("Please enter a 2 digit number.\n");
  scanf("%2s", tmp);
  getchar();
  i = atoi(tmp);
  printf("You enetered %i\n", i);
  
  printf("Please enter a first and last name (space separated)\n");
  scanf("%19s %19s", first_name, last_name);
  getchar();
  printf("You entered %s %s\n", first_name, last_name);

  printf("Please enter a new 2 digit number.\n");
  scanf("%i", &i);
  getchar();
  printf("You entered %i\n", i);
  
  char food[5];
  printf("Enter favorite food: ");
  fgets(food, sizeof(food), stdin);
  printf("You entered %s\n", food);

  return 0;

}

/* ANALYSIS:

You run into problems mixing scanf and fgets. Do one or the other...
See http://stackoverflow.com/questions/20763240/fgets-not-working-in-a-function

After scanf, getchar is used to consume the \newline that is put back on stdin

For the favorite food, if more than sizeof(food) chars are entered, they are ignored.

*/
