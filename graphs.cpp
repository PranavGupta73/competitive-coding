#include<bits/stdc++.h>
using namespace std;
void topologicalSortDFSHelper(int ** edges, int curr,bool* visited,stack<int>& st,int n);

int fordfulkersonbfs(int source,int sink, vector<int>& parent,vector<vector<int>>&residualGraph){
    fill(parent.begin(),parent.end(),-1);
    int v=residualGraph.size();
    parent[source]=-2;
    queue<pair<int,int>>q;
    q.push({source,INT_MAX});

    while(!q.empty()){
        int u=q.front().first;
        int capacity=q.front().second;
        q.pop();
        for(int av=0;av<v;av++){
            if(u != av & parent[av] == -1 && residualGraph[u][av] != 0){
                parent[av] = u;
                int min_cap = min(capacity,residualGraph[u][av]);
                if(av == sink){
                    return min_cap;
                }
                q.push({av,min_cap});
            }
        }
    }
    return 0;
}

int ford_fulkerson(vector<vector<int>>& graph,int source, int sink){
    vector<int> parent(graph.size(),-1);
    vector<vector<int>> residualGraph = graph;
    int min_cap=0,max_flow=0;
    while(min_cap == fordfulkersonbfs(source,sink,parent,residualGraph)){
        max_flow+=min_cap;
        int u= sink;
        while(u!=source){
            int v=parent[u];
            residualGraph[u][v]+=min_cap;
            residualGraph[v][u]-=min_cap;
            u=v;
        }
    }
    return max_flow;
}


void kosrajuAlgoHelper(int** edges , int n , int curr ,bool* visited){
    cout<<curr<<" ";
    visited[curr]=true;
    for(int i=0;i<n;i++){
        if(edges[curr][i]==1 && !visited[i]){
            kosrajuAlgoHelper(edges,n,i,visited);
            // cout<<"i:"<<i<<"curr:"<<curr<<endl;
        }
    }
}
void kosarajuAlgo(int** edges , int n ){
    stack<int> st;
    bool* visited = new bool[n];
    
    for(int i=0;i<n;i++){
        visited[i]=false;
    }
    for(int i=0;i<n;i++){
        if(!visited[i]){
            topologicalSortDFSHelper(edges,i,visited,st,n);
        }
    }


    //Transpose the graph
    int** transpose= new int*[n];
    for(int i=0;i<n;i++){
        transpose[i]= new int[n];
    }

    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            if(edges[i][j]==1){
                transpose[j][i]=1;
            }else{
                transpose[j][i]=0;
            }
        }
    }

    //DFS acc to stack on transpose

    for(int i=0;i<n;i++){
        visited[i]=false;
    }
    while(!st.empty()){
        int top=st.top();
        st.pop();
        if(!visited[top]){
            kosrajuAlgoHelper(transpose,n,top,visited);
            cout<<endl;
        }

        
    }


}


void articulationPointHelper(int ** edges , int n , int curr ,int parent, int * tin ,int * low ,int &count,int* ans){
    low[curr]=count;
    tin[curr]=count;
    count++;
    int child=0;
    for(int i=0;i<n;i++){
        if(edges[curr][i]==1 && i!=parent){
            if(tin[i]==0){
                articulationPointHelper(edges,n,i,curr,tin,low,count,ans);
                low[curr]=min(low[curr],low[i]);
                if(low[i]>=tin[curr] && parent != -1){
                    ans[curr]=1;
                }
                child++;  // to count the independent children;
            }else{
                low[curr]=min(low[curr],tin[i]);
            }
        }
    }

    if(parent==-1 && child>1){
        ans[curr]=1;
    }
}

void articulationPoint(int** edges, int n){
    int* tin = new int[n];
    int* low = new int[n];
    int *isArticulation = new int[n];
    for(int i=0;i<n;i++){
        tin[i]=0;
        low[i]=INT_MAX;
        isArticulation[i]=0;
    }
    int count=1;
    // set<int> ans;
   
    articulationPointHelper(edges,n,0,-1,tin,low,count,isArticulation);
    for(int i=0;i<n;i++){
        if(isArticulation[i]==1){
            cout<<i<<" ";
        }
    }cout<<endl;
}
void bridgesInGraphHelper(int **edges, int n,int curr,int parent, int *tin, int* low,int& count){
    low[curr]=count;
    tin[curr]=count;
    count++;
    for(int i=0;i<n;i++){
        if(edges[curr][i]==1 && i!=parent){
            if(tin[i]==0){
                bridgesInGraphHelper(edges,n,i,curr,tin,low,count);
                low[curr]=min(low[curr],low[i]);
                if(low[i]>tin[curr]){
                    cout<<i<<" "<<curr<<endl;
                }

            }else{
                low[curr]=min(low[curr],tin[i]);
            }
        }
    }
}
void bridgesInGraph(int** edges, int n){

    int* tin = new int[n];
    int* low = new int[n];

    for(int i=0;i<n;i++){
        tin[i]=0;
        low[i]=INT_MAX;
    }
    int count=1;
    bridgesInGraphHelper(edges,n,0,-1,tin,low,count);
    // for(int i=0;i<n;i++){
    //     cout<<tin[i]<<" "<<low[i]<<endl;
    // }
}

