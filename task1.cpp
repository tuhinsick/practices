#include<bits/stdc++.h>
using namespace std;

const int N = 100;
const int INF = 1e9+10;
#define iPair pair<int,int>

vector<pair<int,iPair>> g[N][N];
vector<int> dist[N];


void dijkstra(iPair source){
    priority_queue<pair<int,iPair>, vector<pair<int,iPair>>, greater<pair<int,iPair>>> pq;
    dist[source.first][source.second] = 0;
    pq.push({0,source});
    while(!pq.empty()){
        pair<int,iPair> v = pq.top();
        pq.pop();
        for(auto vertices : g[v.second.first][v.second.second]){
            int wt = vertices.first;
            //cout<<"wt : "<<wt<<endl;
            int u = vertices.second.first;
            int vw = vertices.second.second;
            // cout<<"root "<<v.second.first<<" "<<v.second.second<<" ";
            // cout<<"u v weight "<<u<<" ";
            // cout<<vw<<" "<<wt<<endl;
            if(dist[u][vw] > dist[v.second.first][v.second.second] + wt){
                dist[u][vw] = dist[v.second.first][v.second.second] + wt;
                ///cout<<dist[u][vw]<<endl;
                pq.push({dist[u][vw],{u,vw}});
            }
        }

    }
}

int main(){
    freopen("in.txt","r",stdin);
    for(int i = 0; i < N; i++){
        dist[i].resize(N,INF);
    }

    int n,m,c;
    cin>>n>>m>>c;
    vector<int> weights;
    for(int i=0;i<n;i++){
        int wt;
        cin>>wt;
        weights.push_back(wt);
        //cout<<"weights"<<wt<<endl;
    }

    for(int i=1;i<=n;i++){
        for(int j=0;j<=c;j++){
            for(int k=j+1;k<=c;k++){
                // cout<<"w "<<weights[i-1]<<endl;
                // cout<<"k-j "<<(k-j)<<endl;
                int wt = weights[i-1]*(k-j);
                //cout<<"i j k weight "<<i<<" "<<j<<" "<<k<<" "<<wt<<endl;
                g[i][j].push_back({wt,{i,k}});
                g[i][k].push_back({wt,{i,j}});
            }
        }
    }

    for(int i=0;i<m;i++){
        int u,v,wt;
        cin>>u>>v>>wt;
        for(int j=0;j<=c-wt;j++){
            g[u][c-j].push_back({wt*weights[u-1],{v,c-j-wt}});
            g[v][c-j].push_back({wt*weights[v-1],{u,c-j-wt}});
        }
    }

    int s,d;
    cin>>s>>d;
    dijkstra({s,0});

    int min = INF;
    for(int i=0;i<=10;i++){
        cout<<dist[d][i]<<endl;
        if(dist[d][i] < min){
            min = dist[d][i];
        }
    }

    if(min == INF){
        cout<<"impossible"<<endl;
        return 0;
    }

    cout<<min<<endl;


    return 0;
}