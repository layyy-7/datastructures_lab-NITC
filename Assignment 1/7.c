//assignment 1 question 7

#include <stdio.h>
#include <stdlib.h>

struct element1
{
    int k;
    struct element1 *l;
    struct element1 *r;
    struct element1 *p;
};
typedef struct element1 *node;

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
    new->p=NULL;
    
    return new;
}

node build(char *s)
{
    s=s+2;
    
    if(*s==')')
    {
        return NULL;
    }
    
    int num,temp;
    num=0;
    
    while(*s>='0' && *s<='9')
    {
        num=num*10+*s-'0';
        s++;
    }
    
    node tag;
    tag=create(num);
    
    s++;
    tag->l=build(s);

    //checking tag->l is not NULL is imp
    //then assigning tag as the parent of tag->l
    if(tag->l!=NULL)
    {
        tag->l->p=tag;
    }
    
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

    //checking tag->r is not NULL is imp
    //then assigning tag as the parent of tag->r
    if(tag->r!=NULL)
    {
        tag->r->p=tag;
    }
    
    return tag;
}

//function for searching a key in binary search tree
node search(int key,node tag)
{
    while(tag!=NULL && tag->k!=key)
    {
        if(key<tag->k)
        {
            tag=tag->l;
        }
        
        else
        {
            tag=tag->r;
        }
    }
    
    return tag;
}

//printing all ancestors of the target node starting from its parent 
void print(node tag)
{
    while(tag->p!=NULL)
    {
        printf("%d ",tag->p->k);
        tag=tag->p;
    }
}

int main()
{
    char *s;
    s=(char *) malloc(1000000*sizeof(char));
    scanf(" %[^\n]",s);
    
    binarytree bt;
    bt=(binarytree) malloc(sizeof(struct element2));
    bt->root=build(s);
    
    int key;
    scanf("%d",&key);
    
    node tag;
    tag=search(key,bt->root);

    if(tag!=NULL && tag->p!=NULL)
    {
        print(tag);
    }

    else
    {
        printf("-1\n");
    }
    
    return 0;
}