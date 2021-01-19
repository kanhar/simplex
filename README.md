simplex
=======
Simplex Problem: http://www.slideshare.net/sbishop2/simplex-algorithm

output
=======

root@KM-UB-DEV:/home/kanhar/bras/hw2_smplx/simplex# ./a.out 
Preparing test1: two variables, many inequalities
Running test1: 40  inequalities
Test1: extremal point (1.000000, 1.000000) after 21 steps

Preparing test2: ten variables, twelve inequalities
Running test2
Test2: extremal point 
1.000000, 1.000000, 1.000000, 1.000000, 1.000000,0.000000, 0.000000, 0.000000, 0.000000, 0.000000
found after 5 steps

Sam's comments
==============

<pre>
yeah pointer arithmetic is a bit tricky if its dimensions > 1, if not its trivial ... 
heres a refresher:
1) Difference between, statically and dynamically allocation multidimensional arrays. 

Statically allocated multidimensional arrays are nothing more then a long sequence of values, while dynamically allocated values is a long sequence of either pointers (address) or values that points to either another long sequence of pointers or values ... and so on.

2) Compilers are smart
Compilers are somewhat smart and based on the type of the variable they know which formula to use when you use [] operator.
Giving two varibales int A[size][] and int **A_p = new int*[size];
A[2][3]   == *(&A[0][0] + (size *2 ) + 3); // long sequence calc
A_p[2][3] ==  *(*(A_p + size) + 3); // initial long seq of pointers go to the appropriate pointer, dereference and point the right value

its crucial that you don't use A but A[0] or &A[0][0] since this a double pointer and hence the wrong values will be added when you apply arithmetic operators to it.

3) Typecasting pains!
Then we come to typecasting, since the compiler will use the type of the variable to properly calculate the address, if you do something like this
int **A_p = &A[0][0] then A_p[1][2] != A[1][2]
and even worse still 
int *A_p = &A[0][0] this is really bad since A_p[1][2] won't even compile.
well you can't rely on the compiler for the appropriate formula so just do it manually ...

int A[size][];
int *A_p = &A[0][0]
then A[1][2] == *(A_p + (size*1) + 2)
</pre>
