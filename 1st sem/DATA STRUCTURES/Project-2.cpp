// Project 2 - Galang, Alliah & Salanatin, Nathaly

#include <iostream>
#include <fstream>
#include <unordered_map>
#include <queue>
#include <time.h>
#include <conio.h>
#include <windows.h>
#include <iomanip>

using namespace std;

struct Node {
    char c;
    int freq;
    Node *left, *right;
    Node(char c, int freq) : c(c), freq(freq), left(nullptr), right(nullptr) {}
    Node(char c, int freq, Node* left, Node* right) : c(c), freq(freq), left(left), right(right) {}
};

struct Compare {
    bool operator()(const Node* l, const Node* r) {
        return l->freq > r->freq;
    }
};

class Algorithm {
    public:
        void start(string file);
        void buildHuffmanTree(unordered_map<char, int>& charFrequencies, Node*& root);
        void buildEncodingMap(Node* root, unordered_map<char, string>& encodingMap, string code);
        void compress(ifstream& inputFile, ofstream& outputFile, unordered_map<char, string>& encodingMap);
        void decompress(ifstream& inputFile, ofstream& outputFile, Node* root);
};

class Display {
    public:
        void inputFile_Menu();
        void loading_bar();
        void file_content(string filename);
};

HANDLE console_color = GetStdHandle(STD_OUTPUT_HANDLE);

void delay(int milliseconds);
void gotoxy(int x,int y);
void ShowConsoleCursor(bool showFlag);

int main()
{
    Algorithm algo; Display dp;

    string mainMenu[2] = {"   Compress   ", "     Exit   "};
    int pointer = 0;
    const char ENTER = 13;
    char ch = ' ';

    while (true) {
        system("cls");
        ShowConsoleCursor(false);
        SetConsoleTextAttribute(console_color, 14);
        gotoxy(78, 12);  cout << "M A I N  M E N U";
        SetConsoleTextAttribute(console_color, 8);
        gotoxy(75, 19); cout << "Use Up or Down Arrow Keys";
        gotoxy(75, 20); cout << "to Navigate through Menu";

        for (int i=0; i < 2; ++i) {
            if(i==pointer) {
                gotoxy(79, 14+i);
                SetConsoleTextAttribute(console_color, 12);
                cout << mainMenu[i] << endl;
            }
            else {
                gotoxy(79, 14+i);
                SetConsoleTextAttribute(console_color, 7);
                cout << mainMenu[i] << endl;
            }
            SetConsoleTextAttribute(console_color, 7);
        }

        while (true) {
            if (GetAsyncKeyState(VK_UP) != 0) {
                delay(100);
                --pointer;
                if(pointer == -1){
                    pointer = 1;
                }
                break;
            }
            else if (GetAsyncKeyState(VK_DOWN) != 0) {
                delay(100);
                ++pointer;
                if(pointer == 2){
                    pointer = 0;
                }
                break;
            }
            else if(ch = getch() == ENTER) {
                switch(pointer) {
                    case 0:
                    {
                        ShowConsoleCursor(true);
                        dp.inputFile_Menu();
                        break;
                    }
                    case 1:
                    {
                        ShowConsoleCursor(false);
                        exit(0);
                    }
                }
                break;
            }
        }
    }
}

void Algorithm::buildHuffmanTree(unordered_map<char, int>& charFrequencies, Node*& root)
{
    priority_queue<Node*, vector<Node*>, Compare> pq;

    for (auto pair : charFrequencies) {
        pq.push(new Node(pair.first, pair.second));
    }

    while (pq.size() > 1) {
        Node* left = pq.top();
        pq.pop();
        Node* right = pq.top();
        pq.pop();
        int sum = left->freq + right->freq;
        Node* node = new Node('\0', sum, left, right);
        pq.push(node);
    }

    root = pq.top();
}

void Algorithm::buildEncodingMap(Node* root, unordered_map<char, string>& encodingMap, string code)
{
    if (!root)
        return;
    if (root->c != '\0') {
        encodingMap[root->c] = code;
    }
    buildEncodingMap(root->right, encodingMap, code + "1");
    buildEncodingMap(root->left, encodingMap, code + "0");
}

