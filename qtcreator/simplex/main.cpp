#include <stdio.h>
#include <math.h>

#define CMAX  100
#define VMAX  100
#define ZERO 0
#define ONE 1

int NV, NC, MAXROW, MAXCOL, PR, PC;
double M[CMAX][VMAX];

void testCode();
void Print();

void GetIndexSmallestNegValueInObjectiveFunction();
void GetIndexSmallestNegRatioForConstraints();
void UpdatePivotRow();
void UpdateNonPivotRows();
bool ObjectiveRowContainsNegativeValues();


int   simplex(int d, int n, double *a, double *b, double *c,  double *result);
void LoadArray(int d, int n, double a[CMAX][VMAX], double b[VMAX], double c[VMAX],  double result[VMAX]);

void myTest1();
void myTest2();
void myTest3();
void myTest4();

void Test1();
void Test2();
void testCode();
void PrintMe(double *A);
void PrintMe2D(double *B);

bool VERBOSE=false;
int main()
{
    testCode();

    return -1;
}


/*
Attached is the test code.
The optimal point for the first test is 1,1,
for the second is 1,1,1,1,1,0,0,0,0,0
 Peter Brass*/

void testCode()
{
    int i, j;
    double s;

    double A1[40][2];
    double A2[12][10];

    double b1[40];
    double b2[12];
    double c1[2];
    double c2[10];

    double result1[2];
    double result2[10];

    printf("Preparing test1: two variables, many inequalities\n");
    i=0;
    for( s=0.05; s <= 1.001; s+=0.05 )
    {
        A1[i][0] = (1.0/s);
        A1[i][1] = (s-1.0)/(s*s);
        b1[i]=1.0; i+=1;

        A1[i][1] = (1.0/s);
        A1[i][0] = (s-1.0)/(s*s);
        b1[i]=1.0;

        i+=1;
    }

    c1[0]=1.0;
    c1[1]=1.0;
    printf("Running test1: %d  inequalities\n", i);
    j = simplex(2,40, &(A1[0][0]), &(b1[0]), &(c1[0]), &(result1[0]));
    printf("Test1: extremal point (%f, %f) after %d steps\n\n",result1[0], result1[1], j);


    printf("Preparing test2: ten variables, twelve inequalities\n");
    for( i=0; i<12; i++ )
     for (j=0; j<10; j++ )
       A2[i][j]=0.0;

    for( i=0; i<10; i++ )
    {
        A2[i][i] =1.0;
        b2[i]=1.0;
    }

    for( i=0; i<10; i++ )
    {
        A2[10][i] =1.0;
        A2[11][i] =0.0;
    }

    b2[10] = 5.0;
    for( i=6; i<10; i++ )
        A2[11][i] = i;

    b2[11] =3.0;
    for( i=0; i<10; i++ )
        c2[i] = 11.0-i;

    printf("Running test2\n");
    j = simplex(10,12, &(A2[0][0]), &(b2[0]), &(c2[0]), &(result2[0]));

    printf("Test2: extremal point \n");
    printf("%f, %f, %f, %f, %f,%f, %f, %f, %f, %f\n",
          result2[0], result2[1], result2[2], result2[3], result2[4],
          result2[5], result2[6], result2[7], result2[8], result2[9]);

    printf("found after %d steps\n", j);
}


