#include <linux/kernel.h>
#include <linux/syscalls.h>
#include <stdio.h>
#include <errno.h>
#include <generated/asm-offsets.h>
#include <linux/init.h>
#include <linux/module.h>
#include <pthread.h>
#include <asm/uacess.h>
#include "bstsbx.c"



static pthread_rwlock_t list[NR_syscalls];

pthread_rwlock_t p_lock;
#define MAX_PROC_ID = 4194304;

static int __init create_bst(void) {
	long i;
	for (i = 0; i < NR_SYSCALLS; i++) {
		bst_arr[0] = NULL;
	}

	p_lock = PTHREAD_RWLOCK_INITIALIZER;
	
	return 0;
}

SYSCALL_DEFINE2(sbx421_block, pid_t, proc, unsigned long, nr) {
	
	if(proc > MAX_PROC_ID || proc < 0) {
		return -EINVAL;
	}
	else if (nr > NR_syscalls || nr < 0) {
		return -ENOSYS;
	}

	pthread_rwlock_wrlock(&p_lock);
	pthread_rwlock_wrlock(&list[nr]);

	node *newNode;

	if(bst_arr[nr].search(proc, newNode) == NULL) {
		bst_arr[nr].insert(proc, newNode);
	}
	else {
		return -EPERM;
	}

	pthread_rwlock_wrlock(&list[nr]);
	pthread_rwlock_wrunlock(&perm_lock);
	
	return 0;
}

SYSCALL_DEFINE2(sbx421_unblock, pid_t, proc, unsigned long, nr) {
		
	if(proc > MAX_PROC_ID || proc < 0) {
		return -EINVAL;
	}
	else if (nr > NR_syscalls || nr < 0) {
		return -ENOSYS;
	}

	pthread_rwlock_wrlock(&p_lock);
	pthread_rwlock_wrlock(&list[nr]);
	node *newNode;

	if(bst_arr[nr].search(proc, newNode) == NULL) {
		bst_arr[nr].insert(proc, newNode);
	}
	else {
		return -EPERM;
	}

	pthread_rwlock_wrlock(&list[nr]);
	pthread_rwlock_wrunlock(&perm_lock);

	return 0;
}

SYSCALL_DEFINE2(sbx421_count, pid_t, proc, unsigned long, nr) {

        if(proc > MAX_PROC_ID || proc < 0) {
		return -EINVAL;
	}
	else if (nr > NR_syscalls || nr < 0) {
		return -ENOSYS;
	}

	pthread_rwlock_rdlock(&p_lock);
	pthread_rwlock_rdlock(&list[nr]);

	node *newNode;

	if(bst_arr[nr].search(proc, newNode) == NULL) {
		bst_arr[nr].insert(proc, newNode);
	}
	else {
		return -EPERM;
	}

	pthread_rwlock_rdlock(&list[nr]);
	pthread_rwlock_rdunlock(&perm_lock);

        return 0;
}


