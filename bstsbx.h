#ifndef BST_H_INCLUDED
#define BST_H_INCLUDED
#include <sys/types.h>
#include <pthread.h>

typedef struct node {

	pid_t pid;
	
	struct node *left, right;

	int count;

	pthread_rwlock_t *rwlock;
	
} rb_node;

typedef struct node *n_node(pid_t pid) {
	struct node *temp = (struct node *)malloc(sizeof(struct node));
	temp->pid = pid;
	temp->left = temp->right = NULL;
	return temp;
}

node* search(pid_t pid, node *n);
node* insert(pid_t pid, node *n);
node* delete(pid_t pid, node *root);
node* minpid(node *n);
int getpid(node *n);
void clear(node *n);

#endif
