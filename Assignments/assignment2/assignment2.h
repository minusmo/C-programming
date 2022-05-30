typedef int boolean;
struct node;
struct Bst;
struct qNode;
struct Queue;

void test();
void testIsEmpty();
void testContains(int data);
void testInOrder();
void testPreOrder();
void testPostOrder();

void makeEmpty();
void inOrder(struct node* root);
void preOrder(struct node* root);
void postOrder(struct node* root);
void postOrderDelete(struct node* root);
boolean isEmpty();
boolean contains(int data);

struct node* createNode(int data);
struct node* search(struct node* root, int data);
struct node* searchLeafNode(struct node* root, int data);
struct node* searchParent(struct node* root, int data);
void addChild(struct node* parent, int data);

void put(int data);
void delete(int data);
void deleteNode(struct node* parent, int data);
void deleteChild(struct node* parent, struct node* child, boolean isLeftChild);
struct node* findMaxNodeParent(struct node* root);

boolean isLeafNode(struct node* root);
boolean hasAChild(struct node* root);
boolean hasTwoChildren(struct node* root);

struct qNode* createQNode(int data);
void pushQueue(struct Queue* queue, int data);
int popQueue(struct Queue* queue);
void printQueue(struct Queue* queue);