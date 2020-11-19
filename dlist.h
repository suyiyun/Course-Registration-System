//
//	menu.h
//	Created by Yiyun Su on 08/08/2019


#ifndef DLIST_H
#define DLIST_H
//链表特点:无序，可重复，可存储任何类型数据,在同一个链表只会保存同一类型的数据
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SYSERR(x,option,y,message,z)	if((x) option (y))				\
										{									\
											printf("%s %s : %d : %s\n",__FILE__,__func__,__LINE__,message);\
											return z;						\
										}
//定义节点
typedef struct node	//链表的节点
{
	struct node *before;	//前向指针
	void *data;				//数据指针	
	struct node *after;		//后向指针
}node_t;
/*
功能：创建链表
返回值：NULL表示创建失败，head->before = head->after = head 表示创建成功
*/
node_t *create_dlist();


/*
功能：插入数据到链表头部
参数：head: 链表头节点； data: 要插入的数据，类型随意； size要插入的数据的数据类型所占内存的大小
返回值：-1表示插入失败，0表示插入成功
*/
int insert_hdlist(node_t *head,const void *data,int size);


/*
功能：插入数据到链表尾部
参数：head: 链表头节点； data: 要插入的数据，类型随意； size要插入的数据的数据类型所占内存的大小
返回值：-1表示插入失败，0表示插入成功
*/
int insert_tdlist(node_t *head,const void *data,int size);


typedef void (*showfun_t)(const void *);
/*
功能：从头开始显示链表内的数据
参数：head: 链表头节点； showfun:表示特定数据类型所要求的显示方法
*/
void show_hdlist(node_t *head,showfun_t showfun);


/*
功能：从头开始显示链表内的数据
参数：head: 链表头节点； showfun:表示特定数据类型所要求的显示方法
*/
void show_tdlist(node_t *head,showfun_t showfun);



typedef int (*cmpfun_t)(const void *,const void *);

/*
功能：查找链表内的数据
参数：head: 链表头节点； data: 要插入的数据，类型随意； cmpfun:根据查找的数据确定查找方法
返回值：NULL表示未找到，head->after ！= head 表示成功找到数据并存储在链表中
*/
node_t *find_vdlist(node_t *head,const void *data,cmpfun_t cmpfun);


/*
功能：删除链表头部的第一个数
参数：head: 链表头节点
返回值：-1表示删除失败，0表示删除成功
*/
int delete_hdlist(node_t *head);


/*
功能：删除链表尾部的最后一个数
参数：head: 链表头节点
返回值：-1表示删除失败，0表示删除成功
*/
int delete_tdlist(node_t *head);

/*
功能：删除链表内特定数据
参数：head: 链表头节点； data: 要删除的数据，类型随意； cmpfun:根据查找的数据确定查找方法返回值：
返回值：NULL表示未找到数据删除，head->after ！= head 表示找到数据并成功存储在链表中
*/
node_t *delete_vdlist(node_t *head,const void *data,cmpfun_t cmpfun);


/*
功能：释放整个链表所占的内存
参数：head: 链表头节点的地址
*/
void destroy_dlist(node_t **head);


/*
功能：从头开始按从小到大的顺序排列链表内的数据，用冒泡排序方法实现
参数：head: 链表头节点； cmpfun:根据查找的数据确定查找方法
*/
void blubsort(node_t *head,cmpfun_t cmpfun);

/*
功能：从头开始按从小到大的顺序排列链表内的数据，用插入排序方法实现
参数：head: 链表头节点； cmpfun:根据查找的数据确定查找方法
*/
void insertsort(node_t *head,cmpfun_t cmpfun);


/*
功能：从头开始按从小到大的顺序排列链表内的数据，用选择排序方法实现
参数：head: 链表头节点； cmpfun:根据查找的数据确定查找方法
*/
void selectsort(node_t *head,cmpfun_t cmpfun);
#endif
