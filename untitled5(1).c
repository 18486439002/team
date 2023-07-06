#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>
typedef struct node{
	int flag;//是否空闲
	int begin;
	int size;
	struct node *next;
	struct node *previous;
}list;
int guide;//当前所指内存分区


void print_data(list *head){
	list *p;
	p=head->next;
	printf("  ");
	
	for(int i=0;i<127;i++){
		printf("_");
	}
	printf("\n |");
	while(1){
		if(p->flag==1){
			for(int i=1;i<p->size;i++){
				printf("::");
			}
			printf(":|");
		}else{
			for(int i=1;i<p->size;i++){
				printf("__");
			}
			printf("_|");
		}
		if(p->next==NULL){
			break;
		}
		p=p->next;
	}
	printf("\n :");
	for(int i=0;i<16;i++){
		printf("_._._._:");
	}
	printf("\n ");
	for(int i=0;i<=16;i++){
		if(i<3){
			printf("%dK      ",i*4);
		}else{
			printf("%dK     ",i*4);
		}
	}
}

// 在由head所表示的单链表里插入一个元素 x 到位置 i。
int ListInsert(list *head, int i, int x, int flag_insert)
{
	list *p,*q;
	p=head->next;
	while(1)
	{
		if(p->flag==1){
			if(p->next==NULL){
				return 1;
			}
			p=p->next;
			continue;
		}
		if(p->begin==i){
			break;
		}else if(p->begin<i && p->size+p->begin>=i+x){//p->size+p->begin>i+x这样会排除相等的情况，所以当p->size+p->begin=i+x时，会执行else导致卡死
			ListInsert(p->previous,p->begin,i-p->begin,0);
			break;
		}else
			p=p->next;
	}
	q=(list *)malloc(sizeof(list));
	q->size=x;
	q->begin=i;
	q->flag=flag_insert;
	
	p->previous->next=q;
	q->previous=p->previous;
	p->previous=q;
	q->next=p;
	
	p->begin=x+i;
	p->size-=x;
	if(p->size==0){
		if(p->next!=NULL){// q p p->n
			q->next=p->next;
			p->next->previous=q;
			free(p);
		}else{
			q->next=NULL;
			free(p);
		}
		
	}
	return 0;
}

// 在由head所表示的链表里删除位置 i 上的元素。调用成功后，列表长度减1。
int ListDelete(list *head, int i)
{
	list *p,*s;
	p=head->next;
	while(1){
		if(p->begin==i){
			break;
		}else{
			p=p->next;
		}
		if(p->next==NULL){
			return 1;
		}
	}
	
	if((p->begin==0 && p->next->flag==1) || (p->size+p->begin==64 && p->previous->flag==1)){
		p->flag=0;
	}
	s=p;
	if(p->previous->flag==0){
		p->previous->size+=p->size;
		if(p->next!=NULL){
			p->previous->next=p->next;
			p->next->previous=p->previous;
			p=p->previous;
			free(s);
		}else{
			p->previous->next=NULL;
			free(s);
		}
		
		
	}
	s=p->next;
	if(p->next!=NULL&&p->next->flag==0){
		p->size+=p->next->size;
		p->flag=0;
		if(p->next->next!=NULL){
			p->next=p->next->next;
			p->next->next->previous=p;
		}else{
			p->next=NULL;
		}
		free(s);
	}
	
	
	
	
	return 0;
}

int ListInitiate(list **head){ 
	*head=(list *) malloc(sizeof (list));
	(*head)->next=NULL;
	
	list *temp;
	temp=(list *) malloc(sizeof (list));
	if(*head==NULL || temp==NULL){
		exit(0);
	}
	(*head)->next=temp;
	temp->previous=*head;
	temp->size=64;
	temp->begin=0;
	temp->flag=0;
	
	return 0;
}
int Destroy(list **head)
{
	list *p,*p1;
	p=*head;
	while(p!=NULL)
	{
		p1=p;
		p=p->next;
		free(p1);
	}
	*head=NULL;
	return 0;
}

