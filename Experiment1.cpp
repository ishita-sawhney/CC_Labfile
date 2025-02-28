#include <iostream>
#include <string.h>
using namespace std;

int dfa=0;

void state0(char c)
{
    if (c=='a')
    {
        dfa=1;
    }
    else if(c=='b')
    {
        dfa=3;
    }
    else
    {
        dfa=-1;
    }
}

void state1(char c)
{
    if (c=='a')
    {
        dfa=0;
    }
    else if(c=='b')
    {
        dfa=2;
    }
    else
    {
        dfa=-1;
    }
}

void state2(char c)
{
    if (c=='a')
    {
        dfa=3;
    }
    else if(c=='b')
    {
        dfa=1;
    }
    else
    {
        dfa=-1;
    }
}

void state3(char c)
{
    if (c=='a')
    {
        dfa=2;
    }
    else if(c=='b')
    {
        dfa=0;
    }
    else
    {
        dfa=-1;
    }
}

int isAccepted(string str)
{
    int i, len=str.size();
    for(i=0;i<len;i++)
    {
        if(dfa==0)
            state0(str[i]);
            
        else if(dfa==1)
            state1(str[i]);
            
        else if(dfa==2)
            state2(str[i]);
            
        else if(dfa==3)
            state3(str[i]);
            
        else
            return 0;
    }
    if (dfa==3)
        return 1;
    else
        return 0;
}


int main()
{
    string str;
    cout<<"Enter the string to be checked for EVEN a's and ODD b's: ";
    cin>>str;
    if (isAccepted(str))
        cout<<"ACCEPTED";
    else
        cout<<"NOT ACCEPTED";

    return 0;
}
