#ifndef _FILE_LIST_H
#define _FILE_LIST_H
typedef struct _LinkNode{
	int filename;
	int priority;
	struct _LinkNode *next;
}LinkNode,*LinkList;

void list_init(LinkList *head);

void list_insert(LinkList *head,int fileName,int proi);


//delete head node...
void list_delete(LinkList *head);

int list_isEmpty(LinkList list);
int list_header(LinkList list);

void list_print(LinkList head);


#endif
