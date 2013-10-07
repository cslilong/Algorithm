#include<iostream>
#include<cstdio>
#include<cstring>
#include<cstdlib>
using namespace std;
 
const int NMAX = 110;
//const double INF = 1e99;
const int INF =0x7fffffff;
int n;
//double path[NMAX][NMAX];
int path[NMAX][NMAX];
int pre[NMAX];
bool vis[NMAX], del[NMAX];
//double min_cost;
int min_cost,xx;

int fold[NMAX], fpre[NMAX];

struct node
{
	int key;
	node *nxt[27];
}*root,tire[20000];
int nodenum,tirenum;


void new_node(node* &x)
{
	//x = new node;
	x = &tire[tirenum++];
	memset(x,0,sizeof(node));
	x->key = -1;
}

int getnum(char *x)
{
	int i,k;
	node *ptr=root;
	for(i=0;x[i];++i)
	{
		if(x[i]=='_') k=26;
		else k = x[i]-'A';
		if(ptr->nxt[k]==0) new_node(ptr->nxt[k]);
		ptr = ptr->nxt[k];
	}
	if(ptr->key == -1) ptr->key = nodenum++;
	return ptr->key;
}

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
    //if(xx!=1) del[xx]=true;
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
    int x,y,z,d1,d2;
	char s1[30],s2[30];   
    while(scanf("%d",&n)!=EOF) {
		if(n==0) break;
		nodenum=2; tirenum=0;
		new_node(root);	
		
        for (i=0; i<=105; i++) {
            for (j=0; j<=105; j++) {
                path[i][j] = INF;
			}
		}
		xx=1;
        for(i=0;i<n;++i)
		{
			scanf("%s%d%s%d",s1,&d1,s2,&d2);
			x=getnum(s1);
			y=getnum(s2);
			if(strcmp(s1,"THE_WINDY")==0) xx=x;
			if(strcmp(s2,"THE_WINDY")==0) xx=y;
			if(path[1][x]>d1) path[1][x]=d1;
			if(x==y) continue;
			if(path[y][x]>d2) path[y][x]=d2;
		}

		path[1][xx]=0;

		n=nodenum-1;

        if( !min_tree_graph(1) ) puts("impossible");
        else 
        {
            printf("%d\n", min_cost);
        }
    }
    return 0;
}