int findPar(int node, int* parent){
    if(node == parent[node] ){
        return node;
    }

    //Path Compression//
    int par = findPar(parent[node],parent);
    parent[node]= par;
    //   //   

    return par; 
}
void unionF(int x, int y, int*parent, int * rank,int n){
     x=findPar(x,parent);
     y=findPar(y,parent);

     if(rank[x]<rank[y]){
        parent[x]=y;
     }else if(rank[x]==rank[y]){
         parent[x]=y;
         rank[y]++;
     }else{
         parent[y]=x;
     }
}
void disjoint(int **edges , int n){
    int * rank = new int[n];
    for(int i=0;i<n;i++){
        rank[i]=0;
    }
    int * parent = new int[n];
    for(int i=0;i<n;i++){
        parent[i]=i;
    }

    int q;
    cin>>q;
    for(int i=0;i<n;i++){
        int x,y;
        cin>>x>>y;
        unionF(x,y,parent,rank,n);
    }
}

void primAlgo(int ** edges, int n){
    int parent[n];
    int key[n];
    bool mst[n];
    for(int i=0;i<n;i++){
        key[i]=INT_MAX;
        mst[i]=false;
    }
    priority_queue<pair<int,int> , vector<pair<int,int>>, greater<pair<int,int>>> pq;
    key[0]=0;
    parent[0]=-1;
    pq.push({0,0});

    for(int i=0;i<n-1;i++){
        int u = pq.top().second;
        pq.pop();
        mst[u]=true;

        for(int j=0;j<n;j++){
            if(edges[u][j]!=0){
                if(mst[j]==false && edges[u][j] < key[j]){
                    parent[j]=u;
                    pq.push({key[j],j});
                    key[j]=edges[u][j];
                }
            }
        }
    }
    for(int i=1;i<n;i++){
        cout<<parent[i]<<"-"<<i<<endl;
    }
    return ;
}
void shortestDistanceInWeightedDAGHelper(int** edges,int sv, int n, stack<int>& st,bool* visited){
    visited[sv]=true;
    for(int i=0;i<n;i++){
        if(edges[sv][i]!=0 && !visited[i]){
            shortestDistanceInWeightedDAGHelper(edges,i,n,st,visited);
        }
    }
    st.push(sv);
}
void shortestDistanceInWeightedDAG(int**edges , int n){
    bool* visited = new bool[n];
    
    for(int i=0;i<n;i++){
        visited[i]=false;
    }

    stack<int> st;
    shortestDistanceInWeightedDAGHelper(edges,0,n,st,visited);
    // cout<<st.top()<<endl;
    int * distance = new int[n];
    for(int i=0;i<n;i++){
        distance[i]=INT_MAX;
    }
    distance[st.top()]=0;
    while(!st.empty()){
        int curr = st.top();
        int dis = distance[curr];
        st.pop();
        if(distance[curr]!=INT_MAX){
            for(int i=0;i<n;i++){
                if(edges[curr][i]!=0){
                    if(distance[i]>dis+edges[curr][i]){
                        distance[i] = dis+edges[curr][i];
                    }
                }
            }
        }
        
    }

    for(int i=0;i<n;i++){
        cout<<distance[i]<<" ";
    }cout<<endl;




}
void shortestPathInUndirectedHelper(int** edges, int n ,int* distance,int src){
    queue<int> q;
    q.push(src);
    distance[src]=0;
    while(!q.empty()){
        int curr= q.front();
        q.pop();
        int dis=distance[curr];
        for(int i=0;i<n;i++){
            if(edges[curr][i]==1){
                if(distance[i]>(dis+1)){
                    q.push(i);
                    distance[i] = dis+1;
                }
            }
        }
    }
}
int shortesPathInUndirected(int** edges,int n,int src,int dest){
    int* distance= new int[n];
    for(int i=0;i<n;i++){
        distance[i]=INT_MAX;
    }
    shortestPathInUndirectedHelper(edges,n,distance,src);
    for(int i=0;i<n;i++){
        cout<<distance[i]<<" ";
    }cout<<endl;

    return distance[dest];
}

