#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "move.h"

int checkMoves(disk board[SIZE][SIZE], player currentPlayer, player opponent, int possibleMoves[SIZE][SIZE])
{
    int i, j, c, d;
    int counter = 64;
    /* Initializing all array elements to 0 */
    for(i=0; i<SIZE; i++)
    {
        for(j=0; j<SIZE; j++)
        {
            possibleMoves[i][j] = 0;
        }
    }
    /* Checking for tiles with currentPlayer's disk on them
       And checking all direction from these tiles to find
       possible moves */
    for(i=0; i<SIZE; i++)
    {
        for(j=0; j<SIZE; j++)
        {
            if(board[i][j].type == currentPlayer.type)
            {   /* Checking to the right */
                for(c=i; c<SIZE; c++)
                {
                    if(board[c][j].type == NONE && board[c-1][j].type != opponent.type)
                    {
                        break;
                    }
                    else if(board[c][j].type == NONE && board[c-1][j].type == opponent.type)
                    {
                        possibleMoves[c][j] = 1;
                    }
                } /* Checking to the left */
                for(c=i; c>=0; c--)
                {
                    if(board[c][j].type == NONE && board[c+1][j].type != opponent.type)
                    {
                        break;
                    }
                    else if(board[c][j].type == NONE && board[c+1][j].type == opponent.type)
                    {
                        possibleMoves[c][j] = 1;
                    }
                } /* Checking down */
                for(c=j; c<SIZE; c++)
                {
                     if(board[i][c].type == NONE && board[i][c-1].type != opponent.type)
                    {
                        break;
                    }
                     else if(board[i][c].type == NONE && board[i][c-1].type == opponent.type)
                    {
                        possibleMoves[i][c] = 1;
                    }
                } /* Checking up */
                for(c=j; c>=0; c--)
                {
                     if(board[i][c].type == NONE && board[i][c+1].type != opponent.type)
                    {
                        break;
                    }
                     else if(board[i][c].type == NONE && board[i][c+1].type == opponent.type)
                    {
                        possibleMoves[i][c] = 1;
                    }
                } /* Checking diagonal up/left */
                for(c=i, d=j; c>=0 && d>=0; c--, d--)
                {
                     if(board[c][d].type == NONE && board[c+1][d+1].type != opponent.type)
                     {
                        break;
                     }
                     else if(board[c][d].type == NONE && board[c+1][d+1].type == opponent.type)
                     {
                        possibleMoves[c][d] = 1;
                     }
                } /* Checking diagonal up/right */
                for(c=i, d=j; c<SIZE && d>=0; c++, d--)
                {
                     if(board[c][d].type == NONE && board[c-1][d+1].type != opponent.type)
                     {
                         break;
                     }
                     if(board[c][d].type == NONE && board[c-1][d+1].type == opponent.type)
                     {
                         possibleMoves[c][d] = 1;
                     }
                }  /* Checking diagonal down/right */
                for(c=i, d=j; c<SIZE && d<SIZE; c++, d++)
                {
                     if(board[c][d].type == NONE && board[c-1][d-1].type != opponent.type)
                     {
                         break;
                     }
                     if(board[c][d].type == NONE && board[c-1][d-1].type == opponent.type)
                     {
                         possibleMoves[c][d] = 1;
                     }
                }  /* Checking diagonal down/left */
                for(c=i, d=j; c>=0 && d<SIZE; c--, d++)
                {
                     if(board[c][d].type == NONE && board[c+1][d-1].type != opponent.type)
                     {
                         break;
                     }
                     if(board[c][d].type == NONE && board[c+1][d-1].type == opponent.type)
                     {
                         possibleMoves[c][d] = 1;
                     }
                }
            }
        }

    }
    /* Checking to see if possibleMoves has any possible moves in it */
    for(i=0; i<SIZE; i++)
    {
        for(j=0; j<SIZE; j++)
        {
            if(possibleMoves[i][j] != 0)
            {
                counter--;
            }
        }
    }
    return counter;
}

void printMoves(int possibleMoves[SIZE][SIZE])  /* Printing the possible moves */
{
    int i, j;

    printf("\n\nYour possible moves are as follows:\n");
    for(i=0; i<SIZE; i++)
    {
        for(j=0; j<SIZE; j++)
        {
            if(possibleMoves[i][j] == 1)
            {
                printf("(%d,%d) ", i+1, j+1);  /* Displaying all of the possible moves the player can have in a user-friendly way*/
            }
        }
    }

}

