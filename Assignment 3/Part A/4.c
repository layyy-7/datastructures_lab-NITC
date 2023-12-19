#include <stdio.h>

int heapsize;

void minheapify(int a[],int heapsize,int i)
{
    int l,r,swap,small;
    
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
    
    if(i!=small)
    {
        swap=a[i];
        a[i]=a[small];
        a[small]=swap;
        
        minheapify(a,heapsize,small);
    }
}

void buildminheap(int a[],int n)
{
    int i;
    for(i=(n/2)-1;i>=0;i--)
    {
        minheapify(a,n,i);
    }
}

int main()
{
    int n;
    scanf("%d",&n);
    
    int i,cost,x,y;
    int a[n];
    
    for(i=0;i<n;i++)
    {
        scanf("%d",&a[i]);
    }
    
    buildminheap(a,n);
    heapsize=n;
    cost=0;
    
    while(heapsize>1)
    {
        //storing the smallest element and replacing it with the last element of heap
        x=a[0];
        a[0]=a[heapsize-1];
        heapsize--;
        minheapify(a,heapsize,0);

        //storing the other smallest element and adding the cost of joining both of them
        //inserting the cost of joining back in the heap
        y=a[0];
        cost+=x+y;
        a[0]=x+y;
        minheapify(a,heapsize,0);
    }
    
    printf("%d\n",cost);
}