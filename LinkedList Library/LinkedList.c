//LinkedList.c
#include "LinkedList.h"
#include <stdlib.h>
#include<memory.h>

#pragma warning (disable:4996)

void Create(LinkedList* linkedList) {
	linkedList->head = NULL;
	linkedList->tail = NULL;
	linkedList->length = 0;
	linkedList->current = NULL;
}

Node* InsertBefore(LinkedList* linkedList, Node* index, void* object, size_t size) {
	linkedList->current = (Node*)malloc(sizeof(Node) + size);
	memcpy(linkedList->current + 1, object, size);

	linkedList->current->next = index;
	if (linkedList->head != index) {
		linkedList->current->previous = index->previous;
		index->previous->next = linkedList->current;
	}
	else {
		linkedList->current->previous = linkedList->current;
		linkedList->head = linkedList->current;
	}
	index->previous = linkedList->current;
	linkedList->length++;
	return linkedList->current;
}

Node* AppendFromHead(LinkedList* linkedList, void* object, size_t size) {
	linkedList->current = (Node*)malloc(sizeof(Node) + size);
	memcpy(linkedList->current + 1, object, size);
	if (linkedList->head != NULL) {
		linkedList->current->next = linkedList->head;
		linkedList->current->previous = linkedList->current;
	}
	else {
		linkedList->current->next = linkedList->current;
		linkedList->tail = linkedList->current;
	}
	linkedList->head = linkedList->current;
	linkedList->length++;
	return linkedList->current;
}

Node* AppendFromTail(LinkedList* linkedList, void* object, size_t size) {
	linkedList->current = (Node*)malloc(sizeof(Node) + size);
	memcpy(linkedList->current + 1, object, size);
	linkedList->current->next = linkedList->current;
	if (linkedList->tail != NULL) {
		linkedList->current->previous = linkedList->tail;
		linkedList->tail->next = linkedList->current;
	}
	else {
		linkedList->current->previous = linkedList->current;
		linkedList->head = linkedList->current;
	}
	linkedList->tail = linkedList->current;
	linkedList->length++;
	return linkedList->current;
}

Node* GetAt(LinkedList* linkedList, Node* index, void* object, size_t size) {
	memcpy(object, index + 1, size);
}

Node* DeleteFromTail(LinkedList* linkedList) {
	Node* last;
	last = linkedList->tail;
	if (linkedList->head != linkedList->tail) {
		last->previous->next = last->previous;
		linkedList->tail = last->previous;
		linkedList->current = linkedList->tail;
	}
	else {
		linkedList->head = NULL;
		linkedList->tail = NULL;
		linkedList->current = NULL;
	}
	if (last != NULL) {
		free(last);
		last = NULL;
	}
	linkedList->length--;
	return last;
}

Node* DeleteFromHead(LinkedList* linkedList) {
	Node* first;
	first = linkedList->head;
	if (linkedList->head != linkedList->tail) {
		first->next->previous = first->next;
		linkedList->head = first->next;
		linkedList->current = linkedList->head;
	}
	else {
		linkedList->head = NULL;
		linkedList->tail = NULL;
		linkedList->current = NULL;
	}
	if (first != NULL) {
		free(first);
		first = NULL;
	}
	linkedList->length--;
	return first;
}

Node* InsertAfter(LinkedList* linkedList, Node* index, void* object, size_t size) {
	linkedList->current = (Node*)malloc(sizeof(Node) + size);
	memcpy(linkedList->current + 1, object, size);

	linkedList->current->previous = index;
	if (linkedList->tail != index) {
		linkedList->current->next = index->next;
		index->next->previous = linkedList->current;
	}
	else {
		linkedList->current->next = linkedList->current;
		linkedList->tail = linkedList->current;
	}
	index->next = linkedList->current;
	linkedList->length++;
	return linkedList->current;
}

Node* LinearSearchUnique(LinkedList* linkedList, void* key, size_t size, int(*compare)(void*, void*)) {
	Node* previous = NULL;
	linkedList->current = linkedList->head;
	while (linkedList->current != previous && Compare(linkedList->current + 1, key) != 0) {
		previous = linkedList->current;
		linkedList->current = linkedList->current->next;
	}
	if (linkedList->current == previous) {
		linkedList->current = NULL;
	}
	return linkedList->current;
}

void LinearSearchDuplicate(LinkedList* linkedList, void* key, Node** (*indexes), Long* count, size_t size, int(*compare)(void*, void*)) {
	Node* previous = NULL;
	Long i = 0;
	*count = 0;

	*indexes = (Node * (*))calloc(linkedList->length, sizeof(Node * (*)));
	linkedList->current = linkedList->head;
	while (linkedList->current != previous) {
		if (compare(linkedList->current + 1, key) == 0) {
			(*indexes)[i] = linkedList->current;
			(*count)++;
			i++;
		}
		previous = linkedList->current;
		linkedList->current = linkedList->current->next;
	}
}

Node* First(LinkedList* linkedList) {
	linkedList->current = linkedList->head;
	return linkedList->current;
}

Node* Last(LinkedList* linkedList) {
	linkedList->current = linkedList->tail;
	return linkedList->current;
}

Node* Previous(LinkedList* linkedList) {
	linkedList->current = linkedList->current->previous;
	return linkedList->current;
}

Node* Next(LinkedList* linkedList) {
	linkedList->current = linkedList->current->next;
	return linkedList->current;
}

Node* Move(LinkedList* linkedList, Node* index) {
	linkedList->current = index;
	return linkedList->current;
}

Node* Delete(LinkedList* linkedList, Node* index) {
	if (linkedList->head != index && linkedList->tail != index) {
		index->previous->next = index->next;
		index->next->previous = index->previous;
		linkedList->current = index->next;
	}
	else if (linkedList->head == index && linkedList->head != linkedList->tail) {
		index->next->previous = index->next;
		linkedList->head = index->next;
		linkedList->current = linkedList->head;
	}
	else if (linkedList->tail == index && linkedList->head != linkedList->tail) {
		index->previous->next = index->previous;
		linkedList->tail = index->previous;
		linkedList->current = linkedList->tail;
	}
	else {
		linkedList->head = NULL;
		linkedList->tail = NULL;
		linkedList->current = NULL;
	}
	if (index != NULL) {
		free(index);
		index = NULL;
	}
	linkedList->length--;
	return index;
}

void DeleteAllItems(LinkedList* linkedList) {
	Node* previous = NULL;
	linkedList->current = linkedList->head;
	while (linkedList->current != previous) {
		previous = linkedList->current;
		linkedList->head = linkedList->current->next;
		if (linkedList->current != NULL) {
			free(linkedList->current);
		}
		linkedList->current = linkedList->head;
	}
	linkedList->head = NULL;
	linkedList->tail = NULL;
	linkedList->current = NULL;
	linkedList->length = 0;
}

void Destroy(LinkedList* linkedList) {
	Node* previous = NULL;
	linkedList->current = linkedList->head;
	while (linkedList->current != previous) {
		previous = linkedList->current;
		linkedList->head = linkedList->current->next;
		if (linkedList->current != NULL) {
			free(linkedList->current);
		}
		linkedList->current = linkedList->head;
	}
}