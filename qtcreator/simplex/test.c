#include <stdio.h>
main()
{  double A1[40][2], A2[12][10], b1[40], b2[12],c1[2],c2[10];
   double result1[2], result2[10];
   int i, j; double s, t;
   printf("Preparing test1: two variables, many inequalities\n");
   i=0;
   for( s=0.05; s <= 1.001; s+=0.05 )
   {  A1[i][0] = (1.0/s); A1[i][1] = (s-1.0)/(s*s); b1[i]=1.0; i+=1; 
      A1[i][1] = (1.0/s); A1[i][0] = (s-1.0)/(s*s); b1[i]=1.0; i+=1; 
   }
   c1[0]=1.0; c1[1]=1.0;
   printf("Running test1: %d  inequalities\n", i);
   j = simplex(2,40, &(A1[0][0]), &(b1[0]), &(c1[0]), &(result1[0]));
   printf("Test1: extremal point (%f, %f) after %d steps\n", 
          result1[0], result1[1], j);
   printf("Preparing test2: ten variables, twelve inequalities\n");
   for( i=0; i<12; i++ )
     for (j=0; j<10; j++ )
       A2[i][j]=0.0;
   for( i=0; i<10; i++ )
   {  A2[i][i] =1.0;
      b2[i]=1.0;
   }
   for( i=0; i<10; i++ )
   {  A2[10][i] =1.0; A2[11][i] =0.0;
   }
   b2[10] = 5.0;
   for( i=6; i<10; i++ )
   {  A2[11][i] = i;
   }
   b2[11] =3.0;
   for( i=0; i<10; i++ )
     c2[i] = 11.0-i;
   printf("Running test2\n");
   j = simplex(10,12, &(A2[0][0]), &(b2[0]), &(c2[0]), &(result2[0]));
   printf("Test2: extremal point \n");
   printf("%f, %f, %f, %f, %f,\n %f, %f, %f, %f, %f\n",
          result2[0], result2[1], result2[2], result2[3], result2[4],
          result2[5], result2[6], result2[7], result2[8], result2[9]);
   printf("found after %d steps\n", j);
}

