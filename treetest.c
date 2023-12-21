#include <stdio.h>
#include "cal.h"

int main(void) {
	struct IcsElement *element = ie_create("test", "hello", 0);
	struct IcsElement *child = ie_create("child", "lole", 0);
	ie_addchild(element, child);

	for(int i = 0; i < 100; i++) {
		struct IcsElement *grandchild = ie_create("grandchild", "kehjfhj", 0);
		ie_addchild(child, grandchild);
	}

	ie_printall(element);

	ie_freeall(element);

	return 0;
}
