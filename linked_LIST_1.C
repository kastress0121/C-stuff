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
	Node *head;
	Node *tail;
	Node *current;
}Linked;

typedef struct employ
{
    char name[20];
    unsigned int age;
}Employee;

typedef void (*DISPLAY)(void *);
typedef int (*COMPARE)(void *, void *);

void initList(Linked *);
void addHead(Linked *, void *);
void addTail(Linked *, void *);
void deleteNode(Linked *, Node *);
void printList(Linked *, DISPLAY);
void dis(Employee *);
int compName(Employee *, Employee *);
Node *getNode(Linked *, COMPARE, void *);
                                   
int main(int argc, char *argv[]){
    Linked list;
    initList(&list);
    
    Employee *tim = (Employee *)malloc(sizeof(Employee));
    strcpy(tim->name, "Tim");
    tim->age = 21;
    
    Employee *joyce = (Employee *)malloc(sizeof(Employee));
    strcpy(joyce->name, "Joyce");
    joyce->age = 21;
    
    Employee *andy = (Employee *)malloc(sizeof(Employee));
    strcpy(andy->name, "Andy");
    andy->age = 30;
    
    Employee *cella = (Employee *)malloc(sizeof(Employee));
    strcpy(cella->name, "Cella");
    cella->age = 26;

    addHead(&list, tim);
    addHead(&list, joyce);
    addTail(&list, andy);
    addTail(&list, cella);
    
    printList(&list, (DISPLAY)dis);
    Node *toDelete = getNode(&list, (int (*)(void *, void *))compName, cella);
    deleteNode(&list, toDelete);
    printList(&list, (DISPLAY)dis);
    
    return 0;
}

void dis(Employee *employee){
    printf("Employee name: %s, age: %u\n", employee->name, employee->age);
}

int compName(Employee *node1, Employee *node2){
    return strcmp(node1->name, node2->name);
}

void initList(Linked *list){
	list->head = NULL;
	list->tail = NULL;
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


void deleteNode(Linked *list, Node *node){
	// because free from the head of the list, have to check the condition
        // when there is only one node in the list
    if( node == list->head ){
        // if the node is the last node in the list
        if( list->head->next == NULL){
            list->head = NULL;
            list->tail = NULL;
        } else {
            // when deleting from the head but the head node is not the only one
            // left in the list, then simply ignore the head node. Make the 
            list->head = list->head->next;
        }
    } else {
        Node *temp = list->head;
        // keep finding the node you want to delete 
        // make temp be the node before the node you want to delete
        while( (temp != NULL) && (temp->next != node) ){
            temp = temp->next;
        }
        if(temp != NULL)
            temp->next = node->next;
        /*
         * if comment the free(); then there is logical error
         */
    }
    free(node);
}

Node *getNode(Linked *list, COMPARE compare, void *data){
    Node *node = (Node *)malloc(sizeof(Node));
    node = list->head;
    while( node != NULL){
        if( compare(node->data, data) == 0){
            return node;
        }
        node = node->next;
    }
    free(node);
    return NULL;
}


void printList(Linked *list, DISPLAY display){
    printf("The linked list: \n");
    Node *node = list->head;
    while(node != NULL){
        
        display(node->data);
        node = node->next;
    }
    
}






