Node *createNode(int key)
{
  Node *node = (Node *)malloc(sizeof(Node));
  if (!*node)
    return NULL;
  (*node)->left = NULL;
  (*node)->right = NULL;
  (*node)->key = key;

  return node;
}

void insertNode(Node **node, int key)
{
  if (!*node)
  {
    *node = createNode(key);
    return;
  }

  if (key < ((*node)->key))
    insertNode(&((*node)->left), key);
  else
    insertNode(&((*node)->right), key);
}