//case 1-union without rank and find without path compression
//case 2-union with rank and find without path compression
//case 3-union without rank and find with path compression
//case 4-union with rank and find with path compression

//idk why my case s does not work for case 2(everything else working fine)

#include <stdio.h>

int count1=0;
int count2=0;
int count3=0;
int count4=0;

//p-parent
//r-rank
struct element
{
    int p;
    int r;
};
typedef struct element ds;

void makeset(ds a[],ds b[],ds c[],ds d[],int key)
{
    a[key].p=key;
    a[key].r=0;
    
    b[key].p=key;
    b[key].r=0;
    
    c[key].p=key;
    c[key].r=0;
    
    d[key].p=key;
    d[key].r=0;
}

//find without path compression 
int findset1(ds a[],int key)
{
    count1++;
    
    if(a[key].p!=key)
    {
        return findset1(a,a[key].p);
    }
    
    return a[key].p;
}

//find without path compression 
int findset2(ds b[],int key)
{
    count2++;
    
    if(b[key].p!=key)
    {
        return findset2(b,b[key].p);
    }
    
    return b[key].p;
}

//find with path compression 
int findset3(ds c[],int key)
{
    if(c[key].p!=key)
    {
        c[key].p=findset3(c,c[key].p);
    }
    
    count3++;
    return c[key].p;
}

//find with path compression 
int findset4(ds d[],int key)
{
    if(d[key].p!=key)
    {
        d[key].p=findset4(d,d[key].p);
    }
    
    count4++;
    return d[key].p;
}

//union without rank
int unionset1(ds a[],int key1,int key2)
{
    a[key2].p=key1;
    return key1;
}

//union with rank
int unionset2(ds a[],int key1,int key2)
{
    if(a[key1].r<a[key2].r)
    {
        a[key1].p=key2;
        return key2;
    }
    
    else if(a[key1].r>a[key2].r)
    {
        a[key2].p=key1;
    }
    
    else
    {
        a[key2].p=key1;
        a[key1].r++;
    }
    
    return key1;
}

int main()
{
    char ch;
    int key1,key2,x;
    ds a[10001],b[10001],c[10001],d[10001];
    
    int i;    
    for(i=0;i<10001;i++)
    {
        a[i].p=-1;
        b[i].p=-1;
        c[i].p=-1;
        d[i].p=-1;
    }
    
    while(1)
    {
        scanf("%c",&ch);
        
        switch(ch)
        {
            case 'm':
            scanf("%d",&key1);
            if(a[key1].p!=-1)
            {
                printf("-1\n");
            }
            else
            {   printf("%d\n",key1);
                makeset(a,b,c,d,key1);
            }
            break;
            
            case 'f':
            scanf("%d",&key1);
            if(a[key1].p==-1)
            {
                printf("-1\n");
            }
            else
            {
                key1=findset1(a,key1);
                printf("%d ",key1);
                key1=findset2(b,key1);
                printf("%d ",key1);
                key1=findset3(c,key1);
                printf("%d ",key1);
                key1=findset4(d,key1);
                printf("%d\n",key1);
            }
            break;
            
            case 'u':
            scanf("%d",&key1);
            scanf("%d",&key2);
            if(a[key1].p==-1 || a[key2].p==-1)
            {
                printf("-1\n");
            }
            else
            {
                x=unionset1(a,findset1(a,key1),findset1(a,key2));
                printf("%d ",x);
                x=unionset2(b,findset2(b,key1),findset2(b,key2));
                printf("%d ",x);
                x=unionset1(c,findset3(c,key1),findset3(c,key2));
                printf("%d ",x);
                x=unionset2(d,findset4(d,key1),findset4(d,key2));
                printf("%d\n",x);
            }
            break;
            
            case 's':
            printf("%d %d %d %d\n",count1,count2,count3,count4);
            return 0;
        }
    }
}