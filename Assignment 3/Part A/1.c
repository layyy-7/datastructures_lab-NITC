//red black tree insertion with recursive approach(no parent pointers)
//can also be done with iterative approach(using parent pointers)

#include <stdio.h>
#include <stdlib.h>

struct element
{
    int k;
    char color;
    struct element *l;
    struct element *r;
};

typedef struct element *rbt;
rbt root=NULL;

rbt create(int key)
{
    rbt new;
    new=(rbt ) malloc(sizeof(struct element));
    
    //during insertion process in rbt,initially a node is always coloured to red 
    new->color='R';
    new->k=key;
    new->l=NULL;
    new->r=NULL;
    
    return new;
}

//right rotation of the node z whose left child is y
rbt rightrotate(rbt z)
{
    rbt y,temp;
    
    y=z->l;
    temp=y->r;
    
    y->r=z;
    z->l=temp;
    
    return y;
}

//left rotation of the node z whose right child is y
rbt leftrotate(rbt z)
{
    rbt y,temp;
    
    y=z->r;
    temp=y->l;
    
    y->l=z;
    z->r=temp;
    
    return y;
}

//insertion process starts with normal bst insertion(recursive approach)
rbt insert(rbt tag,rbt new)
{
    if(tag==NULL)
    {
        return new;
    }
    
    else if(new->k<tag->k)
    {
        tag->l=insert(tag->l,new);
    }
    
    else
    {
        tag->r=insert(tag->r,new);
    }
    
    //case 1
    //parent is red,uncle is red
    //recolouring of parent and uncle to black and recolouring grandparent to red 
    if(tag->l!=NULL && tag->l->color=='R' && tag->r!=NULL && tag->r->color=='R')
    {
        if((tag->l->l!=NULL && tag->l->l->color=='R') || (tag->l->r!=NULL && tag->l->r->color=='R'))
        {
            tag->l->color='B';
            tag->r->color='B';
            tag->color='R';
        }
        
        else if((tag->r->l!=NULL && tag->r->l->color=='R') || (tag->r->r!=NULL && tag->r->r->color=='R'))
        {
            tag->l->color='B';
            tag->r->color='B';
            tag->color='R';
        }
    }
    
    //case 2
    //parent is red,uncle is either black or not present
    //right rotation at grandparent and recolouring grandparent to red
    else if(tag->l!=NULL && tag->l->color=='R')
    {
        //LL case
        //recoluring parent to black
        if(tag->l->l!=NULL && tag->l->l->color=='R')
        {
            tag->color='R';
            tag->l->color='B';
            tag=rightrotate(tag);
        }
        
        //LR case
        //recolouring the given node(the newly inserted node) to black
        else if(tag->l->r!=NULL && tag->l->r->color=='R')
        {
            tag->color='R';
            tag->l->r->color='B';
            tag->l=leftrotate(tag->l);
            tag=rightrotate(tag);            
        }
    }
    
    //case 3
    //parent is red,uncle is either black or not present
    //left rotation at grandparent and recolouring grandparent to red
    else if(tag->r!=NULL && tag->r->color=='R')
    {
        //RR case
        //recoluring parent to black
        if(tag->r->r!=NULL && tag->r->r->color=='R')
        {
            tag->color='R';
            tag->r->color='B';
            tag=leftrotate(tag);
        }
        
        //RL case
        //recolouring the given node(the newly inserted node) to black
        else if(tag->r->l!=NULL && tag->r->l->color=='R')
        {
            tag->color='R';
            tag->r->l->color='B';
            tag->r=rightrotate(tag->r);
            tag=leftrotate(tag);            
        }
    }
    
    return tag;
}

void print(rbt tag)
{
    printf("( ");
    if(tag!=NULL)
    {
        printf("%d ",tag->k);
        printf("%c ",tag->color);
        print(tag->l);
        print(tag->r);        
    }
    printf(") ");
}

int main()
{
    int key,i;
    rbt new;
    char s[100];
    
    while(1)
    {
        scanf(" %s",s);
        
        if(s[0]=='t')
        {
            return 0;
        }
        
        i=0;
        key=0;
        while(s[i]!='\0')
        {
           key=key*10+s[i]-'0';
           i++;
        }
        
        //point to be noted,root is coloured black
        //for cases when colour of root is changed due to the insertion process
        new=create(key);
        root=insert(root,new);
        root->color='B';
        
        print(root);
        printf("\n");
    }
}