/*
唯一的最小生成树 
Acceteped : 4    Submit : 14  
Time Limit : 1000 MS   Memory Limit : 65536 KB 
  
Description 
求一个非负权边的无向连通图的最小生成树，如果这个无向图存在两个或两个以上的最小生成树，就输出Not Unique，否则输出最小生成树的边的权值和。


输入：

第一行是一个整数K，表示有多少个测试用例，以后每个测试用例占m+1行。每个测试用例的第一行为两个整数n，m（3<=n<=100），表示图的顶点数和边数，从第二行开始每行为三个整数i，j,w,表示从i到j顶点的权值。


输出：

每行输出一个测试用例的结果。如果这个无向图存在两个或两个以上的最小生成树，就输出Not Unique，否则输出最小生成树的边的权值和。
 
  
Sample Input  
2
3 3
1 2 1
2 3 2
3 1 3
4 4
1 2 2
2 3 2
3 4 2
4 1 2 
  
Sample Output  
3
Not Unique 
*/
#include<iostream>
using namespace std;
int a[110][110],b[110];
bool mark[110],flag;
int cases,n,m,i,j,k,minn,minsum,pre,next,x,y,z;
int main()
{
	scanf("%d",&cases);
	while(cases--)
	{
		memset(mark,false,sizeof(mark));
		memset(a,0,sizeof(a));
		memset(b,0,sizeof(b));
		minsum=0;flag=false;
		mark[1]=true;b[1]=1;
		scanf("%d%d",&n,&m);
		for(i=1;i<=m;i++) { scanf("%d%d%d",&x,&y,&z); a[x][y]=z;a[y][x]=z; }		
		for(k=2;k<=n;k++){
			minn=9999999;
			for(i=1;i<k;i++){
				for(j=1;j<=n;j++){
					if(!mark[j]) {
						if(a[b[i]][j]<minn&&a[b[i]][j]!=0) { minn=a[b[i]][j]; next=j; pre=b[i]; }
					}
				}
			}
			b[k]=next;
			for(i=1;i<k;i++)
			{
				if(b[i]==pre) continue;
				if(a[b[i]][next]==minn) { flag=true; break; }
			}
			if(flag) break;
			mark[next]=true;
			minsum+=minn;
		}
		if(flag) printf("Not Unique\n"); else printf("%d\n",minsum);
	//}
	return 0;
}