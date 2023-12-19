//using hashing with open addressing to resolve collisions
//all three methods of open addressing are used here
//in each method,the primary hash value is same(key(modn)) but the offsets vary

//array a contains i elements and has size i
//initialised size(n) and used size(i) are different(n denotes the maximum size of i possible)
//array b also contains i elements but has size n

//array a is the array for storing keys according to input order
//array b is the array for storing keys according to the hash values

//point to be noted,value of array a is changed nowhere
//and this is very crucial as arrays pass by reference
//if any value in array a is changed it will be reflected in other functions and will give undesirable results

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//function for checking whether given integer is prime or not
//If n is a composite integer, then n has a prime divisor less than or equal to sqrt(n)(method for checking prime)
int check(int j)
{
    int k,x;
    x=(int)pow((double)j,0.5);
    
    for(k=x;k>2;k--)
    {
        //if some integer k<=x divides j,j is not prime,so 0 will be returned
        if(j%k==0)
        {
            return 0;
        }
    }
    
    //else 1 will be returned,if prime
    return 1;
}

//function for finding the largest prime less than n
//already given n is prime and n>=3
int prime(int n)
{
    if(n==3)
    {
        return 2;
    }
    
    int j,k;
    
    //doing j=j-2 as n is prime(implies it is odd)
    for(j=n-2;j>2;j=j-2)
    {
        k=check(j);
        
        //the first prime that comes is returned to double hash function
        //which is obviously also the largest prime less than n 
        if(k==1)
        {
            return j;
        }
    }
}

void linearprob(int n,int i,int a[])
{
    int j,k,count,x,y,z,w;
    int b[n];
    
    //initialising all elements of array b to -1 so as to know whether given position is empty or not
    //because given that all keys are positive
    for(j=0;j<n;j++)
    {
        b[j]=-1;
    }
    
    //count of number of collisions
    count=0;
    
    for(j=0;j<i;j++)
    {
        //initial hash value of the key a[j]
        w=a[j]%n;
        
        //if given position is empty,then change the value at position to key value
        if(b[w]==-1)
        {
            b[w]=a[j];
            printf("%d ",w);
        }
        
        else
        {
            //y is used for modifying hash values for different values of k
            //z is assigned initial hash value so as to reinitialise y to initial hash value(w) if again a collision occurs
            y=w;
            z=w;
            
            //count is incremented here as it comes here only after collision occurs for k=0
            count++;
            
            for(k=1;k<n;k++)
            {
                //x is the offset
                //x is added to y to modify the hash value
                
                //be careful,(a(modm)+b(modm))modm=(a+b)(modm)
                //y which is equivalent to a(modm) is already there
                //so do not do (y+k)%n which is completly wrong
                //(y+k)%n is equivalent to (a(modm)+b)modm but we need (a(modm)+b(modm))modm
                
                x=k%n;
                y+=x;
                y%=n;
                
                //if given position is empty,then change the value at position to key value
                if(b[y]==-1)
                {
                    b[y]=a[j];
                    printf("%d ",y);
                    
                    goto end;
                }
                
                y=z;
                count++;
            }
            
            //if element cannot fit at any position
            printf("E ");
            end:;
        }
    }
    
    printf("\n%d\n",count);
}

void quadraticprob(int n,int i,int a[])
{
    int j,k,count,x,y,z,w;
    int b[n];
    
    for(j=0;j<n;j++)
    {
        b[j]=-1;
    }
    
    count=0;
    
    for(j=0;j<i;j++)
    {
        w=a[j]%n;
        
        if(b[w]==-1)
        {
            b[w]=a[j];
            printf("%d ",w);
        }
        
        else
        {
            y=w;
            z=w;
            count++;
            
            for(k=1;k<n;k++)
            {
                //just x(offset) different than other methods,everything else same
                x=(k*k)%n;
                y+=x;
                y%=n;
                
                if(b[y]==-1)
                {
                    b[y]=a[j];
                    printf("%d ",y);
                    
                    goto end;
                }
                
                y=z;
                count++;
            }
            
            printf("E ");
            end:;
        }
    }
    
    printf("\n%d\n",count);
}

void doublehash(int n,int i,int a[])
{
    int r;
    r=prime(n);
    
    int j,k,count,x,y,z,w,h;
    int b[n];
    
    for(j=0;j<n;j++)
    {
        b[j]=-1;
    }
    
    count=0;
    
    for(j=0;j<i;j++)
    {
        w=a[j]%n;
        
        if(b[w]==-1)
        {
            b[w]=a[j];
            printf("%d ",w);
        }
        
        else
        {
            //original value of key must be used in the hash function
            //if w or some other value is used,it will be wrong
            h=r-(a[j]%r);
            
            y=w;
            z=w;
            count++;
            
            for(k=1;k<n;k++)
            {
                //just x(offset) different from other methods,everything else same
                x=(k*h)%n;
                y+=x;
                y%=n;
                
                if(b[y]==-1)
                {
                    b[y]=a[j];
                    printf("%d ",y);
                    
                    goto end;
                }
                
                y=z;
                count++;
            }
            
            printf("E ");
            end:;
        }
    }
    
    printf("\n%d\n",count);
}

int main()
{
    //size of table
    int n;
    scanf("%d",&n);
    
    char *s;
    s=(char *) malloc(100000*sizeof(char));
    scanf(" %[^\n]",s);
    
    //array a to store keys,
    //max size n as given in question that number of keys to be inserted is less than or equal to size of table
    //i keeps the count of total number of keys
    int a[n];
    int i,num;
    
    i=0;
    
    //extracting keys from string input
    while(*s!='\0')
    {
        num=0;
        
        while(*s>='0' && *s<='9')
        {
            num=num*10+*s-'0';
            s++;
        }
        
        a[i]=num;
        
        i++;
        s++;
    }

    linearprob(n,i,a);
    quadraticprob(n,i,a);
    doublehash(n,i,a);
    
    return 0;
}