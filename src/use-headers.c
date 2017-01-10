#include <stdio.h>
#include "headers.h"

int main() {
  int x = add(1, 2); // Call the add function, exposed through headers.h
  int y = subtract(2, 1); // Call the subtract function, also exposed through headers.h
  printf("1 + 2 = %i\n", x);
  printf("2 - 1 = %i\n", y);
  printf("SAMPLE_VALUE = %i\n", SAMPLE_VALUE); // Display the SAMPLE_VALUE variable exposed through headers.h
}

/* ANALYSIS

add, subtract, and SAMPLE_VALUE are all from the headers.h header file.
They are used simply here just to demonstrate a simple situation that is pulling in code from other files.

*/
