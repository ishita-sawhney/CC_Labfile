#include <iostream>
#include <map>
#include <set>
#include <vector>
#include <sstream>
#include <cctype>

using namespace std;

map<string, vector<string>> productions; 
map<string, set<string>> firstSet;       
map<string, set<string>> followSet;      
set<string> terminals;                
vector<string> nonTerminals;              
set<string> visited;                     

vector<string> splitProduction(string prod) 
{
    vector<string> parts;
    stringstream ss(prod);
    string part;
    while (getline(ss, part, '|')) 
    {
        parts.push_back(part);
    }
    return parts;
}

void computeFirst(const string& symbol) 
{
    if (!firstSet[symbol].empty()) return; 
    if (visited.count(symbol)) return;    
    visited.insert(symbol); 
    for (const string& rule : productions[symbol]) 
    {
        int i = 0;
        bool nullable = true;
        while (i < rule.size() && nullable) 
        {
            string token = "";
            while (i < rule.size() && (isalnum(rule[i]) || rule[i] == '_')) {
                token += rule[i];
                i++;
            }
            if (token.empty() && (rule[i] == '(' || rule[i] == ')')) {
                token += rule[i];
                i++;
            }
            if (token.empty()) break;
            if (terminals.count(token)) 
            {  
                firstSet[symbol].insert(token);
                nullable = false;
                break;
            } 
            else 
            {  // If non-terminal
                computeFirst(token); // Compute FIRST if not already done
                // Add all non-null symbols from FIRST(token) to FIRST(symbol)
                for (const string& sym : firstSet[token]) 
                {
                    if (sym != "^") 
                    {
                        firstSet[symbol].insert(sym);
                    }
                }

                // If FIRST(token) contains null, continue to the next symbol in the rule
                if (firstSet[token].count("^") == 0) {
                    nullable = false;
                }
            }
        }

        // If all symbols in the rule are nullable, add epsilon to FIRST(symbol)
        if (nullable) {
            firstSet[symbol].insert("^");
        }
    }

    visited.erase(symbol); // Unmark after processing
}


void computeFollow() {
    followSet[nonTerminals[0]].insert("$");

    bool changed;
    do {
        changed = false;

        for (const auto& prod : productions) {
            string A = prod.first; 

            for (const string& rule : prod.second) {
                vector<string> tokens;
                string token;
                for (size_t i = 0; i < rule.size(); i++) {
                    if (isalnum(rule[i]) || rule[i] == '_') {
                        token += rule[i];
                    } else {
                        if (!token.empty()) tokens.push_back(token);
                        token = "";
                        if (rule[i] != ' ') tokens.push_back(string(1, rule[i])); // Handle symbols like '(' ')'
                    }
                }
                if (!token.empty()) tokens.push_back(token);

                for (size_t i = 0; i < tokens.size(); i++) 
                {
                    if (terminals.count(tokens[i])) continue;

                    set<string>& followB = followSet[tokens[i]];
                    size_t beforeSize = followB.size();

                    // Case 1: A → αBβ  (FOLLOW(B) += FIRST(β) - {ε})
                    if (i + 1 < tokens.size()) {
                        string nextSymbol = tokens[i + 1];

                        if (terminals.count(nextSymbol)) {
                            followB.insert(nextSymbol);
                        } else {
                            followB.insert(firstSet[nextSymbol].begin(), firstSet[nextSymbol].end());
                            followB.erase("^"); // Remove ε if present

                            // If β is nullable, add FOLLOW(A) to FOLLOW(B)
                            if (firstSet[nextSymbol].count("^")) {
                                followB.insert(followSet[A].begin(), followSet[A].end());
                            }
                        }
                    }

                    // Case 2: If B is at the end or everything after B is nullable
                    bool isLast = (i + 1 == tokens.size());
                    bool isNullableSuffix = true;
                    for (size_t j = i + 1; j < tokens.size(); j++) 
                    {
                        if (terminals.count(tokens[j]) || firstSet[tokens[j]].count("^") == 0) 
                        {
                            isNullableSuffix = false;
                            break;
                        }
                    }
                    if (isLast || isNullableSuffix) 
                    {
                        followB.insert(followSet[A].begin(), followSet[A].end());
                    }
                    if (followB.size() > beforeSize) changed = true;
                }
            }
        }
    } while (changed);
}


int main() {
    int t, n;
    cout << "Enter the number of Terminals: ";
    cin >> t;
    cout << "Enter the Terminals: ";
    for (int i = 0; i < t; i++) 
    {
        string term;
        cin >> term;
        terminals.insert(term);
    }
    cout << "Enter the number of Non-Terminals: ";
    cin >> n;
    cin.ignore();
    for (int i = 0; i < n; i++) 
    {
        string nt, rhs;
        cout << "Enter the Non-Terminal " << i + 1 << ": ";
        cin >> nt;
        cin.ignore();
        nonTerminals.push_back(nt);
        cout << "Enter the production rules for " << nt << " : ";
        getline(cin, rhs);
        productions[nt] = splitProduction(rhs);
    }
    for (const string& nt : nonTerminals) 
    {
        computeFirst(nt);
    }
    computeFollow();
    cout << "\nFIRST Sets:\n";
    for (const string& nt : nonTerminals) 
    {
        cout << "FIRST(" << nt << ") = { ";
        bool first = true;
        for (const string& sym : firstSet[nt]) 
        {
            if (!first) cout << ", ";
            cout << sym;
            first = false;
        }
        cout << " }\n";
    }
    cout << "\nFOLLOW Sets:\n";
    for (const string& nt : nonTerminals) 
    {
        cout << "FOLLOW(" << nt << ") = { ";
        bool first = true;
        for (const string& sym : followSet[nt]) 
        {
            if (!first) cout << ", ";
            cout << sym;
            first = false;
        }
        cout << " }\n";
    }
    return 0;
}
