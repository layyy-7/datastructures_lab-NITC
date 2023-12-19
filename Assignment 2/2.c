//using hashing with chaining
//instead of a linked list in usual chaining,
//we have bst in chaining

//every element of array a is pointer of type record
//hence every array element of a stores a bst
//hence total 26 bsts can be made one starting at each array index

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct element
{
    char first[100];
    char last[100];
    char gender;
    char dob[100];
    char dept[100];
    float cgpa;
    int group;
    struct element *l;
    struct element *r;
    struct element *p;
};

//array of 26 pointers to type record
typedef struct element record;
record *a[26];

//creating new record
record *create(record list)
{
    record *new;
    new=(record *) malloc(sizeof(record));
    
    strcpy(new->first,list.first);
    strcpy(new->last,list.last);
    new->gender=list.gender;
    strcpy(new->dob,list.dob);
    strcpy(new->dept,list.dept);
    new->cgpa=list.cgpa;
    new->group=list.group;
    
    new->p=NULL;
    new->l=NULL;
    new->r=NULL;
    
    return new;
}

//inserting the new record
//similar to bst insertion
void insert(record *new)
{
    //assigning tag1 the required array index
    //so tag1 starts from the starting of that array
    record *tag1,*tag2;
    tag1=a[new->group];
    tag2=NULL;
    
    int ct;
    ct=0;
    
    while(tag1!=NULL)
    {
        ct++;
        tag2=tag1;
        
        //comparing the first name
        if(strcmp(tag1->first,new->first)>0)
        {
            tag1=tag1->l;
        }
        
        else if(strcmp(tag1->first,new->first)<0)
        {
            tag1=tag1->r;
        }
        
        //if first names are same,i.e,strcmp(tag1->first,new->first)==0
        //we compare last names
        else if(strcmp(tag1->last,new->last)>0)
        {
            tag1=tag1->l;
        }
        
        else
        {
            tag1=tag1->r;    
        }
    }
    
    new->p=tag2;
    
    //if new element is the root,
    //the array with given index starts with new element 
    if(tag2==NULL)
    {
        a[new->group]=new;
    }
    
    else if(strcmp(tag2->first,new->first)>0)
    {
        tag2->l=new;
    }
    
    else if(strcmp(tag2->first,new->first)<0)
    {
        tag2->r=new;
    }
    
    else if(strcmp(tag2->last,new->last)>0)
    {
        tag2->l=new;
    }
    
    else
    {
        tag2->r=new;
    }
    
    printf("%d\n",ct);
}

int count;

//similar to bst search
record *search(char s1[],char s2[])
{
    //finding the group
    int g;
    g=s1[0]-'A';
    
    //assigning tag the required array index
    //so tag starts from the starting of that array
    record *tag;
    tag=a[g];
    
    while(tag!=NULL)
    {
        //if both first name and last name are same,we found the match,so we exit
        if(strcmp(tag->first,s1)==0 && strcmp(tag->last,s2)==0)
        {
            break;
        }
        
        //be careful,this count is global variable
        //its working starts from here
        //count is increased if match is not found till tag!=NULL
        count++;
        
        if(strcmp(tag->first,s1)>0)
        {
            tag=tag->l;
        }
        
        else if(strcmp(tag->first,s1)<0)
        {
            tag=tag->r;
        }
        
        else if(strcmp(tag->last,s2)>0)
        {
            tag=tag->l;
        }
        
        else
        {
            tag=tag->r;    
        }
    }
    
    return tag;
}

//somewhat similar to search
//prints the series of nodes followed from root to given node
void location(char s1[],char s2[])
{
    //finding the group
    int g;
    g=s1[0]-'A';
    
    //assigning tag the required array index
    //so tag starts from the starting of that array
    record *tag;
    tag=a[g];
    
    int ct;
    ct=0;
    
    //array used for storing the bst sequence
    char s[1000];
    int i;
    
    while(tag!=NULL)
    {
        //if both first name and last name are same,we found the match,so we exit
        if(strcmp(tag->first,s1)==0 && strcmp(tag->last,s2)==0)
        {
            break;
        }
        
        //ct is increased if match is not found till tag!=NULL
        ct++;
        
        if(strcmp(tag->first,s1)>0)
        {
            tag=tag->l;
            s[ct-1]='L';
        }
        
        else if(strcmp(tag->first,s1)<0)
        {
            tag=tag->r;
            s[ct-1]='R';
        }
        
        else if(strcmp(tag->last,s2)>0)
        {
            tag=tag->l;
            s[ct-1]='L';
        }
        
        else
        {
            tag=tag->r;
            s[ct-1]='R';
        }
    }
    
    if(tag!=NULL)
    {
        printf("%d-",g);
        
        for(i=0;i<ct;i++)
        {
            printf("%c",s[i]);
        }
        
        printf("\n");
    }
    else
    {
        printf("-1\n");
    }
}

