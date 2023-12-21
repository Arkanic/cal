#include <stdio.h>
#include "cal.h"

int main(int argc, char *argv[]) {
	if(argc <= 1) {
		printf("Specify .ics file to open!\n");
		return 1;
	}

	char *filename = argv[argc - 1];
	struct IcsElement *head = ics_fromfile(filename);

	ie_printall(head);

	ie_freeall(head);

	return 0;
}
