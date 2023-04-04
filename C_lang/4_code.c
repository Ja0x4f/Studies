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

  if(guess == secret_number) {
    printf("Gz, you win.\n");
  }
  else{
    if(guess > secret_number){
      printf("Slow down, your guess is to high!\n");
    }
    if(guess < secret_number){
      printf("Nope, the secret number is bigger.\n");
    }
  }

  return 0;
}
