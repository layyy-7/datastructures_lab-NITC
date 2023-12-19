//assignment 1 question 3

#include <stdio.h>
#include <stdlib.h>

struct element1
{
    int k;
    struct element1 *l;
    struct element1 *r;
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

int sum,count,x;

//for counting the sum of a subtree rooted at the target node
void check(node tag)
{
    if(tag!=NULL)
    {
        x+=tag->k;
        check(tag->l);
        check(tag->r);
    }
}

//function for passing every single node to check function
//also,x(subtree sum) is initialized here to zero everytime before it goes to the check function
void print(node tag)
{
    if(tag!=NULL)
    {
        x=0;
        check(tag);
        
        if(x==sum)
        {
            count++;
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
    
    scanf("%d",&sum);
    print(bt->root);
    printf("%d",count);
    
    return 0;
}