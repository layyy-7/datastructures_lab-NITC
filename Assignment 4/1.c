//printing the adjacency list from adjacency matrix
//taking a[n][n] will save lot of space instead of a[1000][1000]

#include <stdio.h>

int main()
{
    int n;
    scanf("%d",&n);
    
    int i,j;
    int a[n][n];
    
    for(i=0;i<n;i++)
    {
        for(j=0;j<n;j++)
        {
            scanf("%d",&a[i][j]);
        }
    }
    
    for(i=0;i<n;i++)
    {
        printf("%d ",i);
        for(j=0;j<n;j++)
        {
            if(a[i][j]!=0)
            {
                printf("%d ",j);
            }
        }
        printf("\n");
    }
}