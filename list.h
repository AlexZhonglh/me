#ifndef LIST_H_
#define LIST_H_
#include<stdbool.h>

#define NAMEMAX 10
#define TELMAX 15

typedef struct item{
	char name[NAMEMAX];
	char tel[TELMAX];
} Item;

typedef struct node{
	Item item;
	struct node * next;
} Node;

typedef struct list{
	Node * head;
	int count;
} List;

List * init(void);
void show(const List * list);
void additem(List * list);
void quit(List * list);
Node * find(Node * pnode, char * name);
void delet(List * list);
void deletall(List * list);

#endif


