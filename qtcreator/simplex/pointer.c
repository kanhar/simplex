    double A[10];
    int i,j;
    for (i=0;i<10;i++)
        A[i]=i;
    //PrintMe(&(A[0]));

    int ptr=0;
    double B[10][2];
    for (i=0;i<10;i++)
        for(j=0;j<2;j++)
            B[i][j]=ptr++;

    PrintMe2D(&(B[0][0]));


void PrintMe2D(double *B)
{
    int i, j;
    for (i=0;i<10;i++)
        for(j=0;j<2;j++)
            printf("B[%d,%d] = %f \n",i,j, B[i*2 + j] );
}

void PrintMe(double *A)
{
    int i;
    for (i=0;i<10;i++)
        printf("A[%d] = %f\n",i, *(A + i) );

}

