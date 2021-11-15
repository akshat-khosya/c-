#include <stdio.h> 
#include <stdlib.h>
  struct node
  {
    int info;
    struct node * lchild;
    struct node * rchild;
  }*root;

void find(int item, struct node **par, struct node **loc)
{
  struct node *ptr, *ptrsave;
 
  if (root == NULL)
  {
    *loc = NULL;
    *par = NULL;
    return;
  }
 
  if (item == root->info)
  {
    *loc = root;
    *par = NULL;
    return;
  }
 
  if (item < root->info)
    ptr = root->lchild;
  else
    ptr = root->rchild;
  ptrsave = root;
 
  while (ptr != NULL)
  {
    if (item == ptr->info)
    {*loc = ptr;
      *par = ptrsave;
      return;
    }
 
    ptrsave = ptr;
    if (item < ptr->info)
      ptr = ptr->lchild;
    else
      ptr = ptr->rchild;
  }
 
  *loc = NULL;
  *par = ptrsave;
}
 
void insert(int item)
{
  struct node *tmp, *parent, *location;
  find(item, &parent, &location);
  if (location != NULL)
  {
    printf("Item already present");
    return;
  }
 
  tmp = (struct node *) malloc(sizeof(struct node));
  tmp->info = item;
  tmp->lchild = NULL;
  tmp->rchild = NULL;
 
  if (parent == NULL)
    root = tmp;
  else
  if (item < parent->info)
    parent->lchild = tmp;
  else
    parent->rchild = tmp;
}
 
void case_a(struct node *par, struct node *loc) // leaf node
{
  if (par == NULL)
    root = NULL;
  else
  if (loc == par->lchild)
    par->lchild = NULL;
  else
    par->rchild = NULL;
}
 
void case_b(struct node *par, struct node *loc)
{
  struct node * child;
 
 //intializing child
  if (loc->lchild != NULL)
    child = loc->lchild;
  else
    child = loc->rchild;
 
  if (par == NULL)
    root = child;
  else
  if (loc == par->lchild)
    par->lchild = child;
  else
    par->rchild = child;
}
 
void case_c(struct node *par, struct node *loc)
{
  struct node *ptr, *ptrsave, *suc, *parsuc;
 
  ptrsave = loc;
  ptr = loc->rchild;
  while (ptr->lchild != NULL)
  {
    ptrsave = ptr;
    ptr = ptr->lchild;
  }
 
  suc = ptr;
  parsuc = ptrsave;
 
  if (suc->lchild == NULL && suc->rchild == NULL)
    case_a(parsuc, suc);
  else
    case_b(parsuc, suc);
 
  if (par == NULL)
    root = suc;
  else
  if (loc == par->lchild)
    par->lchild = suc;
  else
    par->rchild = suc;
 
  suc->lchild = loc->lchild;
  suc->rchild = loc->rchild;
}
 
int del(int item)
{
  struct node *parent, *location;
  if (root == NULL)
  {
    printf("Tree empty");
    return 0;
  }
 
  find(item, &parent, &location);
  if (location == NULL)
  {
    printf("Item not present in tree");
    return 0;
  }
 
  if (location->lchild == NULL && location->rchild == NULL)
    case_a(parent, location);
  if (location->lchild != NULL && location->rchild == NULL)
    case_b(parent, location);
  if (location->lchild == NULL && location->rchild != NULL)
    case_b(parent, location);
  if (location->lchild != NULL && location->rchild != NULL)
    case_c(parent, location);
  free(location);
}
 
int traversal(struct node *ptr)
{
  if (root == NULL)
  {
    printf("Tree is empty");
    return 0;
  } 
  if (ptr != NULL)
  {
    printf("%d  ", ptr->info);
    traversal(ptr->lchild);
    traversal(ptr->rchild);
  } 
}
int search(struct node *ptr, int n)
{
    if(ptr == NULL)
    return 0;
    else if(n==ptr->info)
    return 1;
    else
    {
        if(n<=ptr->info)
            return search(ptr->lchild, n);
        else
            return search(ptr->rchild, n);
    }
}
void display(struct node *ptr, int level)
{
  int i;
  if (ptr != NULL)
  {
    display(ptr->rchild, level + 1);
    printf("\n");
    for (i = 0; i < level; i++)
      printf("    ");
    printf("%d", ptr->info);
    display(ptr->lchild, level + 1);
  }
}

int main()
{
  int choice, num;
  root = NULL;
  while (1)
  {
    printf("\n");
    printf("1.Insert\n");
    printf("2.Traversal\n");
    printf("3.Display\n");
    printf("4.Search\n");
    printf("5.Delete\n");
    printf("6.Quit\n");
    printf("\nEnter your choice : ");
    scanf("%d", &choice);
 
    switch (choice)
    {
      case 1:
        printf("Enter the number to be inserted : ");
        scanf("%d", &num);
        insert(num);
        break;
      case 2:
        printf("\n");
        traversal(root);
        printf("\n");
        break;
      case 3:
        display(root, 1);
        break;
      case 4:
        printf("Enter element to search: ");
        int el;
        scanf("%d", &el);
        int f=search(root, el);
        if(f==1)
        printf("Element Found\n");
        else
        printf("Element not found\n");
        break;
      case 5:
        printf("Enter the number to be deleted : ");
        scanf("%d", &num);
        del(num);
        break;
      case 6:
      printf("\nProgram ended successfully.");
      printf("\n\n");
      exit(1);
        break;
      default:
        printf("Wrong choice\n");
    }
  }
  return 0;
}