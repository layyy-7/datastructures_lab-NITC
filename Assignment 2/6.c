#include <stdio.h>
#include <stdlib.h>

struct element
{
    int k;
    int h;
    int n;
    struct element *l;
    struct element *r;
};

typedef struct element *avl;
avl root=NULL;

avl create(int key)
{
    avl new;
    new=(avl ) malloc(sizeof(struct element));
    
    //initialization is imp(for the base case,i.e,leaves)
    //or else the leaf nodes wont get the correct height or number as insert function directly returns in that case
    new->k=key;
    new->h=0;
    new->n=1;
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

//counts the total number of elements present at a subtree rooted at a given node
int number(avl tag)
{
    if(tag==NULL)
    {
        return 0;
    }
    
    else
    {
        //number=elements present in left subtree + elements present in right subtree + node itself
        return 1+number(tag->l)+number(tag->r);
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
    
    //this is imp,or else number of nodes at given subtree will be incorrect after rotation
    z->n=number(z);
    y->n=number(y);
    
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
    
    //this is imp,or else number of nodes at given subtree will be incorrect after rotation
    z->n=number(z);
    y->n=number(y);
    
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
    
    //updates the number of elements and height of a subtree rooted at a particular node
    tag->n=number(tag);
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

int count;

//function to calculate median
//keeping track of total number of elements helps us find median easily without using any extra space
//as without that we needed to use an array to store all elements
void median(avl tag,int key)
{
    if(tag!=NULL)
    {
        median(tag->l,key);
        count++;
        if(count==key)
        {
            printf("%d\n",tag->k);
        }
        median(tag->r,key);
    }
}

void print(avl tag)
{
    if(tag!=NULL)
    {
        print(tag->l);
        printf("%d ",tag->k);
        print(tag->r);
    }
}

int main()
{
    char c;
    int key;
    avl new;
    
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
            
            case 'g':
            count=0;
            key=root->n;
            if(key%2==0)
            {
                key=key/2;
            }
            else
            {
                key=(key+1)/2;
            }
            median(root,key);
            break;
            
            case 'p':
            print(root);
            printf("\n");
            break;
            
            case 't':
            return 0;
        }
    }

    return 0;
}