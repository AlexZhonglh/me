#include<stdio.h>
#include<stdbool.h>
#include<string.h>
#include "list.h"
#include<stdlib.h>

void func(List * list);
char getchoice(void);
void findone(List * list);

int main(void)
{
	List * list;

	if ((list = init()) == NULL)
	{
		fprintf(stderr, "初始化失败");
		exit(1);
	}
	func(list);
	puts("感谢使用");

	return 0;
}

void func(List * list)
{
	while (1)
	{
		puts("请选择：");
		puts("1.添加联系人");
		puts("2.浏览电话本");
		puts("3.查询联系人");
		puts("4.删除联系人");
		puts("5.删除所有联系人");
		puts("6.退出");
		switch(getchoice())
		{
			case '1': additem(list); break;
			case '2': show(list); break;
			case '3': findone(list); break;
			case '4': delet(list); break;
			case '5': deletall(list); break;
			case '6': quit(list); break;
		}
		puts("操作完成");
	}
}

char getchoice(void)
{
	char ans;
	ans = getchar();
	while (getchar() != '\n')
		;
	while (strchr("123456", ans) == NULL)
	{
		puts("请输入正确的选项");
		ans = getchar();
		while (getchar() != '\n')
			;
	}
	
	return ans;
}

void findone(List * list)
{
	char name[NAMEMAX];
	Node * pnode = list->head, *temp;

	puts("请输入联系人姓名：");
	scanf("%s", name);
	temp = find(pnode, name);
	if (!temp)
		puts("查无此人！");
	else
	{
		printf("%s :", name);
		printf("%s\n", temp->item.tel);
	}
}





	
