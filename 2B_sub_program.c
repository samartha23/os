/*

Problem Statement: Implement the C program in which main program accepts an array. Main program uses the FORK
system call to create a new process called a child process. Parent process sorts an array and passes the
sorted array to child process through the command line arguments of EXECVE system call. The child
process uses EXECVE system callto load new program which display array in reverse order.
*/

#include <stdio.h>

void bubble_sort(char arr[]) {
    for(int i=0; i<5; i++) {
        for(int j=i+1; j<5; j++) {
            if(arr[i] > arr[j]) {
                int temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
    }

    printf("Sorted array: ");
    for(int i=0; i<5; i++) {
        printf("%d ", arr[i]);
    }
}

int main(int argc, char *argv[]) {
    bubble_sort(argv[1]);
}
