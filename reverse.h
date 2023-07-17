#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
#include<stdio.h>
#include<stdlib.h>
using namespace std;
string rev(string c)
{
    string s;
    int l=c.length()-1;
    for(;l>=0;l--)
    {
        s+=c[l];
    }
    return s;
}