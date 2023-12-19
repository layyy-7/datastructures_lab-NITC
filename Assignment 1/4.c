//assignment 1 question 4

#include <stdio.h>
#include <stdlib.h>

struct element
{
    int k;
    struct element *l;
    struct element *r;
    struct element *p;
};

typedef struct element *bst;
bst root=NULL;

bst create(int key)
{
    bst new;
    new=(bst) malloc(sizeof(struct element));
    
    new->k=key;
    new->l=NULL;
    new->r=NULL;
    new->p=NULL;
    
    return new;
}

void insert(bst new)
{
    bst tag1,tag2;
    tag1=root;
    tag2=NULL;
    
    while(tag1!=NULL)
    {
        tag2=tag1;
        
        if(new->k<tag1->k)
        {
            tag1=tag1->l;
        }
        
        else
        {
            tag1=tag1->r;
        }
    }
    
    new->p=tag2;
    
    if(tag2==NULL)
    {
        root=new;
    }
    
    else if(new->k<tag2->k)
    {
        tag2->l=new;
    }
    
    else
    {
        tag2->r=new;
    }
}

bst search(int key)
{
    bst tag;
    tag=root;
    
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

void transplant(bst tag1,bst tag2)
{
    if(tag1->p==NULL)
    {
        root=tag2;
    }
    
    else if(tag1==tag1->p->l)
    {
        tag1->p->l=tag2;
    }
    
    else
    {
        tag1->p->r=tag2;
    }
    
    if(tag2!=NULL)
    {
        tag2->p=tag1->p;
    }
}

void delete(bst tag)
{
    bst tag2;
    
    if(tag->l==NULL)
    {
        transplant(tag,tag->r);
    }
    
    else if(tag->r==NULL)
    {
        transplant(tag,tag->l);
    }
    
    else
    {
        tag2=tag->r;
        
        while(tag2->l!=NULL)
        {
            tag2=tag2->l;
        }
        
        if(tag2->p!=tag)
        {
            transplant(tag2,tag2->r);
            tag2->r=tag->r;
            tag2->r->p=tag2;
        }
        
        transplant(tag,tag2);
        tag2->l=tag->l;
        tag2->l->p=tag2;
    }
}

//root is level 1,its children are level 2 and so on
void level(bst tag)
{
    bst tag2;
    tag2=root;
    
    int count;
    count=1;
    
    while(tag2!=tag)
    {
        if(tag->k<tag2->k)
        {
            tag2=tag2->l;
        }
        
        else
        {
            tag2=tag2->r;
        }
        
        count++;
    }
    
    printf("%d\n",count);
}

void minimum(bst tag)
{
    while(tag->l!=NULL)
    {
        tag=tag->l;
    }
    
    printf("%d\n",tag->k);
}

void maximum(bst tag)
{
    while(tag->r!=NULL)
    {
        tag=tag->r;
    }
    
    printf("%d\n",tag->k);
}

void predecessor(bst tag)
{
    bst tag2;
    
    if(tag->l!=NULL)
    {
        tag2=tag->l;
        
        while(tag2->r!=NULL)
        {
            tag2=tag2->r;
        }
    }
    
    else
    {
        tag2=tag->p;
        
        while(tag2!=NULL && tag==tag2->l)
        {
            tag=tag2;
            tag2=tag2->p;
        }
    }
    
    printf("%d\n",tag2->k);
}

void successor(bst tag)
{
    bst tag2;
    
    if(tag->r!=NULL)
    {
        tag2=tag->r;
        
        while(tag2->l!=NULL)
        {
            tag2=tag2->l;
        }
    }
    
    else
    {
        tag2=tag->p;
        
        while(tag2!=NULL && tag==tag2->r)
        {
            tag=tag2;
            tag2=tag2->p;
        }
    }
    
    printf("%d\n",tag2->k);
}

void inorder(bst tag)
{
    if(tag!=NULL)
    {
        inorder(tag->l);
        printf("%d ",tag->k);
        inorder(tag->r);
    }
}

void preorder(bst tag)
{
    if(tag!=NULL)
    {
        printf("%d ",tag->k);
        preorder(tag->l);
        preorder(tag->r);
    }
}

void postorder(bst tag)
{
    if(tag!=NULL)
    {
        postorder(tag->l);
        postorder(tag->r);
        printf("%d ",tag->k);
    }
}

int main()
{
    int key;
    char c;
    bst new,tag;
    
    while(1)
    {
        scanf("%c",&c);
        
        switch(c)
        {
            case 'a':
            scanf("%d",&key);
            new=create(key);
            insert(new);
            break;
            
            case 'd':
            scanf("%d",&key);
            tag=search(key);
            if(tag==NULL)
            {
                printf("-1\n");
            }
            else
            {
                delete(tag);
            }
            break;
            
            case 's':
            scanf("%d",&key);
            tag=search(key);
            if(tag==NULL)
            {
                printf("-1\n");
            }
            else
            {
                printf("1\n");
            }
            break;
            
            case 'l':
            scanf("%d",&key);
            tag=search(key);
            if(tag==NULL)
            {
                printf("-1\n");
            }
            else
            {
                level(tag);
            }
            break;
            
            case 'm':
            tag=root;
            minimum(tag);
            break;
            
            case 'x':
            tag=root;
            maximum(tag);
            break;
            
            case 'r':
            scanf("%d",&key);
            tag=search(key);
            if(tag==NULL)
            {
                printf("-1\n");
            }
            else
            {
                predecessor(tag);
            }
            break;
            
            case 'u':
            scanf("%d",&key);
            tag=search(key);
            if(tag==NULL)
            {
                printf("-1\n");
            }
            else
            {
                successor(tag);
            }
            break;
            
            case 'i':
            tag=root;
            inorder(tag);
            printf("\n");
            break;
            
            case 'p':
            tag=root;
            preorder(tag);
            printf("\n");
            break;
            
            case 't':
            tag=root;
            postorder(tag);
            printf("\n");
            break;
            
            case 'e':
            return 0;
        }
    }
    
    return 0;
}