int input_FF(list *head, int x){
	list *p;
	p=head->next;
	for(int i=0;i<guide;){
		if(p->flag==1){
			p=p->next;
			continue;
		}else{
			p=p->next;
			i++;
		}
	}
	while(1){
		if(p->flag==1){
			p=p->next;
			continue;
		}
		if(p->size>=x){
			ListInsert(p->previous,p->begin,x,1);
			return 0;
		}
		if(p->next==NULL){
			return 1;
		}
	}
}
int input_NF(list *head, int x){
	list *p;
	p=head->next;
	while(1){
		if(p->flag==1){
			p=p->next;
			continue;
		}
		if(p->size>=x){
			ListInsert(p->previous,p->begin,x,1);
			return 0;
		}
		if(p->next==NULL){
			return 1;
		}
	}
}
int input_BF(list *head, int x){
	list *p,*p1;
	p=head->next;
	p1=p;
	p=p->next;
	while(1){
		if(p->flag==1){
			if(p->next==NULL){
				break;
			}else{
				p=p->next;
				continue;
			}
			
		}
		if(p->size>=x){
			if(p1->size>p->size){
				p1=p;
				if(p->next==NULL){
					break;
				}else{
					p=p->next;
				}
				
			}
		}
		if(p->next==NULL){
			break;
		}
	}
	if(p1->size<x){
		return 1;
	}else{
		ListInsert(p1->previous,p1->begin,x,1);
		return 0;
	}
}
int input_WF(list *head, int x){
	list *p,*p1;
	p=head->next;
	p1=p;
	p=p->next;
	while(1){
		if(p->flag==1){
			if(p->next==NULL){
				break;
			}else{
				p=p->next;
				continue;
			}
			
		}
		if(p->size>p1->size){
			p1=p;
			if(p->next==NULL){
				break;
			}else
				p=p->next;
		}
		
	}
	if(p1->size<x){
		return 1;
	}else{
		ListInsert(p1->previous,p1->begin,x,1);
		return 0;
	}
}

int main(){
	guide=0;
	list *head;
	ListInitiate(&head);
	head->flag=1;
	print_data(head);
	
	printf("1.按顺序输入“进程首地址（0~63）K”和“申请占用空间大小（1~32）KB”，每输入一组数据按一下回车，当’首地址+占用空间>64时自动退出输出：\n");
	int start=0,data=0;
	while(1){
		scanf("%d %d",&start,&data);
		if(start+data>64){
			break;
		}
		ListInsert(head,start,data,1);
	}
	
	print_data(head);
	
	int select1,select2;
	while(1){
		printf("\n 2.选择操作（1-申请内存 2-回收内存 3-退出）：");
		scanf("%d",&select1);
		if(select1==1){
			printf(" '-2.1选择动态分区分配算法（1-FF 2-NF 3-BF 4-WF）：");
			scanf("%d",&select2);
			printf("    '---2.1.2输入当前进程待申请的空间（1~32）KB：");
			scanf("%d",&data);
			if(select2==1){
				if(input_FF(head,data)){
					printf("找不到合适的内存分区，分配失败");
				}else
					printf("操作成功");
			}else if(select2==2){
				if(input_NF(head,data)){
					printf("找不到合适的内存分区，分配失败");
				}else
					printf("操作成功");
			}else if(select2==3){
				if(input_BF(head,data)){
					printf("找不到合适的内存分区，分配失败");
				}else
					printf("操作成功");
			}else
				if(input_WF(head,data)){
					printf("找不到合适的内存分区，分配失败");
				}else
					printf("操作成功");
		}else if(select1==2){
			printf("'-2.2输入待回收的进程空间首地址（0-63）K：");
			scanf("%d",&start);
			if(ListDelete(head,start)){
				printf("找不到该进程，请仔细输入！！");
				continue;
			}else
				printf("操作成功");
		}else{
			break;
		}
		
		print_data(head);
	}
	Destroy(&head);
	printf("\n\n\n");
	return 0;
}

