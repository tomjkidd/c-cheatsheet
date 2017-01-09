#include <stdio.h>

// NOTE: If the argument was an int, then when called, a copy would be created, which is on the stack and is no longer the address of the int we wanted!
int * get_address(int * x) {
  return * (&x);
}

/* 
   get_value and set_value are simple functions to map the syntax for C memory pointers to function calls.
   This is to make it easier to remember how to dereference (get_value) and update (set_value) the value that pointers are pointing to.
*/
int get_value(int * pointer) {
  return *pointer;
}

void set_value(int * pointer, int new_value) {
  *pointer = new_value;
}

int main() {
  int x = 107;
  int * x_address = &x; // Use the address of operator to get the address of x (also called a pointer!)

  printf("x is stored at %p\n", x_address);
  printf("x using get_address is  %p\n", get_address(x_address)); // Display the address of x in hex, note this is to verify the true address
  printf("x is %i before the update\n", get_value(x_address)); // Use address of x to get it's value
  set_value(x_address, 108); // change the value of x
  printf("x is %i after the update\n", get_value(x_address)); // Use address of x to get it's new value

  return 0;
}

/* ANALYSIS:

& - 'address of' operator. This will return the address of where the variable is stored in memory.
* - 'dereference' operator. This will take a pointer to a memory address and return the value at that address.

NOTE: This is PLACE ORIENTED programming at it's finest.
NOTE: C is call by value, so if go_south_east had int arguments and not int pointer arguments, when called it would
  copy the values into new memory locations.

*/
