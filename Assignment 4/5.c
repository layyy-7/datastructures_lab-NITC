//program for finding shortest path between a vertex and all other vertices or between two given vertices
//in any undirected as well as directed graph where edge weights are non-negative

//the given program uses dijkstra's algorithm
//here dijkstra's algorithm is implemented using adjacency matrix

#include <stdio.h>
#include <string.h>
#include <limits.h>

//function to return the index of the minimum dist from the vertices not yet included in mst
int min(int hash[],int dist[],int n)
{
    int mini,minv;
    minv=INT_MAX;
    
    int i;
    for(i=0;i<n;i++)
    {
        if(hash[i]==0 && dist[i]<minv)
        {
            minv=dist[i];
            mini=i;
        }
    }
    
    return mini;
}

void dijkstra1(int n,int am[][n],int src)
{
    int i,j,x;
    int dist[n],hash[n];
    
    for(i=0;i<n;i++)
    {
        dist[i]=INT_MAX;
        hash[i]=0;
    }
    
    dist[src]=0;
    
    for(i=0;i<n-1;i++)
    {
        x=min(hash,dist,n);
        hash[x]=1;
        
        for(j=0;j<n;j++)
        {
            if(am[x][j]!=0 && hash[j]==0 && dist[x]!=INT_MAX && dist[x]+am[x][j]<dist[j])
            {
                dist[j]=dist[x]+am[x][j];
            }
        }
    }
    
    for(i=0;i<n;i++)
    {
        if(dist[i]==INT_MAX)
        {
            printf("INF ");
        }
        else
        {
            printf("%d ",dist[i]);
        }
    }
    printf("\n");
}

void dijkstra2(int n,int am[][n],int src,int dest)
{
    int i,j,x;
    int dist[n],hash[n];
    
    for(i=0;i<n;i++)
    {
        dist[i]=INT_MAX;
        hash[i]=0;
    }
    
    dist[src]=0;
    
    for(i=0;i<n-1;i++)
    {
        x=min(hash,dist,n);
        hash[x]=1;
        
        for(j=0;j<n;j++)
        {
            if(am[x][j]!=0 && hash[j]==0 && dist[x]!=INT_MAX && dist[x]+am[x][j]<dist[j])
            {
                dist[j]=dist[x]+am[x][j];
            }
        }
    }
    
    if(dist[dest]==INT_MAX)
    {
        printf("UNREACHABLE\n");
    }
    else
    {
        printf("%d\n",dist[dest]);
    }
}

int main()
{
    int n;
    scanf("%d",&n);
    
    int i,j,k,num;
    char s[10000];
    int v[n][n],w[n][n];
    
    //initializing each vertex so as to know when the array column ends
    for(i=0;i<n;i++)
    {
        for(j=0;j<n;j++)
        {
            v[i][j]=-1;
        }
    }
    
    //reading the vertices
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
            
            v[i][j]=num;
            j++;
            
            if(s[k]!='\0')
            {
                k++;
            }
        }
    }
    
    //reading the weights corresponding to the vertices
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
            
            w[i][j]=num;
            j++;
            
            if(s[k]!='\0')
            {
                k++;
            }
        }
    }
    
    int am[n][n];
    int src,dest;
    
    for(i=0;i<n;i++)
    {
        for(j=0;j<n;j++)
        {
            am[i][j]=0;
        }
    }
    
    //very imp part
    //converting the vertex and weight represetation using adjacency list to vertex and weight representation using adjacency matrix
    for(i=0;i<n;i++)
    {
        for(j=1;j<n && v[i][j]!=-1;j++)
        {
            am[i][v[i][j]]=w[i][j];
        }
    }
    
    //dijkstra1 and dijkstra2 are same functions,they just print different results
    while(1)
    {
        scanf(" %s",s);
        
        if(strcmp(s,"apsp")==0)
        {
            scanf("%d",&src);
            dijkstra1(n,am,src);
        }
        
        else if(strcmp(s,"sssp")==0)
        {
            scanf("%d",&src);    
            scanf("%d",&dest);
            dijkstra2(n,am,src,dest);
        }
        
        else if(strcmp(s,"stop")==0)
        {
            return 0;
        }
    }
}