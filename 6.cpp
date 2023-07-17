#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <stdlib.h>
using namespace std;

class student
{
public:
    string usn;
    string name;
    string branch;
    string sem;
    string buffer;
    string usn_list[100];
    string name_list[100];  // Secondary key index
    int Address_list[100];
    int count;

    void read_data();
    void pack();
    void write_to_file();
    void create_index();
    void remove(string);
    void search(string);
    int search_index(string, bool);
    string extract_name();
    void sort_index();
};

void student::read_data()
{
    cout << "usn:";
    cin >> usn;
    cout << "name:";
    cin >> name;
    cout << "branch:";
    cin >> branch;
    cout << "semester:";
    cin >> sem;
}

void student::pack()
{
    string temp;
    buffer.erase();
    buffer += usn + "|" + name + "|" + branch + "|" + sem + "$" + "\n";
}

void student::write_to_file()
{
    int pos;
    fstream file;
    file.open("6.txt", ios::out | ios::app);
    pos = file.tellp();
    file << buffer;
    file.close();
    usn_list[++count] = usn;
    name_list[count] = name;  // Update secondary key index
    Address_list[count] = pos;
    sort_index();
}

string student::extract_name()// ,dn
{
    string nmae;
    int i = 0;
    name.erase();
    while (buffer[i] != '|')
        name += buffer[i++];
    return nmae;
}

void student::create_index()
{
    fstream file;
    int pos;
    string usn, name;
    count = -1;
    file.open("6.txt", ios::in);
    while (!file.eof())
    {
        pos = file.tellg();
        buffer.erase();
        getline(file, buffer);
        if (buffer[0] != '*')
        {
            if (buffer.empty())
                break;
            name = extract_name();
            name = name_list[++count] = extract_name();  // Update secondary key index
            usn_list[count] = usn;
            Address_list[count] = pos;
        }
    }
    file.close();
    sort_index();
    buffer.erase();
}

void student::sort_index()
{
    int i, j, temp_Address;
    string temp_usn, temp_name;
    for (int i = 0; i <= count; i++)
    {
        for (int j = i + 1; j <= count; j++)
        {
            if (usn_list[i] > usn_list[j])
            {
                temp_usn = usn_list[i];
                usn_list[i] = usn_list[j];
                usn_list[j] = temp_usn;

                temp_name = name_list[i];  // Sort secondary key index accordingly
                name_list[i] = name_list[j];
                name_list[j] = temp_name;

                temp_Address = Address_list[i];
                Address_list[i] = Address_list[j];
                Address_list[j] = temp_Address;
            }
        }
    }
    for (i = 0; i <= count; i++)
    {
        cout << usn_list[i] << "\t" << name_list[i] << "\t" << Address_list[i] << "\n";
    }
}

int student::search_index(string key, bool byName)
{
    int low = 0, high = count, mid = 0, flag = 0, pos;
    while (low <= high)
    {
        mid = (low + high) / 2;
        if (byName)
        {
            if (name_list[mid] == key)
            {
                flag = 1;
                break;
            }
            if (name_list[mid] > key)
                high = mid - 1;
            if (name_list[mid] < key)
                low = mid + 1;
        }
        else
        {
            if (usn_list[mid] == key)
            {
                flag = 1;
                break;
            }
            if (usn_list[mid] > key)
                high = mid - 1;
            if (usn_list[mid] < key)
                low = mid + 1;
        }
    }
    if (flag)
        return mid;
    else
        return -1;
}

void student::search(string key)
{
    int pos = 0, address;
    fstream file;
    buffer.erase();

    pos = search_index(key, true);
    if (pos == -1)
    {
        cout << endl << "record not found" << endl;
        return;
    }

    cout << "Records found:\n";
    while (pos >= 0 && name_list[pos] == key)
    {
        file.open("6.txt");
        address = Address_list[pos];
        file.seekp(address, ios::beg);
        getline(file, buffer);
        cout << buffer << endl;
        file.close();
        pos++;
    }
}

void student::remove(string key)
{
    int pos = 0, i, address;
    fstream file;
    pos = search_index(key, true);
    if (pos == -1)
    {
        cout << "record not found" << endl;
        return;
    }
    
    cout << "Records deleted: " << endl;
    while (pos >= 0 && name_list[pos] == key)
    {
        file.open("6.txt", ios::out | ios::in);
        address = Address_list[pos];
        file.seekp(address, ios::beg);
        file.put('*');
        file.close();
        cout << usn_list[pos] << "\t" << name_list[pos] << "\t" << Address_list[pos] << endl;
        for (i = pos; i < count; i++)
        {
            usn_list[i] = usn_list[i + 1];
            name_list[i] = name_list[i + 1];
            Address_list[i] = Address_list[i + 1];
        }
        count--;
        pos++;
    }
}

int main()
{
    int choice, count, i;
    string key;
    student s1;
    s1.create_index();
    while (1)
    {
        cout << "\nMain Menu\n--------\n1.Add \n2.Search by name \n3.Delete by name\n4.Exit\n---------\n";
        cout << "Enter the choice:";
        cin >> choice;
        switch (choice)
        {
        case 1:
            cout << "\nhow many records to insert\n";
            cin >> count;
            for (i = 0; i < count; i++)
            {
                cout << "data\n";
                s1.read_data();
                s1.pack();
                s1.write_to_file();
            }
            break;
        case 2:
            cout << "\nEnter the name to search\n";
            cin >> key;
            s1.search(key);
            break;
        case 3:
            cout << "\n\nEnter the name to delete\n";
            cin >> key;
            s1.remove(key);
            break;
        case 4:
            return 0;
        default:
            cout << "\n\nWrong choice\n";
            break;
        }
    }
}
