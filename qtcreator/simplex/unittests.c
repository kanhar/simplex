
void myTest4()
{
    double A[CMAX][VMAX], B[VMAX], C[VMAX], R[VMAX];
    int d,n, count;

    d = 3; n = 3;

    A[0][0] = 2;    A[0][1] = 1;    A[0][2] = 1;
    A[1][0] = 4;    A[1][1] = 2;    A[1][2] = 3;
    A[2][0] = 2;    A[2][1] = 5;    A[2][2] = 5;

    B[0]= 14;        B[1]= 28;       B[2]= 30;
    C[0] = 1;        C[1]= 2;        C[2]= -1;

    count = SimplexAlgorithm(d,n, A, B, C, R);

}


void myTest3()
{
    double A[CMAX][VMAX], B[VMAX], C[VMAX], R[VMAX];
    int d,n, count;

/*
'* Maximize  P = 90x + 75y with conditions:      *
             3x+2y  <=66
             9x+4y  <=180
             2x+10y <=200

      */
    d = 2; n = 3;

    A[0][0] = 3;    A[0][1] = 2;
    A[1][0] = 9;    A[1][1] = 4;
    A[2][0] = 2;    A[2][1] = 10;

    B[0]= 66;        B[1]= 180;       B[2]= 200;
    C[0] = 90;      C[1]= 75;

    count = SimplexAlgorithm(d,n, A, B, C, R);

}

void myTest2()
{
    double A[CMAX][VMAX], B[VMAX], C[VMAX], R[VMAX];
    int d,n, count;

/*
'* Maximize 15 X1 + 17 X2 + 20 X3 with conditions:      *
'*                    X2 -   X3 <= 2                     *
'*           3 X1 + 3 X2 + 5 X3 <= 15                    *
'*           3 X1 + 2 X2 +   X3 <= 8

      */
    d = 3; n = 3;

    A[0][0] = 0;    A[0][1] = 1;    A[0][2] = -1;
    A[1][0] = 3;    A[1][1] = 3;    A[1][2] = 5;
    A[2][0] = 3;    A[2][1] = 2;    A[2][2] = 1;

    B[0]= 2;        B[1]= 15;       B[2]= 8;
    C[0] = 15;      C[1]= 17;       C[2]= 20;

    count = SimplexAlgorithm(d,n, A, B, C, R);

}

void myTest1()
{
    double A[CMAX][VMAX], B[VMAX], C[VMAX], R[VMAX];
    int d,n, count;

    //Maximize 2x+ 3y  + 4z:
    //    3x + 2y +  z   < 10
    //    2x + 5y + 3z   < 15

    //P - 2x  -3y - 4z  + 0s + 0t = 0
    //    3x + 2y +  z  + s       = 10
    //    2x + 5y + 3z  + 0s + 1t = 15

    d = 3; n = 2;

    A[0][0] = 3;    A[0][1] = 2;    A[0][2] = 1;
    A[1][0] = 2;    A[1][1] = 5;    A[1][2] = 3;
    B[0]= 10;       B[1]= 15;
    C[0] = 2;       C[1]= 3;        C[2]= 4;

    count = SimplexAlgorithm(d,n, A, B, C, R);

}



