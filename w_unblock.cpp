#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <linux/kernel.h>
#include <sys/syscall.h>

#define __NR_unblock 435

long unblock_syscall(pid_t proc, unsigned long nr) {
	return syscall(__NR_unblock);
}

int main(int argc, char *argv[]) {
	long rv;
	long proc;
	unsigned long nr;
	proc = argv[1];
	nr = argv[2];
	if(argc != 3) {
		perror("Incorrect arguments\n");
	}
	else if(proc <= 0 || nr > 436) {
		perror("Incorrect arguments\n");
	}
	else {
		rv = unblock_syscall(proc, nr);

		if(rv < 0) {
			perror("Syscall failed\n");
		}
		else {
			printf("Unblock successful\n");
		}
		return 0;
	}
	return 0;
}
