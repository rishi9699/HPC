/*
Laplace solver on a unit square
The actual function here is x^2 - y^2

Iterating over the sub-2d-array using a single variable, without OpenMP
*/

#include <stdio.h>
#include <time.h>

int main()
{
    int r=500, c=500;  //number of grid points
    float a[r][c];

    //Initializing array
    for(int x=0; x<c; x++)
    for(int y=0; y<r; y++)
    a[y][x]=0;

    //Imposing boundary conditions
    for(int x=0; x<c; x++)
    {
        a[0][x]=(float)x/(c-1)*x/(c-1);
        a[r-1][x]=(float)x/(c-1)*x/(c-1)-1;
    }
     for(int y=0; y<r; y++)
    {
        a[y][0]=-(float)y/(r-1)*y/(r-1);
        a[y][r-1]=1-(float)y/(r-1)*y/(r-1);
    }


    //Another array for carrying iterations
    float b[r][c];
    for(int y=0; y<r; y++){
        //printf("\n");
    for(int x=0; x<c; x++){
        b[y][x]=a[y][x];
        //printf("%.5f ", a[y][x]);
    }}

    //printf("\n");

    float *ptr1=(float *)a;
    float *ptr2=(float *)b;

    float sum1=0, sum2=0;
    int counter = 10000;   //number of iterations

    float *pos1=NULL, *pos2=NULL, *temp=NULL;  //To be used inside the loop during iteration

    clock_t tic = clock();
   
    while(counter > 0)
    {
        //sum1=sum2;
        //sum2=0;
        temp=ptr1;  //interchanging the reference to the arrays
        ptr1=ptr2;
        ptr2=temp;

        for(int i=0;i<((r-2)*(c-2));i++)
        {
            pos1=ptr1+((i/(r-2))+1)*c+(i%(c-2))+1;
            pos2=ptr2+((i/(r-2))+1)*c+(i%(c-2))+1;
            *(pos2)=0.25*(*(pos1-c)+*(pos1+c)+*(pos1-1)+*(pos1+1));

            /* printf("%.2f ",*pos2);
            if((i+1)%(c-2) == 0)
            printf("\n"); */
            
            //sum2=sum2+ ((*pos2) * (*pos2));
        }
        
        //printf("\n");
        counter--;
        //printf("%.2f, %.2f, %.4f\n", sum1, sum2, sum1-sum2);
    }

    clock_t toc = clock(); //stop counter

    //SUM OF SQUARES OF THE ELEMENTS FOR THE 2 ARRAYS
    for(int i=0;i<((r-2)*(c-2));i++)
    {
        pos1=ptr1+((i/(r-2))+1)*c+(i%(c-2))+1;
        pos2=ptr2+((i/(r-2))+1)*c+(i%(c-2))+1;
        
        sum1=sum1+ ((*pos1) * (*pos1));
        sum2=sum2+ ((*pos2) * (*pos2));
    }


    
    printf("%.8f, %.8f, %.8f\n", sum1, sum2, sum1-sum2);   //the difference in square sums
    printf("%.15f\n", (double)(toc - tic) / CLOCKS_PER_SEC); //time taken

    /*int x=55;
    int y=73;
    printf("%.5f, %.5f", a[y][x], (float)x/(c-1)*x/(c-1) - (float)y/(r-1)*y/(r-1));*/ //To check the true value vs. computed value

    return 0;
}
