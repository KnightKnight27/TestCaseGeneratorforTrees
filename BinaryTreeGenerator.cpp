#include<bits/stdc++.h> 
using namespace std; 
#define LL long long int
#define RUN 1
#define MAXNODE 8
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
    if(adj[v].size()>3)
    {
        return true;
    }
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
void dfs(string &ans,LL src,LL par,vector<LL> *pr,LL depth)
{
    for(LL i=0;i<depth;i++)
    {
        ans+="-";
    }
    ans+= to_string(src);
    if(pr[src].size()==1)
    {
        LL val=pr[src][0];
        if(val!=par)
        {
           dfs(ans,val,src,pr,depth+1);
        }
    }
    if(pr[src].size()==2)
    {
        LL val=pr[src][0];
        if(val!=par)
        {
           dfs(ans,val,src,pr,depth+1); 
        }
        val=pr[src][1];
        if(val!=par)
        {
           dfs(ans,val,src,pr,depth+1); 
        }
        
    }
    if(pr[src].size()==3)
    {
        LL val=pr[src][0];
        if(val!=par)
        {
           dfs(ans,val,src,pr,depth+1); 
        }
        val=pr[src][1];
        if(val!=par)
        {
           dfs(ans,val,src,pr,depth+1); 
        }
        val=pr[src][2];
        if(val!=par)
        {
            dfs(ans,val,src,pr,depth+1); 
        }
    }
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
        // cout<<NUM<<endl;
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
        vector<LL> pr[100000];
        for (it=container.begin(); it!=container.end(); ++it) 
        { 

            pr[it->first+1].push_back(it->second+1);
            pr[it->second+1].push_back(it->first+1);
            // cout<<it->first+1<<" "<<it->second+1<<endl; USE THIS TO PRINT THE NODES OF BINARY TREE
        } 
        LL y=0;
        for(LL i=1;i<=NUM;i++)
        {
            if(pr[i].size()<3)
            {
                y=i;
            }
        }
        string ans="";
        dfs(ans,y,-1,pr,0);
        cout<<ans<<endl;
        container.clear();
    }
} 
