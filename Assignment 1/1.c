//assignment 1 question 1

#include <stdio.h>
#include <stdlib.h>

struct element1
{
    int k;
    struct element1 *l;
    struct element1 *r;
};
typedef struct element1 *node;
node z;

struct element2
{
    node root;
};
typedef struct element2 *binarytree;

node create(int num)
{
    node new;
    new=(node) malloc(sizeof(struct element1));
    
    new->k=num;
    new->l=NULL;
    new->r=NULL;
    
    return new;
}

node build(char *s)
{
    int num,temp;
    
    num=0;
    s=s+2;
    
    if(*s==')')
    {
        return NULL;
    }

    while(*s<='9' && *s>='0')
    {
        num=num*10+*s-'0';
        s++;
    }
    
    node tag;
    tag=create(num);
    
    s++;
    tag->l=build(s);
    
    s++;
    temp=1;
    
    while(temp!=0)
    {
        if(*s=='(')
        {
            temp++;
        }
        
        if(*s==')')
        {
            temp--;
        }
        
        s++;
    }
    
    s++;
    tag->r=build(s);
    
    return tag;
}

//searching for a node in a binary tree(not necessarily a binary search tree)
void search(node tag,int x)
{
    if(tag!=NULL)
    {
        if(tag->k==x)
        {
            z=tag;
            return;
        }
        
        search(tag->l,x);
        search(tag->r,x);
    }
}

//printing all the descendants at distance k from the target node
void descendant(node tag,int key)
{
    if(tag==NULL || key<0)
    {
        return;
    }
    
    if(key==0)
    {
        printf("%d ",tag->k);
        return;
    }
    
    descendant(tag->l,key-1);
    descendant(tag->r,key-1);
}

int main()
{
    char *s;
    s=(char *)malloc(1000000*sizeof(char));
    scanf(" %[^\n]",s);
    
    int x,key;
    scanf("%d",&x);
    scanf("%d",&key);
    
    binarytree bt;
    bt=(binarytree)malloc(sizeof(struct element2));
    bt->root=build(s);
    
    search(bt->root,x);
    descendant(z,key);
    
    return 0;
}