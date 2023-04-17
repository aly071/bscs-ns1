//Nathaly Pearl Salanatin BSCS-NS 2AB
#include <iostream>
#include <iomanip>
#include <fstream>
#include <windows.h>
using namespace std;

#define MAX 5

typedef struct StudentRecord {
    string name;
    int quiz[3];
} StudentRec;

typedef struct List {
    StudentRec DATA[MAX];
    int last;
} LIST;

class Algorithm {
    private:
        LIST l;
        int locateName(string n);
        float getAve(int q1, int q2, int q3);
        bool isFull();
        bool isEmpty();

    public:
        void makeNull();
        void addRecord(StudentRec student);
        void deleteRecord(string n);
        void displayRecord();
        void updateRecord(string n);
        void save();
        void retrieve();
};

// Display
void gotoxy(int x, int y);
int updateMenu();
int mainMenu();


int main()
{
    Algorithm algo;
    StudentRec rec;

    algo.makeNull();
    algo.retrieve();

    while(true) {
        int ch = mainMenu();
        switch(ch) {
            case 1:
                system("cls");
                gotoxy(40, 5); cout << "Input Name: "; cin.ignore(); getline(cin, rec.name);
                gotoxy(40, 6); cout << "Add Quiz 1: "; cin >> rec.quiz[0];
                gotoxy(40, 7); cout << "Add Quiz 2: "; cin >> rec.quiz[1];
                gotoxy(40, 8); cout << "Add Quiz 3: "; cin >> rec.quiz[2];
                algo.addRecord(rec);
                break;

            case 2:
                system("cls");
                gotoxy(40, 5); cout << "Input Name: "; cin.ignore(); getline(cin, rec.name);
                algo.updateRecord(rec.name);
                break;

            case 3:
                system("cls");
                gotoxy(40, 5); cout << "Delete Name: "; cin.ignore(); getline(cin, rec.name);
                algo.deleteRecord(rec.name);
                break;

            case 4:
                algo.displayRecord();
                break;

            case 5:
                algo.save();
                exit(0);

            default:
                gotoxy(40, 5); cout << "Invalid imputed number!" << endl;
                gotoxy(40, 6); system("pause");
        }
    }

}

void Algorithm::makeNull()
{
    l.last = -1;
}
void Algorithm::addRecord(StudentRec student)
{
    int i, p;
    if (isFull()) {
        cout << "List is full.\n";
        system("pause");
    }
    else {
        l.last++;
        l.DATA[l.last] = student;
    }
}
void Algorithm::deleteRecord(string n)
{

    if (isEmpty()) {
        cout << "List is empty.\n";
        system("pause");
    }
    else {
        int i, p;
        p = locateName(n);
        if (p == -1) {
            cout << "Not found.\n";
            system("pause");
        }
        else {
            for (i=p; i<l.last; i++)
                l.DATA[i] = l.DATA[i+1];
            l.last--;
        }
    }
}
void Algorithm::displayRecord()
{
    int i;
    float ave;
    system("cls");
    gotoxy(30, 5);  cout << "Name";
    gotoxy(50, 5);  cout << "Quiz 1";
    gotoxy(60, 5);  cout << "Quiz 2";
    gotoxy(70, 5);  cout << "Quiz 3";
    gotoxy(80, 5);  cout << "Averaged";
    gotoxy(90, 5);  cout << "Remarks";
    for(i=0; i<=l.last; i++) {
        ave = getAve(l.DATA[i].quiz[0], l.DATA[i].quiz[1], l.DATA[i].quiz[2]);
        cout << setprecision(2) << fixed;
        gotoxy(25, 7+i);  cout << i+1;
        gotoxy(30, 7+i);  cout << l.DATA[i].name;
        gotoxy(50, 7+i);  cout << l.DATA[i].quiz[0];
        gotoxy(60, 7+i);  cout << l.DATA[i].quiz[1];
        gotoxy(70, 7+i);  cout << l.DATA[i].quiz[2];
        gotoxy(80, 7+i);  cout << ave;
        string remarks = (ave>=75)? "PASSED":"FAILED";
        gotoxy(90, 7+i); cout << remarks;
    }
    gotoxy(35, 7+i);    system("pause");
}
void Algorithm::updateRecord(string n)
{

}
void Algorithm::save()
{
    fstream fp;
    fp.open("student_record.txt", ios::out);
    if (!fp) {
        gotoxy(40, 5); cout << "File not found." << endl;
        gotoxy(40, 6); system("pause");
    }
    else {
        for (int i=0; i<=l.last; i++){
            fp << l.DATA[i].name << endl;
            fp << l.DATA[i].quiz[0] << " " << l.DATA[i].quiz[1] << " " << l.DATA[i].quiz[2] << endl;
        }
        fp.close();
    }
}
void Algorithm::retrieve()
{
    fstream fp;
    StudentRec student;
    fp.open("student_record.txt", ios::in);
    if (!fp) {
        gotoxy(40, 5); cout << "File not found." << endl;
        gotoxy(40, 6); system("pause");
    }
    else {
        string name;
        int q1, q2, q3;
        while(true) {
            getline(fp, student.name);
            fp >> student.quiz[0] >> student.quiz[1] >> student.quiz[2];
            fp.ignore();
            if(!fp.eof())
                addRecord(student);
            else
                break;
        }
        fp.close();
    }
}


int Algorithm::locateName(string n)
{
    int i;
    for (i=0; i<l.last; i++)
        if (l.DATA[i].name == n)
            return i;
    return -1;
}
float Algorithm::getAve(int q1, int q2, int q3)
{
    float ave;
    ave = (q1 + q2 + q3)/3.00;
    return ave;
}
bool Algorithm::isFull()
{
    return(l.last==MAX-1);
}
bool Algorithm::isEmpty()
{
    return(l.last==-1);
}

// Display
int mainMenu()
{
    int op;
    system("cls");
    gotoxy(40, 5); cout << "MENU\n";
    gotoxy(40, 6); cout << "1. Add Record\n";
    gotoxy(40, 7); cout << "2. Update Record\n";
    gotoxy(40, 8); cout << "3. Delete Record\n";
    gotoxy(40, 9); cout << "4. Display\n";
    gotoxy(40, 10); cout << "5. Save & Exit\n";
    gotoxy(40, 12); cout << "Select(1-4): ";
    cin >> op;
    return op;
}
int updateMenu()
{
    Algorithm x;
    int op;
    system("cls");
    x.displayRecord();
    gotoxy(120, 5); cout << "Update Menu\n";
    gotoxy(120, 7); cout << "1. Quiz 1\n";
    gotoxy(120, 8); cout << "2. Quiz 2\n";
    gotoxy(120, 9); cout << "3. Quiz 3\n";
    gotoxy(120, 10); cout << "4. Exit\n";
    gotoxy(120, 11); cout << "Select(1-4): ";
    cin >> op;
    return op;
}
void gotoxy(int x, int y)
{
    COORD coord = {0,0};
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
}
