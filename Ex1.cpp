#include <iostream>
#include <vector>
#include <cstring>
#include <fstream>
#include <chrono>
#include <algorithm>
using namespace std;

typedef unsigned long ul;

/// Hashing
ul djb2hash(unsigned char *str){
    ul hash = 5381;
    int c;
    while(c = *str++)
        hash = ((hash << 5) + hash) + c;
    return hash; 
}


bool isPrime(ul num)
{
    if (num < 2)
        return false;
    for (int i = 2; i * i <= num; i++)
        if (num % i == 0)
            return false;
    return true;
}

ul nextPrime(ul N)
{
    ul res = N + 1;
    while (1)
    {
        if (isPrime(res))
            return res;
        res++;
    }
}

// Node HashTable - Chaining 
struct NodeHash{
    string data;
    NodeHash *next;
};

struct ChainingApproachHash
{
    vector<NodeHash*> table;
    ul tableSize;

    // Constructor
    ChainingApproachHash(ul size) : table(size, NULL), tableSize(size) {}

    ul Hash(const string name)
    {
        return djb2hash((unsigned char *)name.c_str()) % tableSize;
    }

    // Insert function
    void insert(const string name)
    {
        ul index = Hash(name);
        NodeHash* newNode = new NodeHash;
        newNode->data = name;
        newNode->next = NULL;

        if (!table[index])
            table[index] = newNode;
        else 
        {
            NodeHash* tmp = table[index];
            newNode->next = tmp;
            table[index] = newNode;
        }
    }

    // Search function 
    bool search(const string name)
    {
        ul index = Hash(name);
        NodeHash* cur = table[index];
        while (cur)
        {
            if (cur->data == name)
                return true;
            cur = cur->next;
        }
        return false;
    }

};

struct LinearProbingHash
{
    vector<string> table;
    ul tableSize;

    // Constructor
    LinearProbingHash(ul size) : table(size, ""), tableSize(size) {}

    // Hash linear
    ul Hash(const string name)
    {
        return djb2hash((unsigned char *)name.c_str()) % tableSize;        
    }

    // Insert function
    void insert(const string name)
    {
        ul H = Hash(name);
        ul index = H;
        ul i = 0;
        while (table[index] != "" && i < tableSize)
        {
            if (table[index] == name)
                return;
            i++;
            index = (H + i) % tableSize;
        }
        table[index] = name;
    } 

    // Search function
    bool search(const string name)
    {
        ul H = Hash(name);
        ul index = H;
        ul i = 0;
        while (table[index] != "" && i < tableSize)
        {
            if (table[index] == name)
                return true;
            i++;
            index = (H + i) % tableSize;
        }
        return false;
    }

};

struct QuadraticProbingHash
{
    vector<string> table;
    ul tableSize;

    // Constructor
    QuadraticProbingHash(ul size) : table(size, ""), tableSize(size) {}

    // Hash linear
    ul Hash(const string name)
    {
        return djb2hash((unsigned char *)name.c_str()) % tableSize;        
    }

    // Insert function
    void insert(const string name)
    {
        ul H = Hash(name);
        ul index = H;
        ul i = 0;
        while (table[index] != "")
        {
            if (table[index] == name)
                return;
            i++;
            index = (H + i*i) % tableSize;
        }
        table[index] = name;
    } 

    // Search function
    bool search(const string name)
    {
        ul H = Hash(name);
        ul index = H;
        ul i = 0;
        while (table[index] != "")
        {
            if (table[index] == name)
                return true;
            i++;
            index = (H + i*i) % tableSize;
        }
        return false;
    }

};

struct DoubleHash
{
    vector<string> table;
    ul tableSize;

    // Constructor
    DoubleHash(ul size) : table(size, ""), tableSize(size) {}


    // Hash linear
    ul Hash_1(const string name)
    {
        return djb2hash((unsigned char *)name.c_str()) % tableSize;        
    }
    // tableSize must be Prime
    ul Hash_2(const string name)
    {
        return 1 + ((djb2hash((unsigned char *)name.c_str()) / tableSize) % (tableSize - 1));        
    }
    

