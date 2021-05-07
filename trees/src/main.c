#include <stdio.h>
#include <stdlib.h>

#include "avl-node-def.c"
#include "draw-tree.c"

int getNodeHeight(struct Node *N)
{
  if (N == NULL)
    return 0;
  return N->height;
}

int maxInt(int a, int b)
{
  return (a > b) ? a : b;
}

struct Node *newNode(int key)
{
  struct Node *node = (struct Node *)
      malloc(sizeof(struct Node));
  node->key = key;
  node->left = NULL;
  node->right = NULL;
  node->height = 1; // new node is initially added at leaf
  return (node);
}

struct Node *rightRotate(struct Node *y)
{
  struct Node *x = y->left;
  struct Node *T2 = x->right;

  // Perform rotation
  x->right = y;
  y->left = T2;

  // Update heights
  y->height = maxInt(getNodeHeight(y->left), getNodeHeight(y->right)) + 1;
  x->height = maxInt(getNodeHeight(x->left), getNodeHeight(x->right)) + 1;

  // Return new root
  return x;
}

// A utility function to left rotate subtree rooted with x
// See the diagram given above.
struct Node *leftRotate(struct Node *x)
{
  struct Node *y = x->right;
  struct Node *T2 = y->left;

  // Perform rotation
  y->left = x;
  x->right = T2;

  //  Update heights
  x->height = maxInt(getNodeHeight(x->left), getNodeHeight(x->right)) + 1;
  y->height = maxInt(getNodeHeight(y->left), getNodeHeight(y->right)) + 1;

  // Return new root
  return y;
}

// Get Balance factor of node N
int getBalance(struct Node *N)
{
  if (N == NULL)
    return 0;
  return getNodeHeight(N->left) - getNodeHeight(N->right);
}

struct Node *insertAvlNode(struct Node *node, int key)
{
  /* 1.  Perform the normal BST insertion */
  if (node == NULL)
    return (newNode(key));

  if (key < node->key)
    node->left = insertAvlNode(node->left, key);
  else if (key > node->key)
    node->right = insertAvlNode(node->right, key);
  else // Equal keys are not allowed in BST
    return node;

  /* 2. Update height of this ancestor node */
  node->height = 1 + maxInt(getNodeHeight(node->left),
                            getNodeHeight(node->right));

  /* 3. Get the balance factor of this ancestor
          node to check whether this node became
          unbalanced */
  int balance = getBalance(node);

  // If this node becomes unbalanced, then
  // there are 4 cases

  // Left Left Case
  if (balance > 1 && key < node->left->key)
    return rightRotate(node);

  // Right Right Case
  if (balance < -1 && key > node->right->key)
    return leftRotate(node);

  // Left Right Case
  if (balance > 1 && key > node->left->key)
  {
    node->left = leftRotate(node->left);
    return rightRotate(node);
  }

  // Right Left Case
  if (balance < -1 && key < node->right->key)
  {
    node->right = rightRotate(node->right);
    return leftRotate(node);
  }

  /* return the (unchanged) node pointer */
  return node;
}

int main()
{
  struct Node *rootAvl = NULL;
  struct Node *rootBst = NULL;

  int keys[] = {10, 20, 30, 40, 50, 25};
  int keysLength = (sizeof(keys) / sizeof(keys[0]));

  for (int i = 0; i < keysLength - 1; i++)
  {
    rootAvl = insertAvlNode(rootAvl, keys[i]);
    rootBst = insertAvlNode(rootBst, keys[i]);
  }

  printf("Árvore AVL:\n");
  drawTree(rootAvl);

  printf("Árvore ABP:\n");

  return 0;
}