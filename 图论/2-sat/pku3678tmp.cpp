#include<iostream>
#include<vector>
using namespace std;
const int MAXN    = 10010;
const char NOTVIS = 0x00;   //顶点没有访问过的状态
const char VIS     = 0x01;   //顶点访问过,但没有删除的状态
const char OVER    = 0x02;   //顶点删除的状态

vector<int> adj[MAXN]; //正向邻接表
int num[MAXN];
int n,m;

char     flag[MAXN];         //用于标记顶点状态,状态有NOTVIS,VIS,OVER
int      belg[MAXN];         //存储强连通分量,其中belg[i]表示顶点i属于第belg[i]个强连通分量
int      stck[MAXN];         //堆栈,辅助作用
int      mlik[MAXN];         //很关键,与其邻接但未删除顶点地最小访问时间
int      indx[MAXN];         //顶点访问时间

//深搜过程,该算法的主体都在这里
void Visit(int cur, int &sig, int &scc_num)
{
   int i;
   stck[++stck[0]] = cur; flag[cur] = VIS;
   mlik[cur] = indx[cur] = ++sig;
   for ( i=0; i<adj[cur].size(); ++i )
   {
      if ( NOTVIS==flag[adj[cur][i]] )
      {
          Visit(adj[cur][i],sig,scc_num);
          if ( mlik[cur]>mlik[adj[cur][i]] )
          {
             mlik[cur] = mlik[adj[cur][i]];
          }
      }
      else if ( VIS==flag[adj[cur][i]] )
      {
          if ( mlik[cur]>indx[adj[cur][i]] ) 
		  //该部分的indx应该是mlik,但是根据算法的属性,使用indx也可以,且时间更少
          {
             mlik[cur] = indx[adj[cur][i]]; 
          }
      }
   }
   if ( mlik[cur]==indx[cur] )
   {
      ++ scc_num;
      do
      {
          belg[stck[stck[0]]] = scc_num;
          flag[stck[stck[0]]] = OVER;
      }
      while ( stck[stck[0]--]!=cur );    
   }
}
//Tarjan算法,求解belg[1..n],且返回强连通分量个数,
int Tarjan()
{
   int i, sig, scc_num;
   memset(flag,NOTVIS,sizeof(char)*n);
   sig = 0; scc_num = 0; stck[0] = 0;
   for ( i=0; i<n; ++i )
   {
      if ( NOTVIS==flag[i] )
      {
          Visit(i,sig,scc_num);
      }
   }
   return scc_num;
}
 
bool input() 
{
     if (scanf("%d%d",&n,&m)==EOF)  return false;
     n = n+n;
     int cc;
     char ss[10];
     for (int i=0;i<n;i++)  adj[i].clear();
     for (int i=0;i<m;i++)
     {
         int a,b,c,d;
         scanf("%d%d%d%s",&a,&b,&cc,ss); 
         a = a+a;
         b = b+b;
         c=a^1; d=b^1;
		 //if (a%2==0) c=a+1;  else  c=a-1;
         //if (b%2==0) d=b+1;  else  d=b-1;
         if(ss[0]=='A') {
		 	if(cc==1) { adj[c].push_back(a);  adj[d].push_back(b); }
		 	else { adj[a].push_back(d);  adj[b].push_back(c); }
		 } else if(ss[0]=='O') {
			if(cc==1) { adj[c].push_back(b);  adj[d].push_back(a); }
		 	else { adj[a].push_back(c);  adj[b].push_back(d); }
		 } else {
		 	if(cc==1) { adj[a].push_back(d);  adj[d].push_back(a); adj[c].push_back(b);  adj[b].push_back(c); }
		 	else { adj[a].push_back(b);  adj[b].push_back(a); adj[c].push_back(d);  adj[d].push_back(c); }
		 }         
     }
     Tarjan();     
     return true;
}

bool judge()
{
	for(int i=0;i<n;i+=2) if(belg[i]==belg[i+1]) return false;
	return true;
}

int main()
{
	while(input())
	{
		if(judge()) printf("YES\n");
		else printf("NO\n");
	}
	return 0;
}
