#include <iostream>
#include <string.h>
using namespace std;
int main()
{
    string str;
    int dfa=0;
    cout<<"Enter the binary number to be checked for divisibility by 5: ";
    cin>>str;
    for (int i=0;str[i]!='\0';i++)
    {
        switch(dfa)
        {
            case 0:
            if (str[i]=='0')
                dfa=0;
            else if(str[i]=='1')
                dfa=1;
            else
                dfa=-1;
            break;
            
            case 1:
            if (str[i]=='0')
                dfa=2;
            else if(str[i]=='1')
                dfa=3;
            else
                dfa=-1;
            break;
            
            case 2:
            if (str[i]=='0')
                dfa=4;
            else if(str[i]=='1')
                dfa=0;
            else
                dfa=-1;
            break;
            
            case 3:
            if (str[i]=='0')
                dfa=1;
            else if(str[i]=='1')
                dfa=2;
            else
                dfa=-1;
            break;
            
            case 4:
            if (str[i]=='0')
                dfa=3;
            else if(str[i]=='1')
                dfa=4;
            else
                dfa=-1;
            break;
        }
    }
    if (dfa==0)
        cout<<"ACCEPTED";
    else
        cout<<"NOT ACCEPTED";
    return 0;
}