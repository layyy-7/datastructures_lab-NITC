//assignment 1 question 5

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
    
    if(tag->r!=NULL)
    {
        tag->r->p=tag;
    }
    
    return tag;
}

//max keeps the maximum sum
//min keeps the minimum index(for the case when sum is equal)
//array a stores the current sequence
//array b stores the sequence when the sum is max and sequence is smallest
int max,min;
char a[1000],b[1000];

//for finding the sum
//also keeps track of the series of nodes followed from leaf to root
void sum(node tag)
{
    int i,s;
    
    i=0;
    s=tag->k;
    
    while(tag->p!=NULL)
    {
        if(tag==tag->p->l)
        {
            a[i]='L';
            i++;
        }
        
        else
        {
            a[i]='R';
            i++;
        }
        
        s+=tag->p->k;
        tag=tag->p;
    }
    
    if(s>max)
    {
        strcpy(b,a);
        max=s;
        min=i;
    }
    
    //for the case when sum is equal but series of nodes is smaller than what was earlier
    if(s==max && i<min)
    {
        strcpy(b,a);
        min=i;
    }
}

//to check whether a given node is a leaf node or not
//if yes,call the sum function
void check(node tag)
{
    if(tag->l==NULL && tag->r==NULL)
    {
        sum(tag);
    }
}

//to pass every node to the check function
void print(node tag)
{
    if(tag!=NULL)
    {
        print(tag->l);
        check(tag);
        print(tag->r);
    }
}

int main()
{
    char *s;
    s=(char *)malloc(1000000*sizeof(char));
    scanf(" %[^\n]",s);
    
    binarytree bt;
    bt=(binarytree)malloc(sizeof(struct element2));
    bt->root=build(s);
    
    int i;
    print(bt->root);
    
    //printing in the reverse order
    //as we need the series of nodes from root to leaf
    for(i=min-1;i>=0;i--)
    {
        printf("%c",b[i]);
    }
    
    //if only root is present print the sum without any space
    if(min==0)
    {
        printf("%d",max);
    }
    
    else
    {
        printf(" %d",max);
    }
    
    return 0;
}   