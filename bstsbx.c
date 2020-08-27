#include <stdio.h>
#include "bstsbx.h"


void clear(node *n) {

	if( n != NULL ) {
		clear(n->left);
		clear(n->right);
		free(n);
	}

}

int getpid(node *n) {
	return n->pid;
}

node* search(pid_t pid, node *root) {
	
	if (root == NULL || root->pid == pid) {
		return root;
	}
	if (root->pid < pid)
		return search(pid, root->right);
	
	return search(pid, root->left);
}

node* insert(pid_t pid, node *n) {
	
	if (n == NULL)
		return n_node(pid);
	
	if (pid < n->pid)
		n->left = insert(pid, n->left);
	else if (pid > n->pid)
		n->right = insert(pid, n->right);
	
	return n;

}

node* minpid(node *n) {
	node *curr = n;
	while (curr && curr->left != NULL)
		curr = curr->left;
	return curr;
}

node* delete(pid_t pid, node *root) {

	if (root == NULL)
		return root;

	if (pid < root->pid)
		root->left = delete(root->right, pid);

	else if(pid > root->pid)
		root->right = delete(root->right, pid);

	else {
		if(root->left == NULL) {
			node *temp = root->right;
			free(root);
			return temp;
		}
		else if (root->right == NULL) {
			node *temp = root->left;
			free(root);
			return temp;
		}

		node *temp = minpid(root->right);
		root->pid = temp->pid;
		root->right = delete(root->right, temp->pid);
	}
	return root;
}




	








