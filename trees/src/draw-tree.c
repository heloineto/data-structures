#include "avl-node-def.c"

int _printTree(Node *tree, int isLeft, int offset, int depth, char s[20][255])
{
  char b[20];
  int width = 5;

  if (!tree)
    return 0;

  sprintf(b, "(%03d)", tree->key);

  int left = _printTree(tree->left, 1, offset, depth + 1, s);
  int right = _printTree(tree->right, 0, offset + left + width, depth + 1, s);

  for (int i = 0; i < width; i++)
    s[2 * depth][offset + left + i] = b[i];

  if (depth && isLeft)
  {

    for (int i = 0; i < width + right; i++)
      s[2 * depth - 1][offset + left + width / 2 + i] = '-';

    s[2 * depth - 1][offset + left + width / 2] = '+';
    s[2 * depth - 1][offset + left + width + right + width / 2] = '+';
  }
  else if (depth && !isLeft)
  {

    for (int i = 0; i < left + width; i++)
      s[2 * depth - 1][offset - width / 2 + i] = '-';

    s[2 * depth - 1][offset + left + width / 2] = '+';
    s[2 * depth - 1][offset - width / 2 - 1] = '+';
  }

  return left + width + right;
}

void drawTree(Node *tree)
{
  char s[20][255];
  for (int i = 0; i < 20; i++)
    sprintf(s[i], "%80s", " ");

  _printTree(tree, 0, 0, 0, s);

  for (int i = 0; i < 20; i++)
    printf("%s\n", s[i]);
}