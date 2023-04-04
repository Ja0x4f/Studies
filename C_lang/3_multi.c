#include <stdio.h>

/*
  Write a program that asks the user to input two integer variables (x and y). 
  Printing the result of multiplication of both.
*/

int main(){

  int num_x;
  int num_y;

  printf("Please, insert the number values: \n");
  printf("X: ");
  scanf("%d", &num_x);
  printf("\nY: ");
  scanf("%d", &num_y);

  // Result
  printf("\n\nThe result of X * Y is: %d ", num_x*num_y);
  return 0;
}
