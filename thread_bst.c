#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<pthread.h>

//#include<alloc.h>
//#include<conio.h>
#define MAX 3000

struct treenode
{	
	struct treenode *leftchild;
	int data;
	struct treenode *rightchild;
};
	
typedef struct treenode tree;

typedef struct _thread_data_t
{
	int amount;			// the size of input array 
	int list[2000];			// the array to catch all the input numbers
	int tid;
	int search_num;			// what number to search
	int total;			// how many numbers to search that you have
	char *arg;
}thread_data_t;

//typedef struct output_file

tree *insert(tree *, int);
tree *delete(tree *, int);
tree *search(tree *, int);
void inorder(tree *);
tree *find_min(tree *);
tree *find_max(tree *);
void *thr_func(void *);


int main(int argc, char *argv[ ])
{
	tree *bst = NULL;
	int input[ 5000 ];
	char input_num[MAX];
	char *temp;
	char *temp2;
	int b[MAX];
	int try[5] = {5,4,3,2,1};
	int i=0, num, req;
	int j = 0;
	int count = 0;
	int check = 0;
	int input_size = 0;
	int a[MAX] = {0};
	int test;
	char get_ch ;
	//  FILE pointer of reading and writing
	//  and thread_t
	FILE *fp;
	FILE *fw;

	//   check the arguments if it is exactly three
	/*
	if(argc != 3){
		perror("parameter amount error!");
		return 0;
	}
	*/
	

	// open two files for read input and write output
	fp = fopen(argv[1], "r");
 	//fw = fopen(argv[2], "a");
	/*
	while( (get_ch = fgetc(fp)) != EOF ){
		printf("this character: %s\n",get_ch);
		if( get_ch != )
		count ++;
	}
	*/
	while( fgets(input_num,MAX,fp) != NULL )
	{	
		printf("this is count: %d\n", count);
		temp = strtok(input_num," ");	
		while( temp != NULL){
			printf("%s\n",temp);
			//printf("test\n");
			if(count == 0){
				b[i] = atoi(temp);
				//printf("what is b[%d] ? %d\n",i,b[i]);
				i++;
				check++;
			}else{
				input[j] = atoi(temp);
				j++;
				input_size++;	
			}
			//printf("%s ",temp);
			temp = strtok(NULL, " ");
		}
		
		//char temp[10];
		count++;
	}
	i = 0;
	j = 0;
	// arr to catch the "to search numbers"
	// the value of the array "arr" is the number to search in the bst
	int arr[check];
	//printf("\n\ncheck: %d\n",check);
	for(j=0;j<check;++j){
		arr[j] = b[j];
		printf(" array arr value: %d \n",arr[j]);
	}
	printf("the total input numbers' size: %d\n",input_size);
	for(i=0;i<input_size;i++)
		printf("input[%d] , value: %d\n",i,input[i]);
	// create thread according to the number of int's on the first line
	pthread_t threads[check];
	// thread_data_t type structture initialize
	thread_data_t thr_data[check];
	// check the thread ids
	int check_thread[check];
	for(i=0;i<check;++i){
		thr_data[i].amount = input_size;
		thr_data[i].tid = i;
		thr_data[i].search_num = arr[i];
		thr_data[i].arg = argv[2];
		for(j=0;j<thr_data[i].amount;++j){
			thr_data[i].list[j] = input[j];
		}
		if( (check_thread[i] = pthread_create(&threads[i], NULL, thr_func, &thr_data[i])) ){
			fprintf(stderr,"error: pthread_create, thread: %d\n",check_thread[i]);
			return EXIT_FAILURE;
		}
	}
		// insert the array into the tree
	
	// print out the data in the inorder fashion
	//inorder(bst);
	printf("\n");
	// to open a file
	// while to insert 
	pthread_exit(NULL);
	fclose(fp);
	fclose(fw);
	return 0;
}

// the functnio that the threads need to do.
void *thr_func(void *arg)
{
	thread_data_t *data = (thread_data_t *)arg;
	//printf("hello thread, you are thread %d, value: %d\n",data->tid,data->search_num);
	tree *node = NULL;
	int k ;
	// construct tree:  insert all node into the tree
	for( k = 0; k<data->amount; k++ ){
		node = insert(node, data->list[k]);
	}
	//inorder(node);
	
	// search tree:
	int num = 0;
	//int a = data->amount;
	//int search_arr[data->] = {0};
	for( k = 0 ; k < data->amount ; k++){
		if( (data->list[k]) == (data->search_num) ){
			if( (node = search(node, data->search_num))!= NULL){
				num = num + 1;
			}
		}
	}
	data->total = num;
	printf("number of same: %d\n", num);
	FILE *fptr;
	fptr = fopen(data->arg,"a");
	fprintf(fptr,"search number: %d, the amount: %d\n", data->search_num, num);

	pthread_exit("thread exit success\n");

}


tree *find_min( tree *node )
{
	tree * current;
	current = node;
	while(current->leftchild != NULL)
		current = current->rightchild;
	return current;
}


tree *find_max(tree *node)
{
	if( node == NULL)
		return NULL;
	if( node->rightchild)
		return find_max(node->rightchild);
	else
		return node;
}



tree *insert( tree *node, int num)
{
	if( node == NULL ) {
		tree *temp;
		temp = (tree *)malloc( sizeof( struct treenode ) );
		temp->data = num;
		temp->leftchild = NULL;
		temp->rightchild = NULL;
		return temp;
	}
	if( num < node->data )		// leftchild
		node->leftchild = insert( node->leftchild , num );
	else
		node->rightchild = insert( node->rightchild , num );
	return node;
	
}



tree *delete( tree *node, int num)
{		
	tree *temp;
	if( node == NULL ){
		printf("the tree is empty\n");
		return node;
	}else if(num < node->data){
		node->leftchild = delete( node->leftchild , num);
	}else if(num > node->data){
		node->rightchild = delete( node->rightchild, num);
	}else{
		// if both children exists,
		// use the smallest on the righthand child
		if( node->leftchild && node->rightchild){
			temp = find_min( node->rightchild );
			node->data = temp->data;
			node->rightchild = delete( node->rightchild, temp->data);
		}else{
			temp = node; 		//
			if( node->leftchild == NULL){		// discard the leftchild
				temp = node->rightchild;
				return temp;
			}
			else if( node->rightchild == NULL){		// discard rightchild
				temp = node->leftchild;
				return temp;
			}
		}

	}
	return node;
}



tree *search( tree *node, int num)
{	
	int match = 0;
	if( node == NULL){
		return 0;
	}else if( num < node->data ){
		return search( node->leftchild, num);
	}else if( num > node->data ){
		return search ( node->rightchild, num);
	}else
		//match = match + 1;
		return node;
	
	
}



void inorder( tree *bst)
{
	if( bst != NULL){
		inorder( bst->leftchild);
		printf("%d ", bst->data);
		inorder( bst->rightchild);
	}
}
