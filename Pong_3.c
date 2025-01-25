#include <stdlib.h>
#include <stdio.h>

//Pair with collatzConjecture
int oddEvenNumber(int number) {
    if (number % 2 == 0) {
        return 1;
    } 
    else {
        return 0;
    }
}

int instructions(void) {
    printf("The game's name is Pong\n");
    printf("To play this game, you must enter a number that ranges from 1 to 999\n");
    printf("To move down you, you must enter a range of numbers from 1 to 333\n");
    printf("To stay at the same position, you must enter a range of numbers from 334 to 666\n");
    printf("To move up, you must enter a range of numbers from 667 to 999\n");
}

int collatzConjecture(int number) {
    //Computers decisor
    //Biased to make more even numbers than odd
    // 66.16% Evens 33.84%
    //Solution is to also factor in if the user inputted an odd or even number
    for (int i; i<=10; i++){
        if (number % 2 == 0){
            number = number/2;
        }
        else {
            number = (number * 3) + 1;
        }
    }
    if (number % 2 == 0){
        return 1;
    }
    else{
        return 0;
    }
}

typedef struct {
    int ballXAxis;
    int ballYAxis;
    int transistor;
    int straight;
    int odd;
    int even;
    int verticalBounce;
} BallState;

// Updates the ball's position and direction, return unlike the previous version
BallState ballMovement(int number, BallState state, int width) {
    if (state.transistor == 1) {
        if (state.ballXAxis == 69) {
            state.transistor = 0;
        }
        else if (state.straight == 1) {
            state.ballXAxis += 1;
        }
        else if (state.even == 1) {
            state.ballXAxis += 1;
            state.ballYAxis += state.verticalBounce;
        }
        else if (state.odd == 1) {
            state.ballXAxis += 1;
            state.ballYAxis -= state.verticalBounce;
        }
    }
    else if (state.transistor == 0) {
        if (state.ballXAxis == 11) {
            state.transistor = 1;
        }
        else if (state.straight == 1) {
            state.ballXAxis -= 1;
        }
        else if (state.even == 1) {
            state.ballXAxis -= 1;
            state.ballYAxis += state.verticalBounce;
        }
        else if (state.odd == 1) {
            state.ballXAxis -= 1;
            state.ballYAxis -= state.verticalBounce;
        }
    }

    if (collatzConjecture(number) == 1 && oddEvenNumber(number) == 1 && (state.ballXAxis == 11 || state.ballXAxis == 69)) {
        state.straight = 1;
        state.even = 0;
        state.odd = 0;
    }
    else if (collatzConjecture(number) == 0 && (state.ballXAxis == 11 || state.ballXAxis == 69)) {
        state.straight = 0;
        state.even = 1;
        state.odd = 0;
    }
    else if (collatzConjecture(number) == 1 && oddEvenNumber(number) == 0 && (state.ballXAxis == 11 || state.ballXAxis == 69)) {
        state.straight = 0;
        state.even = 0;
        state.odd = 1;
    }
    if (state.ballYAxis <= 1) { // Top border
        state.verticalBounce = 1; // Change direction to move downward
    }
    else if (state.ballYAxis >= width - 2) { // Bottom border
        state.verticalBounce = -1; // Change direction to move upward
    }
    return state;
}

int main() {
    int playersHeight = 6, computersHeight = 6;
    int length = 82, width = 17;
    int spacer, border, number, x, decision;
    int  playerScore = 0, computerScore = 0;
    BallState ball = {40, 7, 0, 1, 0, 0, 1};

    while (1) {
        instructions();
        printf("\nEnter a number: ");
        scanf("%d", &number);

        if (number >= 1 && number <= 333 && playersHeight != width - 5) {
            playersHeight++;
        }
        else if (number >= 667 && number <= 999 && playersHeight != 1) {
            playersHeight--;
        }
        else if (number < 1 || number > 999) {
            printf("\nInvalid input entered");
            break;
        }
        if (collatzConjecture(number) == 1 && oddEvenNumber(number) == 1 && computersHeight != width - 5){
            computersHeight++;
        }
        else if (collatzConjecture(number) == 1 && oddEvenNumber(number) == 0 && computersHeight != 1){
            computersHeight--;
        }

        ball = ballMovement(number, ball, width);

        for (x = 0; x < width; x++) {
            if (x == 0 || x == width - 1) {
                printf("\n");
                for (border = 0; border <= length + 2; border++) {
                    printf("-");
                }
            }
            else {
                printf("\n|");
                //Kind of improper to use three if statements on a row...
                for (spacer = 0; spacer <= length; spacer++) {
                    if (x >= playersHeight && x <= playersHeight + 3 && spacer == 10) {
                        printf("[");
                        spacer++;
                    }
                    if (spacer == ball.ballXAxis && x == ball.ballYAxis) {
                        printf("*");
                        spacer++;
                    }
                    if (x >= computersHeight && x <= computersHeight + 3 && spacer == 70) {
                        printf("]");
                        spacer++;
                    }
                    printf(" ");
                }
                printf("|");
            }

        }
        if (ball.ballXAxis <= 11 && (ball.ballYAxis < playersHeight || ball.ballYAxis > playersHeight + 3)) {
            playersHeight = 6, computersHeight = 6, length = 82, width = 17;
            ball = (BallState){40, 7, 0, 1, 0, 0, 1};
            computerScore++;
            printf("\nYou lost. Computer's score: %d", computerScore);
            printf("\nDo you want to play again? Press 1 to confirm, Press 2 to decline, Press 3 to show score, Press 4 to show instructions again ");
            scanf("%d", &decision);
            switch (decision) {
                case 1:
                    continue;
                case 2:
                    return 0;
                case 3:
                    printf("Player's score: %d\nComputer's score: %d\n", playerScore, computerScore);
                    continue;
                case 4:
                    instructions();
                    continue;
                default:
                    printf("Invalid response. Try again\n");
                    continue;
            }
        } else if (ball.ballXAxis >= 69 && (ball.ballYAxis < computersHeight || ball.ballYAxis > computersHeight + 3)) {
            playersHeight = 6, computersHeight = 6, length = 82, width = 17;
            ball = (BallState){40, 7, 0, 1, 0, 0, 1};
            playerScore++;
            printf("\nYou won! Player's score: %d", playerScore);
            printf("\nDo you want to play again? Press 1 to confirm, Press 2 to decline, Press 3 to show score, Press 4 to show instructions again ");
            scanf("%d", &decision);
            switch (decision) {
                case 1:
                    continue;
                case 2:
                    return 0;
                case 3:
                    printf("Player's score: %d\nComputer's score: %d\n", playerScore, computerScore);
                    continue;
                case 4:
                    instructions();
                    continue;
                default:
                    printf("Invalid response. Try again\n");
                    continue;
            }
        }
    }
}
