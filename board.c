#include "board.h"
#include <stdio.h>

void init_board(int b[][COL_BOARD])
{
    for(int i=0;i<FIL_BOARD;i++)
    {
        for(int j=0;j<COL_BOARD;j++)
        {
            b[i][j] = 0;
        }
    }

}

void print_board(int b[][COL_BOARD])
{
    for (int i=0;i<FIL_BOARD;i++)
    {
        for (int j=0;j<COL_BOARD;j++)
        {
            printf("%d ",b[i][j]);
        }
        printf("\n");
    }
}
