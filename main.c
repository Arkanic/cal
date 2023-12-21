#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cal.h"

#define TITLE_BUF_LEN 128
#define CONTENT_BUF_LEN 2048
#define IE_MAX_DEPTH 16

struct IcsElement *head = 0;

void processLine(char *title, char *content);

int main(int argc, char *argv[]) {
	if(argc <= 1) {
		printf("Specify .ics file to open!\n");
		return 1;
	}

	char *filename = argv[argc - 1];
	FILE *fp = fopen(filename, "r");
	if(!fp) {
		printf("Failed to open .ics file\n");
		return 1;
	}

	char title[TITLE_BUF_LEN]; int titlePosition = 0;
	char content[CONTENT_BUF_LEN]; int contentPosition = 0;
	unsigned short writingToContent = 0;
	for(char c = fgetc(fp); c != EOF; c = fgetc(fp)) {
		switch(c) {
			case ':':
				writingToContent = 1;
				break;
			case '\n':
				title[titlePosition] = '\0';
				content[contentPosition] = '\0';
				processLine(title, content);
				writingToContent = 0;
				titlePosition = 0;
				contentPosition = 0;
				break;
			default:
				if(writingToContent == 0) {
					if(titlePosition == TITLE_BUF_LEN) {
						printf("Title buffer overflow\n");
						return 1;
					} else {
						title[titlePosition] = c;
						titlePosition++;
					}
				} else {
					if(contentPosition == CONTENT_BUF_LEN) {
						printf("Content buffer overflow\n");
						return 1;
					} else {
						content[contentPosition] = c;
						contentPosition++;
					}
				}
				break;
		}
	}

	fclose(fp);

	// tree is now complete
	ie_printall(head);

	ie_freeall(head);

	return 0;
}

struct IcsElement *parentStack[IE_MAX_DEPTH]; int parentStackCount = 0;

void processLine(char *title, char *content) {
	int childBufPrefillSize = 0;
	if(strcmp(title, "BEGIN") == 0) childBufPrefillSize = 20;
	struct IcsElement *element = ie_create(title, content, childBufPrefillSize);
	if(head == 0) {
		head = element;
		parentStack[0] = element;
		parentStackCount++;
		return;
	}

	ie_addchild(parentStack[parentStackCount - 1], element);

	if(strcmp(title, "BEGIN") == 0) {
		parentStack[parentStackCount] = element;
		parentStackCount++;
	} else if(strcmp(title, "END") == 0) {
		parentStackCount--;
	}
}
