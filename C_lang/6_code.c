#include <stdio.h>

int main(void){

  int secret = 20;
  int guess;
  int i = 1;

  for(i; i <= 3; i++){
    printf("Turn %d\n", i);
    printf("Your guess?\n");
    printf("# ");
    scanf("%d", &guess);

    int right = (guess == secret);

    if(right) {
      printf("It's right. You won.\n");
      break;
    }

    else if(guess < 0){
      printf("You cannot type negative numbers.\n");
      printf("This attempt will not be counted.\n");
      i--;
      continue;
    }
    
    else if(guess > secret){
      printf("Slow down, your guess is bigger than the secret number.\n");
    }
    else if(guess < secret){
      printf("Your guess is smaller than the secret number, try again if you can.\n");
    }

  }
  return 0;
}
