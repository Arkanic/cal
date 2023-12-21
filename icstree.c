#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cal.h"

#define IE_CHILD_BUF_INCREMENT 16

struct IcsElement *ie_create(char *title, char *content, int preallocChildLength) {
	struct IcsElement *element = (struct IcsElement *)malloc(sizeof(struct IcsElement));

	if(preallocChildLength > 0) {
		element->children = (struct IcsElement **)malloc(sizeof(struct IcsElement *) * preallocChildLength);
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


void ie_free(struct IcsElement *element) {
	free(element->children);
	free(element->name);
	free(element->content);

	free(element);
}

void ie_freeall(struct IcsElement *head) {
	for(int i = 0; i < head->childCount; i++) {
		ie_freeall(head->children[i]);
	}

	ie_free(head);
}

void ie_addchild(struct IcsElement *parent, struct IcsElement *child) {
	if(parent->childCount >= parent->childBufLen) {
		parent->children = (struct IcsElement **)realloc(parent->children, (parent->childBufLen + IE_CHILD_BUF_INCREMENT) * sizeof(struct IcsElement *));
		parent->childBufLen = parent->childBufLen + IE_CHILD_BUF_INCREMENT;
	}

	parent->children[parent->childCount] = child;
	parent->childCount++;

	child->parent = parent;
}

void ie_print(struct IcsElement *element, int spaces) {
	for(int i = 0; i < spaces; i++) printf("  ");
	printf("%s: %s\n", element->name, element->content);

	for(int i = 0; i < element->childCount; i++) {
		ie_print(element->children[i], spaces + 1);
	}
}

void ie_printall(struct IcsElement *element) {
	ie_print(element, 0);
}
