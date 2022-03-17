//main.c
#include "LinkedList.h"
#include<stdlib.h>
#include <stdio.h>

int Compare(void* one, void* other);

int main(int argc, char* argv[]) {
	LinkedList linkedList;
	Node* index;
	Long i;
	Long count;
	int object;
	int ret;
	int key;
	Node* (*indexes);

	Create(&linkedList);

	object = 10;
	index = AppendFromTail(&linkedList, &object, sizeof(int));
	GetAt(&linkedList, index, &ret, sizeof(int));
	printf("%d\n", ret);

	index = DeleteFromTail(&linkedList, sizeof(int));
	if (index == NULL) {
		printf("지워졌습니다\n");
	}
	
	object = 10;
	index = AppendFromHead(&linkedList, &object, sizeof(int));
	GetAt(&linkedList, index, &ret, sizeof(int));
	printf("%d\n", ret);

	object = 20;
	index = InsertBefore(&linkedList, index, &object, sizeof(int));
	GetAt(&linkedList, index, &ret, sizeof(int));
	printf("%d\n", ret);

	object = 30;
	index = InsertAfter(&linkedList, index, &object, sizeof(int));
	GetAt(&linkedList, index, &ret, sizeof(int));
	printf("%d\n", ret);

	key = 10;
	index = LinearSearchUnique(&linkedList, &key, sizeof(int), Compare);
	GetAt(&linkedList, index, &ret, sizeof(int));
	printf("%d\n", ret);

	object = 20;
	index = AppendFromTail(&linkedList, &object, sizeof(int));
	GetAt(&linkedList, index, &ret, sizeof(int));
	printf("%d\n", ret);

	printf("==================\n");

	key = 20;
	LinearSearchDuplicate(&linkedList, &key, &indexes, &count, sizeof(int), Compare);

	i = 0;
	while (i < count) {
		GetAt(&linkedList, indexes[i], &ret, sizeof(int));
		printf("%d\n", ret);
		i++;
	}
	if (indexes != NULL) {
		free(indexes);
		indexes = NULL;
	}

	index = Last(&linkedList);
	GetAt(&linkedList, index, &ret, sizeof(int));
	printf("%d\n", ret);

	index = Previous(&linkedList);
	GetAt(&linkedList, index, &ret, sizeof(int));
	printf("%d\n", ret);

	index = First(&linkedList);
	GetAt(&linkedList, index, &ret, sizeof(int));
	printf("%d\n", ret);

	index = Next(&linkedList);
	GetAt(&linkedList, index, &ret, sizeof(int));
	printf("%d\n", ret);

	index = DeleteFromHead(&linkedList, sizeof(int));
	if (index == NULL) {
		printf("지워졌습니다\n");
	}

	index = First(&linkedList);
	GetAt(&linkedList, index, &ret, sizeof(int));
	printf("%d\n", ret);

	index = Move(&linkedList, index);
	GetAt(&linkedList, index, &ret, sizeof(int));
	printf("%d\n", ret);

	index = Delete(&linkedList, index);
	if (index == NULL) {
		printf("지워졌습니다\n");
	}

	DeleteAllItems(&linkedList);
	if (index == NULL) {
		printf("지워졌습니다\n");
	}

	Destroy(&linkedList);

	return 0;
}

int Compare(void* one, void* other) {
	int ret;
	if (*((int*)one) > *((int*)other)) {
		ret = 1;
	}
	else if (*((int*)one) == *((int*)other)) {
		ret = 0;
	}
	else if (*((int*)one) < *((int*)other)) {
		ret = -1;
	}
	return ret;
}