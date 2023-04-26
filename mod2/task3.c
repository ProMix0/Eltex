#include <stdio.h>
#include <stdlib.h>
#define CHECKNULL \
	if (list == 0) return -1;

typedef struct Node {
	struct Node *next, *prev;
	int data;
} Node;

typedef struct List {
	Node *first, *last;
	int count;
} List;

List createList();
int addFirst(List* list, int data);
int addLast(List* list, int data);
int addAt(List* list, int data, int index);
int removeFirst(List* list);
int removeLast(List* list);
int removeAt(List* list, int index);
int editFirst(List* list, int newData);
int editLast(List* list, int newData);
int editAt(List* list, int index, int newData);
int print(List* list);
int printReversed(List* list);
List createRandom(int count);
int clearList(List* list);
int sortUp(List* list);
int sortDown(List* list);

Node* createNode(int data);
Node* getNode(List* list, int index);

void main() {
	List list = createList();

	while (1) {
		printf("Функции:\n");
		printf("(в скобочках указываются номера аргументов)\n");
		printf("\t1. Добавить элемент(1) первым в список\n");
		printf("\t2. Добавить элемент(1) последним в список\n");
		printf("\t3. Добавить элемент(1) в список по индексу(2)\n");
		printf("\t4. Удалить первый элемент\n");
		printf("\t5. Удалить последний элемент\n");
		printf("\t6. Удалить элемент по индексу(1)\n");
		printf("\t7. Задать значение(1) первому элементу\n");
		printf("\t8. Задать значение(1) последнему элементу\n");
		printf("\t9. Задать значение(1) элементу по индексу(2)\n");
		printf(
			"\t10. Заполнить список заданной длины(1) случайными значениями\n");
		printf("\t11. Вывести длину списка\n");
		printf("\t12. Вывести список\n");
		printf("\t13. Вывести список в обратном порядке\n");
		printf("\t14. Очистить список\n");
		printf("\t15. Отсортировать по возрастанию\n");
		printf("\t16. Отсортировать по убыванию\n");
		printf("\t0. Выход\n> ");

		int option = -1, item = -1, index = -1;
		scanf("%d", &option);
		switch (option) {
			case 0:
				clearList(&list);
				return;
			case 1:
				scanf("%d", &item);
				addFirst(&list, item);
				break;
			case 2:
				scanf("%d", &item);
				addLast(&list, item);
				break;
			case 3:
				scanf("%d %d", &item, &index);
				addAt(&list, item, index);
				break;
			case 4:
				removeFirst(&list);
				break;
			case 5:
				removeLast(&list);
				break;
			case 6:
				scanf("%d", &index);
				removeAt(&list, index);
				break;
			case 7:
				scanf("%d", &item);
				editFirst(&list, item);
				break;
			case 8:
				scanf("%d", &item);
				editLast(&list, item);
				break;
			case 9:
				scanf("%d %d", &item, &index);
				editAt(&list, item, index);
				break;
			case 10:
				scanf("%d", &index);
				clearList(&list);
				list = createRandom(index);
				break;
			case 11:
				printf("%d\n", list.count);
				break;
			case 12:
				print(&list);
				break;
			case 13:
				printReversed(&list);
				break;
			case 14:
				clearList(&list);
				break;
			case 15:
				sortUp(&list);
				break;
			case 16:
				sortDown(&list);
				break;
			default:
				printf("Неизвестная команда\n");
				break;
		}
	}
}

