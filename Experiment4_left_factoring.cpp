#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

string findLongestCommonPrefix(vector<string>& strs) 
{
    if (strs.empty()) return "";
    string prefix=strs[0];
    for (size_t i=1;i<strs.size();i++) 
    {
        size_t j = 0;
        while (j<prefix.length() && j<strs[i].length() && prefix[j]==strs[i][j]) 
        {
            j++;
        }
        prefix = prefix.substr(0, j);
        if (prefix.empty()) break; 
    }
    return prefix;
}

vector<string> FindParts(string& prod) 
{
    vector<string> parts;
    size_t start = 0, pos;
    while ((pos = prod.find('|', start)) != string::npos) 
    {
        parts.push_back(prod.substr(start, pos - start));
        start = pos + 1;
    }
    parts.push_back(prod.substr(start));
    return parts;
}

int main() {
    int n;
    cout<<"Enter the number of Non-Terminals: ";
    cin>>n;
    vector<string> non_term(n);
    unordered_map<string, vector<string>> new_prods;  
    vector<int> no(n);
    for (int i=0; i<n; i++) 
    {
        cout<<"Enter the Non-Terminal "<<i+1<<": ";
        cin>>non_term[i];
        cout<<"Enter the number of productions of Non-terminal "<<non_term[i]<<": ";
        cin>>no[i];
        vector<string> prod(no[i]);
        for (int j = 0; j < no[i]; j++) 
        {
            cout << "Enter the RHS of the production "<<j+1<<" of the Non-Terminal " <<non_term[i]<<": ";
            cin >> prod[j];
            vector<string> parts=FindParts(prod[j]);
            vector<string> factoredParts;
            unordered_map<string, vector<string>> prefixMap;
            for (const string& p : parts) 
            {
                string prefix=p.substr(0, 1); 
                prefixMap[prefix].push_back(p);
            }
            string new_nt =non_term[i]+"'";
            for (auto& entry : prefixMap) 
            {
                if (entry.second.size()>1) 
                {  
                    string commonPrefix=findLongestCommonPrefix(entry.second); 
                    vector<string> suffixes;
                    for (string s : entry.second) 
                    {
                        string suffix = s.substr(commonPrefix.length()); 
                        if (suffix.empty()) suffix = "^";
                        suffixes.push_back(suffix);
                    }
                    new_prods[new_nt] = suffixes;
                    factoredParts.push_back(commonPrefix + new_nt);
                } 
                else 
                {
                    factoredParts.push_back(entry.second[0]);
                }
            }
            new_prods[non_term[i]] = factoredParts;
        }
    }
    cout<<"The new productions are: " << endl;
    for (const auto& entry : new_prods) 
    {
        cout<<entry.first<<" -> ";
        for(size_t j=0; j<entry.second.size(); j++) 
        {
            cout<<entry.second[j];
            if (j!=entry.second.size()-1) 
            cout << " | ";
        }
        cout << endl;
    }
    return 0;
}
