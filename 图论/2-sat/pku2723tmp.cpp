#include<iostream>
#include<vector>
using namespace std;
const int MAXN    = 4010;
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
struct{int x,y;}dr[MAXN];   //记录door上的两把锁 
int opp[MAXN]; //opp[i]表示与i冲突的元素。即同组的钥匙。

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
		  // if(mlik[cur]>mlik[adj[cur][i]])
          {
             mlik[cur] = indx[adj[cur][i]]; 
             //mlik[cur] = mlik[adj[cur][i]]; 
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

bool judge()
{
	for(int i=0;i<n;++i) if(belg[i]==belg[opp[i]]) return false;
	return true;
}

bool check(int ans)
{
	for(int i=0;i<n;i++) adj[i].clear();    
    for(int i=0;i<ans;i++)//建图。 当门要求的钥匙是a或b时，我们就添置~a->b,~b->a 
    {//把前ans个门的钥匙，建成一张图。
        adj[dr[i].x].push_back(opp[dr[i].y]);
        adj[dr[i].y].push_back(opp[dr[i].x]);
    }
    Tarjan();
    for(int i=0;i<n;++i) if(belg[i]==belg[opp[i]]) return false;
	return true;
}

void input(){
    int a,b;
    for(int i=0;i<n;i++){//n把钥匙         
        scanf("%d%d",&a,&b);
        opp[a] = b;//opp表示分组，矛盾点 
        opp[b] = a;
    }
    for(int i=0;i<m;i++)//门信息存入dr[] 
        scanf("%d%d",&dr[i].x,&dr[i].y);    
}

int main(){
    while(scanf("%d%d",&n,&m)!=EOF){//锁子组数、门数 
        if(n==0) break;
		input();
        n=n<<1;
        int left=1, right=m, mid;//r为最多开启门数，初始化为M个门 。r=rigth l=left 
        while(left<right)// 二分答案！！ 
        {
            if(left==right-1){
                if(!check(right))
                    right = left;
                break;
            }
            mid = (left + right)/2;
            if(check(mid))
                left = mid;//若k可行，说明最大解在右边，故left赋为k 
            else
                right = mid-1;//否则，最大解必在左边，right赋为k 
        }
        //cout<<right<<endl;
        printf("%d\n",right);
    }
    return 0;
}
