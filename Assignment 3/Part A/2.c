//operations on a binary heap
//only new operation added is delete
//rest all are same

#include <stdio.h>

int heapsize;

void minheapify(int a[],int i)
{
    int l,r,small,swap;
    
    l=2*i+1;
    r=2*i+2;
    
    if(l<heapsize && a[l]<a[i])
    {
        small=l;
    }
    
    else
    {
        small=i;
    }
    
    if(r<heapsize && a[r]<a[small])
    {
        small=r;
    }
    
    if(small!=i)
    {
        swap=a[small];
        a[small]=a[i];
        a[i]=swap;
        
        minheapify(a,small);
    }
}

void print(int a[])
{
    int i;
    
    if(heapsize==0)
    {
        printf("-1\n");
        return;
    }
    
    for(i=0;i<heapsize;i++)
    {
        printf("%d ",a[i]);
    }
    printf("\n");
}

void extract(int a[])
{
    if(heapsize!=0)
    {
        a[0]=a[heapsize-1];
        heapsize--;
        minheapify(a,0);
    }
}

void decrease(int a[],int key,int new)
{
    int i,swap;
    
    for(i=0;i<heapsize;i++)
    {
        if(a[i]==key)
        {
            a[i]=new;
            break;
        }
    }
    
    while(new<a[(i-1)/2])
    {
        swap=a[i];
        a[i]=a[(i-1)/2];
        a[(i-1)/2]=swap;
        
        i=(i-1)/2;
    }
}

void get(int a[])
{
    if(heapsize==0)
    {
        printf("-1\n");
    }
    
    else
    {
        printf("%d\n",a[0]);
    }
}

void insert(int a[],int key)
{
    a[heapsize]=key;
    heapsize++;
    
    int i,swap;
    i=heapsize-1;
    
    while(key<a[(i-1)/2])
    {
        swap=a[i];
        a[i]=a[(i-1)/2];
        a[(i-1)/2]=swap;
        
        i=(i-1)/2;
    }
}

//decreases the key to -infinity so that it goes to the top of min heap
//then calls the process extract to delete the key
void delete(int a[],int key)
{
    int i;
    for(i=0;i<heapsize;i++)
    {
        if(a[i]==key)
        {
            break;
        }
    }
    
    if(i==heapsize)
    {
        printf("-1\n");
        return;
    }
    
    else
    {
        printf("%d\n",key);
    }
    
    decrease(a,key,-1000001);
    extract(a);   
}

int main()
{
    char c;
    int key,new;
    int a[10000];
    
    heapsize=0;
    
    while(1)
    {
        scanf("%c",&c);
        
        switch(c)
        {
            case 'i':
            scanf("%d",&key);
            insert(a,key);
            break;
            
            case 'd':
            scanf("%d",&key);
            delete(a,key);
            break;
            
            case 'p':
            print(a);
            break;
            
            case 'x':
            extract(a);
            print(a);
            break;
            
            case 'r':
            scanf("%d",&key);
            scanf("%d",&new);
            if(new>=key)
            {
                printf("-1\n");
            }
            else
            {
                printf("%d\n",new);
                decrease(a,key,new);
            }
            break;
            
            case 'g':
            get(a);
            break;
           
            case 'e':
            return 0;
        }
    }
}