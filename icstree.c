#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "icstree.h"

#define CE_CHILD_BUF_INCREMENT 16

struct CalendarElement *ce_create(char *title, char *content, int preallocChildLength) {
	struct CalendarElement *element = (struct CalendarElement *)malloc(sizeof(struct CalendarElement));

	if(preallocChildLength > 0) {
		element->children = (struct CalendarElement **)malloc(sizeof(struct CalendarElement *) * preallocChildLength);
	}

	element->childCount = 0;
	element->childBufLen = preallocChildLength;

	int titleLength = strlen(title) + 1;
	int contentLength = strlen(content) + 1;

	element->name = (char *)malloc(sizeof(char) * titleLength);
	memcpy(element->name, title, titleLength);
	element->content = (char *)malloc(sizeof(char) * contentLength);
	memcpy(element->content, content, contentLength);

	return element;
}


void ce_free(struct CalendarElement *element) {
	free(element->children);
	free(element->name);
	free(element->content);

	free(element);
}

void ce_freeall(struct CalendarElement *head) {
	for(int i = 0; i < head->childCount; i++) {
		ce_freeall(head->children[i]);
	}

	ce_free(head);
}

void ce_addchild(struct CalendarElement *parent, struct CalendarElement *child) {
	if(parent->childCount >= parent->childBufLen) {
		parent->children = (struct CalendarElement **)realloc(parent->children, (parent->childBufLen + CE_CHILD_BUF_INCREMENT) * sizeof(struct CalendarElement *));
		parent->childBufLen = parent->childBufLen + CE_CHILD_BUF_INCREMENT;
	}

	parent->children[parent->childCount] = child;
	parent->childCount++;

	child->parent = parent;
}

void ce_print(struct CalendarElement *element, int spaces) {
	for(int i = 0; i < spaces; i++) printf("  ");
	printf("%s: %s\n", element->name, element->content);

	for(int i = 0; i < element->childCount; i++) {
		ce_print(element->children[i], spaces + 1);
	}
}

void ce_printall(struct CalendarElement *element) {
	ce_print(element, 0);
}
