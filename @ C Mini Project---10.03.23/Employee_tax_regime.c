//C MINI PROJECT - Handling Employee Details using Linked Lists
//Rahul G Athreyas & Navaneeth N
//1RN21CS118 & 1RN21CS098
//3rd Sem CSE 'B'

#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#define SIZE 50

//structure declaration
typedef struct employee {
    char name[30];
    float salary;
    float experience;
    struct employee *link;
}emp;

//function declarations
emp* get_node();
emp* ins_details(emp *);
emp* del_details(char[],emp *);
emp* search(char[],emp *);
void sort(int,emp *);
void tax(char[],emp*);
emp* display(emp* );

//Main Function
int main() {
    emp *first=NULL,*loc=NULL;
    int ch;
    char name[30];
    for(;;) {
         printf("Enter\n1:Add an emoployee\t2:Delete an employee\t3:Display an employee\t4:Search an employee\n5:Sort the employee list\t6:Tax Regime of an employee\t7:Exit\n");
         scanf("%d",&ch);
         switch(ch) {
            case 1:first=ins_details(first);
                    break;
            case 2:if(first==NULL) {
                        printf("The list is null\n");
                        break;
                    }
                    printf("Enter the name of emeployee whose details are to be deleted\n");
                    scanf("%s",name);
                    first=del_details(name,first);
                    break;
            case 3:if(first==NULL) {
                        printf("The list is null\n");
                        break;
                    }
                    display(first);
                    break;
            case 4:if(first==NULL) {
                        printf("The list is null\n");
                        break;
                    }
                    printf("Enter the name of employee whose details is to be known\n");
                    scanf("%s",name);
                    loc=search(name,first);
                    if(loc==NULL){
                        printf("Search was unsuccessful\n");
                        break;
                    }
                    printf("The details of the employee %s found:\n",name);
                    printf("Name: %s\t Salary: Rs.%f\tExperience: %.2f years\n",(loc->name),(loc->salary),(loc->experience));
                    break;
            case 5:printf("Enter 1:Sort the list based on salary\t2:Sort the list based on Experience\n");
                   scanf("%d",&ch);
                   switch(ch){
                       case 1:sort(ch,first);
                              break;
                       case 2:sort(ch,first);
                              break;
                       default:printf("Invalid choice\nPlease enter the choices between 1 and 2\n");
                   }
                   break;
            case 6:printf("Enter the name of employee whose tax status is to be known\n");
                   scanf("%s",name);
                   tax(name,first);
                   break;
            case 7:printf("Thank You\nEnd of program\n");
                   exit(0);
            default:printf("Invalid choice\nPlease enter the choices between 1 to 4\n");
         }
    }
}

//Function to get a new node
emp * get_node() {
    emp* new=(emp *)malloc(sizeof(emp));
    if(new==NULL) {
        printf("No memory\n");
        return NULL;
    }
    return new;
}

//Inserting a node[Employee]
emp* ins_details(emp *first) {
    emp *temp;
    emp *new=get_node();
    printf("Enter the detais of the employee\n");
    printf("Enter the name\n");
    scanf("%s",new->name);
    printf("Enter the salary\n");
    scanf("%f",&new->salary);
    printf("Enter the experience\n");
    scanf("%f",&new->experience);
    new->link=NULL;
    if(first==NULL) {
        return new;
    }
    temp=first;
    while(temp->link!=NULL) 
    {
        temp=temp->link;
    }
    temp->link=new;
    return first;
}

//Deleting a node[Employee]
emp* del_details(char name[],emp *first) {
    emp *pre=NULL,*cur=NULL;
    if(!(strcmp(name,first->name))) {
        printf("The details of the deleted employee are:\n");
        printf("Name: %s\t Salary: Rs.%f\tExperience: %.2f years\n",(first->name),(first->salary),(first->experience));
        cur=first;
        first=first->link;
        free(cur);
        return first;
    }
    pre=NULL;
    cur=first;
    while(cur!=NULL) {
        if(!(strcmp(name,cur->name))){
            printf("The details of the deleted employee are:\n");
            printf("Name: %s\t Salary: Rs.%f\tExperience: %.2f years\n",(cur->name),(cur->salary),(cur->experience));
            return first;
        }
        pre=cur;
        cur=cur->link;
    }
    if(cur==NULL) {
        printf("Search is unsuccesful search\n");
        return first;
    }
    pre->link=cur->link;
    return first;
}

