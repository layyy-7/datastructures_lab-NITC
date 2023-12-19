//program for depth first search
//dfs using recursion where each key is initially hashed to 0

#include <stdio.h>
#include <stdlib.h>

int n;

//initializing n global and giving it to second index of parameter a in function call is very imp
//or else correct output does not come
//function to print the dfs representation
void dfs(int a[][n],int b[],int x)
{
    int i;
    
    b[x]=1;
    printf("%d ",x);
    
    for(i=0;i<n && a[x][i]!=-1;i++)
    {
        //will be done only if the hash value of element is 0 
        if(b[a[x][i]]==0)
        {
            dfs(a,b,a[x][i]);
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
    
    //first element is always 0(given in question)
    dfs(a,b,a[0][0]);
}    