/*pku 3659 Cell Phone Network ��С֧�伯
http://acm.pku.edu.cn/JudgeOnline/problem?id=3659
�������ٵĶ��㸲�����ж�������һ��ǰ�������ţ���¼���ӹ�ϵ��ʹ�ö��ӵı�Ŵ��ڸ��׵ı�Ž���o��n��������ɨ��̰��ѡ��֧�伯�Ķ��㼯�ϡ�
*/
#include <iostream>
#include <vector>
using namespace std;
vector < int > vec[10001]; //ԭͼ��˫��
int id[10001];  //��ͼ
int parent[10001]; //���ӹ�ϵ
int hash[10001];  //dfs����
int num; //���
int Set[10001], Count; //��С֧�伯�ļ��Ϻ͸���
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