vector<int> topologicalSortBFSHelper(int **edges,int n,bool* visited,int* indegree){
    queue<int> q;
    vector<int> ans;
    for(int i=0;i<n;i++){
        if(!visited[i] && indegree[i]==0){
            q.push(i);
        }
    }
    while(!q.empty()){
        int curr=q.front();
        q.pop();
        ans.push_back(curr);
        visited[curr]=true;
        for(int i=0;i<n;i++){
            if(edges[curr][i]==1){
                indegree[i]--;
                if(indegree[i]==0){
                    q.push(i);
                }
            }
        }        
    }
    return ans;
}

vector<int> topologicalSortBFS(int **edges,int n){
    bool *visited = new bool[n];
    for(int i=0;i<n;i++){
        visited[i]=false;
    }
    int *indegree = new int[n];
    for(int i=0;i<n;i++){
        indegree[i]=0;
    }
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            if(edges[i][j]==1){
                indegree[j]++;
            }
        }
    }

    vector<int> ans=topologicalSortBFSHelper(edges,n,visited,indegree);
    return ans;
}
void topologicalSortDFSHelper(int ** edges, int curr,bool* visited,stack<int>& st,int n){
    visited[curr]=true;
    for(int i=0;i<n;i++){
        if(edges[curr][i]==1 &&!visited[i]){
            topologicalSortDFSHelper(edges,i,visited,st,n);
        }
    }
    st.push(curr);
}

vector<int> topologicalSortDFS(int **edges,int n){
    bool *visited = new bool[n];
    for(int i=0;i<n;i++){
        visited[i]=false;
    }
    stack<int> st;
    for(int i=0;i<n;i++){
        if(!visited[i]){
            topologicalSortDFSHelper(edges,i,visited,st,n);
        }
    }
    vector<int> ans;
    for(int i=0;i<n;i++){
        ans.push_back(st.top());
        st.pop();
    }
    return ans;
}


bool checkCycleDirectedBFS(int**edges, int n){

    vector<int> topsort = topologicalSortBFS(edges,n);
    if(topsort.size()!=n){
        return true;
    }
    return false;

}

bool checkCycleDirectedDFS(int**edges,int sv, bool*visited, bool* dfsvisited,int n){

    visited[sv]=true;
    dfsvisited[sv]=true;

    for(int i=0;i<n;i++){
        if(edges[sv][i]==1){
            if(visited[i]){
                if(dfsvisited[i]) return true;
                else continue;
            }
            if(checkCycleDirectedDFS(edges,i,visited,dfsvisited,n)){
                return true;
            }
        }
    }

    dfsvisited[sv]=false;
    
    return false;
}

bool checkCycleBFS(int **edges,int sv, bool*visited,int n){
    queue<pair<int,int>> nodes;
    nodes.push({sv,-1});
    visited[sv]=true;
    while(!nodes.empty()){
        pair<int,int> cur=nodes.front();
        nodes.pop();

        int curr=cur.first;
        int par=cur.second;

        for(int i=0;i<n;i++){
            if(edges[curr][i]==1){
                if(visited[i]){
                    if(i==par){
                        continue;
                    }else{
                        return true;
                    }
                }else{
                    nodes.push({i,curr});
                    visited[i]=true;
                }
            }
        }
    }
    return false;
}

bool checkCycleDFS(int **edges,int curr,bool* visited,int prev,int n){
    visited[curr]=true;
    for(int i=0;i<n;i++){
        if(edges[curr][i]==1){
            if(visited[i]==1){
                if(prev!=i)
                    return true;
                else 
                    continue;
            }
            if(checkCycleDFS(edges,i,visited,curr,n)){
                return true;
            }
        }
    }
    return false;
}

bool checkCycle(int **edges,int n){
    bool *visited= new bool[n];
    for(int i=0;i<n;i++){
        visited[i]=false;
    }
    for(int i=0;i<n;i++){
        if(!visited[i]){
            // if(checkCycleBFS(edges,i,visited,n)){
            //     return true;
            // }
            if(checkCycleDFS(edges,i,visited,-1,n)){
                return true;
            }
        }
    }
    return false;
}

bool checkCycleDirected(int **edges,int n){
    bool* visited= new bool[n];
    bool* dfsvisited = new bool[n];

    for(int i=0;i<n;i++){
        visited[i]=false;
        dfsvisited[i]=false;
    }
    
    for(int i=0;i<n;i++){
        if(!visited[i]){
            if(checkCycleDirectedDFS(edges,i,visited,dfsvisited,n)){
                return true;
            }
        }
    }
    
    return false;
}

