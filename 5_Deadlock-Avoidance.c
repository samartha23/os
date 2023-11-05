/* 

Title: C program for Deadlock Avoidance
Problem Statement: Implement the C program for Deadlock Avoidance Algorithm:Banker's Algorithm
*/

#include <stdio.h>
#include <stdlib.h>
void final_output(int k[][10], int n, int p)
{
    int i, j;
    for (i = 0; i < n; i++)
    {
        printf("\n");
        for (j = 0; j < p; j++)
        {
            printf("%d\t", k[i][j]);
        }
    }
}

// Banker's Algorithm
void Banker(int A[][10], int N[][10], int M[10][10], int W[1][10], int *n, int *m)
{
    int i, j;
    printf("Enter total no. of processes : ");
    scanf("%d", n);
    printf("\nEnter total no. of resources : ");
    scanf("%d", m);
    printf("\n");
    printf("Allocated Resources");
    for (i = 0; i < *n; i++)
    {
        printf("\nProcess %d\n", i + 1);
        for (j = 0; j < *m; j++)
        {
            printf("Resource %d : ", j + 1);
            scanf("%d", &A[i][j]);
        }
    }
    printf("\n");
    printf("Maximum Resources Required by processes");
    for (i = 0; i < *n; i++)
    {
        printf("\nProcess %d\n", i + 1);
        for (j = 0; j < *m; j++)
        {
            printf("Resource %d : ", j + 1);
            scanf("%d", &M[i][j]);
        }
    }

    printf("\nAvailable resources : \n");
    for (i = 0; i < *m; i++)
    {
        printf("Resource %d : ", i + 1);
        scanf("%d", &W[0][i]);
    }

    for (i = 0; i < *n; i++)
        for (j = 0; j < *m; j++)
            N[i][j] = M[i][j] - A[i][j];

    printf("\nAllocation Matrix");
    final_output(A, *n, *m);
    printf("\nMaximum Requirement Matrix");
    final_output(M, *n, *m);
    printf("\nNeed Matrix");
    final_output(N, *n, *m);
}

// Safety algorithm
int safety(int A[][10], int N[][10], int B[1][10], int n, int m, int a[])
{

    int i, j, k, x = 0, f1 = 0, f2 = 0;
    int F[10], W[1][10];
    for (i = 0; i < n; i++)
        F[i] = 0;
    for (i = 0; i < m; i++)
        W[0][i] = B[0][i];

    for (k = 0; k < n; k++)
    {
        for (i = 0; i < n; i++)
        {
            if (F[i] == 0)
            {
                f2 = 0;
                for (j = 0; j < m; j++)
                {
                    if (N[i][j] > W[0][j])
                        f2 = 1;
                }
                if (f2 == 0 && F[i] == 0)
                {
                    for (j = 0; j < m; j++)
                        W[0][j] += A[i][j];
                    F[i] = 1;
                    f1++;
                    a[x++] = i;
                }
            }
        }
        if (f1 == n)
            return 1;
    }
    return 0;
}

// Resource Request algorithm
void request(int A[10][10], int N[10][10], int B[10][10], int pid, int K)
{
    int rmat[1][10];
    int i;
    printf("\nEnter additional request : \n");
    for (i = 0; i < K; i++)
    {
        printf("Request for resource %d : ", i + 1);
        scanf("%d", &rmat[0][i]);
    }

    for (i = 0; i < K; i++)
        if (rmat[0][i] > N[pid][i])
        {
            printf("\nError encountered\n");
            exit(0);
        }

    for (i = 0; i < K; i++)
        if (rmat[0][i] > B[0][i])
        {
            printf("\nResources unavailable\n");
            exit(0);
        }

    for (i = 0; i < K; i++)
    {
        B[0][i] -= rmat[0][i];
        A[pid][i] += rmat[0][i];
        N[pid][i] -= rmat[0][i];
    }
}

int banker(int A[][10], int N[][10], int W[1][10], int n, int m)
{
    int j, i, a[10];
    j = safety(A, N, W, n, m, a);
    if (j != 0)
    {
        printf("\n\n");
        printf("\nSafe sequence\n");
        printf("<");
        for (i = 0; i < n; i++)
            printf(" P%d ", a[i]);
        printf(">");
        printf("\n");
        return 1;
    }
    else
    {
        printf("\nDeadlock has occured.\n");
        return 0;
    }
}

int main()
{
    int All[10][10], Max[10][10], Need[10][10], W[1][10];
    int n, m, pid, c, r;
    Banker(All, Need, Max, W, &n, &m);
    r = banker(All, Need, W, n, m);
    if (r != 0)
    {
        printf("\nDo you want make an additional"
               "request for any of the process ? (1=Yes|0=No)");
        scanf("%d", &c);
        if (c == 1)
        {
            printf("\nEnter process number : ");
            scanf("%d", &pid);
            request(All, Need, W, pid - 1, m);
            r = banker(All, Need, W, n, m);
            if (r == 0)
            {
                exit(0);
            }
        }
    }
    else
        exit(0);
    return 0;
}

/*
Output:

Enter total no. of processes : 4

Enter total no. of resources : 2

Allocated Resources
Process 1
Resource 1 : 1
Resource 2 : 0

Process 2
Resource 1 : 1
Resource 2 : 1

Process 3
Resource 1 : 1
Resource 2 : 2

Process 4
Resource 1 : 1
Resource 2 : 1

Maximum Resources Required by processes
Process 1
Resource 1 : 1
Resource 2 : 1

Process 2
Resource 1 : 2
Resource 2 : 3

Process 3
Resource 1 : 2
Resource 2 : 2

Process 4
Resource 1 : 3
Resource 2 : 2

Available resources :
Resource 1 : 1
Resource 2 : 1

Allocation Matrix
1       0
1       1
1       2
1       1
Maximum Requirement Matrix
1       1
2       3
2       2
3       2
Need Matrix
0       1
1       2
1       0
2       1


Safe sequence
< P0  P2  P3  P1 >

Do you want make an additionalrequest for any of the process ? (1=Yes|0=No)0