void Algorithm::compress(ifstream& inputFile, ofstream& outputFile, unordered_map<char, string>& encodingMap)
{
    char c;
    while (inputFile.get(c)) {
        outputFile << encodingMap[c];
    }
}

void Algorithm::decompress(ifstream& inputFile, ofstream& outputFile, Node* root)
{
    Node* curr = root;
    char c;
    while (inputFile.get(c)) {
        if (c == '0') {
            curr = curr->left;
        } else {
            curr = curr->right;
        }
        if (curr->c != '\0') {
            outputFile << curr->c;
            curr = root;
        }
    }
}

void Algorithm::start(string file)
{
    Algorithm algo; Display dp;

    unordered_map<char, int> charFrequencies;

    string inputFilename = file;
    string outputFilename = "compressed.txt";

    ifstream inputFile(inputFilename, ios::binary);
    ofstream outputFile(outputFilename, ios::binary);


    dp.loading_bar();

    char c;
    int size = 0;
    while (inputFile.get(c)) {
        charFrequencies[c]++;
        size++;
    }

    Node* root;
    algo.buildHuffmanTree(charFrequencies, root);

    unordered_map<char, string> encodingMap;
    algo.buildEncodingMap(root, encodingMap, "");

    inputFile.clear();
    inputFile.seekg(0, ios::beg);

    algo.compress(inputFile, outputFile, encodingMap);

    inputFile.close();
    outputFile.close();

    string newInputFilename = outputFilename;
    string newOutputFilename = "decompressed.txt";

    inputFile.open(newInputFilename, ios::binary);
    outputFile.open(newOutputFilename, ios::binary);

    algo.decompress(inputFile, outputFile, root);
    inputFile.close();
    outputFile.close();
}

void Display::inputFile_Menu()
{
    Algorithm algo;
    while (true) {
        string filename;
        system("cls");
        SetConsoleTextAttribute(console_color, 14);
        gotoxy(70, 12); cout << "-------- C O M P R E S S  F I L E --------";
        SetConsoleTextAttribute(console_color, 8);
        gotoxy(87, 13); cout << "<input>";
        SetConsoleTextAttribute(console_color, 9);
        gotoxy(80, 15); cout << "File Name: ";
        SetConsoleTextAttribute(console_color, 3);
        cin >> filename;

        ifstream fp(filename, ios::in);
        if (fp.fail()) {
            system("cls");
            cout << "File error.";
            Sleep(1500);
            continue;
        }
        else {
            fp.close();
            algo.start(filename);
            file_content(filename);
            break;
        }
    }
}

void Display::loading_bar()
{
    printf("\e[?25l");

    SetConsoleCP(437);
    SetConsoleOutputCP(437);
    int bar1 = 177, bar2 = 219;
    system("cls");
    SetConsoleTextAttribute(console_color, 7);
    gotoxy(76, 16);
    cout << "        Compressing...";
    SetConsoleTextAttribute(console_color, 8);
    cout << "\n\n\t\t\t\t\t\t\t\t";
    for (int i = 0; i < 50; i++)
    {
        cout << (char)bar2;
        Sleep(100);
    }
    cout << endl;
}

void Display::file_content(string filename)
{
    system("cls");
    SetConsoleTextAttribute(console_color, 14);
    gotoxy(50, 1); cout << "----------------------------------------- F I L E  C O N T E N T ----------------------------------------" << endl;
    SetConsoleTextAttribute(console_color, 4);
    ifstream fp(filename);
    string line;
    int pos = 0;
    while (getline(fp, line)) {
        char ch = fp.get();
        gotoxy(55, 3+pos);
        //cout << ch;
        cout << line << endl;
        Sleep(50);
        pos++;
    }
    fp.close();
    SetConsoleTextAttribute(console_color, 8);
    gotoxy(90, 12+pos); system("pause");
}

void delay(int milliseconds)
{
    clock_t start_time = clock();
    while (clock() < start_time + milliseconds);
}

void gotoxy(int x,int y)
{
    COORD coord = {0,0};
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
}

void ShowConsoleCursor(bool showFlag)
{
    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_CURSOR_INFO     cursorInfo;

    GetConsoleCursorInfo(out, &cursorInfo);
    cursorInfo.bVisible = showFlag;
    SetConsoleCursorInfo(out, &cursorInfo);
}
