//program for binomial heap
//order of a tree is the maximum degree of a node

//alwyas keep in mind the very imp property of pointers while doing this question
//if some link is changed it will be affected to every variable even if the variable was assigned before the operation

#include <stdio.h>
#include <stdlib.h>

//k-key
//d-degree
//lc-leftmost child
//rs-right sibling
//p-parent
struct element
{
    int k;
    int d;
    struct element *lc;
    struct element *rs;
    struct element *p;
};
typedef struct element *bh;

//function for creating a new node in the heap
bh create(int key)
{
    bh new;
    new=(bh) malloc(sizeof(struct element));
    
    //degree(number of children) of new node is initialized to zero
    new->d=0;
    new->k=key;
    new->lc=NULL;
    new->rs=NULL;
    new->p=NULL;
    
    return new;
}

//function to link two binomial trees of order k-1 to form a binomial tree of order k
//y is the binomial tree whose root has lower value compared to value of root of binomial tree z
bh link(bh y,bh z)
{
    z->p=y;
    z->rs=y->lc;
    y->lc=z;
    y->d++;
    
    return y;
}

//function to merge two heaps(merging root lists of the heaps into a single root list) 
//i.e,merges the root lists according to the order of the binomial trees(increasing order)
bh heapmerge(bh root1,bh root2)
{
    bh root,temp;
    
    if(root1==NULL && root2==NULL)
    {
        return NULL;
    }
    
    if(root1==NULL)
    {
        return root2;
    }
    
    if(root2==NULL)
    {
        return root1;
    }
    
    if(root1->d<root2->d)
    {
        root=root1;
        root1=root1->rs;
    }
    
    else
    {
        root=root2;
        root2=root2->rs;
    }
    
    //getting the head of the merged list and assigning it to temp
    root->rs=NULL;
    temp=root;
    
    while(root1!=NULL && root2!=NULL)
    {
        if(root1->d<root2->d)
        {
            root->rs=root1;
            root1=root1->rs;
        }
        
        else
        {
            root->rs=root2;
            root2=root2->rs;
        }
        
        root=root->rs;
        root->rs=NULL;
    }
    
    while(root1!=NULL)
    {
        root->rs=root1;
        root1=root1->rs;
        root=root->rs;
        root->rs=NULL;
    }
    
    while(root2!=NULL)
    {
        root->rs=root2;
        root2=root2->rs;
        root=root->rs;
        root->rs=NULL;
    }
    
    //returning temp which is the head of the merged root list
    return temp;
}

//function for making union of two heaps
//this function checks whether more than one binomial trees of same order are present or not
//if yes,then it links them into a binomial tree of order one more than their order using link fucntion
bh heapunion(bh root1,bh root2)
{
    bh root,temp,rootprev,rootnext;
    
    root=heapmerge(root1,root2);
    rootprev=NULL;
    
    if(root==NULL || root->rs==NULL)
    {
        return root;
    }
    
    //assigning temp the head of the merged root list
    temp=root;
    
    //rootprev and rootnext help to maintain the root list
    //as when link function is called links of root list may change
    while(root!=NULL && root->rs!=NULL)
    {
        //if two binomial trees of same order are found
        if(root->d==root->rs->d)
        {
            //if three binomial trees of same order are found
            //we skip the first binomial tree and link the other two trees
            if(root->rs->rs!=NULL && root->rs->rs->d==root->d)
            {
                rootprev=root;
                root=root->rs;
            }
            
            else
            {
                if(root->k<root->rs->k)
                {
                    rootnext=root->rs->rs;
                    root=link(root,root->rs);
                    root->rs=rootnext;
                }
                
                else
                {
                    if(rootprev!=NULL)
                    {
                        rootprev->rs=root->rs;
                    }
                    root=link(root->rs,root);
                }
            }
        }
        
        else
        {
            rootprev=root;
            root=root->rs;
        }
    }
    
    //the head node may have become some other nodes child during the call to link function
    //so we need to get to its parent to get head of the root list
    while(temp->p!=NULL)
    {
        temp=temp->p;
    }
    
    //returning temp which is the head of the merged root list
    return temp;
}

//function for printing the root list of the binomial heap
void print(bh root)
{
    while(root!=NULL)
    {
        printf("%d ",root->k);
        root=root->rs;
    }
    printf("\n");
}

//function for finding the minimum element in the binomial heap
void minimum(bh root)
{
    int min;
    min=root->k;
    
    while(root!=NULL)
    {
        if(root->k<min)
        {
            min=root->k;
        }
        
        root=root->rs;
    }
    
    printf("%d\n",min);
}

//recursive function for finding key in a binomial heap
//using the condition temp==NULL is very imp
bh find(bh root,int key)
{
    bh temp;
    temp=NULL;
    
    if(root->k==key)
    {
        return root;
    }
    
    if(root->lc!=NULL && temp==NULL)
    {
        temp=find(root->lc,key);
    }
    
    if(root->rs!=NULL && temp==NULL)
    {
        temp=find(root->rs,key);
    }
    
    return temp;
}