int simplex(int d, int n, double *a, double *b, double *c,  double *result)
{
    int row, col, count;

    NV      = d;
    NC      = n;
    MAXROW  = NC + 1;
    MAXCOL  = NV + NC + 2;

    count   = 1;
    PR      = 1;

    //Add co-eff Matrix
    for(row=0; row<NC; row++)
        for(col=0;col<NV; col++)
            M[2+row][2+col] = a[row*d+col];

    //Add Objective Equation
    for(col=0;col<NV;col++)
        M[1][2+col]=*(c+col) * -1;

    //Add RHS Values (b)
    for(row=0;row<NC;row++)
        M[2+row][MAXCOL]=*(b+row);

    //Value for P
    M[1][1] = 1;

    //Set 1's
    for(row=0;row<NC; row++)
        M[2+row][NV+2+row] = 1;

    if (VERBOSE)
        Print();

    //Core Simplex Iteration Step
    while(ObjectiveRowContainsNegativeValues())
    {
        if (VERBOSE)
            printf("Iteration %d\n", count);
        GetIndexSmallestNegValueInObjectiveFunction();
        GetIndexSmallestNegRatioForConstraints();

        UpdatePivotRow();        
        UpdateNonPivotRows();
        if (VERBOSE)
            Print();

        count++;        
    }

    if (VERBOSE)
        Print();

    //Get Result Values (of Variables x,y,z...)
    int i,j, ptr;

    ptr=NV-1;

    for(i=1; i<=MAXROW; i++)
    {
        for(j=2; j<=NV+1; j++)
        {            
            if (i==1)
            {
                if(M[i][j] != 0.0)
                {                    
                    //Old code:   *(result + (j-2)) = 0.1;                    
                    if (ptr>=0)
                        *(result+ptr--) = 0;
                }
            }
            else
            {
                if (M[i][j] == 1.000000 )
                {
                    if (ptr>=0)
                        *(result+ptr--) = M[i][MAXCOL];
                    //OLD CODE:   *(result + (j-2)) = M[i][MAXCOL];
                }
            }            
        }
    }

    if (VERBOSE)
    {
        //Print Variable Values
        for(i=0;i<NV; i--)
            printf("var %d= %f \n",i, *(result+i));
        printf("Number of Iterations: %d\n", count-1);
    }

    return count -1;
}

bool ObjectiveRowContainsNegativeValues()
{
    int i;
    for (i=1; i<=MAXCOL; i++)
        if (M[1][i] < 0)
            return true;

    return false;
}

void UpdateNonPivotRows()
{
    int i,j;
    double Mul;

    for (i=1; i<=MAXROW; i++)
    {
        if (i==PR)
            continue;

        Mul = M[i][PC] / M[PR][PC] * -1;
        for(j=1; j<=MAXCOL; j++)
            M[i][j] += M[PR][j] * Mul;
    }
}


void UpdatePivotRow()
{
    int i ;
    double Pivot;
    Pivot = M[PR][PC];    
    for(i=1;i<=MAXCOL;i++)
        M[PR][i] = M[PR][i]/Pivot;

    if (VERBOSE)
        printf("Dividing Pivot Row= %d by %f\n", PR, Pivot);
}

//Not Sure: Difference between iRowValue <= Min or < Min
void GetIndexSmallestNegValueInObjectiveFunction()
{
    int i, Col;
    float iValue, Min;

    Min = 99999;

    for(i=1;i<=MAXCOL; i++)
    {
        iValue = M[1][i];
        if (iValue <= Min && iValue <0)
        {
            Min = iValue;
            Col = i;
        }
    }
    PC = Col;
    if (VERBOSE)
        printf("smallest negative value at Col %d in objective function is %f \n", PC, Min);
}

//Not Sure: If No Value Found or Value Negative?
void GetIndexSmallestNegRatioForConstraints()
{
    int i, Row;
    float iValue, MIN;

    MIN = 99999;

    for(i=2;i<=MAXROW; i++)
    {        
        iValue = M[i][MAXCOL] / M[i][PC];
        if (iValue < 0 )
            continue;

        if (iValue <= MIN)
        {
            MIN = iValue;
            Row = i;
        }
    }
    PR = Row;
    if (VERBOSE)
    {
        printf("smallest Positive Ratio for constraints is at Row %d, value = %f, ratio = %f\n", PR, M[PR][PC], MIN);
        printf("pivot PR, PC (%d,%d) =%f \n", PR, PC, M[PR][PC]);
    }
}


void Print()
{
    int i,j;

    printf("\n");
    for(i=1; i<=MAXROW; i++)
    {
        for(j=1; j<=MAXCOL; j++)
        {
            printf("%f \t", M[i][j]);
        }
        printf("\n\n");
    }
    printf("\n\n");
}


