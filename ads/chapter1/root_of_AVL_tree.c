#include <stdio.h>
#include <stdlib.h>
typedef struct avl_node *avl_ptr;
typedef struct avl_node node;
struct avl_node
{
    avl_ptr left;
    avl_ptr right;
    int height;
    int element;
};
typedef avl_ptr avl_tree;

avl_ptr insert(avl_ptr T, int X);
avl_ptr singlerotatewithleft(avl_ptr T);
avl_ptr singlerotatewithright(avl_ptr T);
avl_ptr doublerotatewithleft(avl_ptr T);
avl_ptr doublerotatewithright(avl_ptr T);
int Getheight(avl_ptr T);
int max(int a, int b);

void main()
{
    int n, X, i;
    scanf("%d", &n);
    avl_tree T = NULL;
    for (i = 0; i < n; i++)
    {
        scanf("%d", &X);
        T = insert(T, X);
    }
    printf("%d", T->element);
}

avl_ptr insert(avl_ptr T, int X)
{
    if (T == NULL)
    {
        T = (avl_ptr)malloc(sizeof(node));
        T->element = X;
        T->left = T->right = 0;
        T->height = 0;
    }
    else if (X < T->element)
    {
        T->left = insert(T->left, X);
        if (Getheight(T->left) - Getheight(T->right) > 1)
        {
            if (X < T->left->element)
            {
                T = singlerotatewithleft(T);
            }
            else
            {
                T = doublerotatewithleft(T);
            }
        }
    }
    else
    {
        T->right = insert(T->right, X);
        if (Getheight(T->right) - Getheight(T->left) > 1)
        {
            if (X > T->right->element)
            {
                T = singlerotatewithright(T);
            }
            else
            {
                T = doublerotatewithright(T);
            }
        }
    }
    T->height = max(Getheight(T->left), Getheight(T->right)) + 1;
    return T;
}

avl_ptr singlerotatewithleft(avl_ptr T)
{
    avl_ptr temp = T->left;
    T->left = temp->right;
    temp->right = T;
    T->height = max(Getheight(T->left), Getheight(T->right)) + 1;
    temp->height = max(Getheight(temp->left), Getheight(temp->right)) + 1;
    return temp;
}

avl_ptr singlerotatewithright(avl_ptr T)
{
    avl_ptr temp = T->right;
    T->right = temp->left;
    temp->left = T;

    T->height = max(Getheight(T->left), Getheight(T->right)) + 1;
    temp->height = max(Getheight(temp->left), Getheight(temp->right)) + 1;
    return temp;
}

avl_ptr doublerotatewithleft(avl_ptr T)
{
    T->left = singlerotatewithright(T->left);
    T = singlerotatewithleft(T);
    return T;
}

avl_ptr doublerotatewithright(avl_ptr T)
{
    T->right = singlerotatewithleft(T->right);
    T = singlerotatewithright(T);
    return T;
}

int max(int a, int b)
{
    if (a > b)
    {
        return a;
    }
    else
    {
        return b;
    }
}

int Getheight(avl_ptr T)
{
    if (T == NULL)
    {
        return -1;
    }
    else
    {
        return T->height;
    }
}