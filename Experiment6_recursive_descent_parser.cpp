#include <iostream>
using namespace std;

void E(string &input, int &index);
void T(string &input, int &index);
void F(string &input, int &index);
void E_prime(string &input, int &index);
void T_prime(string &input, int &index);

void F(string &input, int &index) 
{
    if (input.substr(index, 2) == "id") 
    {
        index += 2;
    } else if (input[index] == '(') 
    {
        index++;
        E(input, index);
        if (input[index] == ')') 
        {
            index++;
        } else 
        {
            cout << "Parsing Failed" << endl;
            exit(1);
        }
    } 
    else 
    {
        cout << "Parsing Failed" << endl;
        exit(1);
    }
}

void T_prime(string &input, int &index) 
{
    if (input[index] == '*') 
    {
        index++;
        F(input, index);
        T_prime(input, index);
    }
}

void T(string &input, int &index) 
{
    F(input, index);
    T_prime(input, index);
}

void E_prime(string &input, int &index) 
{
    if (input[index] == '+') 
    {
        index++;
        T(input, index);
        E_prime(input, index);
    }
}

void E(string &input, int &index) 
{
    T(input, index);
    E_prime(input, index);
}

int main() 
{
    string input;
    int index = 0;
    cout<<"Recursive Descent Parser workd for the following Grammar: "<<endl;
    cout<<"E->E+T|T"<<endl;
    cout<<"T->T*F|F"<<endl;
    cout<<"F->id|(E)"<<endl;
    cout << "Enter the string to be parsed: ";
    cin >> input;
    input += "$";
    E(input, index);
    if (input[index] == '$') 
    {
        cout << "Parsing Successful" << endl;
    } else 
    {
        cout << "Parsing Failed" << endl;
    }
    return 0;
}
