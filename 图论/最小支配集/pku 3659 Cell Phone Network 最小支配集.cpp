/*pku 3659 Cell Phone Network 最小支配集
http://acm.pku.edu.cn/JudgeOnline/problem?id=3659
求用最少的顶点覆盖所有顶点先做一次前序遍历编号，记录父子关系，使得儿子的编号大于父亲的编号进行o（n）的逆序扫描贪心选出支配集的顶点集合。
*/
#include <iostream>
#include <vector>
using namespace std;
vector < int > vec[10001]; //原图，双向
int id[10001];  //新图
int parent[10001]; //父子关系
int hash[10001];  //dfs判重
int num; //标号
int Set[10001], Count; //最小支配集的集合和个数
void dfs(int u){    
	int i, size = vec[u].size();   
	for(i = 0; i < size; i++)  {     
		int v = vec[u][i];      
		if(!hash[v])   {            
			hash[v] = 1;         
			id[v] = num++;        
			parent[ id[v] ] = id[u];   
			dfs(v);      
		}    
	}
}
int main()
{  
	int n, i, a, b;   
	while(scanf("%d", &n) != EOF )  
	{     
		for(i = 0; i < n-1; i++)      
		{       
			scanf("%d%d", &a, &b);        
			vec[a].push_back(b);       
			vec[b].push_back(a);      
		}        
		num = 1;  
		memset(hash, 0, sizeof (hash));  
		for(i = 1; i <= n; i++)     
		{    
			if(vec[i].size() == 1)          
			{         
				hash[i] = 1;             
				id[i] = num++;         
				parent[ id[i] ] = id[i];     
				dfs(i);             
				break;        
			}     
		}      
		Count = 0;   
		memset(Set, 0, sizeof(Set));      
		memset(hash, 0, sizeof(hash));    
		for(i = n; i >= 1; i--)       
		{    
			if(!hash[ i ])       
			{       
				if(!Set[ parent[i] ])            
					Count++;              
				Set[ parent[i] ] = 1;       
				hash[ parent[i] ] = 1;          
				hash[ parent[  parent[i] ]] = 1;   
			}      
		}        
		printf("%d\n", Count);   
	}
	return 0;
}

