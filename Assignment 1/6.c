//assignment 1 question 6

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

//function for printing all the nodes between x and y(x and y inclusive)
void print(int x,int y,node tag)
{
    if(tag!=NULL)
    {
        print(x,y,tag->l);

        if(tag->k>=x && tag->k<=y)
        {
            printf("%d ",tag->k);
        }
        
        print(x,y,tag->r);
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
    
    int x,y;
    scanf("%d",&x);
    scanf("%d",&y);
    
    print(x,y,bt->root);
    
    return 0;
}