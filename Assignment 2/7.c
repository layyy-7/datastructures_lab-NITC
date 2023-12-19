#include <stdio.h>
#include <stdlib.h>

struct element
{
    int k;
    int h;
    struct element *l;
    struct element *r;
};

typedef struct element *avl;
avl root=NULL;

avl create(int key)
{
    avl new;
    new=(avl ) malloc(sizeof(struct element));
    
    new->k=key;
    new->h=0;
    new->l=NULL;
    new->r=NULL;
    
    return new;
}

int max(int a,int b)
{
    if(a>b)
    {
        return a;
    }
    
    else
    {
        return b;
    }
}

int height(avl tag)
{
    int a,b,x;
    
    if(tag==NULL)
    {
        return -1;
    }
    
    else
    {
        a=height(tag->l);
        b=height(tag->r);
        x=max(a,b);
        
        return 1+x;
    }
}

int balance(avl tag)
{
    if(tag==NULL)
    {
        return 0;
    }
    
    else
    {
        return height(tag->l)-height(tag->r);
    }
}

avl rightrotate(avl z)
{
    avl y,temp;
    
    y=z->l;
    temp=y->r;
    
    y->r=z;
    z->l=temp;
    
    z->h=height(z);
    y->h=height(y);
    
    return y;
}

avl leftrotate(avl z)
{
    avl y,temp;
    
    y=z->r;
    temp=y->l;
    
    y->l=z;
    z->r=temp;
    
    z->h=height(z);
    y->h=height(y);
    
    return y;
}

avl insert(avl tag,avl new)
{
    int flag1,flag2;
    
    if(tag==NULL)
    {
        return new;
    }
    
    if(new->k<tag->k)
    {
        tag->l=insert(tag->l,new);
    }
    
    else
    {
        tag->r=insert(tag->r,new);
    }
    
    tag->h=height(tag);
    flag1=balance(tag);
    
    if(flag1>1)
    {
        flag2=balance(tag->l);
        
        if(flag2>=0)
        {
            tag=rightrotate(tag);
        }
        
        else
        {
            tag->l=leftrotate(tag->l);
            tag=rightrotate(tag);
        }
    }
    
    if(flag1<-1)
    {
        flag2=balance(tag->r);

        if(flag2<=0)
        {
            tag=leftrotate(tag);
        }
        
        else
        {
            tag->r=rightrotate(tag->r);
            tag=leftrotate(tag);
        }
    }
    
    return tag;
}

int ct;

//counting all elements greater than given key
void count(avl tag,int key)
{
    if(tag!=NULL)
    {
        count(tag->l,key);
        if(tag->k>key)
        {
            ct++;
        }
        count(tag->r,key);
    }
}

//printing all elements greater than given key
void print(avl tag,int key)
{
    if(tag!=NULL)
    {
        print(tag->l,key);
        if(tag->k>key)
        {
            printf("%d ",tag->k);
        }
        print(tag->r,key);
    }
}

int main()
{
    char c;
    int key;
    avl new,tag;
    
    while(1)
    {
        scanf("%c",&c);
        
        switch(c)
        {
            case 'i':
            scanf("%d",&key);
            new=create(key);
            root=insert(root,new);
            break;
            
            case 'c':
            scanf("%d",&key);
            ct=0;
            count(root,key);
            printf("%d\n",ct);
            print(root,key);
            printf("\n");
            break;
            
            case 'e':
            return 0;
        }
    }

    return 0;
}