    // Insert function
    void insert(const string name)
    {
        ul i = 0;
        ul H1 = Hash_1(name);
        ul H2 = Hash_2(name);
        ul index = (H1 + i*H2) % tableSize;
        
        while (table[index] != "")
        {
            if (table[index] == name)
                return;
            i++;
            index = (H1 + i*H2) % tableSize;
        }
        table[index] = name;
    } 

    // Search function
    bool search(const string name)
    {
        ul i = 0;
        ul H1 = Hash_1(name);
        ul H2 = Hash_2(name);
        ul index = (H1 + i*H2) % tableSize;

        while (table[index] != "")
        {
            if (table[index] == name)
                return true;
            i++;
            index = (H1 + i*H2) % tableSize;
        }
        return false;
    }

};

bool linearSearch(vector<string> &A, string val)
{
    for (int i = 0; i < A.size(); i++)
        if (A[i] == val)
            return true;
    return false;
}

bool binarySearch(vector<string> &A, string val)
{
    ul l = 0, r = A.size() - 1;
    ul mid;
    while (l <= r)
    {
        mid = (l + r) / 2;
        if (A[mid] == val)
            return true;
        else if (A[mid] < val)
            l = mid + 1;
        else    
            r = mid - 1;
    }
    return false;
}

void Menu()
{
    ul tableSize = 0;
    vector<string> A, B;
    string s;
    string fileName;
    cout << "Nhap ten file: ";
    cin >> fileName;
    ifstream fi;
    fi.open(fileName);

    while (getline(fi, s))
    {
        tableSize++;
    }

    tableSize = tableSize * 1.3;
    tableSize = nextPrime(tableSize);

    ChainingApproachHash CHash(tableSize);
    LinearProbingHash LHash(tableSize);
    QuadraticProbingHash QHash(tableSize);
    DoubleHash DHash(tableSize);

    fi.clear();
    fi.seekg(0);
    while (getline(fi, s))
    {
        A.push_back(s);
        B.push_back(s);
        CHash.insert(s);
        LHash.insert(s);
        QHash.insert(s);
        DHash.insert(s);
    }
    
    // Linear Search
    auto start = chrono::high_resolution_clock::now();
    
    for (int i = 0; i < A.size(); i++)
        linearSearch(A, A[i]);

    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double, milli> duration = end - start;
    cout << "Linear Search: " << duration.count() << " ms. \n";

    // Binary Search
    sort(B.begin(), B.end());
    start = chrono::high_resolution_clock::now();

    for (int i = 0; i < A.size(); i++)
        binarySearch(B, A[i]);
    
    end = chrono::high_resolution_clock::now();
    duration = end - start;
    cout << "Binary Search: " << duration.count() << " ms. \n";

    // Chaining Hash
    start = chrono::high_resolution_clock::now();

    for (int i = 0; i < A.size(); i++)
        CHash.search(A[i]);
    
    end = chrono::high_resolution_clock::now();
    duration = end - start;
    cout << "Chaining Approach Hash: " << duration.count() << " ms. \n";

    // Linear Probing Hash
    start = chrono::high_resolution_clock::now();

    for (int i = 0; i < A.size(); i++)
        LHash.search(A[i]);
    
    end = chrono::high_resolution_clock::now();
    duration = end - start;
    cout << "Linear Probing Hash: " << duration.count() << " ms. \n";

    // Quadratic Probing Hash
    start = chrono::high_resolution_clock::now();

    for (int i = 0; i < A.size(); i++)
        QHash.search(A[i]);
    
    end = chrono::high_resolution_clock::now();
    duration = end - start;
    cout << "Quadratic Probing Hash: " << duration.count() << " ms. \n";

    // Double Hashing
    start = chrono::high_resolution_clock::now();

    for (int i = 0; i < A.size(); i++)
        DHash.search(A[i]);
    
    end = chrono::high_resolution_clock::now();
    duration = end - start;
    cout << "Double Hashing: " << duration.count() << " ms. \n";

    fi.close();

}

int main()
{
    Menu();
    return 0;
}