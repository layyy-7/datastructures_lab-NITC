//method of direct addressing
//numbers should be in the range of 0 to 100000

#include <stdio.h>

int main()
{
    int i,n,x;
    scanf("%d",&n);
    
    int a[100001];
    int b[100001];
    
    for(i=0;i<100001;i++)
    {
        a[i]=0;
        b[i]=0;
    }
    
    for(i=0;i<n;i++)
    {
        scanf("%d",&x);
        a[x]++;
    }
    
    for(i=0;i<n;i++)
    {
        scanf("%d",&x);
        b[x]++;
    }
    
    for(i=0;i<100001;i++)
    {
        if(a[i]!=b[i])
        {
            printf("0\n");
            goto end;
        }
    }
    
    printf("1\n");
    end:;
    
    return 0;
}