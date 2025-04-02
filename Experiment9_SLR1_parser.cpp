#include <iostream>
#include <map>
#include <string>
#include <stack>
#include <sstream>
#include <set>
#include <vector>

using namespace std;

vector<pair<char, string>> productions = 
{
    {'E', "E+T"}, 
    {'E', "T"},   
    {'T', "T*F"}, 
    {'T', "F"},   
    {'F', "(E)"},
    {'F', "id"}
};

map<string, string> I0 =
{
    {"E'", ".E"},
    {"E", ".E+T"},
    {"E", ".T"},
    {"T", ".T*F"},
    {"T", ".F"},
    {"F", ".(E)"},
    {"F", ".id"}
};

map<string, string> I1 =
{
    {"E'", "E."},
    {"E", "E.+T"}
};

map<string, string> I2 =
{
    {"E", "T."},
    {"T", "T.*F"}
};

map<string, string> I3 =
{
    {"T", "F."}
};

map<string, string> I4 =
{
    {"F", "(.E)"},
    {"E", ".E+T"},
    {"E", ".T"},
    {"T", ".T*F"},
    {"T", ".F"},
    {"F", ".(E)"},
    {"F", ".id"}
};

map<string, string> I5 =
{
    {"F", "id."}
};

map<string, string> I6 =
{
    {"E", "E+.T"},
    {"T", ".T*F"},
    {"T", ".F"},
    {"F", ".(E)"},
    {"F", ".id"}
};

map<string, string> I7 =
{
    {"T", "T*.F"},
    {"F", ".(E)"},
    {"F", ".id"}
};

map<string, string> I8 =
{
    {"E", "E.+T"},
    {"F", "(E.)"}
};

map<string, string> I9 =
{
    {"E", "E+T."},
    {"T", "T.*F"}
};

map<string, string> I10 =
{
    {"T", "T*F."}
};

map<string, string> I11 =
{
    {"F", "(E)."}
};

map<char, set<string>> followSets = 
{
    {'E', {")", "$","+"}},  
    {'T', {"*","+", ")", "$"}},  
    {'F', {"*", "+", ")", "$"}}  
};

map<pair<int, string>, int> gotoTable = 
{
    {{0, "E"}, 1},
    {{0, "T"}, 2},
    {{0, "F"}, 3},
    {{0, "("}, 4},
    {{0, "id"}, 5},
    {{1, "+"}, 6},
    {{2, "*"}, 7},
    {{4, "("}, 4},
    {{4, "E"}, 8},
    {{4, "T"}, 2},
    {{4, "F"}, 3},
    {{4, "id"}, 5},
    {{6, "T"}, 9},
    {{6, "F"}, 3},
    {{6, "("}, 4},
    {{6, "id"}, 5},
    {{7, "F"}, 10},
    {{7, "("}, 4},
    {{7, "id"}, 5},
    {{8, "+"}, 6},
    {{8, ")"}, 11},
    {{9, "*"}, 7}
};

int getProductionNumber(const map<string, string>& state) 
{
    for (const auto& item : state) 
    {
        string lhs = item.first;
        string rhs = item.second;
        if (lhs == "E'" && rhs == "E.") 
        {
            continue;
        }
        if (rhs.back() == '.') 
        {
            string productionRhs = rhs.substr(0, rhs.length() - 1); 
            for (size_t i = 0; i < productions.size(); i++) 
            {
                if (productions[i].first == lhs[0] && productions[i].second == productionRhs) 
                {
                    return i + 1; 
                }
            }
        }
    }
    return -1; 
}

bool hasAcceptAction(const map<string, string>& state)
{
    for (const auto& item : state)
    {
        if (item.first == "E'" && item.second == "E.")
        {
            return true;
        }
    }
    return false;
}

