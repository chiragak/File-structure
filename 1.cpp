#include<iostream> //input output operation
#include<fstream> //reading input and writing output from a file
#include<sstream> //used for string manupulation to concatenate strings
#include<stdlib.h> //exit(), instead of exit()we can also use return(0)
#include "reverse.h"
using namespace std;
int main()
{
    int choice,n;
    string rv,name,s;
    cout<<"1.From standard input\n2.From file\n3.Exit\n";
    cin>>choice;
    switch(choice)
    {
        case 1:cout<<"From standard I/O \n";
        cout<<"How many ?\n";
        cin>>n;
        for(int i=0;i<n;i++)
        {
            cout<<"Enter the string:";
            cin>>name;
            rv=rev(name);
        }
        break;

        case 2:cout<<"From standard I/O \n";
        fstream f1,f2,file;
        f1.open("str.txt",ios::in);
        f2.open("rev.txt",ios::out);
        while(!file.eof())
        {
            s.erase();
            f1>>s;
            rv.erase();
            rv=rev(s);
            f2<<rv<<"\n";
        

        } 
        cout<<"\n reverse contents copied";
        break;
        
        case 3:return (0);

    }
}