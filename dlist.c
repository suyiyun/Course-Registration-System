#include "dlist.h"


node_t *create_dlist()
{
	node_t *head = malloc(sizeof(node_t));
	SYSERR(NULL,==,head,"malloc error",NULL);
	head->data = NULL;
	head->before = head->after = head;

	return head;
}


int insert_hdlist(node_t *head,const void *data,int size)
{
	SYSERR(NULL,==,head,"head is null",-1);
	SYSERR(data,==,NULL,"data is null",-1);
	SYSERR(size,<,1,"size must >= 1",-1);
	node_t *newnode = malloc(sizeof(node_t));


	SYSERR(NULL,==,newnode,"malloc error",-1);
	newnode->data = malloc(size);
	if(NULL == newnode->data)
	{
		free(newnode);
		return -1;
	}

	memcpy(newnode->data,data,size);
	newnode->after = head->after;
	newnode->before = head;
	head->after->before = newnode;

	head->after = newnode;
	return 0;
}


void show_hdlist(node_t *head,showfun_t showfun)
{
	SYSERR(NULL,==,head,"head is null",);
	node_t *temp = head->after;
	while(temp != head && temp->data != NULL)
	{
		showfun(temp->data);
		temp = temp->after;
	}
	printf("\n");
}


void show_tdlist(node_t *head,showfun_t showfun)
{
	SYSERR(NULL,==,head,"head is null",);
	node_t *temp = head->before;
	while(temp != head && temp->data != NULL)
	{
		showfun(temp->data);
		temp = temp->before;
	}
	printf("\n");
}


int insert_tdlist(node_t *head,const void *data,int size)
{
	SYSERR(NULL,==,head,"head is null",-1);
	SYSERR(data,==,NULL,"data is null",-1);
	SYSERR(size,<,1,"size must >= 1",-1);
	node_t *newnode = malloc(sizeof(node_t));

	SYSERR(NULL,==,newnode,"malloc error",-1);
	newnode->data = malloc(size);
	if(NULL == newnode->data)
	{
		free(newnode);
		return -1;
	}

	memcpy(newnode->data,data,size);
	newnode->after = head;
	newnode->before = head->before;
	head->before->after = newnode;

	head->before = newnode;
	return 0;
}


node_t *find_vdlist(node_t *head,const void *data,cmpfun_t cmpfun)
{
	SYSERR(NULL,==,head,"head is null",NULL);
	SYSERR(data,==,NULL,"data is null",NULL);
	node_t *temp = head->after;
	while(temp != head && temp->data != NULL)
	{
		if(!cmpfun(temp->data,data))
			return temp;
		temp = temp->after;
	}
	return NULL;
}


int delete_hdlist(node_t *head)
{
	SYSERR(NULL,==,head,"head is null",-1);
	SYSERR(head->after,==,head,"list is empty",-1);
	node_t *temp = head->after;
	temp->after->before = head;
	
	head->after = temp->after;
	free(temp->data);
	free(temp);
	return 0;
}


int delete_tdlist(node_t *head)
{
	SYSERR(NULL,==,head,"head is null",-1);
	SYSERR(head->after,==,head,"list is empty",-1);
	node_t *temp = head->before;
	temp->before->after = head;

	head->before = temp->before;
	free(temp->data);
	free(temp);
	return 0;
}


node_t *delete_vdlist(node_t *head,const void *data,cmpfun_t cmpfun)
{
	SYSERR(NULL,==,head,"head is null",NULL);
	SYSERR(head->after,==,head,"list is empty",NULL);
	SYSERR(NULL,==,data,"data is null",NULL);
	node_t *temp = head->after,*before = NULL;

	while(temp != head && temp->data != NULL)
	{
		if(!cmpfun(temp->data,data))
		{
			before = temp->before;
			temp->after->before = temp->before;
			temp->before->after = temp->after;
			free(temp->data);
			free(temp);
			return before;
		}
		temp = temp->after;
	}
	return NULL;
}


void destroy_dlist(node_t **head)
{
	SYSERR(NULL,==,*head,"head is null",);
	node_t *temp = (*head)->after,*after = NULL;
	while(temp != *head)
	{
		after = temp->after;
		free(temp->data);
		free(temp);
		temp = after;
	}

	free(*head);
	*head = NULL;
}


void blubsort(node_t *head,cmpfun_t cmpfun)
{
	SYSERR(NULL,==,head,"head is null",);
	SYSERR(head->after,==,head,"list is empty!",);
	node_t *inext,*jnext,*end;
	void *temp = NULL;

	int flag;
	for(inext = head->after,end = head; inext->after != head; inext = inext->after,end = end->before)
	{
		flag = 0;
		for(jnext = head->after; jnext->after != end; jnext = jnext->after)
		{
			if(cmpfun(jnext->data,jnext->after->data) > 0)
			{
				temp = jnext->data;
				jnext->data = jnext->after->data;
				jnext->after->data = temp;
				flag = 1;
			}
		}

		if(!flag)
			break;
	}
}


void insertsort(node_t *head,cmpfun_t cmpfun)
{	
	SYSERR(NULL,==,head,"head is null",);
	SYSERR(head->after,==,head,"list is empty!",);
	node_t *inext,*jnext;
	void *temp = NULL;

	for(inext = head->after; inext != head; inext = inext->after)
	{
		temp = inext->data;
		for(jnext = inext; jnext->before != head && cmpfun(temp,jnext->before->data) < 0; jnext = jnext->before)
			jnext->data = jnext->before->data;
		jnext->data = temp;
	}
}


void selectsort(node_t *head,cmpfun_t cmpfun)
{
	SYSERR(NULL,==,head,"head is null",);
	SYSERR(head->after,==,head,"list is empty!",);
	node_t *inext,*jnext,*min;
	void *temp = NULL;
	
	for(inext = head->after; inext != head; inext = inext->after)
	{
		min = inext;
		for(jnext = inext->after; jnext != head; jnext = jnext->after)
		{
			if(cmpfun(jnext->data,min->data) > 0)
				min = jnext;
		}

		if(inext != min)
		{
			temp = inext->data;
			inext->data = min->data;
			min->data = temp;
		}
	}
}
