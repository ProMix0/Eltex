#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX(a, b) \
	if (a < b) a = b;

struct node {
	struct node *left, *right, *parent;
	int data;
	int width, selfWidth, count;
};

typedef struct node node;

node* newNode(int data) {
	node* node = malloc(sizeof(struct node));
	node->data = data;
	node->left = 0;
	node->right = 0;
	node->width = 0;
	node->selfWidth = 0;
}

node* insert(node* root, int data) {
	if (root == 0) return 0;

	while (1) {
		if (root->data > data) {
			if (root->left == 0) {
				root->left = newNode(data);
				return root->left;
			}
			root = root->left;
		} else {
			if (root->right == 0) {
				root->right = newNode(data);
				return root->right;
			}
			root = root->right;
		}
	}
}

void width(node* root) {
	if (root == 0) return;
	int count = 0;
	root->width = 0;
	if (root->left) {
		count++;
		width(root->left);
		root->width += root->left->width;
	}
	if (root->right) {
		count++;
		width(root->right);
		root->width += root->right->width;
	}
	int selfWidth = 0;
	int temp = root->data;
	if (temp == 0) {
		selfWidth = 1;
	} else {
		if (temp < 0) {
			temp = -temp;
			selfWidth++;
		}
		while (temp) {
			temp /= 10;
			selfWidth++;
		}
	}
	root->selfWidth = selfWidth;
	switch (count) {
		case 0:
			root->width = selfWidth + 1;
			break;
		case 1:
			MAX(root->width, selfWidth)
			break;
		case 2:
			selfWidth += 2;
			MAX(root->width, selfWidth);
			break;
	}
	root->count = count;
}

void printNode(node* node) {
	if (node->parent && node->parent->count == 1)
		node->width = node->parent->width;
	if (node->count == 2) {
		int spaces = (node->width - node->selfWidth) / 2 - 1;
		int hyphLeft = spaces - node->left->width / 2;
		int hyphRight = spaces - node->right->width / 2;
		for (int i = 0; i < spaces - hyphLeft; i++) printf(" ");
		printf("/");
		for (int i = 0; i < hyphLeft; i++) printf("-");
		printf("%d", node->data);
		for (int i = 0; i < hyphRight; i++) printf("-");
		printf("\\");
		if (spaces == 0) printf(" ");
		for (int i = 0; i < spaces - hyphRight; i++) printf(" ");
	} else {
		int spaces = (node->width - node->selfWidth) / 2;
		for (int i = 0; i < spaces; i++) printf(" ");
		printf("%d", node->data);
		if (spaces == 0) printf(" ");
		for (int i = 0; i < spaces; i++) printf(" ");
	}
}

void printNodeInfo(node* root) {
	if (root == 0) return;
	printNodeInfo(root->left);
	printf("Node: %d, count: %d, width: %d\n", root->data, root->count,
		   root->width);
	printNodeInfo(root->right);
}

typedef struct nodePrint {
	node* node;
	int width;
} nodePrint;

void printTree(node* root) {
	width(root);

	// printNodeInfo(root);

	nodePrint *curr = malloc(sizeof(struct nodePrint)), *next;
	int currCount = 1;
	int nextCount = 0;
	curr[0].node = root;
	while (1) {
		// printf("Curr count: %d\n", currCount);
		// for (int i = 0; i < currCount; i++)
		// 	printf("x%x %d\t", curr[i].node, curr[i].width);
		// printf("\n");
		nextCount = 0;
		next = malloc(sizeof(struct nodePrint) * currCount * 2);
		for (int i = 0; i < currCount; i++) {
			if (curr[i].node) {
				printNode(curr[i].node);
				if (curr[i].node->left)
					next[nextCount++].node = curr[i].node->left;
				if (curr[i].node->right)
					next[nextCount++].node = curr[i].node->right;
				if (curr[i].node->count == 0) {
					next[nextCount].node = 0;
					next[nextCount++].width = curr[i].node->width;
				}
			} else {
				for (int j = 0; j < curr[i].width; j++) printf(" ");
				next[nextCount].node = 0;
				next[nextCount++].width = curr[i].width;
			}
		}
		printf("\n");
		free(curr);
		curr = next;
		currCount = nextCount;
		int zeroCount = 0;
		for (int i = 0; i < currCount; i++)
			if (curr[i].node == 0) zeroCount++;
		if (zeroCount == currCount) break;
	}
	free(next);
}

void main() {
	int seed = time(0);
	printf("Seed: %d\n", seed);
	srand(seed);
	node* root = newNode(rand());
	for (int i = 0; i < 30; i++) insert(root, rand());
	printTree(root);
}