//Searching a node[Employee]
emp* search(char name[],emp *first){
    emp *temp=first;
    while(temp!=NULL){
        if(!(strcmp(name,temp->name))){
            return temp;
        }
        temp=temp->link;
    }
    return NULL;
}

//Sort the entire employee list
void sort(int choice,emp *first){
    emp *temp=NULL,*next=NULL;
    float e,s;
    char n[30];
    switch(choice){
        case 1://sorting based on salary
                for(temp=first;temp!=NULL;temp=temp->link){
                   for(next=temp->link;next!=NULL;next=next->link){ 
                        if(next->salary < temp->salary){
                            s=temp->salary;
                            temp->salary=next->salary;
                            next->salary=s;
                            
                            e=temp->experience;
                            temp->experience=next->experience;
                            next->experience=e;
                            
                            strcpy(n,temp->name);
                            strcpy(temp->name,next->name);
                            strcpy(next->name,n);
                        }
                    }
                }
                printf("Sorting is completed\n");
                break;
        case 2://sorting based on experience
                for(temp=first;temp!=NULL;temp=temp->link){
                   for(next=temp->link;next!=NULL;next=next->link){ 
                        if(next->experience < temp->experience){
                            e=temp->experience;
                            temp->experience=next->experience;
                            next->experience=e;
                            
                            s=temp->salary;
                            temp->salary=next->salary;
                            next->salary=s;
                            
                            strcpy(n,temp->name);
                            strcpy(temp->name,next->name);
                            strcpy(next->name,n);
                        }
                    }
                }
                printf("Sorting is completed\n");
                break;
    }
    return;
}

//Tax status of an employee
//Assuming the total salary of the employee is less than Rs.1000000
void tax(char name[],emp *first){
    emp* loc=NULL;
    loc=search(name,first);
    if(loc==NULL){
        printf("Employee deatils not found\n");
        return;
    }
    float salary;
    salary=(loc->salary)*12;
    if(salary < 750000){
        printf("Please go to new tax regime so that the payable tax will be Rs.0\n");
        return;
    }
    float taxablesalary,annded;
    printf("Enter the annual deduction amount\n");
    scanf("%f",&annded);
    taxablesalary=salary-annded;
    float oldtax=0,newtax=0;
    //according to the old tax regime
    if(taxablesalary>=250000 && taxablesalary<500000 )
        oldtax=oldtax + (5*taxablesalary/100);
    else if(taxablesalary>=500000 && taxablesalary<750000 )
        oldtax=oldtax + (5*(250000)/100) + (20*(taxablesalary-500000)/100);
    else if(taxablesalary>=750000 && taxablesalary<1000000 )
        oldtax=oldtax + (5*(250000)/100) + (20*(250000)/100) + (20*(taxablesalary-750000)/100);
    //according to the new tax regime
    newtax=newtax + (5*(250000)/100) + (10*(250000)/100) + (15*(salary-750000)/100);
    //checking in which tax scheme the payable amount is greater
    printf("According to old tax regime, tax to be paid is Rs.%.2f\n",oldtax);
    printf("According to new tax regime, tax to be paid is Rs.%.2f\n",newtax);
    if(oldtax>newtax)
        printf("Please go to the new tax regime inorder to reduce the payable tax amount by Rs.%.2f\n",(oldtax-newtax));
    else
        printf("Remain in the old tax regime itself to reduce the payable tax amount by Rs.%.2f\n",(newtax-oldtax));
    return;
}
//Displaying the details of the employees
emp* display(emp* first) {
    emp *temp=NULL;
    int i=1;
    temp=first;
    printf("The details of the employees are:\n");
    while(temp!=NULL) {
        printf("%d. Name: %s\tSalary: Rs.%f\tExperience: %.2f years\n",i++,(temp->name),(temp->salary),(temp->experience));
        temp=temp->link;
    }
    free(temp);
    return first;
}




