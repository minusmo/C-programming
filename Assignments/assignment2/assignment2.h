typedef int boolean;
struct bst;
struct node;
struct bstQueue;
struct queue;
struct qNode;

boolean isEmpty();
void makeEmpty();
void inOrder(struct node* root);
void preOrder(struct node* root);
void postOrder(struct node* root);
void postOrderDelete(struct node* root);
void deleteNode(struct node* root);

void createBstQueue(int queueSize);
void resetBstQueue();
void pushBstQueue(int data);

void pushQueue(int data);
int popQueue();
void clearQueue();
void printQueue(struct qNode* front);

boolean contains(int data);

struct node* search(struct node* root, int data);
struct node* searchLeafNode(struct node* root, int data);
void addChild(struct node* parent, int data);
struct node* createNode(int data);
struct node* searchParent(struct node* root, int data);

void put(int data);
void delete(int data);
void deleteNode(struct node* parent, int data);
void deleteChild(struct node* parent, struct node* child, int isLeftChild);

struct node* findMaxNodeParent(struct node* root);

boolean isLeafNode(struct node* root);
boolean hasAChild(struct node* root);
boolean hasTwoChildren(struct node* root);