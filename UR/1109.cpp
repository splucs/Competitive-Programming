#include <map>
#include <set>
#include <vector>
#include <algorithm>
#include <string>
#include <iostream>
#include <cstdio>
using namespace std;
typedef pair<int,int> ii;

class Node
{
public:
    Node(int id)
    {
        _id = id;
    }
    void addEdge(char carac, int to)
    {
        if (_id == to && carac == '&') return;
        if (!adj.count(carac)) adj[carac] = set<int>();
        adj[carac].insert(to);
    }
    map<char, set<int> > adj;
    int getId()
    {
        return _id;
    }
private:
    int _id;
};

class Automaton
{
public:
    Automaton()
    {
        nodes.clear();
        root = 0;
        end = 1;
        nodes.push_back(Node(root));
        nodes.push_back(Node(end));
    }
    int getSize()
    {
        return (int)nodes.size();
    }

    void addExpression(string expression)
    {
        nodes.clear();
        nodes.push_back(Node(0));
        nodes.push_back(Node(1));
        addExpression(root, end, expression);
        //cout<<nodes.size();
    }
    bool possibleStates(string expression)
    {
        endstates.clear();
        used.clear();
        possibleStatesRecurs(expression,0,nodes[0]);
        return endstates.count(1)==1;
    }
protected:
private:
    int root;
    int end;
    int size;
    vector<Node> nodes;
    set<int> endstates;
    map<ii,bool> used;
    bool isCarac(char carac)
    {
        return (carac == 'a' || carac == 'b');
    }
    bool addExpression(int s, int t, string expression)
    {

        //printf("adding |%s| from %d to %d\n", expression.c_str(), s, t);

        //Check empty string
        if (expression.empty()) return true;

        //Check letter
        if ((int)expression.size() == 1 && isCarac(expression[0]))
        {
            nodes[s].addEdge(expression[0], t);
            return true;
        }


        //Remove brackets
        int openBrackets = 0;
        if (expression.size() >= 2)
        {
            bool eliminate = true;
            for(int i=0; i<(int)expression.size() && eliminate; i++)
            {
                if (expression[i] == '(') openBrackets++;
                if (expression[i] == ')') openBrackets--;
                if (i+1 < (int)expression.size() && openBrackets == 0) eliminate = false;
            }
            if (eliminate) return addExpression(s, t, expression.substr(1, expression.size()-2));
        }

        //Decompose with plus
        openBrackets = 0;
        for(int i=0; i<(int)expression.size(); i++)
        {
            if (expression[i] == '(') openBrackets++;
            if (expression[i] == ')') openBrackets--;
            if (expression[i] == '|' && openBrackets == 0)
            {
                return addExpression(s, t, expression.substr(0, i))
                       && addExpression(s, t, expression.substr(i+1));
            }
        }

        //Decompose with concatenation
        openBrackets = 0;
        for(int i=0; i<(int)expression.size(); i++)
        {
            if (i > 0 && openBrackets == 0 && expression[i]=='.')
            {
                int new_node = (int)nodes.size();
                nodes.push_back(new_node);
                return addExpression(s, new_node, expression.substr(0, i))
                       && addExpression(new_node, t, expression.substr(i+1));
            }
            if (expression[i] == '(') openBrackets++;
            else if (expression[i] == ')') openBrackets--;
        }

        //Decompose with Kleener
        if ((int)expression.size() > 0 && expression[expression.size()-1] == '*')
        {
            int new_node = (int)nodes.size();
            nodes.push_back(new_node);
            nodes[s].addEdge('&', new_node);
            nodes[new_node].addEdge('&', t);
            return addExpression(new_node, new_node, expression.substr(0, expression.size()-1));
        }

        return false;
    }

    void possibleStatesRecurs(string expression,int index,Node node)
    {
        int j;
        char letter;

        //printf("%d %d\n",index,node.getId());

        if (used[ii(index,node.getId())])return;
        used[ii(index,node.getId())]=true;

        if (index == (int)expression.size())
        {
            endstates.insert(node.getId());
            j = 1;
            letter = '&';
        }
        else
        {
            j=0;
            letter = expression[index];
        }
        set<int>::iterator it;
        for (; j<2; j++)
        {
            for (it = node.adj[letter].begin(); it!=node.adj[letter].end(); it++)
            {
                possibleStatesRecurs(expression,index+1-j,nodes[*it]);
            }
            letter = '&';
        }
    }
};

int main(){
    string s;
    int p;
    char c;
    Automaton automaton;

    while (cin>>s){
       // printf("regex: %s\n", s.c_str());
        automaton.addExpression(s);
        scanf("%d%c",&p,&c);
        for (int i=0;i<p;i++){
            getline(cin,s);
       // printf("query: %s\n", s.c_str());
            if (s.size()==0)s = "&";
            if(automaton.possibleStates(s))cout<<"Y"<<endl;
            else cout<<"N"<<endl;
        }
        cout<<endl;
    }
}
