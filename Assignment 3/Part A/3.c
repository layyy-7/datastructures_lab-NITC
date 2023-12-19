//using max heap for finding k largest elements
//build a max heap and extract the top most max heap element k times

#include <stdio.h>

int heapsize;

void maxheapify(int a[],int heapsize,int i)
{
    int l,r,swap,large;
    
    l=2*i+1;
    r=2*i+2;
    
    if(l<heapsize && a[l]>a[i])
    {
        large=l;
    }
    
    else
    {
        large=i;
    }
    
    if(r<heapsize && a[r]>a[large])
    {
        large=r;
    }
    
    if(i!=large)
    {
        swap=a[i];
        a[i]=a[large];
        a[large]=swap;
        
        maxheapify(a,heapsize,large);
    }
}

void buildmaxheap(int a[],int n)
{
    int i;
    for(i=(n/2)-1;i>=0;i--)
    {
        maxheapify(a,n,i);
    }
}

int main()
{
    int t;
    scanf("%d",&t);
    
    int n,k,i;
    int a[10000];
    
    while(t--)
    {
        scanf("%d",&n);
        for(i=0;i<n;i++)
        {
            scanf("%d",&a[i]);
        }
        scanf("%d",&k);
        
        buildmaxheap(a,n);
        heapsize=n;
        
        while(k--)
        {
            printf("%d ",a[0]);
            
            a[0]=a[heapsize-1];
            heapsize--;
            maxheapify(a,heapsize,0);
        }
        printf("\n");
    }
}