////////Bipartite Graph/////////

bool checkBipartiteBFS(int**edges,int n,int* color,int sv){
    color[sv]=0;
    queue<int> nodes;
    nodes.push(sv);
    while(!nodes.empty()){
        int curr=nodes.front();
        nodes.pop();
        int val=0;
        if(color[curr]==0){
            val=1;
        }
        for(int i=0;i<n;i++){
            if(edges[curr][i]==1){
                if(color[i]==-1){
                   color[i]=val; 
                   nodes.push(i);
                }
                else{
                    if(color[i]==color[curr]){
                        return false;
                    }
                }
            }
        }
    }
    return true;
}

bool checkBipartiteDFS(int **edges,int n,int prev,int *color,int curr){
    color[curr] = prev==0?1:0;
    for(int i=0;i<n;i++){
        if(edges[curr][i]==1){
            if(color[i]==-1){
                if(checkBipartiteDFS(edges,n,color[curr],color,i)==false){
                    return false;
                }
            }
            else{
                if(color[i]==color[curr]){
                    return false;
                }
            }
        }
    }
    return true;
}

bool checkBipartite(int ** edges,int n){
    int color[n];
    for(int i=0;i<n;i++){
        color[i]=-1;
    }

    for(int i=0;i<n;i++){
        // if(color[i]==-1){
        //     if(checkBipartiteBFS(edges,n,color,i)==false){
        //         return false;
        //     }
        // }

        if(color[i]==-1){
            if(!checkBipartiteDFS(edges,n,1,color,i)){
                return false;
            }
        }
    }
    // for(int i=0;i<n;i++){
    //     cout<<color[i]<<" ";
    // }cout<<endl;
    return true;
}

void printDFS(int ** edges,int n,int sv,bool* visited){
    cout<<sv<<endl;
    visited[sv]=true;
    for(int i=0;i<n;i++){
        if(i==sv || visited[i]==true){
            continue;
        }
        if(edges[sv][i]==1){
            printDFS(edges,n,i,visited);
        }
    }
}

void printBFS(int **edges,int n,int sv,bool* visited){
    queue<int> index;
    index.push(sv);
    visited[sv]=true;
    while(!index.empty()){
        int front = index.front();
        index.pop();
        cout<<front<<endl;
        for(int i=0;i<n;i++){
            if(edges[front][i]==1 && !visited[i]){
                index.push(i);
                visited[i]=true;
            }
        }
    }
}
bool checkDFS(int ** edges,int n,int sv,bool* visited,int s,int e){
    // cout<<sv<<endl;
    visited[sv]=true;
    for(int i=0;i<n;i++){
        if(i==sv || visited[i]==true){
            continue;
        }
        if(edges[sv][i]==1){
            if(s==sv){
                if(e==i){
                    return true;
                }else{
                    return checkDFS(edges,n,i,visited,i,e);
                }
            }
            if(s==i){
                if(e==sv){
                    return true;
                }else{
                    return checkDFS(edges,n,i,visited,sv,i);
                }
            }
        }
    }
    return false;
}
bool hasPath(int **edges,int n,int s, int e){
    bool * visited = new bool[n];
    for(int i=0;i<n;i++){
        visited[i]=false;
    }
    for(int i=0;i<n;i++){
        if(!visited[i])
            return checkDFS(edges,n,i,visited,s,e);
    }
    // delete[] visited;
    return true;
}
vector<int> getPathDFS(int**edges,int n,bool* visited,int s,int e){
    if(s==e){
        return {e};
    }
    
    visited[s]=true;
    vector<int> path;
    for(int i=0;i<n;i++){
        if(edges[s][i]==1 &&!visited[i]){
            path=getPathDFS(edges,n,visited,i,e);
            if(path.size()!=0){
                break;
            }
        }
    }
    if(path.size()==0){
        return {};
    }else{
        path.push_back(s);
        return path;
    }
}
vector<int> getPathBFS(int **edges,int n,int sv,int e){
    queue<int> index;
    map<int,int> m;
    bool visited[n];
    visited[sv]=true;
    for(int i=0;i<n;i++){
        visited[i]=false;
    }
    index.push(sv);
    bool found=false;
    while(!index.empty() && !found){
        int sve=index.front();
        index.pop();
        for(int i=0;i<n;i++){
            if(!visited[i] && edges[sve][i]){
                index.push(i);
                visited[i]=true;
                m.insert({i,sve});
                if(i==e){
                    found = true;
                    break;
                }
                
            }
        }
    }
    if(!found){
        return {};
    }
    int curr=e;
    
    vector<int> path;
    path.push_back(e);
    while(curr!=sv){
        path.push_back(m[curr]);
        curr=m[curr];
    }
    // delete []visited;
    // cout<<path[0]<<"herer"<<endl;
    return path;
}

