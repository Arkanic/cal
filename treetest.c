#include <stdio.h>
#include "icstree.h"

int main(void) {
	struct CalendarElement *element = ce_create("test", "hello", 0);
	struct CalendarElement *child = ce_create("child", "lole", 0);
	ce_addchild(element, child);

	for(int i = 0; i < 100; i++) {
		struct CalendarElement *grandchild = ce_create("grandchild", "kehjfhj", 0);
		ce_addchild(child, grandchild);
	}

	ce_printall(element);

	ce_freeall(element);

	return 0;
}
