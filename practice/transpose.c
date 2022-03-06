#include <stdio.h>
#define ROW 3
#define COL 2

void transpose(int source[ROW][COL], int target[COL][ROW]) 
{
    int r,c;

    for (r=0; r < ROW; r++)
    {
        for (c=0; c < COL; c++)
        {
            target[c][r] = source[r][c];
        }
    }
}

void main() 
{
    int S[ROW][COL] = {{1,2}, {4,5}, {7,8}};
    int T[COL][ROW];
    int r,c;

    transpose(S, T);
    
    for (r=0; r < COL; r++)
    {
        for (c=0; c < ROW; c++)
        {
            printf("%d\n", T[r][c]);
        }
    }
}