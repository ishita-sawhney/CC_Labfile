#include <iostream>
#include <map>
#include <string>
#include <stack>
#include <sstream>
#include <vector>

using namespace std;

map<string, string> parsing_table = 
{
    {"E id", "T E'"},
    {"E (", "T E'"},
    {"E' +", "+ T E'"},
    {"E' )", "^"}, 
    {"E' $", "^"}, 
    {"T id", "F T'"},
    {"T (", "F T'"},
    {"T' +", "^"},  
    {"T' *", "* F T'"},
    {"T' )", "^"},  
    {"T' $", "^"},  
    {"F id", "id"},
    {"F (", "( E )"}
};

vector<string> split_production(const string &production) 
{
    vector<string> result;
    stringstream ss(production);
    string token;
    while (ss >> token) 
    {
        result.push_back(token);
    }
    return result;
}

void print_parsing_table() 
{
    cout << "Parsing Table:" << endl;
    cout << "Non-Terminal\tTerminal\tProduction" << endl;
    cout << "---------------------------------------------" << endl;
    for (const auto &entry : parsing_table) 
    {
        string non_terminal = entry.first.substr(0, entry.first.find(' '));
        string terminal = entry.first.substr(entry.first.find(' ') + 1);
        string production = entry.first.substr(0, entry.first.find(' '))+"-->"+entry.second;
        cout << non_terminal << "\t\t" << terminal << "\t\t" << production << endl;
    }
}

int main() {
    string input;
    cout<<"Predictive Parser worked for the following Grammar: "<<endl;
    cout<<"E->E+T|T"<<endl;
    cout<<"T->T*F|F"<<endl;
    cout<<"F->id|(E)"<<endl;
    cout<<"Parsing Table: "<<endl;
    cout<<"\t\tTerminals"<<endl;
    print_parsing_table();
    cout << "Enter the input string: ";
    cin >> input;
    input += "$";  
    stack<string> st;
    st.push("$");  
    st.push("E");  
    int i = 0;  
    while (!st.empty()) 
    {
        string top = st.top();
        st.pop();
        stack<string> temp = st;
        vector<string> stack_content;
        while (!temp.empty()) 
        {
            stack_content.push_back(temp.top());
            temp.pop();
        }
        if (top == "$") 
        {
            if (input[i] == '$') 
            {
                cout << "Successful Completion of Parsing" << endl;
                return 0;
            } else {
                cout << "Error: Input not fully consumed" << endl;
                return 1;
            }
        }
        if (isupper(top[0])) 
        {  
            string key;
            if (input.substr(i, 2) == "id") 
            {
                key = top + " id";  
            } 
            else 
            {
                key = top + " " + string(1, input[i]);  
            }
            if (parsing_table.find(key) != parsing_table.end()) 
            {
                string production = parsing_table[key];
                if (production != "^") 
                {  
                    vector<string> symbols = split_production(production);
                    for (auto it = symbols.rbegin(); it != symbols.rend(); ++it) 
                    {
                        st.push(*it);
                    }
                }
            } 
            else 
            {
                cout << "Parsing NOT successful" <<endl;
                return 1;
            }
        } 
        else 
        { 
            if (top == "id" && input.substr(i, 2) == "id") 
            {
                i += 2;  
            } 
            else if (top == string(1, input[i])) 
            {
                i++;  
            } 
            else 
            {
                cout << "Error: Mismatch between stack and input" << endl;
                return 1;
            }
        }
    }
    cout << "String could not be parsed" << endl;
    return 1;
}