//similar to bst transplant
void transplant(record *tag1,record *tag2)
{
    if(tag1->p==NULL)
    {
        a[tag1->group]=tag2;
    }
    
    else if(tag1->p->l==tag1)
    {
        tag1->p->l=tag2;
    }
    
    else
    {
        tag1->p->r=tag2;
        
        if(tag1->p!=NULL && tag1->p->l!=NULL)
        {
            //be careful,this count is global variable
            //its working starts from search
            //the count is incremented here as,
            //if tag1 is the right child of its parent we had already visited the left child of its parent in previous else if
            //so to account for that touch count is incremented
            count++;
        }
    }
    
    if(tag2!=NULL)
    {
        tag2->p=tag1->p;
    }
}

//similar to bst delete
void delete(record *tag)
{
    record *tag2;
    
    if(tag->l==NULL)
    {
        
        if(tag->r!=NULL)
        {
            //be careful,this count is global variable
            //its working starts from search
            //the count is incremented here as to account for the right child of tag
            count++;
        }
        
        transplant(tag,tag->r);
    }
    
    else if(tag->r==NULL)
    {
        if(tag->l!=NULL)
        {
            //be careful,this count is global variable
            //its working starts from search
            //the count is incremented here as to account for the left child of tag
            count++;
        }
        
        transplant(tag,tag->l);
    }
    
    else
    {
        tag2=tag->r;
        
        //be careful,this count is global variable
        //its working starts from search
        //the count is incremented here as to account for the right child of tag
        count++;
        
        while(tag2->l!=NULL)
        {
            tag2=tag2->l;
            
            //be careful,this count is global variable
            //its working starts from search
            //the count is incremented here as to account for the left child of tag2
            count++;
        }
        
        if(tag2->p!=tag)
        {
            if(tag2->r!=NULL)
            {
                //be careful,this count is global variable
                //its working starts from search
                //the count is incremented here as to account for the right child of tag2
                //be careful,the condition tag2->r!=NULL needs to be checked before transplant
                count++;
            }
            
            transplant(tag2,tag2->r);
            tag2->r=tag->r;
            tag2->r->p=tag2;
        }
        
        transplant(tag,tag2);
        tag2->l=tag->l;
        tag2->l->p=tag2;
        
        //be careful,this count is global variable
        //its working starts from search
        //the count is incremented here as to account for the left child of tag
        count++;
    }
}

int main()
{
    char c;
    char s1[100],s2[100];
    record list;
    record *new,*tag;
    int i;
    float num;
    
    for(i=0;i<26;i++)
    {
        a[i]=NULL;
    }
    
    while(1)
    {
        //leaving space before %s is imp as just before it we scanned %c
        //not doing so may give erroneous output
        scanf("%c",&c);
        
        switch(c)
        {
            case 'i':
            scanf(" %s",list.first);
            scanf(" %s",list.last);
            scanf(" %c",&list.gender);
            scanf(" %s",list.dob);
            scanf(" %s",list.dept);
            scanf("%f",&list.cgpa);
            list.group=list.first[0]-'A';
            new=create(list);
            insert(new);
            break;
            
            case 'u':
            scanf(" %s",s1);
            scanf(" %s",s2);
            scanf("%f",&num);
            
            //be careful,this count is global variable
            //its working starts from search
            //initialised to 0 before starting everytime
            count=0;
            
            tag=search(s1,s2);
            if(tag!=NULL)
            {
                tag->cgpa=num;
                printf("%d\n",count);
            }
            else
            {
                printf("-1\n");
            }
            break;
            
            case 'l':
            scanf(" %s",s1);
            scanf(" %s",s2);
            location(s1,s2);
            break;

            case 'd':   
            scanf(" %s",s1);
            scanf(" %s",s2);
            
            //be careful,this count is global variable
            //its working starts from search
            //initialised to 0 before starting everytime
            count=0;
            
            tag=search(s1,s2);
            if(tag!=NULL)
            {
                delete(tag);
                printf("%d\n",count);
            }
            else
            {
                printf("-1\n");
            }
            break;
            
            case 'e':
            return 0;
        }
    }
    
    return 0;
}