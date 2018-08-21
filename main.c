#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "disksAndPlayers.h"
#include "move.h"

int main(void)
{
    int playChoice=1;
    int pMoves[SIZE][SIZE];
    int possible=0;
    int turnCount=1;

    int i,j;
    // Variables declaration
    while(playChoice==1)
    {
        player player1= {"player1", NONE, 0};
        player player2= {"player2", NONE, 0};
        disk board[SIZE][SIZE];

        initializePlayers(&player1, &player2);

        initializeBoard(board);

        printBoard(board);

        while(turnCount<=60)
        {
            if(turnCount%2 == 1)
            {
                possible = checkMoves(board, player1, player2, pMoves);
                if(possible==64)
                {
                    break;
                }
            }
            else
            {
                possible = checkMoves(board, player2, player1, pMoves);
                if(possible==64)
                {
                    break;
                }
            }
            printMoves(pMoves);
            if(turnCount%2 == 1)
            {
                makeMove(player1, player2, pMoves, board);
            }
            else
            {
                makeMove(player2, player1, pMoves, board);
            }
            printBoard(board);
            turnCount++;
        }

        for(i=0; i<SIZE; i++)
        {
            for(j=0; j<SIZE; j++)
            {
                if(board[i][j].type == player1.type)
                {
                    player1.points++;
                }
                else if(board[i][j].type == player2.type)
                {
                    player2.points++;
                }
            }
        }

        if(player1.points > player2.points)
        {
            printf("\n\n%s wins!\nPress 1 if you would like to play again. Press any other key if not: ", player1.name);
            scanf("%d", &playChoice);
            fflush(stdin);
        }
        else if(player2.points > player1.points)
        {
            printf("\n\n%s wins!\nPress 1 if you would like to play again: Press any other key if not: ", player2.name);
            scanf("%d", &playChoice);
            fflush(stdin);
        }
        else
        {
            printf("\n\nThe result is a draw!\nPress 1 if you would like to play again: Press any other key if not: ");
            scanf("%d", &playChoice);
            fflush(stdin);
        }
    }
    return 0;
}

