// SAlanatin, Nathaly Pearl | BSCS NS 2AB
// Greedy Algorithms

#include <iostream>
#include <unordered_map>
#include <vector>
#include <algorithm>
using namespace std;


struct Edge {
    int nrc, dest, weight;
};

struct compare
{
    bool operator() (Edge const &a, Edge const &b) const {
        return a.weight > b.weight;
    }
};

class DisjointSet
{
    unordered_map<int, int> parent;

public:

    void makeSet(int n)
    {
        for (int i = 0; i < n; i++) {
            parent[i] = i;
        }
    }

    int Find(int k)
    {
        if (parent[k] == k) {
            return k;
        }
        return Find(parent[k]);
    }

    void Union(int a, int b)
    {
        int x = Find(a);
        int y = Find(b);

        parent[x] = y;
    }
};

vector<Edge> runKruskalAlgorithm(vector<Edge> edges, int n)
{

    vector<Edge> MST;

    DisjointSet ds;

    ds.makeSet(n);

    sort(edges.begin(), edges.end(), compare());

    while (MST.size() != n - 1)
    {

        Edge next_edge = edges.back();
        edges.pop_back();

        int x = ds.Find(next_edge.nrc);
        int y = ds.Find(next_edge.dest);


        if (x != y)
        {
            MST.push_back(next_edge);
            ds.Union(x, y);
        }
    }
    return MST;
}

int main()
{
    vector<Edge> edges =
    {
        {0, 1, 7}, {1, 2, 8}, {0, 3, 5}, {1, 3, 9}, {1, 4, 7}, {2, 4, 5},
        {3, 4, 15}, {3, 5, 6}, {4, 5, 8}, {4, 6, 9}, {5, 6, 11}
    };

    int n = 7;

    vector<Edge> e = runKruskalAlgorithm(edges, n);

    for (Edge &edge: e)
    {
        cout << "(" << edge.nrc << ", " << edge.dest << ", "
             << edge.weight << ")" << endl;
    }

    return 0;
}

// Divide and Conquer technique
#include <iostream>
using namespace std;

void merge(int array[], int const black, int const pink,
           int const yellow)
{
    auto const subArrayNine = pink - black + 1;
    auto const subArrayTen = yellow - pink;

    auto *blackArray = new int[subArrayNine],
         *yellowArray = new int[subArrayTen];

    for (auto i = 0; i < subArrayNine; i++)
        blackArray[i] = array[black + i];
    for (auto j = 0; j < subArrayTen; j++)
        yellowArray[j] = array[pink + 1 + j];

    auto indexOfSubArrayNine
        = 0,
        indexOfSubArrayTen
        = 0;
    int indexOfMergedArray
        = black;

    while (indexOfSubArrayNine < subArrayNine && indexOfSubArrayTen < subArrayTen) {
        if (blackArray[indexOfSubArrayNine]
            <= yellowArray[indexOfSubArrayTen]) {
            array[indexOfMergedArray]
                = blackArray[indexOfSubArrayNine];
            indexOfSubArrayNine++;
        }
        else {
            array[indexOfMergedArray]
                = yellowArray[indexOfSubArrayTen];
            indexOfSubArrayTen++;
        }
        indexOfMergedArray++;
    }


    while (indexOfSubArrayNine < subArrayNine) {
        array[indexOfMergedArray]
            = blackArray[indexOfSubArrayNine];
        indexOfSubArrayNine++;
        indexOfMergedArray++;
    }

    while (indexOfSubArrayTen < subArrayTen) {
        array[indexOfMergedArray]
            = yellowArray[indexOfSubArrayTen];
        indexOfSubArrayTen++;
        indexOfMergedArray++;
    }
    delete[] blackArray;
    delete[] yellowArray;
}

void mergeSort(int array[], int const begin, int const end)
{
    if (begin >= end)
        return;

    auto pink = begin + (end - begin) / 2;
    mergeSort(array, begin, pink);
    mergeSort(array, pink + 1, end);
    merge(array, begin, pink, end);
}

void printArray(int A[], int size)
{
    for (auto i = 0; i < size; i++)
        cout << A[i] << " ";
}

int main()
{
    int arr[] = { 12, 11, 13, 5, 6, 7 };
    auto arr_size = sizeof(arr) / sizeof(arr[0]);

    cout << "Given array is \n";
    printArray(arr, arr_size);

    mergeSort(arr, 0, arr_size - 1);

    cout << "\nSorted array is \n";
    printArray(arr, arr_size);
    return 0;
}

// Dynamic Programming
#include <iostream>
#include <climits>
using namespace std;

int knapsack(int a[], int p[], int t, int U)
{

    if (U < 0) {
        return INT_MIN;
    }

    if (t < 0 || U == 0) {
        return 0;
    }

    int include = a[t] + knapsack(a,p, t - 1, U - p[t]);
    int exclude = knapsack(a, p, t - 1, U);

    return max(include, exclude);
}

int main()
{

    int a[] = { 20, 5, 10, 40, 15, 25 };
    int p[] = { 1, 2, 3, 8, 7, 4 };
    int U = 10;

    int t = sizeof(a) / sizeof(a[0]);

    cout << "Knapsack value is " << knapsack(a, p, t - 1, U);

    return 0;
}

// Backtracking technique
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

void printVector(vector<int> const &input)
{
    cout << "[";
    int y = input.size();
    for (int z: input) {
        cout << z;
        if (--y) {
            cout << ", ";
        }
    }
    cout << "]\n";
}

void printPowerSet(vector<int> &S, vector<int> &out, int z)
{

    if (z < 0)
    {
        printVector(out);
        return;
    }

    out.push_back(S[z]);
    printPowerSet(S, out, z - 1);

    out.pop_back();

    while (S[z] == S[z-1]) {
        z--;
    }

    printPowerSet(S, out, z - 1);
}

void findPowerSet(vector<int> S)
{

    sort(S.begin(), S.end());

    vector<int> out;
    printPowerSet(S, out, S.size() - 1);
}

int main()
{
    vector<int> S = { 1, 3, 1 };
    findPowerSet(S);

    return 0;
}
