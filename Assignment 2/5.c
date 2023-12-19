//avl tree without parent pointers using recursion

//for avl insertion,only 1 rotation is required
//so after 1 rotation is done,when the recursion bottoms up all flags will be in range -1 to 1
//for avl deletion,rotations can go up till the root
//so when recursion bottoms up necessary rotations will be done 

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
    
    //height of new node is always zero
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

//finding height of a node in recursive way
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
        
        //height=1+max(height of left subtree,height of right subtree)
        return 1+x;
    }
}

//finding the balance factor of a node
int balance(avl tag)
{
    if(tag==NULL)
    {
        return 0;
    }
    
    else
    {
        //balance factor=height of left subtree-height of right subtree
        return height(tag->l)-height(tag->r);
    }
}

//printing the parenthesis representation of avl tree
//be careful,where spaces are given
void print(avl tag)
{
    printf("( ");
    
    if(tag!=NULL)
    {
        printf("%d ",tag->k);
        print(tag->l);
        print(tag->r);
    }
    
    printf(") ");
}

//right rotating the node z whose left child is y
//construct a avl tree for better understanding
avl rightrotate(avl z)
{
    avl y,temp;
    
    y=z->l;
    temp=y->r;
    
    //rotation process
    y->r=z;
    z->l=temp;
    
    //modified heights of y and z
    z->h=height(z);
    y->h=height(y);
    
    return y;
}

//left rotating the node z whose right child is y
//construct a avl tree for better understanding
avl leftrotate(avl z)
{
    avl y,temp;
    
    y=z->r;
    temp=y->l;
    
    //rotation process
    y->l=z;
    z->r=temp;
    
    //modified heights of y and z
    z->h=height(z);
    y->h=height(y);
    
    return y;
}

//recursive insertion process for avl tree(without using parent pointer)
avl insert(avl tag,avl new)
{
    int flag1,flag2;
    
    //searching the right position for insertion
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
    
    //updating height and finding balance factor
    tag->h=height(tag);
    flag1=balance(tag);
    
    //flag1>1 implies we got imbalance due to greater height of left subtree
    if(flag1>1)
    {
        //finding balance factor of left subtree
        flag2=balance(tag->l);
        
        //flag2>=0 implies we got LL imbalance
        //flag2=0 can be anything LL or LR but LL is more convienent
        if(flag2>=0)
        {
            tag=rightrotate(tag);
        }
        
        //when flag2<0 we get LR imbalance
        else
        {
            tag->l=leftrotate(tag->l);
            tag=rightrotate(tag);
        }
    }
    
    //flag1<-1 implies we got imbalance due to greater height of right subtree
    if(flag1<-1)
    {
        //finding balance factor of right subtree
        flag2=balance(tag->r);

        //flag2<=0 implies we got RR imbalance
        //flag2=0 can be anything RR or Rl but RR is more convienent
        if(flag2<=0)
        {
            tag=leftrotate(tag);
        }
        
        //when flag2>0 we get RL imbalance        
        else
        {
            tag->r=rightrotate(tag->r);
            tag=leftrotate(tag);
        }
    }
    
    return tag;
}

//search for avl same as search for bst
avl search(avl tag,int key)
{
    while(tag!=NULL && key!=tag->k)
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

//recursive deletion process for avl tree(without using parent pointer)
avl delete(avl tag,int key)
{
    int flag1,flag2;
    avl temp;
    
    //searching the node for deletion
    if(tag==NULL)
    {
        return tag;
    }
    
    if(key<tag->k)
    {
        tag->l=delete(tag->l,key);
    }
    
    else if(key>tag->k)
    {
        tag->r=delete(tag->r,key);
    }
    
    //when node to be deleted is found
    //a bit different deletion technique than what I used to do previously
    //as there are no parent pointers,the need of transplant will also be eliminated
    else
    {
        //be careful,tag=tag->r is a completly wrong way of doing it
        //what I do here is replace tag by tag->r
        if(tag->l==NULL)
        {
            temp=tag->r;
            tag=temp;
        }
        
        //be careful,tag=tag->l is a completly wrong way of doing it
        //what I do here is replace tag by tag->l
        else if(tag->r==NULL)
        {
            temp=tag->l;
            tag=temp;
        }
        
        //we use predecessor instead of successor here
        //it does not have any significance(but question told it to do that way)
        else
        {
            temp=tag->l;
            
            while(temp->r!=NULL)
            {
                temp=temp->r;
            }
            
            //value of predecessor of tag->l is given to tag
            //then predecessor of tag->l is deleted
            tag->k=temp->k;
            tag->l=delete(tag->l,temp->k);
        }
    }
    
    //if after deletion tag becomes NULL,just return
    if(tag==NULL)
    {
        return tag;
    }
    
    //updating height and finding balance factor
    tag->h=height(tag);
    flag1=balance(tag);
    
    //flag1>1 implies we got imbalance due to greater height of left subtree
    if(flag1>1)
    {
        //finding balance factor of left subtree
        flag2=balance(tag->l);
        
        //flag2>=0 implies we got LL imbalance
        //flag2=0 can be anything LL or LR but LL is more convienent
        if(flag2>=0)
        {
            tag=rightrotate(tag);
        }
        
        //when flag2<0 we get LR imbalance
        else
        {
            tag->l=leftrotate(tag->l);
            tag=rightrotate(tag);
        }
    }
    
    //flag1<-1 implies we got imbalance due to greater height of right subtree
    if(flag1<-1)
    {
        //finding balance factor of right subtree
        flag2=balance(tag->r);
        
        //flag2<=0 implies we got RR imbalance
        //flag2=0 can be anything RR or RL but RR is more convienent
        if(flag2<=0)
        {
            tag=leftrotate(tag);
        }
        
        //when flag2>0 we get RL imbalance
        else
        {
            tag->r=rightrotate(tag->r);
            tag=leftrotate(tag);
        }
    }
    
    return tag;
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
            
            case 'd':
            scanf("%d",&key);
            tag=search(root,key);
            if(tag==NULL)
            {
                printf("FALSE\n");
            }
            else
            {
                printf("%d\n",key);
                root=delete(root,key);
            }
            break;
            
            case 's':
            scanf("%d",&key);
            tag=search(root,key);
            if(tag==NULL)
            {
                printf("FALSE\n");
            }
            else
            {
                printf("TRUE\n");
            }
            break;
            
            case 'b':
            scanf("%d",&key);
            tag=search(root,key);
            if(tag==NULL)
            {
                printf("FALSE\n");
            }
            else
            {
                printf("%d\n",balance(tag));
            }
            break;
            
            case 'p':
            print(root);
            printf("\n");
            break;
            
            case 'e':
            return 0;
        }
    }

    return 0;
}