void print_parsing_tables()
{
    cout << "\nGoto Table:" << endl;
    cout << "State\tNon-Terminal\tGoto" << endl;
    cout << "---------------------------------------------" << endl;
    string nonTerminals[] = {"E", "T", "F"};
    for (int state = 0; state <= 11; state++)
    {
        for (const string& nonTerminal : nonTerminals)
        {
            auto it = gotoTable.find({state, nonTerminal});
            if (it != gotoTable.end())
            {
                int nextState = it->second;
                cout << "I" << state << "\t" << nonTerminal << "\t\t" << nextState << endl;
            }
        }
    }
    cout << "Action Table:" << endl;
    cout << "State\tTerminal\tAction" << endl;
    cout << "---------------------------------------------" << endl;
    string terminals[] = {"+", "*", "(", ")", "id", "$"};
    map<pair<int, string>, vector<string>> actionTable;
    for (int state = 0; state <= 11; state++) 
    {
        for (const string& terminal : terminals) 
        {
            map<string, string> currentState;
            switch (state) 
            {
                case 0: currentState = I0; break;
                case 1: currentState = I1; break;
                case 2: currentState = I2; break;
                case 3: currentState = I3; break;
                case 4: currentState = I4; break;
                case 5: currentState = I5; break;
                case 6: currentState = I6; break;
                case 7: currentState = I7; break;
                case 8: currentState = I8; break;
                case 9: currentState = I9; break;
                case 10: currentState = I10; break;
                case 11: currentState = I11; break;
            }
            if (terminal == "$" && hasAcceptAction(currentState)) 
            {
                actionTable[{state, terminal}].push_back("ACCEPT");
            }
            else 
            {
                int productionNumber = getProductionNumber(currentState);
                if (productionNumber != -1) 
                {
                    pair<char, string> production = productions[productionNumber - 1];
                    char lhs = production.first;  
                    if (followSets[lhs].find(terminal) != followSets[lhs].end()) 
                    {
                        actionTable[{state, terminal}].push_back("R" + to_string(productionNumber));
                    }
                }
                if (state != 1 || terminal != "$") 
                {
                    auto it = gotoTable.find({state, terminal});
                    if (it != gotoTable.end()) 
                    {
                        int nextState = it->second;
                        actionTable[{state, terminal}].push_back("S" + to_string(nextState));
                    }
                }
            }
        }
    }

    for (const auto& entry : actionTable) 
    {
        int state = entry.first.first;
        string terminal = entry.first.second;
        const vector<string>& actions = entry.second;
        cout << "I" << state << "\t" << terminal << "\t\t";
        for (size_t i = 0; i < actions.size(); i++) 
        {
            cout << actions[i];
            if (i < actions.size() - 1) 
            {
                cout << "/";
            }
        }
        cout << endl;
        if (actions.size() > 1) 
        {
            bool hasShift = false;
            bool hasReduce = false;
            for (const string& action : actions) 
            {
                if (action[0] == 'S') 
                {
                    hasShift = true;
                }
                else if (action[0] == 'R') 
                {
                    hasReduce = true;
                }
            }
            if (hasShift && hasReduce) 
            {
                cout << "Conflict in I" << state << " on terminal " << terminal << ": Shift-Reduce Conflict" << endl;
                cout << "Hence, This grammar cannot be parsed by SLR(1) Parser" << endl;
                break;
            }
            else if (actions.size() > 1 && hasReduce) 
            {
                cout << "Conflict in I" << state << " on terminal " << terminal << ": Reduce-Reduce Conflict" << endl;
                cout << "Hence, This grammar cannot be parsed by SLR(1) Parser" << endl;
                break;
            }
        }
    }
}


int main() {
    string input;
    cout << "SLR(1) Parser worked for the following Grammar: "<<endl;
    cout << "E->E+T|T" << endl;
    cout << "T->T*F|F" << endl;
    cout << "F->id|(E)" << endl;
    cout << "Parsing Table: " << endl;
    print_parsing_tables();
    cout << "Enter the input string: ";
    cin >> input;
    input += "$"; 
    stack<int> stateStack;
    stack<char> symbolStack;
    stateStack.push(0); 
    symbolStack.push('$');  
    int i = 0; 
    while (true) {
        int currentState=stateStack.top();
        char currentInputChar=input[i];
        string currentInputSymbol;
        if (input.substr(i, 2)=="id")
        {
            currentInputSymbol="id";
        } 
        else 
        {
            currentInputSymbol=string(1, currentInputChar);
        }
        cout<<"Current State: "<<currentState<<", Input Symbol: "<<currentInputSymbol<<endl;
        map<string, string> currentStateMap;
        switch (currentState) 
        {
            case 0: currentStateMap = I0; break;
            case 1: currentStateMap = I1; break;
            case 2: currentStateMap = I2; break;
            case 3: currentStateMap = I3; break;
            case 4: currentStateMap = I4; break;
            case 5: currentStateMap = I5; break;
            case 6: currentStateMap = I6; break;
            case 7: currentStateMap = I7; break;
            case 8: currentStateMap = I8; break;
            case 9: currentStateMap = I9; break;
            case 10: currentStateMap = I10; break;
            case 11: currentStateMap = I11; break;
            default:
                cout<<"Error: Invalid state "<<currentState<<endl;
                return 1;
        }
        auto actionEntry=gotoTable.find({currentState, currentInputSymbol});
        if (actionEntry!=gotoTable.end()) 
        {
            int nextState=actionEntry->second;
            stateStack.push(nextState);
            symbolStack.push(currentInputChar);  
            if (currentInputSymbol=="id") 
            {
                i += 2;  
            } 
            else 
            {
                i++;  
            }
        } 
        else 
        {
            int productionNumber=getProductionNumber(currentStateMap);
            if (productionNumber!=-1) 
            {
                pair<char, string> production=productions[productionNumber - 1];
                char lhs=production.first;  
                string rhs=production.second;  
                if (followSets[lhs].find(currentInputSymbol) != followSets[lhs].end()) 
                {
                    int rhsLength=rhs.length(); 
                    if (rhs=="id") 
                    {
                        rhsLength = 1; 
                    }
                    for (int j=0; j<rhsLength; j++) 
                    {
                        if (stateStack.empty() || symbolStack.empty()) 
                        {
                            cout << "Error: Stack underflow during reduce action." << endl;
                            return 1;
                        }
                        stateStack.pop();
                        symbolStack.pop();
                    }
                    symbolStack.push(lhs);
                    int newState=stateStack.top(); 
                    auto gotoEntry=gotoTable.find({newState, string(1, lhs)}); 
                    if (gotoEntry!=gotoTable.end()) 
                    {
                        stateStack.push(gotoEntry->second);
                    } 
                    else 
                    {
                        cout<<"Error: Goto entry not found for state "<<newState<<" and symbol "<<lhs<<endl;
                        return 1;
                    }
                }
            } 
            else if (hasAcceptAction(currentStateMap)) 
            {
                cout << "Input string accepted!" << endl;
                return 0;
            } 
            else 
            {
                cout<<"Error: Parsing failed at state "<<currentState<<" with input symbol "<<currentInputSymbol<<endl;
                return 1;
            }
        }
    }
    return 0;
}
