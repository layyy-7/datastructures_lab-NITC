//program for breadth first search
//bfs using queue where each key is initially hashed to 0

#include <stdio.h>
#include <stdlib.h>

int n;

struct element
{
    int val;
    struct element *next;
};

typedef struct element queue;
queue *head=NULL;
queue *tail=NULL;

queue *create(int key)
{
    queue *new;
    new=(queue *) malloc(sizeof(queue));
    
    new->val=key;
    new->next=NULL;
    
    return new;
}

void enqueue(queue *new)
{
    if(tail==NULL)
    {
        tail=new;
    }
    
    else
    {
        tail->next=new;
        tail=new;
    }
    
    //this is very imp
    //must be written separately and not included with tail==NULL
    if(head==NULL)
    {
        head=new;
    }
}

int dequeue()
{   
    int x;
    
    x=head->val;
    head=head->next;
    
    return x;
}

//initializing n global and giving it to second index of parameter a in function call is very imp
//or else correct output does not come
//function to print the bfs representation
void bfs(int a[][n],int b[])
{
    int i,x;
    queue *new;
    
    //first element is always 0(given in question)
    //the given key is hashed to 1 so that it will not be enqueued again
    new=create(a[0][0]);
    enqueue(new);
    b[a[0][0]]=1;
       
    while(head!=NULL)
    {
        //we run the loop with first index as dequeued element
        x=dequeue();
        printf("%d ",x);
        
        for(i=0;i<n && a[x][i]!=-1;i++)
        {
            //will be done only if the element was previously not enqueued
            if(b[a[x][i]]==0)
            {
                new=create(a[x][i]);
                enqueue(new);
                b[a[x][i]]=1;
            }
        }
    }
}

int main()
{
    scanf("%d",&n);
    
    int i,j,k,num;
    int a[n][n];
    int b[n];
    char s[10000];
    
    //each element of 2D array is initialized to -1
    //each key is hashed to 0(each key because the vertices are labelled from 0 to n-1)
    for(i=0;i<n;i++)
    {
        for(j=0;j<n;j++)
        {
            a[i][j]=-1;
        }
        
        b[i]=0;
    }
    
    //to transform the strings into 2D array
    for(i=0;i<n;i++)
    {
        scanf(" %[^\n]",s);
        
        k=0;
        j=0;
        
        while(s[k]!='\0')
        {
            num=0;
            
            while(s[k]>='0' && s[k]<='9')
            {
                num=num*10+s[k]-'0';
                k++;
            }
            
            a[i][j]=num;
            j++;
            
            if(s[k]!='\0')
            {
                k++;
            }
        }
    }
    
    bfs(a,b);
}