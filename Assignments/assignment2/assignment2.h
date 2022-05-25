typedef int boolean;
struct bst;
struct node;
struct bstQueue;

boolean isEmpty();
void makeEmpty();
void inOrder(struct node* root);
void preOrder(struct node* root);
void postOrder(struct node* root);
void postOrderDelete(struct node* root);
void deleteNode(struct node* root);
void createQueue(int queueSize);
void pushQueue(int data);
int popQueue();
boolean contains(int data);
void put(int data);
void delete(int data);