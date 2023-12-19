//doing this with hashing is lot more efficient than what I had done previously

//firstly,it saves a lot of space
//as previously,I had taken an array of record list[1000] 
//but now I take an array of pointers a[4] which uses only necessary space

//secondly,it saves time too
//as previously,I scanned the whole array of record list[1000] to find and print the students in a particular group
//but now I only need to iterate that particular group to print all students

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

//taking structure for storing data and keeping the next pointer
struct element
{
    char name[1000];
    char roll[1000];
    int age;
    int group;
    struct element *next;
};

typedef struct element record;

//a[4] is an array of 4 pointers to record
//list is a variable of type record
record *a[4];
record list;

record *create()
{
    record *new;
    new=(record *)malloc(sizeof(record));
    
    //point to be noted
    //always remember strcpy for copying strings
    //they cannot be copied directly
    
    //new is a pointer of type record
    //list is a variable of type record
    //hence using -> for new and . for list
    
    strcpy(new->name,list.name);
    strcpy(new->roll,list.roll);
    new->age=list.age;
    new->group=list.group;
    new->next=NULL;
    
    return new;
}

//function for inserting the new pointer to type record to the required array index
void insert(record *new)
{
    if(a[list.group]==NULL)
    {
        a[list.group]=new;
    }
    
    else
    {
        new->next=a[list.group];
        a[list.group]=new;
    }
}

void f1(int k)
{
    int count;
    count=0;
    
    //assigning the temporary pointer tag is important or else a[k] will be modified
    //as we are doing a[k]=a[k]->next(tag=tag->next)
    record *tag;
    tag=a[k];
    
    if(tag!=NULL)
    {
        while(tag->next!=NULL)
        {
            count++;
            tag=tag->next;
        }
        
        count++;
        printf("%d ",count);
    }
    
    else
    {
        printf("0\n");
    }
    
    //assigning the temporary pointer tag is important or else a[k] will be modified
    //as we are doing a[k]=a[k]->next(tag=tag->next)
    tag=a[k];

    if(tag!=NULL)
    {
        while(tag->next!=NULL)
        {
            printf("%s ",tag->name);
            tag=tag->next;
        }
        
        printf("%s\n",tag->name);
    }
}

void f2(int k,char s[])
{
    int count;
    count=0;
    
    //assigning the temporary pointer tag is important or else a[k] will be modified
    //as we are doing a[k]=a[k]->next(tag=tag->next)
    record *tag;
    tag=a[k];
    
    while(tag!=NULL)
    {
        if(tag->roll[7]==toupper(s[0]) && tag->roll[8]==toupper(s[1]))
        {
            count++;
            printf("%s ",tag->name);
        }
        
        tag=tag->next;
    }
    
    if(count==0)
    {
        printf("-1\n");
    }
    
    else
    {
        printf("\n");
    }
}

int main()
{
    int i,j,k,l,n;
    char c;
    char s[10];
    record *new;
    
    //initialising every element of array a to NULL
    for(i=0;i<4;i++)
    {
        a[i]=NULL;
    }
    
    scanf("%d",&n);
    
    for(i=0;i<n;i++)
    {
        scanf("%s",list.name);
        scanf("%s",list.roll);
        scanf("%d",&list.age);
        
        l=strlen(list.name);
        list.group=0;
        
        //calculating the ASCII value
        for(j=0;j<l;j++)
        {
            list.group+=list.name[j];
        }
        
        list.group+=list.age;
        list.group=(list.group)%4;
        
        new=create();
        insert(new);
    }
    
    while(1)
    {
        //leaving space before %s is imp as just before it we scanned %c
        //not doing so may give erroneous output
        scanf("%c",&c);
        
        switch(c)
        {
            case 'c':
            scanf("%d",&k);
            f1(k);
            break;
            
            case '0':
            scanf(" %s",s);
            f2(0,s);
            break;
            
            case '1':
            scanf(" %s",s);
            f2(1,s);
            break;
            
            case '2':
            scanf(" %s",s);
            f2(2,s);
            break;
            
            case '3':
            scanf(" %s",s);
            f2(3,s);
            break;
            
            case 'e':
            return 0;
        }
    }
    
    return 0;
}