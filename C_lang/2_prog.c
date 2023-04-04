#include <stdio.h>

int main(void){

  int secret_number = 42;

  int guess;

  // Print the header
  printf("#######################\n");
  printf("# Welcome to the game #\n");
  printf("#######################\n");

  printf("%d is the secret number. Do not tell it to anyone!\n", secret_number);
  printf("\nGuess the number.\n");
  printf("# ");
  scanf("%d", &guess);

  printf("You think that the secret number is %d.\n", guess);

  return 0;
}
