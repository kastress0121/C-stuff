#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct node
{
	void *data;
	struct node *next;
}Node;

typedef struct linked_list
{
	Node *prev;
	Node *next;
	Node *current;
}Linked;

void init(Linked *);
void addHead(Linked *, void *);
void addTail(Linked *, void *);
void delete(Linked *, Node *);

int main(int argc, char *argv[]){
	

}


void initList(Linked *list){
	list->prev = NULL;
	list->next = NULL;
	list->current = NULL;
}

void addHead(Linked *list, void *data){
	Node *node = (Node *)malloc(sizeof(Node));
	node->data = data;
	// if list is empty, then make tail point to node, this is the rule, 
	// because we will however make head point to node later, so do the tail part here
	// moreover, the only node has to point to null
	if(list->head == NULL){
		list->tail = node;
		node->next = NULL;
	}else{
		// make the new node's next point to the old list head
		node->next = list->head;
	}
	// list head has to point to node 
	list->head = node;
}

void addTail(Linked *list, void *data){
	Node *node = (Node *)malloc(sizeof(Node));
	node->data = data;
	node->next = NULL;
	if(list->head == NULL){
		list->head = node;
	}else{
		list->tail->next = node;
	}

	list->tail = node;
}


void delete(Linked *list, Node *node){
	// 


}

