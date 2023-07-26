#include <iostream>
#include <vector>
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

struct HashNode
{
    string key;
    string val;
};

struct LinearProbingHash
{
    vector<HashNode> table;
    ul tableSize;

    // Constructor
    LinearProbingHash(ul size) : table(size, {"", ""}), tableSize(size) {}

    ul Hash(const string name)
    {
        return djb2hash((unsigned char *)name.c_str()) % tableSize;        
    }

    // insert
    void add(string key, string val)
    {
        ul H = Hash(key);
        ul index = H;
        ul i = 0;
        while (table[index].key != "" && i < tableSize)
        {
            if (table[index].key == key)
            {
                cout << key << "'s phone number is available!\n";
                int x;
                cout << "Do you want to update? (1/0): ";
                cin >> x;
                if (x == 0)
                    return;
                else
                    update(key, val);
                return;
            }
                
            i++;
            index = (H + i) % tableSize;
        }
        table[index] = {key, val}; 
    }

    // Delete
    void Delete(string key)
    {
        ul H = Hash(key);
        ul index = H;
        ul i = 0;
        while (i < tableSize)
        {
            if (table[index].key == key)
            {
                table[index] = {"", ""}; 
                return;
            }
                
            i++;
            index = (H + i) % tableSize;
        }
        cout << "Error!!!! \n";
    }

    void update(string key, string val)
    {
        ul H = Hash(key);
        ul index = H;
        ul i = 0;
        while (i < tableSize)
        {
            if (table[index].key == key)
            {
                table[index].val = val;
                return;
            }
                
            i++;
            index = (H + i) % tableSize;
        }
        cout << "Error!!!! \n";
    }

    string find(string key)
    {
        ul H = Hash(key);
        ul index = H;
        ul i = 0;
        while (i < tableSize)
        {
            if (table[index].key == key)
            {
                return table[index].val;
            }
            i++;
            index = (H + i) % tableSize;
        }
        return "Error!!!! \n";
    }
};

void Menu(LinearProbingHash &HashTable)
{
    cout << "MENU: MONSTER'S PHONE NUMBER";
    while (1)
    {
        cout <<"\n-------------------------------\n";
        cout << "Press 1 to add: \n"
            << "Press 2 to Delete: \n"
            << "Press 3 to update: \n"
            << "Press 4 to find: \n"
            << "Press another_key to exit: \n"
            << "Your choice: ";
        int x;
        cin >> x;
        switch (x)
        {
        case 1:
        {
            string phoneNum;
            string name;
            cout << "Monster's name: ";
            cin.ignore();
            getline(cin, name);
            cout << "Monster's phone number: ";
            getline(cin, phoneNum);
            HashTable.add(name, phoneNum);
            break;
        }
        case 2:
        {
            string name;
            cout << "Monster's name: ";
            cin.ignore();
            getline(cin, name);
            HashTable.Delete(name);
            break;
        }
        case 3:
        {
            string phoneNum;
            string name;
            cout << "Monster's name: ";
            cin.ignore();
            getline(cin, name);
            cout << "Monster's phone number: ";
            getline(cin, phoneNum);
            HashTable.update(name, phoneNum);
            break;
        }
        case 4:
        {
            string name;
            cout << "Monster's name: ";
            cin.ignore();
            getline(cin, name);
            cout << name << "'s phone number: " << HashTable.find(name);
            break;      
        }
        default:
            return;
        }

    }
}

int main()
{
    LinearProbingHash HashTable(200204);
    Menu(HashTable);
    return 0;
}