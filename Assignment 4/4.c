//program for finding weight of minimum spanning tree(mst) for undirected graph 
//minimum spanning tree is a spanning tree such that weight of the edges is minimum

//kruskal and prim algorithms can be used only for undirected graphs
//kruskal's algorithm used here uses edge representation 
//prim's algorithm used here uses adjacency matrix representation

#include <stdio.h>
#include <limits.h>

//v1-first vertex of edge
//v2-second vertex of edge
//we-weight of edge(connecting v1 to v2)
struct element
{
    int v1;
    int v2;
    int we;
};
typedef struct element edge;

//function for making disjoint sets
//initializes parent array and rank array
void makeset(int parent[],int rank[],int m)
{
    int i;
    for(i=0;i<m;i++)
    {
        parent[i]=i;
        rank[i]=0;
    }
}

//function for finding parent of given key
//findset using path compression
int findset(int parent[],int key)
{
    if(parent[key]!=key)
    {
        parent[key]=findset(parent,parent[key]);
    }
    
    return parent[key];
}

//function for union of two sets
//unionset using union by rank
void unionset(int parent[],int rank[],int m,int x,int y)
{
    x=findset(parent,x);
    y=findset(parent,y);
    
    if(rank[x]<rank[y])
    {
        parent[x]=y;
    }
    
    else if(rank[x]>rank[y])
    {
        parent[y]=x;
    }
    
    else
    {
        parent[y]=x;
        rank[x]++;
    }
}

//kruskal's algorithm for finding mst
void kruskal(edge e[],int m)
{
    int i,j;
    edge swap;
    
    //sorting the edges according to their weights
    for(i=0;i<m;i++)
    {
        for(j=i;j<m;j++)
        {
            if(e[i].we>e[j].we)
            {
                swap=e[i];
                e[i]=e[j];
                e[j]=swap;
            }
        }
    }

    int cost;
    cost=0;
    
    int parent[m],rank[m];
    makeset(parent,rank,m);
    
    int x,y,z;
    for(i=0;i<m;i++)
    {
        x=findset(parent,e[i].v1);
        y=findset(parent,e[i].v2);
        z=e[i].we;
    
        //if both vertices have different parents,the subgraphs of the two vertices are not connected
        //else they are already connected by some edges of lesser weight
        if(x!=y)
        {
            unionset(parent,rank,m,x,y);
            cost+=z;
        }
    }
    
    printf("%d\n",cost);
}

//function to return the index of the minimum dist from the vertices not yet included in mst
int min(int hash[],int dist[],int n)
{
    int minv,mini;
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

//prim's algorithm for finding mst
//point to be noted,n should be passed before am in function call as am uses n 
void prim(int n,int am[][n])
{
    int i,j,x;
    int parent[n],dist[n],hash[n];
    
    for(i=0;i<n;i++)
    {
        dist[i]=INT_MAX;
        hash[i]=0;
    }
    
    //initializing the dist to zero where we want to start the process for finding mst(here,0)
    //also the parent of that is assigned value -1
    dist[0]=0;
    parent[0]=-1;
    
    for(i=0;i<n-1;i++)
    {
        x=min(hash,dist,n);
        hash[x]=1;
        
        for(j=0;j<n;j++)
        {
            //if there is an edge present between vertices x and j
            //if vertex j is not already counted in mst
            //if the weight of the edge between vertices x and j is less than dist of j
            //dist of j means edge weight of any previous edges between j and any other vertex 
            if(am[x][j]!=0 && hash[j]==0 && am[x][j]<dist[j])
            {
                //updating parent and dist value for the vertices adjacent to x
                //only those vertices which are not yet inlcuded in mst
                parent[j]=x;
                dist[j]=am[x][j];
            }
        }
    }
    
    int cost;
    cost=0;
    
    for(i=1;i<n;i++)
    {
        cost+=am[i][parent[i]];
    }
    
    printf("%d\n",cost);
}

int main()
{
    char c;
    scanf("%c",&c);
    
    int n;
    scanf("%d",&n);
    
    int i,j,k,num,flag;
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
            flag=0;
            
            if(s[k]=='-')
            {
                flag=1;
                k++;
            }
            
            while(s[k]>='0' && s[k]<='9')
            {
                num=num*10+s[k]-'0';
                k++;
            }
            
            if(flag!=1)
            {
                w[i][j]=num;
            }
            else
            {
                w[i][j]=-num;
            }
            
            j++;
            
            if(s[k]!='\0')
            {
                k++;
            }
        }
    }
    
    if(c=='a')
    {
        //hash function so that any edge is not counted twice
        //range of weights is -10000 to 10000
        int hash[20001]={0};
        edge e[10000];
        
        //very imp part
        //converting the vertex and weight represetation to edge and weight representation
        for(i=0,k=0;i<n;i++)
        {
            for(j=1;j<n && v[i][j]!=-1;j++)
            {
                if(hash[w[i][j]+10000]==0)
                {
                    e[k].v1=i;
                    e[k].v2=v[i][j];
                    e[k].we=w[i][j];
                    k++;
                    
                    //changing the hash value
                    hash[w[i][j]+10000]=1;
                }
            }
        }
        
        //k is the total number of edges
        kruskal(e,k);
    }
    
    if(c=='b')
    {
        int am[n][n];
        
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
        
        //n is the dimension of adjacency matrix
        prim(n,am);
    }
    
    return 0;
}