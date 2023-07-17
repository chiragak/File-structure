#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
#include<stdio.h>
#include<stdlib.h>
#include "reverse.h"
using namespace std;
int main()
{
    int choice,n;
    fstream f1,f2;
    cout<<"Enter the oprtion\n 1.From standara I/O\n2.From File\n3.exit";
    cin>>choice;
    string name,s,rv;
    switch(choice)
    {
        case 1:cout<<"How many\n";
        cin>>n;
        for(int i=0;i<n;i++)
        {
            cout<<"Enter the input";
            cin>>name;
            rv=rev(name);
            cout<<rv<<"\n";
        }
        break;
        case 2:
        f1.open("str.txt",ios::in);
        f2.open("rev.txt",ios::out);
        while(!f1.eof())
        {
            s.erase();
            f1>>s;
            rv.erase();
            rv=rev(s);
            f2<<rv<<"\n";

        }
        cout<<"Reverse contents copied";
        break;
        case 3:return(0);
    }
}