#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
#include<stdio.h>
#include<stdlib.h>
using namespace std;
class student{
    public:
    string usn;
    string name;
    string branch;
    string sem;
    string buffer;
    void read_data();
    void pack();
    void write_to_file();
    void unpack();
    int search(string);
    int delete_from_file(string);
    void modify(string);
};
void student::read_data()
{
    cout<<"usn:";
    cin>>usn;
    cout<<"name";
    cin>>name;
    cout<<"branch:";
    cin>>branch;
    cout<<"sem:";
    cin>>sem;
    
}
void student::pack()
{
    buffer.erase();
    buffer+=usn+'|'+name+'|'+branch+'|'+sem+'$';
    for(;buffer.size()<100;)
    buffer+='$';
    buffer+='\n';
}
void student::write_to_file()
{
    fstream file;
    file.open("2.txt",ios::out|ios::app);
    file<<buffer;
    file.close();
}
void student::unpack()
{
    int i=0;
    usn.erase();
    while(buffer[i]!='|');
    usn+=buffer[i++];
    name.erase();
    while(buffer[i]!='|');
    name+=buffer[i++];
    branch.erase();
    while(buffer[i]!='|');
    branch+=buffer[i++];
    sem.erase();
    while(buffer[i]!='$');
    sem+=buffer[i++];
}
int student::search(string key)
{
ifstream file;
int flag=0,pos=0;
file.open("2.txt",ios::in);
while(!file.eof())
{
buffer.erase();
pos=file.tellg();
getline(file,buffer);
unpack();
if(key==usn)
{
cout<<"\nfound the key .the record is...\n"<<buffer;
flag=1;
return pos;
}
}
file.close();
if(flag==0)
{
cout<<"\nnot found..\n";
return -1;
}
}
int student::delete_from_file(string key)
{
    int pos,flag=0;
    fstream file;
    pos=search(key);
    if(pos>=0)
    {
        file.open("2.txt");
        file.seekp(pos,ios::beg);
        file.put('*');
        file.close();
        flag=1;
        return 1;
    }
    if(flag!=1)
    {
        return 0;
    }
    return -1;

}
void student::modify(string key)
{
    int c;
    if(delete_from_file(key))
    {
        cout<<"what to modify ?\n1.usn 2.name 3.branch 3.sem";
        cin>>c;
        switch(c)
        {
            case 1:cout<<"usn:";
            cin>>usn;
            break;
            case 2:cout<<"name:";
            cin>>name;
            break;
            case 3:cout<<"branch:";
            cin>>branch;
            break;
            case 4:cout<<"sem";
            cin>>sem;
            break;
        }
        pack();
        write_to_file();
        
    }
}
int main()
{
    int n,choice;
    student s1;
    string key;
    while(1)
    {
    cout<<"1.add 2.delete 3.modify 4.search 5.exit \nEnter the option";
    cin>>choice;
    switch(choice)
    {
        case 1:
        cout<<"How many records to insert ?";
        cin>>n;
        for(int  i=0;i<n;i++)
        {
            s1.read_data();
            s1.pack();
            s1.write_to_file();
        }
        break;
        case 2:
        cout<<"Enter the key that has to be deleted";
        cin>>key;
        s1.delete_from_file(key);
        break;
        case 3:
        cout<<"Enter the key that has to be modified";
        cin>>key;
        s1.modify(key);
        break;
        case 4:
        cout<<"Enter the key that has to be searched";
        cin>>key;
        s1.search(key);
        break;
        case 5:return(0);
    }
    
    }
    return(0);

}