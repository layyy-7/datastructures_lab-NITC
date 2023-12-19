#include <stdio.h>

//rank and count of number of elements in the set are for the representative element and need not to be maintained for all elements in the set
//that is why whatever change we do in unionset,we do it for the representative element of the given set and not for the element itself

//p-parent of given element
//r-rank of given element
//ct-count of elements in the set in which the element is present

void makeset(int p[],int r[],int ct[],int key)
{
    p[key]=key;
    r[key]=0;
    ct[key]=1;
}

//findset function with path compression
int findset(int p[],int key)
{
    if(p[key]!=key)
    {
        p[key]=findset(p,p[key]);
    }
    
    //very imp,return must be p[key]
    //if you return just key,you will create wrong findset
    return p[key];
}

//arguments passed in the function call of unionset are not the key themselves,they are the representatives of the set
//this is very imp so as to keep the track of rank and count of number of elements of the set

//unionset function with union by rank
//count of number of elements of the other set is also added to the set it is merged with
void unionset(int p[],int r[],int ct[],int key1,int key2)
{
    if(r[key1]<r[key2])
    {
        p[key1]=key2;
        ct[key2]+=ct[key1];
    }
    
    else if(r[key1]>r[key2])
    {
        p[key2]=key1;
        ct[key1]+=ct[key2];
    }
    
    else
    {
        p[key2]=key1;
        r[key1]++;
        ct[key1]+=ct[key2];
    }
}

void func(int p[],int ct[])
{
    int i,j,ans;
    ans=0;
    
    for(i=0;i<1001;i++)
    {
        if(p[i]==i)
        {
            for(j=i+1;j<1001;j++)
            {
                if(p[j]==j)
                {
                    ans+=(ct[j])*(ct[i]);
                }
            }
        }
    }
    
    if(ans==0)
    {
        printf("-1\n");
    }
    else
    {
        printf("%d\n",ans);
    }
}

int main()
{
    char c;
    int key1,key2;
    int p[1001];
    int r[1001];
    int ct[1001];
    
    //initializing all parents to -1
    //so we can diffrentiate whether a given element is part of any set or not
    int i;
    for(i=0;i<1001;i++)
    {
        p[i]=-1;
    }
    
    //to keep track of total number of teams
    int count;
    count=0;
    
    while(1)
    {
        scanf("%c",&c);
        
        switch(c)
        {
            //passing findset of the key instead of the key itself as function argument is very imp
            //as rank and count of number of elements in the set are maintained only for the representative element of the set
            case 't':
            scanf("%d",&key1);
            scanf("%d",&key2);
            
            //when both elements are not present initially in any set
            if(p[key1]==-1 && p[key2]==-1)
            {
                count++;
                makeset(p,r,ct,key1);
                makeset(p,r,ct,key2);
                unionset(p,r,ct,findset(p,key1),findset(p,key2));
            }
            
            //when one of the elements is not present initially in any set
            else if(p[key1]==-1 && p[key2]!=-1)
            {
                makeset(p,r,ct,key1);
                unionset(p,r,ct,findset(p,key1),findset(p,key2));
            }
            
            //when one of the elements is not present initially in any set
            else if(p[key1]!=-1 && p[key2]==-1)
            {
                makeset(p,r,ct,key2);
                unionset(p,r,ct,findset(p,key1),findset(p,key2));
            }
            
            //when both the elements are present initially in some set
            else
            {
                //if they belong to different sets,take union
                //else do nothing
                if(findset(p,key1)!=findset(p,key2))
                {
                    count--;
                    unionset(p,r,ct,findset(p,key1),findset(p,key2));
                }
            }
            break;
            
            case 'T':
            printf("%d\n",count);
            break;
            
            case 'd':
            func(p,ct);
            break;
            
            case 'v':
            scanf("%d",&key1);
            scanf("%d",&key2);
            
            if(key1>=key2 || p[key1]==-1 || p[key2]==-1)
            {
                printf("-1\n");
            }
            else
            {
                if(findset(p,key1)==findset(p,key2))
                {
                    printf("-1\n");
                }
                else
                {
                    printf("1\n");
                }
            }
            break;
            
            case 'e':
            return 0;
        }
    }
}