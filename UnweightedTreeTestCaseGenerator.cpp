#include<bits/stdc++.h> 
using namespace std; 
#define LL long long int
#define RUN 1
#define MAXNODE 20
class Tree 
{ 
    LL V; 
    list<LL> *adj; 
    bool isCyclicUtil(LL v, bool visited[], LL parent); 
public: 
    Tree(LL V); 
    void addEdge(LL v, LL w);
    void removeEdge(LL v, LL w);
    bool isCyclic(); 
}; 
Tree::Tree(LL V) 
{ 
    this->V = V; 
    adj = new list<LL>[V]; 
} 

void Tree::addEdge(LL v, LL w) 
{ 
    adj[v].push_back(w); 
    adj[w].push_back(v);
} 

void Tree::removeEdge(LL v, LL w) 
{ 
    list<LL>::iterator it; 
    for (it=adj[v].begin(); it!=adj[v].end(); it++) 
    { 
        if (*it == w) 
        { 
            adj[v].erase(it); 
            break; 
        } 
    }
    for (it=adj[w].begin(); it!=adj[w].end(); it++) 
    { 
        if (*it == v) 
        { 
            adj[w].erase(it); 
            break; 
        } 
    }  
    return; 
}
bool Tree::isCyclicUtil(LL v, bool visited[], LL parent) 
{ 
    visited[v] = true; 
    list<LL>::iterator i; 
    for (i = adj[v].begin(); i != adj[v].end(); ++i) 
    { 
        if (!visited[*i]) 
        { 
           if (isCyclicUtil(*i, visited, v)) 
              return true; 
        }
        else if(*i != parent) 
           return true; 
    } 
    return false; 
}  
bool Tree::isCyclic() 
{ 
    bool *visited = new bool[V]; 
    for (int i = 0; i < V; i++) 
        visited[i] = false;
    for (int u = 0; u < V; u++) 
        if (!visited[u])
          if (isCyclicUtil(u, visited, -1)) 
             return true; 
    return false; 
} 
int main() 
{ 
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
    set<pair<LL, LL> > container; 
    set<pair<LL,LL> >::iterator it; 
    srand(time(NULL)); 
    LL NUM; 
    for (LL i=1; i<=RUN; i++) 
    { 
        NUM = 2 + rand() % MAXNODE;
        cout<<NUM<<endl;
        Tree t(NUM);
        for (LL j=1; j<=NUM-1; j++) 
        { 
            int a = rand() % NUM; 
            int b = rand() % NUM; 
            pair<LL, LL> p1= make_pair(a, b); 
            pair<LL, LL> p2= make_pair(b, a );
            t.addEdge(a, b);
            while (container.find(p1) != container.end() || container.find(p2) != container.end() || t.isCyclic() == true) 
            { 
                t.removeEdge(a, b); 
                a = rand() % NUM; 
                b = rand() % NUM; 
                p1 = make_pair(a, b); 
                p2 = make_pair(b, a);
                t.addEdge(a, b); 
            } 
            container.insert(p1); 
        } 

        for (it=container.begin(); it!=container.end(); ++it) 
        { 
            cout<<it->first+1<<" "<<it->second+1<<endl;
        } 
        container.clear(); 
        cout<<endl;
    }
} 
