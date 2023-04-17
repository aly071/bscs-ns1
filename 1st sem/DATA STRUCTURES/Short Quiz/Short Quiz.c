// Salanatin, Nathaly Pearl | BSCS NS 1B

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 5

typedef struct records
{
    char name[31];
    int quizzes[3];
} REC;

typedef struct list
{
    REC studs[MAX];
    int last;
}LIST;

LIST L;

// function declarations

void makenull();
void add(REC input);
void del(char name[31]);
void display();
int locate(char name[31]);
float average(int q1, int q2, int q3);
int isempty();
int isfull();
int menu();

int main()
{
    REC stu_rec;
    makenull();
    while (1)//infinite loop -> always true
    {
    switch(menu())
    {
        case 1 : system("cls");printf("Input name : ");scanf("%s", stu_rec.name);printf("Input Quiz 1: "); scanf("%d", &stu_rec.quizzes[0]);
                     printf("Input Quiz 2: "); scanf("%d", &stu_rec.quizzes[1]);printf("Input Quiz 3: "); scanf("%d", &stu_rec.quizzes[2]);
                     add(stu_rec); break;

        case 2 : system("cls");printf("Input name : ");scanf("%s", stu_rec.name); del(stu_rec.name); break;

        case 3 : system("cls"); display(); break;

        case 4 : exit(0);

        default: printf("Invalid Input\n");system("pause");
    }
    }
}

int menu()
{
    int ch;
    system("cls");
    printf("Menu\n");
    printf("1. Insert\n");
    printf("2. Delete\n");
    printf("3. Display\n");
    printf("4. Exit\n");
    printf("Select (1-4): ");
    scanf("%d",&ch);
    return(ch);
}

void makenull()
{
     L.last = -1;
}

int isempty()
{
    return(L.last==-1);
}

int isfull()
{
   return(L.last==MAX-1);
}

float average(int q1, int q2, int q3)
{
    float ave;
    ave = (q1 + q2 + q3) / 3.0;
    return ave;
}

int locate (char name[31])
{
    int i;
    for (i=0;i<=L.last;i++)
        if (strcmp(L.studs[i].name,name)==0)
            return i;
    return -1;
}

void add(REC input)
{
    int i,p;
    if (isfull()){
    printf("List is full.\n");
    system("pause");
    }
    else {
        L.last++;
        L.studs[L.last] = input;
    }
}

void del(char name[31])
{
    int p,i;
    if (isempty())
    {
        printf("List is empty.\n");
        system("pause");
    }
    else
    {
        p=locate(name);
        if (p==-1)
        {
            printf("Not found.\n");
            system("pause");
        }
        else
        {
            for (i=p;i<L.last;i++)
                L.studs[i]=L.studs[i+1];
            L.last--;
        }
    }
}

void display()
{
    int i;
    float ave;
    printf("   NAME\t\tQ1\tQ2\tQ3\tAVE\tRemarks\n"); // header

    for (i =0; i <= L.last; i++)
    {
        ave = average(L.studs[i].quizzes[0], L.studs[i].quizzes[1], L.studs[i].quizzes[2]);
        printf("%d.)%s\t\t%d\t%d\t%d\t%5.2f\t%s\t\n", i+1, L.studs[i].name, L.studs[i].quizzes[0], L.studs[i].quizzes[1], L.studs[i].quizzes[2] , ave, ave >= 75 ? "Passed" : "Failed");
    }
    system("pause");
}