Node* getNode(List* list, int index) {
	if (list == 0) return 0;

	Node* node = list->first;
	for (int i = 0; i < index; i++) {
		node = node->next;
	}
	return node;
}
Node* createNode(int data) {
	Node* result = malloc(sizeof(Node));
	result->data = data;
}
List createList() {
	List list;
	list.first = 0;
	list.last = 0;
	list.count = 0;
	return list;
}
int addFirst(List* list, int data) {
	CHECKNULL

	Node* node = createNode(data);

	if (list->first == 0) {
		list->first = node;
		list->last = node;
		node->next = 0;
		node->prev = 0;
	} else {
		node->next = list->first;
		list->first->prev = node;
		node->prev = 0;
		list->first = node;
	}
	list->count++;
	return 0;
}
int addLast(List* list, int data) {
	CHECKNULL

	Node* node = createNode(data);

	if (list->first == 0) {
		list->first = node;
		list->last = node;
		node->next = 0;
		node->prev = 0;
	} else {
		node->prev = list->last;
		list->last->next = node;
		node->next = 0;
		list->last = node;
	}
	list->count++;
	return 0;
}
int addAt(List* list, int data, int index) {
	CHECKNULL

	if (index == 0) return addFirst(list, data);
	if (index == list->count) return addLast(list, data);
	if (index < 0 || index > list->count) return -1;

	Node* node = getNode(list, index);
	Node* newNode = createNode(data);

	newNode->prev = node->prev;
	node->prev->next = newNode;
	newNode->next = node;
	node->prev = newNode;
	list->count++;
	return 0;
}
int removeFirst(List* list) {
	CHECKNULL

	if (list->first == 0) return -1;

	list->first = list->first->next;
	free(list->first->prev);
	list->first->prev = 0;
	list->count--;
	return 0;
}
int removeLast(List* list) {
	CHECKNULL

	if (list->last == 0) return -1;

	list->last = list->last->prev;
	free(list->last->next);
	list->last->next = 0;
	list->count--;
	return 0;
}
int removeAt(List* list, int index) {
	CHECKNULL

	if (index == 0) return removeFirst(list);
	if (index == list->count - 1) return removeLast(list);
	if (index < 0 || index >= list->count) return -1;

	Node* node = getNode(list, index);
	node->next->prev = node->prev;
	node->prev->next = node->next;
	list->count--;
	free(node);
	return 0;
}
int editFirst(List* list, int newData) {
	CHECKNULL

	if (list->first == 0) return -1;

	list->first->data = newData;
	return 0;
}
int editLast(List* list, int newData) {
	CHECKNULL

	if (list->last == 0) return -1;

	list->last->data = newData;
	return 0;
}
int editAt(List* list, int index, int newData) {
	CHECKNULL

	if (index == 0) return editFirst(list, newData);
	if (index == list->count - 1) return editLast(list, newData);
	if (index < 0 || index >= list->count) return -1;

	getNode(list, index)->data = newData;
	return 0;
}
int print(List* list) {
	CHECKNULL

	Node* node = list->first;
	while (node) {
		printf("%d\n", node->data);
		node = node->next;
	}
	return 0;
}
int printReversed(List* list) {
	CHECKNULL

	Node* node = list->last;
	while (node) {
		printf("%d\n", node->data);
		node = node->prev;
	}
	return 0;
}
List createRandom(int count) {
	List list = createList();
	for (int i = 0; i < count; i++) addLast(&list, rand());
	return list;
}
int clearList(List* list) {
	CHECKNULL

	Node* node = list->first;
	for (int i = 0; i < list->count; i++) {
		Node* next = node->next;
		free(node);
		node = next;
	}
	*list = createList();
	return 0;
}
int sortUp(List* list) {
	CHECKNULL

	if (list->count <= 1) return 0;

	int swap = 1;
	while (swap) {
		swap = 0;
		Node* node = list->first;
		while (node->next != 0) {
			if (node->data > node->next->data) {
				int temp = node->data;
				node->data = node->next->data;
				node->next->data = temp;

				swap = 1;
			}
			node = node->next;
		}
	}

	return 0;
}
int sortDown(List* list) {
	CHECKNULL

	if (list->count <= 1) return 0;

	for (int i = list->count - 1; i > 0; i--) {
		int swap = 1;
		while (swap) {
			swap = 0;
			Node *start = list->first, *end = getNode(list, i);
			while (end != 0) {
				if (start->data < end->data) {
					int temp = start->data;
					start->data = end->data;
					end->data = temp;

					swap = 1;
				}
				start = start->next;
				end = end->next;
			}
		}
	}

	return 0;
}