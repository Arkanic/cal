struct IcsElement {
        struct IcsElement **children;
	struct IcsElement *parent;

        int childCount;
        int childBufLen;

        char *name;
        char *content;
};

struct IcsElement *ie_create(char *title, char *content, int preallocChildLength);
void ie_free(struct IcsElement *element);
void ie_freeall(struct IcsElement *head);
void ie_addchild(struct IcsElement *parent, struct IcsElement *child);
void ie_print(struct IcsElement *element, int spaces);
void ie_printall(struct IcsElement *element);
