#include<iostream>
using namespace std;
 
const int NMAX = 130;
//const double INF = 1e99;
const int INF =0x7fffffff;
int n;
//double path[NMAX][NMAX];
int path[NMAX][NMAX];
int pre[NMAX];
bool vis[NMAX], del[NMAX];
//double min_cost;
int min_cost;

int fold[NMAX], fpre[NMAX];

int smin(int x,int y)
{
    if(x<y) return x;
    return y;
}

void dfs(int pos) {
    int i;
    vis[pos] = true;
    for(i=1;i<=n;i++) {
       // if(!is_INF(path[pos][i]) && !vis[i]) dfs(i);
       if(path[pos][i]!=INF && !vis[i]) dfs(i);
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
//O(N^3)
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
            for(j=1;j<=n;j++) {
                if(del[j]) continue;
                if(path[j][i] < path[ pre[i] ][i]) pre[i] = fpre[fold[i]] = j;
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
            for(j=1;j<=n;j++) {
                if(del[j]) continue;
                if(  path[j][i]!=INF ) path[j][i] -= path[ pre[i] ][i];
            }//i is new fold node
            for(j=pre[i]; j != i ;j=pre[j]) {
                for(k=1;k<=n;k++) {
                    if(del[k]) continue;
                    path[i][k] = smin(path[i][k], path[j][k]);
                    if( path[k][j]!=INF && path[k][i] > path[k][j] - path[ pre[j] ][j]) {
                        path[k][i] = path[k][j] - path[ pre[j] ][j];
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
//print path in min tree graph
void print_mtg(int root) {
    int i, total = n;
    memset(vis, 0, sizeof(vis));
    for(i=1;i<=n;i++) vis[fpre[i]] = true;
    for(i=1;i<=n;i++) {
        if(!vis[i]) {
            int pos = i;
            while(pos != root) {
                printf("%d <- ", pos);
                pos = fpre[pos];
            }
            printf("%d\n", root);
        }
    }
}
 
 
int main() {
    int i,j,m;
    int x,y,z;
    while(scanf("%d%d",&n,&m) !=EOF) {
		if(n==0) break;
        for (i=0; i<=n; i++)
            for (j=0; j<=n; j++)
                path[i][j] = INF;
         
        while(m --) {            
            scanf("%d%d%d", &x,&y,&z);
            path[x][y] = smin(path[x][y],z);
        }
        if( !min_tree_graph(1) ) puts("impossible");
        else 
        {
            //print_mtg(1);
            printf("%d\n", min_cost);
        }
    }
    return 0;
}