void DFS(int ** edges,int n){
    bool * visited = new bool[n];
    for(int i=0;i<n;i++){
        visited[i]=false;
    }

    for(int i=0;i<n;i++){
        if(!visited[i])
            printDFS(edges,n,i,visited);
    }
    delete[] visited;
}
void BFS(int ** edges,int n){
    bool * visited = new bool[n];
    for(int i=0;i<n;i++){
        visited[i]=false;
    }

    for(int i=0;i<n;i++){
        if(!visited[i])
            printBFS(edges,n,i,visited);
    }
    delete[] visited;
}

bool isConnected(int **edges,int n){
    bool visited[n];
    for(int i=0;i<n;i++){
        visited[i]=false;
    }

    printDFS(edges,n,0,visited); //comment out the cout line.
    for(int i=0;i<n;i++){
        if(visited[i]==false){
            return false;
        }

    }
    return true;
}
void dfsvector(int **edges,int n,int sv,bool* visited,vector<int>& v){
    visited[sv]=true;
    v.push_back(sv);
    for(int i=0;i<n;i++){
        if(i==sv || visited[i]==true){
            continue;
        }
        if(edges[sv][i]==1){
            dfsvector(edges,n,i,visited,v);
        }
    }
}
vector<vector<int>> connectedComponents(int **edges,int n,int sv){
    bool visited[n];
    for(int i=0;i<n;i++){
        visited[i]=false;
    }
    vector<vector<int>> ans;
    for(int i=0;i<n;i++){
        vector<int> temp;
        if(!visited[i]){
            dfsvector(edges,n,i,visited,temp);
            ans.push_back(temp);
        }
    }
    return ans;
}
int main(){
    int n;
    int e;
    cin>>n>>e;
    int **edges = new int*[n];
    for(int i=0;i<n;i++){
        edges[i]=new int [n];
        for(int j=0;j<n;j++){
            edges[i][j]=0;
        }
    }

    for(int i=0;i<e;i++){
        int f,s;
        cin>>f>>s;
        edges[f][s]=1;
        // edges[s][f]=1;
    }
    // bool * visited = new bool[n];
    // for(int i=0;i<n;i++){
    //     visited[i]=false;
    // }
    // int v1,v2;
    // cin>>v1>>v2;
    // cout<<"DFS"<<endl;
    // printDFS(edges,n,0,visited);
    // DFS(edges,n);

    // cout<<"BFS"<<endl;
    // printBFS(edges,n,0,visited);
    // BFS(edges,n);
    // cout<<hasPath(edges,n,0,2)<<endl;
    // cout<<hasPath(edges,n,0,4)<<endl;
    // cout<<hasPath(edges,n,0,3)<<endl;

    // vector<int> path=getPathDFS(edges,n,visited,v1,v2);
    // vector<int> path=getPathBFS(edges,n,v1,v2);
    // for(int i=0;i<path.size();i++){
    //     cout<<path[i]<<" ";
    // }cout<<endl;
    // cout<<isConnected(edges,n)<<endl;
    // vector<vector<int>> ans=connectedComponents(edges,n,0);
    // for(int i=0;i<ans.size();i++){
    //     for(int j=0;j<ans[i].size();j++){
    //         cout<<ans[i][j]<<" ";
    //     }cout<<endl;
    // }cout<<endl;

    // cout<<checkCycle(edges,n)<<endl;
    // cout<<checkBipartite(edges,n)<<endl;
    // cout<<checkCycleDirected(edges,n)<<endl;

    // vector<int> toposort = topologicalSortBFS(edges,n);
    // for(int i=0;i<n;i++){
    //     cout<<toposort[i]<<" ";
    // }cout<<endl;

    // cout<<checkCycleDirectedBFS(edges,n)<<endl;
    // cout<<shortesPathInUndirected(edges,n,0,1);
    // shortestDistanceInWeightedDAG(edges,n);
    primAlgo(edges,n);
    // bridgesInGraph(edges,n);
    // articulationPoint(edges,n);
    kosarajuAlgo(edges,n);

    // delete[] visited;
    for(int i=0;i<n;i++){
        delete [] edges[i];
    }
    delete[] edges;
}