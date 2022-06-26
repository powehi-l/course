#include <stdio.h>
#include <stdlib.h>
#define m 3
#define typekey int
#define min -100000
typedef struct BplusNode *Btree, *Bnode;

struct BplusNode
{
    int keynum;
    typekey key[m + 1];
    Bnode children[m + 1];
    Bnode next;
};

Btree Initial()
{
    int i = 0;
    Btree T = (Btree)malloc(sizeof(struct BplusNode));
    while (i < m + 1)
    {
        T->key[i] = min;
        T->children[i] = NULL;
        i++;
    }
    T->keynum = 0;
    T->next = NULL;
    return T;
}

Btree insertelement(int iskey, Btree parent, typekey x, Btree T, int i, int j)
{
    int k;
    if (iskey)
    {
        k = T->keynum - 1;
        while (k >= j)
        {
            T->key[k + 1] = T->key[k];
            k--;
        }
        T->key[j] = x;
        if (parent != NULL)
        {
            parent->key[i] = T->key[0];
        }
        T->keynum++;
    }
    else
    {
        k = parent->keynum - 1;
        while (k >= i)
        {
            parent->children[k + 1] = parent->children[k];
            parent->key[k + 1] = parent->key[k];
            k--;
        }
        parent->key[i] = T->key[0];
        parent->children[i] = T;
        parent->keynum++;
    }
    return T;
}

Btree findsibling(Btree parent, int i)
{
    Bnode sibling = NULL;
    if (i == 0)
    {
        if (parent->children[1]->keynum < m - 1)
            sibling = parent->children[1];
    }
    else if (parent->children[i - 1]->keynum < m - 1)
        sibling = parent->children[i - 1];
    else if (parent->keynum > i + 1 && parent->children[i + 1]->keynum < m - 1)
        sibling = parent->children[i + 1];
    return sibling;
}

Btree splitNode(Btree parent, Btree T, int i)
{

    int j, k, Limit;
    Bnode NewNode = Initial();

    k = 0;
    j = T->keynum / 2;
    Limit = T->keynum;
    while (j < Limit)
    {
        if (T->children[0] != NULL)
        {
            NewNode->children[k] = T->children[j];
            T->children[j] = NULL;
        }
        NewNode->key[k] = T->key[j];
        T->key[j] = min;
        NewNode->keynum++;
        T->keynum--;
        j++;
        k++;
    }

    if (parent != NULL)
    {
        insertelement(0, parent, min, NewNode, i + 1, min);
    }
    else
    {
        parent = Initial();
        insertelement(0, parent, min, T, 0, min);
        insertelement(0, parent, min, NewNode, 1, min);
        return parent;
    }
    return T;
}

void Moveelement(Btree start, Btree des, Btree parent, int i)
{
    int startinfron;
    if (start->key[0] < des->key[0])
    {
        startinfron = 1;
    }
    else
    {
        startinfron = 0;
    }

    if (startinfron)
    {
        insertelement(1, parent, start->key[start->keynum - 1], des, i + 1, 0);
    }
    else
    {
        insertelement(1, parent, start->key[0], des, i - 1, des->key[des->keynum]);
    }
    start->keynum--;
}

Btree insert(Btree T, typekey x, int i, Bnode parent)
{
    int j = 0;
    Bnode sibling;

    while (j < T->keynum && x >= T->key[j])
    {
        if (x == T->key[j])
        {
            printf("Key %d is duplicated\n", x);
            return T;
        }
        j++;
    }
    if (j != 0 && T->children[0] != NULL)
        j--;

    if (T->children[0] == NULL)
        T = insertelement(1, parent, x, T, i, j);
    else
        T->children[j] = insert(T->children[j], x, j, T);

    if (T->keynum > m)
    {
        if (parent == NULL)
        {
            T = splitNode(parent, T, i);
        }
        else
        {
            sibling = findsibling(parent, i);
            if (sibling != NULL)
            {
                Moveelement(T, sibling, parent, i);
            }
            else
            {
                T = splitNode(parent, T, i);
            }
        }
    }
    if (T->keynum > m)
    {
        splitNode(parent, T, i);
    }

    if (parent != NULL)
    {
        parent->key[i] = T->key[0];
    }
    return T;
}

void pri(Btree T)
{
    printf("[");
    int i;
    if (T->children[0] == NULL)
        i = 0;
    else
        i = 1;
    while (i <= T->keynum - 1)
    {
        if (i == T->keynum - 1)
            printf("%d]", T->key[i]);
        else
            printf("%d,", T->key[i]);
        i++;
    }
}

void printtree(Btree T)
{
    Btree num[10000];
    int end[10000], max[10000];
    int in = 0, out = 0, k;
    num[in] = T;
    end[in] = 1;
    max[in++] = 1;
    while (in > out)
    {
        pri(num[out]);
        if (end[out] == 1)
            printf("\n");
        k = 0;
        if (num[out]->children[0] != NULL)
        {
            while (k <= num[out]->keynum - 1)
            {
                num[in] = num[out]->children[k];
                if (k == num[out]->keynum - 1 && max[out] == 1)
                {
                    end[in++] = 1;
                }
                else
                {
                    end[in++] = 0;
                }
                k++;
            }
        }
        out++;
    }
}

int main()
{
    int i, n, x;
    scanf("%d", &n);
    Btree T = Initial();
    for (i = 0; i < n; i++)
    {
        scanf("%d", &x);
        T = insert(T, x, 0, NULL);
    }
    printtree(T);
}