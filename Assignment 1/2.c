//assignment 1 question 2

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
    
    while(*s<='9' && *s>='0')
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

int count;

//function to count the number of nodes whose grandparent has a child as a leaf node
void print(node tag)
{
    if(tag!=NULL)
    {
        //checking whether the node has a grandparent
        if(tag->p!=NULL && tag->p->p!=NULL)
        {
            //if it has a grandparent,
            //and if grandparent's left or right child is not NULL
            //checking whether its grandparent's left or right child is a leaf or not
            if((tag->p->p->l!=NULL && tag->p->p->l->l==NULL && tag->p->p->l->r==NULL) || (tag->p->p->r!=NULL && tag->p->p->r->l==NULL && tag->p->p->r->r==NULL))
            {
                count++;
            }
        }
        
        print(tag->l);
        print(tag->r);
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
    
    print(bt->root);
    printf("%d",count);
    
    return 0;
}