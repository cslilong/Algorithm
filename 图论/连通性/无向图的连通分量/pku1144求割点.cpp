/*pku 1144 xoj 1372 Network 求割点个数 
对无向图去掉一点图不连通，这个点叫做割点 
方法dfs求出每个点的num[i] 和 low[i]
num[i]为节点i在深搜的开始访问时间
low[i] =
 min {
num[i]
孩子结点的num的最小值
孩子结点的low的最小值
}
（1）对根 有2个(或以上)孩子结点时 为割点
（2）对非根节点 uv  u为父亲结点 low[v]>=num[u] 时 u为割点 
*/

#include<iostream>
#include<vector>
using namespace std;

struct node{
	int num,low,parent;
}p[110];
vector<int>adj[110];
bool mark[110];
int a[110][110];
int n,g;

void assign_num(int k) {
	p[k].num=++g;
	mark[k]=true;
	int len = adj[k].size();
	for(int j=0;j<len;++j) {
	int	i=adj[k][j];
		if(!mark[i] ) {
			p[i].parent = k;
			assign_num(i);
		}
	}
}

void assign_low(int k) {
	p[k].low = p[k].num;
	mark[k]=true;
	int len = adj[k].size();
	for(int j=0;j<len;++j) {
	int	i=adj[k][j];			
		if(!mark[i]) {
			assign_low(i);			
			if(p[k].low > p[i].low) p[k].low = p[i].low;
		}
		else {
		//	if(p[k].parent != i) {
				if(p[k].low > p[i].num) p[k].low = p[i].num;
		//	}
		}
	
	}
}

int main()
{
	int i,j,m,k,sum;
	while(scanf("%d",&n)!=EOF) {
		if(n==0) break;
		for(i=1;i<=n;++i) adj[i].clear();
	//	for(i=1;i<=n;++i) for(j=1;j<=n;++j) a[i][j]=false;
		while(scanf("%d",&m)) {
			if(m==0) break;
			while(getchar()!='\n') {
				scanf("%d",&k);
			//	a[m][k]=true; a[k][m]=true;
				adj[m].push_back(k);
				adj[k].push_back(m);
			}
		}
		for(i=1;i<=n;++i) {	mark[i]=false;	}
		g=0;
		assign_num(1);
		for(i=1;i<=n;++i) {	mark[i]=false;	} 
		assign_low(1);
		k=0;  sum=0;
		for(i=2;i<=n;++i) if(p[i].parent==1) sum++;
		if(sum>1) sum=1; else sum=0;
		for(i=1;i<=n;++i) {	mark[i]=false;	}
		for(i=2;i<=n;++i){
			if(p[i].low>=p[p[i].parent].num && p[i].parent!=1) mark[p[i].parent]=true;
		}
		for(i=2;i<=n;++i){
			if(mark[i]==true) sum++;
		}
		printf("%d\n",sum);
	}
	return 0;
}



/*
5
5 1 2 3 4
0
6
2 1 3
5 4 6 2
0
3
1 2
3 2
3 1
0
0

*/
