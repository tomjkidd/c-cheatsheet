#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int not(int t) {
  return !t;
}

int add(int x, int y) {
  return x + y;
}

int subtract(int x, int y) {
  return x - y;
}

int ascending(const void* x, const void* y) {
  int a = *(int*)x; // Cast x to an int pointer and dereference it to get it's value
  int b = *(int*)y; // Cast y to an int pointer and dereference it to get it's value
  return a - b;
}

int descending(const void* x, const void* y) {
  int a = *(int*)x;
  int b = *(int*)y;
  return b - a;
}

void display_scores(int scores[], int len) {
  for (int i=0; i < len; i++) {
    printf("%i", scores[i]);
    if (i < (len - 1)) {
      printf(",");
    }
  }
  printf("\n");
}

int main() {
  /* format: <return type> (*<pointer variable>)(<parameter types>) */
  int (*predicate_function)(int); // Create a function pointer that takes an int and returns an int
  predicate_function = not; // Assign the pointer to an actual function

  int (*arithmatic_function)(int, int); // Create a function pointer that takes two ints and returns an int
  arithmatic_function = add; // Assign the pointer to an actual function

  /* Call the functions, using function the created function pointers. */
  printf("not(1) = %i\n", predicate_function(1));
  printf("not(0) = %i\n", predicate_function(0));

  printf("33 + 66 = %i\n", arithmatic_function(33, 66)); // Show the results of a calculation

  arithmatic_function = subtract; // Change the arithmatic function

  printf("33 - 66 = %i\n", arithmatic_function(33, 66)); // Show the results of a new calculation

  int scores[] = {543,323,32,554,11,3,112};
  int (*compare_function)(const void*, const void*); // Create a function pointer that mimics the qsort comparator
  compare_function = ascending; // Assign pointer to an actual function

  qsort(scores, 7, sizeof(int), compare_function); // Perform (an inplace) sort of the array
  display_scores(scores, 7); // Show the result of the sort
  
  compare_function = descending; // Change the compare function
  
  qsort(scores, 7, sizeof(int), compare_function); // Re-sort the array
  display_scores(scores, 7); // Show the new results
}
