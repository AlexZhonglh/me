#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include "list.h"
#include<string.h>

static char * s_get(char * st, int n);
Node * find(Node * head, char * name);
static Node *findprevious(Node * pnode, Node * node);
static void eatline(void);

/*List * init(void)
{
	FILE *fp;
	int count0 = 0;
	Node * pnew, *temp;
	List * list = (List *) malloc(sizeof(List));

	if ((fp = fopen("cache.dat", "w+b")) == NULL)
		return NULL;
	if (!(pnew = (Node *) malloc(sizeof(Node))))
	{
		return NULL;
	}
	rewind(fp);
	while (!(pnew->next = NULL) && fread(&(pnew->item), sizeof(Item), 1, fp))
	{
		if (++count0 == 1)
			list->head = pnew;
		temp = pnew;
		temp->next = pnew = (Node *) malloc(sizeof(Node));
	}
	free(pnew);
	if (count0 == 0)
	{
		list->head = NULL;
	}
	list->count = count0;
	fclose(fp);

	return list;
}
*/

List * init(void)
{
	FILE * fp;
	Item temp;
	int count0 = 0;
	Node * pnew, *pnode = NULL;
	List * list = (List *) malloc(sizeof(List));

	if ((fp = fopen("cache.dat", "r+b")) == NULL)
	{
		fp = fopen("cache.dat", "w+b");
		if (!fp)
			return NULL;
	}
	rewind(fp);
	while (fread(&temp, sizeof(Item), 1, fp))
	{
		pnew = (Node *) malloc(sizeof(Node));
		if (!pnew)
		{
			puts("空间不足！");
			exit(EXIT_FAILURE);
		}
		if (!pnode)
			list->head = pnew;
		else
			pnode->next = pnew;
		pnew->item = temp;
		pnew->next = NULL;
		pnode = pnew;
		count0++;
	}
	if (!count0)
	{
		list->head = NULL;
		list->count = 0;
	}
	fclose(fp);
	return list;
}

void show(const List * list)
{
	Node * pnode = list->head;

	if (!pnode)
		puts("无联系人");
	else 
	{
		puts("********************");
		while (pnode != NULL)
		{
			printf("%s : ", pnode->item.name);
			printf("%s\n", pnode->item.tel);
			pnode = pnode->next;
		}
		puts("********************");
	}
}

void additem(List * list)
{
	char tempname[NAMEMAX];
	char temptel[TELMAX];
	Node * pnode;

	puts("请输入姓名：");
	s_get(tempname, NAMEMAX);
	puts("请输入电话：");
	s_get(temptel, TELMAX);
	if (!(list->head))
	{
		list->head = pnode = (Node *) malloc(sizeof(Node));
	}
	else
	{
		pnode = list->head;
		while (pnode->next != NULL)
		{
			pnode = pnode->next;
		}
		pnode->next = (Node *) malloc(sizeof(Node));
		pnode = pnode->next;
	}
	strcpy(pnode->item.name, tempname);
	strcpy(pnode->item.tel, temptel);
	pnode->next = NULL;
	list->count++;
}

char * s_get(char * st, int n)	
{
	char * ret_val;
	char * find;

	ret_val = fgets(st, n, stdin);
	if (ret_val)
	{
		find = strchr(st, '\n');
		if (find)
			*find = '\0';

		else
			while (getchar() != '\n')
				;
	}
	
	return ret_val;
}

void quit(List * list)
{
	FILE * fp;
	Node * pnode = list->head,* temp;

	if ((fp = fopen("cache.dat", "w+b")) == NULL)
		{
			puts("文件打开错误");
			exit(EXIT_FAILURE);
		}
	rewind(fp);
	while (pnode)
	{
		fwrite(&(pnode->item), sizeof(Item), 1, fp);
		pnode = pnode->next;
	}
	fclose(fp);
	pnode = list->head;
	while (pnode)
	{
		temp = pnode->next;
		free(pnode);
		pnode = temp;
	}
	free(list);
	exit(0);
}

void delet(List * list)
{
	char ans;
	char name[NAMEMAX];
	Node * pnode = list->head, *temp, *previous;
	
	if (!pnode)
		puts("无可用联系人！");
	else
	{
		puts("请输入将删除联系人姓名：");
		scanf("%s", name);
		getchar();
		if(temp = find(pnode, name))
		{
			printf("确定要删除联系人%s?(y/n)\n", name);
			ans = getchar();
			eatline();
			if (ans == 'y')
			{	
				previous = findprevious(temp, list->head);
				if (!previous)
					list->head = temp->next;
				else 
					previous->next = temp->next;
				free(temp);
				list->count--;
			}
		}
		else 
			puts("查无此人！");
	}
}		
	
Node * find(Node * head, char * name)
{
	Node * pnode = head;

	while (pnode && strcmp(pnode->item.name,name))
		pnode = pnode->next;
	
	return pnode;
}

Node * findprevious(Node * pnode, Node * node)
{
	Node * findnode = node;

	if (findnode == pnode)
		return NULL;
	while (findnode->next != pnode)
		findnode = findnode->next;

	return findnode;
}

void deletall(List * list)
{
	Node * pnode = list->head, *temp;
	char ans;

    puts("确定？(y/n)");
	ans = getchar();
	eatline();
	if (ans == 'y')
	{
		if (pnode)
		{
	    	do 
			{
				temp = pnode->next;
				free(pnode);
				pnode = temp;
			} while (pnode != NULL);
			list->head = NULL;
			list->count = 0;
		}
	}
}

void eatline(void)
{
	while (getchar() != '\n')
		;
}
	
			

		
		
