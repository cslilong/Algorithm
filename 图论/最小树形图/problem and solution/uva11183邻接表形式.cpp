#include <cstdio>
#include <cstring>
#include <cmath>
#include <vector>
#include <algorithm>
using namespace std;

const int NMAX = 1500;
const int INF = 0x7f7f7f7f;
/*
struct LINKT {
    int ls;
    int adj[NMAX];
    void clear() {ls = 0;}
    int operator [] (const int pos) {return adj[pos];}
    int size() {return ls;}
    void push_back(const int pos) {adj[ls ++] = pos;}
};
*/
int n;
int path[NMAX][NMAX];
//LINKT epath[NMAX], nepath[NMAX];
vector<int> epath[NMAX];
vector<int> nepath[NMAX];
int pre[NMAX];
bool vis[NMAX], del[NMAX];
int min_cost;
int fold[NMAX], fpre[NMAX];

void dfs(int pos) {
    int i;
    vis[pos] = true;
    for(i=0;i<epath[pos].size();i++) {
        //if(!vis[ epath[pos].adj[i] ]) dfs(epath[pos].adj[i]);
        if(!vis[ epath[pos][i] ]) dfs(epath[pos][i]);
    }
}

bool is_connect(int root) {
    int i;
    memset(vis, 0, sizeof(vis));
    dfs(root);
    for(i=1;i<=n;i++) {
        if(!vis[i]) return false;
    }
    return true;
}
//O(VE)
bool min_tree_graph(int root) {
    int i,j,k;
    //make sure every node(except root) have in-arc
    if(!is_connect(root)) return false;
    memset(del, 0, sizeof(del));
    min_cost = 0;
    for(i=0;i<=n;i++) fold[i] = fpre[i] = i;
    while(true) {
        for(i=1;i<=n;i++) {
            if(del[i] || i == root) continue;
            pre[i] = i;
            path[i][i] = INF;//delete self-cycle
            for(j=0;j<nepath[i].size();j++) {
                //int t = nepath[i].adj[j];
                int t = nepath[i][j];
                if(del[t]) continue;
                if(path[t][i] < path[ pre[i] ][i]) pre[i] = fpre[fold[i]] = t;
            }
        }//find min in-arc
        for(i=1;i<=n;i++) {
            if(del[i] || i == root) continue;
            j = i;
            memset(vis, 0, sizeof(vis));
            while(!vis[j] && j != root) {
                vis[j] = true;
                j = pre[j];
            }
            if(j == root) continue;//no cycle
            i = j;//cycle begin node
            min_cost += path[ pre[i] ][i];
            for(j=pre[i]; j != i ;j=pre[j]) {
                del[j] = true;//fold cycle
                min_cost += path[ pre[j] ][j];//add cycle cost
            }
            for(j=0;j<nepath[i].size();j++) {
                //int t = nepath[i].adj[j];
                int t = nepath[i][j];
                if(del[t]) continue;
                path[t][i] -= path[ pre[i] ][i];
            }//i is new fold node
            for(j=pre[i]; j != i ;j=pre[j]) {
                for(k=0;k<epath[j].size();k++) {
                    //int t = epath[j].adj[k];
                    int t = epath[j][k];
                    if(del[t]) continue;
                    if(path[i][t] == INF) {
                        epath[i].push_back(t);
                        nepath[t].push_back(i);
                    }
                    path[i][t] = min(path[i][t], path[j][t]);
                }
                for(k=0;k<nepath[j].size();k++) {
                    //int t = nepath[j].adj[k];
                    int t = nepath[j][k];
                    if(del[t]) continue;
                    if(path[t][i] == INF) {
                        epath[t].push_back(i);
                        nepath[i].push_back(t);
                    }
                    if(path[t][i] > path[t][j] - path[ pre[j] ][j]) {
                        path[t][i] = path[t][j] - path[ pre[j] ][j];
                        fold[i] = j;//record fold node
                    }
                }
            }//make new graph
            break;
        }
        if(i > n) {
            for(i=1;i<=n;i++) {
                if(del[i] || i == root) continue;
                min_cost += path[ pre[i] ][i];
            }
            break;
        }//graph no cycle
    }//while have cycle
    
    return true;
}

int main() {
    int i,j,m,t;
    scanf("%d", &t);
    for(i=1;i<=t;i++) {
        scanf("%d %d", &n,&m);
        memset(path, 0x7f,sizeof(path));
        //for(j=0;j<=n;j++) epath[j].ls = nepath[j].ls = 0;
        for(j=0;j<=n;++j) { epath[j].clear(); nepath[j].clear(); }
        while(m --) {
            int x,y,z;
            scanf("%d%d%d", &x,&y,&z);
            x ++; y ++;
            if(x == y) continue;
            if(path[x][y] == INF) {
                epath[x].push_back(y);
                nepath[y].push_back(x);
            }
            path[x][y] = min(path[x][y], z);
        }
        if( !min_tree_graph(1) ) printf("Case #%d: Possums!\n", i);
        else printf("Case #%d: %d\n", i,min_cost);
    }
    //system("pause");
    return 0;
}