void makeMove(player currentPlayer, player opponent, int possibleMoves[SIZE][SIZE], disk board[SIZE][SIZE])
{
    printf("\n\nPlayer '%s' please make a move (choose the relative number):\n", currentPlayer.name);
    int i=0, j=0, c=0, d=0, e=0, f=0;
    int count = 1, choice = 0;
    int counter = 0, counter2 = 0;

    /* Assigning the possible moves a value */
    for(i=0; i<SIZE; i++)
    {
        for(j=0; j<SIZE; j++)
        {
            if(possibleMoves[i][j] == 1)
            {
                possibleMoves[i][j] = count;
                printf("%d:(%d,%d)\n", count, i+1, j+1);
                count++;
            }
        }
    }
    repeat:
    /* Player chooses a move*/
    printf("\nEnter your choice: ");
    scanf("%d", &choice);
    fflush(stdin);

    for(i=0; i<SIZE; i++)
    {
        for(j=0; j<SIZE; j++)
        {
            if(choice == possibleMoves[i][j])
            {
                counter++; /* Checking to see if the user entered a valid choice*/
            }
        }
    }

    /* If the user didn't enter a valid choice then ask them to do it again */
    if(counter != 1)
    {
        if(counter2 >= 0 && counter2 <=4)
        {
            printf("Please enter a valid number\n");
        }
        else if(counter2 > 4 && counter2 <=15)
        {
            printf("You're checking this very thoroughly...\n");
        }
        else if(counter2 > 15)
        {
            printf("Terminating programme...\n");  /* If the user keeps entering in invalid choices the programme shuts down*/
            exit(0);
        }
        counter2++;
        goto repeat;
    }

    for(i=0; i<SIZE; i++)
    {
        for(j=0; j<SIZE; j++)
        {
            /* Checking to see if the value matches the user choice value */
            if(possibleMoves[i][j] == choice)
            {
                board[i][j].type = currentPlayer.type;

                /* Checking right for disks to change colour*/
                for(c=i+1; c<SIZE; c++)
                {
                    if(board[c][j].type == currentPlayer.type && board[c-1][j].type == opponent.type)
                    {
                        d=c;
                        d--;
                        /* Changes opponent's disks colour if necessary */
                        while(board[d][j].type == opponent.type)
                        {
                            board[d][j].type = currentPlayer.type;
                            d--;
                        }
                        break;
                    }
                }
                /* Checking left */
                for(c=i-1; c>=0; c--)
                {
                    if(board[c][j].type == currentPlayer.type && board[c+1][j].type == opponent.type)
                    {
                        d=c;
                        d++;
                        /* Changes opponent's disks colour if necessary */
                        while(board[d][j].type == opponent.type)
                        {
                            board[d][j].type = currentPlayer.type;
                            d++;
                        }
                        break;
                    }
                }
                /* Checking down */
                for(c=j+1; c<SIZE; c++)
                {
                    if(board[i][c].type == currentPlayer.type && board[i][c-1].type == opponent.type)
                    {
                        d=c;
                        d--;
                        /* Changes opponent's disks colour if necessary */
                        while(board[i][d].type == opponent.type)
                        {
                            board[i][d].type = currentPlayer.type;
                            d--;
                        }
                        break;
                    }
                }
                /* Checking up */
                for(c=j-1; c>=0; c--)
                {
                    if(board[i][c].type == currentPlayer.type && board[i][c+1].type == opponent.type)
                    {
                        d=c;
                        d++;
                        /* Changes opponent's disks colour if necessary */
                        while(board[i][d].type == opponent.type)
                        {
                            board[i][d].type = currentPlayer.type;
                            d++;
                        }
                        break;
                    }
                }
                /* Checking diagonal up/left */
                for(c=i-1, d=j-1; c>=0 && d>=0; c--, d--)
                {
                     if(board[c][d].type == currentPlayer.type && board[c+1][d+1].type == opponent.type)
                     {
                        e=c;
                        e++;
                        f=d;
                        f++;
                        /* Changes opponent's disks colour if necessary */
                        while(board[e][f].type == opponent.type)
                        {
                            board[e][f].type = currentPlayer.type;
                            e++;
                            f++;
                        }
                        break;
                     }
                }
                /* Checking diagonal up/right */
                for(c=i+1, d=j-1; c<SIZE && d>=0; c++, d--)
                {
                     if(board[c][d].type == currentPlayer.type && board[c-1][d+1].type == opponent.type)
                     {
                        e=c;
                        e--;
                        f=d;
                        f++;
                        /* Changes opponent's disks colour if necessary */
                        while(board[e][f].type == opponent.type)
                        {
                            board[e][f].type = currentPlayer.type;
                            e--;
                            f++;
                        }
                        break;
                     }
                }
                /* Checking diagonal down/right */
                for(c=i+1, d=j+1; c<SIZE && d<SIZE; c++, d++)
                {
                     if(board[c][d].type == currentPlayer.type && board[c-1][d-1].type == opponent.type)
                     {
                         e=c;
                         e--;
                         f=d;
                         f--;
                         /* Changes opponent's disks colour if necessary */
                         while(board[e][f].type == opponent.type)
                         {
                             board[e][f].type = currentPlayer.type;
                             e--;
                             f--;
                         }
                         break;
                     }
                }
                /* Checking diagonal down/left */
                for(c=i-1, d=j+1; c>=0 && d<SIZE; c--, d++)
                {
                     if(board[c][d].type == currentPlayer.type && board[c+1][d-1].type == opponent.type)
                     {
                         e=c;
                         e++;
                         f=d;
                         f--;
                         /* Changes opponent's disks colour if necessary */
                         while(board[e][f].type == opponent.type)
                         {
                             board[e][f].type = currentPlayer.type;
                             e++;
                             f--;
                         }
                         break;
                     }
                }
            }
        }
    }
}
