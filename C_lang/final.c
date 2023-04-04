#include <stdio.h>

int main(){

  int secret = 42;

  int guess;

  // Print the header
  printf("#######################\n");
  printf("# Welcome to the game #\n");
  printf("#######################\n");

  int tries=1;

  while(1) {

    printf("Turn %d\n", tries);
    printf("Your guess: ");
    scanf("%d\n", &guess);

    if(guess < 0){
      printf("Negativa numbers are not allowed. This attempt will not be counted. \n\n");
      continue;
    }

    int right = (guess == secret);
    int bigger = guess > secret;

    if (right){
      printf("You guessed the right number, which is %d.\n", guess);
      printf("You took %d tries.\n", tries);

      break;
    }
    else if(bigger){
      printf("Your guess is bigger than the secret number\n");
    }
    else{
      printf("Your guess is smaller than the secret number.\n");
    }

    tries++;

  }
  printf("The game is over.\n");

}
