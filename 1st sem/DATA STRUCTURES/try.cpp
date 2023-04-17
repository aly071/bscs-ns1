//Link lists of integers in C++
#include <iostream>
using namespace std;
typedef struct node {
  int data;
  struct node* nxt;
}LIST;
class MyList {
private:
    LIST *L;
public:
    void makenull();
    void add(int x);
    void del(int x);
    void display();
};
void MyList::makenull(){
    L = NULL;
}
void MyList::add(int x){
LIST *p, *q, *temp;
p=q=L;

temp = new LIST;
temp->data = x;
while (p!=NULL && p->data<x){
    q=p;
    p=p->nxt;
}
if (p==L)//first element
    L=temp;
else
    q->nxt = temp;
temp->nxt = p;
}

void MyList::del (int x){
LIST *p, *q;
p=q=L;
while(p!=NULL && p->data!=x){
    q=p;
    p=p->nxt;
}
if (p==NULL){
    printf("Not found.");
    system("pause");
}
else{
    if (p==L)//if first element
       L=p->nxt;
    else
       q->nxt=p->nxt;
    delete(p);
    }
}
void MyList:: display(){
LIST *p;
int i = 1;
p=L;
system("cls");
cout <<"The list contains...\n";
while (p!=NULL){
    cout <<i++<<".) "<<p->data<<endl;

    p=p->nxt;
 }
 system("pause");
}
int menu(){
int op;
system("cls");
cout <<"Menu\n";
cout <<"1. Insert\n";
cout <<"2. Delete\n";
cout <<"3. Display\n";
cout <<"4. Exit\n";
cout <<"Select(1-4): ";
cin >> op;
return(op);

}
int main(){
int x;
MyList num;
num.makenull();//initialize the list L
while(1){
    switch(menu()){
    case 1 : system("cls");cout <<"Insert Mode\n";
             cout << "Input x: ";cin >> x;num.add(x);break;
    case 2 : system("cls");cout <<"Delete Mode\n";
             cout << "Input x: ";cin >> x;num.del(x);break;
    case 3 : num.display();break;
    case 4 : exit(0);
    default:cout << "1 to 4 only.\n";system("pause");
    }
  }
}
