#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define ROWS 500
#define COLUMNS 500

#define ITERATIONS 10000


void boundaryconditions(float *);
void duplicate_grids(float *, float *);
void perform_iterations(float*);
float sum_of_squares(float *);


int main()
{
    /* Allocating memory equivalent to two grids  */
    float *grid1 = calloc(ROWS*COLUMNS*2, sizeof(float));
    float *grid2 = grid1 + (ROWS*COLUMNS);

    boundaryconditions(grid1);

    duplicate_grids(grid1, grid2);

    clock_t tic = clock();
    perform_iterations(grid1);
    clock_t toc = clock();

    
    float sum1=0, sum2=0;
    sum1=sum_of_squares(grid1);
    sum2=sum_of_squares(grid2);


    free(grid1);

    printf("Individual sum of squares: %.8f, %.8f\nDifference: %.8f\n", sum1, sum2, sum1-sum2);
    printf("Time taken for iterations: %.15f\n", (double)(toc - tic) / CLOCKS_PER_SEC);

    return 0;
}


float sum_of_squares(float *grid)
{
    /*Excluding points corresponding to the boundary conditions*/
    float sum=0;
    for(int i=1;i<ROWS-1;i++)
    {
        for(int j=1;j<COLUMNS-1;j++)
        {
            sum = sum + grid[i*COLUMNS + j] * grid[i*COLUMNS + j];
        }
    }
    return sum;
}


void boundaryconditions(float *grid1)
{
    /* Boundary conditions at x=0,x=1,y=0,y=1 for function x^2-y^2*/
    for(int j=0; j<COLUMNS; j++)
    {
        grid1[j]=(float)j/(COLUMNS-1)*j/(COLUMNS-1);
        grid1[(ROWS-1)*COLUMNS+j]=(float)j/(COLUMNS-1)*j/(COLUMNS-1)-1;
    }
     for(int i=0; i<ROWS; i++)
    {
        grid1[i*COLUMNS]=-(float)i/(ROWS-1)*i/(ROWS-1);
        grid1[i*COLUMNS + ROWS-1]=1-(float)i/(ROWS-1)*i/(ROWS-1);
    }
}


void duplicate_grids(float *grid1, float *grid2)
{
    for(int i=0; i<ROWS; i++)
    {
        for(int j=0; j<COLUMNS; j++)
        grid2[i*COLUMNS + j]=grid1[i*COLUMNS + j];
    }
    
}


void perform_iterations(register float *grid1)
{
    int counter = ITERATIONS/2;
    float *grid1end = grid1 + (ROWS-1) * COLUMNS;
    float *grid2end = grid1 + (2*ROWS - 1) * COLUMNS;

    while( (--counter) > 0)
    {
        
        /*Setting up variables for odd iteration*/
        register float *pos_grid1= grid1 + COLUMNS;
        register float *pos_grid2= grid1 + (ROWS+1)*COLUMNS;

        register float *row_end= pos_grid1 + COLUMNS - 1;

        for(; row_end<grid1end ;row_end+=COLUMNS)
        {
            for(;(++pos_grid1)<row_end;)
            {
                *(++pos_grid2)= 0.25f * (pos_grid1[-COLUMNS] + pos_grid1[-1] + pos_grid1[1] + pos_grid1[COLUMNS]);
            }
            pos_grid1+=1;
            pos_grid2+=2;
        }

        /*Setting up variables for even iteration*/
        pos_grid1= grid1 + COLUMNS;
        pos_grid2= grid1 + (ROWS+1)*COLUMNS;

        row_end= pos_grid2 + COLUMNS - 1;

        for(; row_end<grid2end ;row_end+=COLUMNS)
        {
            for(;(++pos_grid2)<row_end;)
            {
                *(++pos_grid1)= 0.25f * (pos_grid2[-COLUMNS] + pos_grid2[-1] + pos_grid2[1] + pos_grid2[COLUMNS]);
            }
            pos_grid2+=1;
            pos_grid1+=2;
        }
    }   
}