//the decreased value is simply propogated upwards to parent until
//smaller value of parent is found or if the parent becomes NULL,i.e,the new value becomes the root of the given binomial tree 
bh decrease(bh root,bh new)
{
    int temp;
    
    while(new->p!=NULL && new->k<new->p->k)
    {
        temp=new->k;
        new->k=new->p->k;
        new->p->k=temp;
        
        new=new->p;
    }
    
    return root;
}

//reverses the linked list and returns the head of the reversed linked list
//very useful function,always keep such functions handy
bh reverse(bh root)
{
    bh curr,prev,next;
    curr=root;
    prev=NULL;
    
    while(curr!=NULL)
    {
        next=curr->rs;
        curr->rs=prev;
        prev=curr;
        curr=next;
    }
    
    return prev;
}

//function to extract the min value from the binomial heap
bh extract(bh root)
{
    //curr stores the node of the minimum key
    //prev1 stores the node previous to curr(node previous to node of the minimum key)
    //prev2 is just used to keep track of previous nodes
    //temp1 is assigned the head of the root list
    bh curr,prev1,prev2,temp1,temp2;
    
    temp1=root;
    curr=root;
    prev1=NULL;
    prev2=NULL;
    
    int min;
    min=root->k;
    
    while(root!=NULL)
    {
        if(root->k<min)
        {
            min=root->k;
            curr=root;
            prev1=prev2;
        }
        
        prev2=root;
        root=root->rs;
    }
    
    //to keep the root list intact
    if(prev1!=NULL)
    {
        prev1->rs=curr->rs;
    }
    
    //if head itself is min change temp to point it to head->rs
    else
    {
        temp1=temp1->rs;
    }
    
    curr->rs=NULL;
    curr=curr->lc;
    
    //incase current was a binomial tree of order zero
    if(curr==NULL)
    {
        return temp1;
    }

    //it changes the parent of all children to NULL(children of node which is removed)
    //if this is not done heapunion will get affected
    //the reason being it accesses the parent of temp to find head of root list 
    temp2=curr;
    while(temp2!=NULL)
    {
        temp2->p=NULL;
        temp2=temp2->rs;
    }
    
    curr=reverse(curr);
    temp1=heapunion(curr,temp1);
    
    //returning the head of the root list
    return temp1;
}

//function to delete a node in the binomial heap
//it decreases the value of given key to -infinity and then calls extract to remove the key
bh delete(bh root,bh new)
{
    root=decrease(root,new);
    root=extract(root);
    
    return root;
}

int main()
{
    char c;
    int key,key2;
    bh new,root1,root2,root;
    
    root1=NULL;
    root2=NULL;
    root=NULL;
    
    while(1)
    {
        scanf("%c",&c);
        
        switch(c)
        {
            case 'i':
            scanf("%d",&key);
            new=create(key);
            root1=heapunion(root1,new);
            break;
            
            case 'j':
            scanf("%d",&key);
            new=create(key);
            root2=heapunion(root2,new);
            break;
            
            case 'd':
            scanf("%d",&key);
            if(root1==NULL)
            {
                printf("-1\n");
            }
            else
            {
                new=find(root1,key);
                if(new==NULL)
                {
                    printf("-1\n");
                }
                else
                {
                    printf("%d\n",key);
                    new->k=-1000000;
                    root1=delete(root1,new);
                }
            }
            break;
            
            case 'p':
            scanf("%d",&key);
            if(key==1)
            {
                if(root1==NULL)
                {
                    printf("-1\n");
                }
                else
                {
                    print(root1);
                }
            }
            else
            {
                if(root2==NULL)
                {
                    printf("-1\n");
                }
                else
                {
                    print(root2);
                }
            }
            break;
            
            case 'm':
            if(root1==NULL)
            {
                printf("-1\n");
            }
            else
            {
                minimum(root1);
            }
            break;
            
            case 'x':
            if(root1==NULL)
            {
                printf("-1\n");
            }
            else
            {
                minimum(root1);
                root1=extract(root1);
            }
            break;
            
            case 'r':
            scanf("%d",&key);
            scanf("%d",&key2);
            if(root1==NULL || key<key2)
            {
                printf("-1\n");
            }
            else
            {
                new=find(root1,key);
                if(new==NULL)
                {
                    printf("-1\n");
                }
                else
                {
                    printf("%d\n",key-key2);
                    new->k=key-key2;
                    root1=decrease(root1,new);
                }
            }
            break;
            
            case 'u':
            root=heapunion(root1,root2);
            print(root);
            root1=NULL;
            root2=NULL;
            break;
            
            case 'e':
            return 0;
        }
    }
}