#include <iostream>
#include <vector>
#include <regex>
using namespace std;

bool isValidNonTerminal(const string& str) 
{
    regex pattern("[A-Z][A-Za-z0-9_]*");
    return regex_match(str, pattern);
}

bool isValidProduction(const string& str) 
{    
    return !str.empty();
}

vector<string> FindParts(string& prod)
{
    vector<string> parts;
    int start=0,pos;
    while ((pos=prod.find('|',start))!=string::npos) 
    {
        parts.push_back(prod.substr(start,pos-start)); 
        start=pos+1;                                 
    }
    parts.push_back(prod.substr(start));
    return parts;
}

int main()
{
    int n;
    cout<<"Enter the number of Non-Terminals: ";
    cin>>n;
    if (n <= 0) 
    {
        cout << "Invalid input: Number of non-terminals must be positive." << endl;
        return 1;
    }
    vector<string> non_term(n);
    vector<int> no(n);
    vector<vector<string>> prod(n);
    for(int i=0;i<n;i++)
    {
        cout<<"Enter the Non-Terminal "<<i+1<<": ";
        cin>>non_term[i];
        if (!isValidNonTerminal(non_term[i])) 
        {
            cout << "Invalid input: Non-terminal name is invalid." << endl;
            return 1;
        }
        cout<<"Enter the number of productions of Non-terminal "<<non_term[i]<<": ";
        cin>>no[i];
        if (no[i] <= 0) 
        {
            cout << "Invalid input: Number of productions must be positive." << endl;
            return 1;
        }
        prod[i].resize(no[i]);
        for(int j=0;j<no[i];j++)
        {
            cout<<"Enter the RHS of the production "<<j+1<<" of the Non-Terminal "<<non_term[i]<<": ";
            cin>>prod[i][j];
            if (!isValidProduction(prod[i][j])) 
            {
                cout << "Invalid input: Production rule is invalid." << endl;
                return 1;
            }
            vector<string> parts=FindParts(prod[i][j]);
            if (parts[j][0]==non_term[i][0])
            {
                string new_non_term = non_term[i] + "'"; 
                non_term.push_back(new_non_term);
                prod.push_back(vector<string>());
                for (int k=0;k<parts.size();k++) 
                {
                    if(parts[k][0]==non_term[i][0]) 
                    {
                        prod.back().push_back(parts[k].substr(1)+new_non_term); 
                    } 
                    else 
                    {
                        prod[i].push_back(parts[k]);
                    }
                }
                prod.back().push_back("^");
                prod[i].clear(); 
                for (int k=1;k<parts.size();k++) 
                {
                    if (parts[k][0]!=non_term[i][0]) 
                    {
                        prod[i].push_back(parts[k]+new_non_term); 
                    } 
                }
            }
        }
    }
    cout<<"The new productions are: "<<endl;
    for (size_t i=0; i<non_term.size(); i++) 
    {
        cout<<non_term[i]<<" -> ";
        for (int j=0;j<prod[i].size();j++) 
        {
            cout<<prod[i][j];
            if (j!= prod[i].size()- 1) 
            cout<<" | ";
        }
        cout<<endl;
    }
    return 0;
}