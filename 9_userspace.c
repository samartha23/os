

#include <stdio.h>
#include <linux/kernel.h>
#include <sys/syscall.h>
#include <unistd.h>
int main()
{
	long int r = syscall(358);
	printf("System call sys_hello returned %ld\n", r);
	return 0;
}
