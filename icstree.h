struct CalendarElement {
        struct CalendarElement **children;
	struct CalendarElement *parent;

        int childCount;
        int childBufLen;

        char *name;
        char *content;
};

struct CalendarElement *ce_create(char *title, char *content, int preallocChildLength);
void ce_free(struct CalendarElement *element);
void ce_freeall(struct CalendarElement *head);
void ce_addchild(struct CalendarElement *parent, struct CalendarElement *child);
void ce_print(struct CalendarElement *element, int spaces);
void ce_printall(struct CalendarElement *element);
