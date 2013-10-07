#include <iostream>
using namespace std;

const int MAXN=1010;
const int MAXM=10010;
/*
v 该点所在环的编号 
rt 对应点所在环的编号
bv 该点原始编号
bt 对应点原始编号
next
cost 
*/ 
typedef struct{
	int v,next,rt,cost,bt,bv;
}edge;

int N,M,eid;
int rt,w;//不定根
int p[MAXN],In[MAXN],ind[MAXN],hash[MAXN];
edge e[MAXM];
bool vist[MAXN];
int clen;

inline void init(){eid=0;memset(p,-1,sizeof(p));}

inline void insert(int from , int to , int cost)
{
	if (from==to) return;
	e[eid].next=p[from];
	e[eid].v=to;
	e[eid].rt=from;
	e[eid].bv=to;
	e[eid].bt=from;
	e[eid].cost=cost;
	p[from]=eid++;
}

// 定根
// inline void dfs(int pos)
// {
// 	int j;
// 	for (j=p[pos];j!=-1;j=e[j].next)
// 	{
// 		if(!vist[e[j].v])
// 		{
// 			vist[e[j].v]=true;
// 			dfs(e[j].v);
// 		}
// 	}
// }
int Cnt;
int st;
inline bool c_dfs(int pos)
{
	int x=ind[pos];
	
	if (x==-1)
	{
		return false;
	}

	int v=e[x].rt;

	if (!vist[v])
	{
		vist[v]=true;
		if(c_dfs(v))
		{
			hash[v]=Cnt;
			return true;
		}
		vist[v]=false;
	}
	else
	{
		return st==v;
	}

	return false;
}

int fit;

inline int Rtree()
{
	int i;
	//以下为不定根
	++w;
	rt=N;
	for (i=0;i<N;++i) insert(rt,i,w);
	++N;
	///////////////////
	//定根专用
	//rt=0
	//memset(vist,0,sizeof(vist));	
	//vist[rt]=true;
	//dfs(rt);
	//for (i=0;i<N;++i) if(!vist[i]) {return -1;}
	///////////////////

	int res=0;
	for (i=0;i<N;++i) hash[i]=i;
	bool flag=true;

	int bbt=rt;
	int ct;

	fit=INT_MAX;

	while(1)
	{
		ct=clen=Cnt=0;
		for (i=0;i<N;++i) In[i]=INT_MAX,ind[i]=-1;
			
		//找最小边
		for (i=0;i<eid;++i)
		{
			int ff=e[i].rt;
			int tt=e[i].v;
			//ff 和 tt 表示两点所在环的编号！！！ 
			if (ff==tt)	continue;

			if (e[i].cost<In[tt])
			{
				In[tt]=e[i].cost;
				ind[tt]=i;	
			}
		}
			
		In[rt]=0;	
		ind[rt]=-1;

		for (i=0;i<N;++i)
		{
			int x=ind[i];
			if(x==-1) continue;
			if(e[x].bt==bbt)
			{
				++ct;
				if(e[x].bv<fit) fit=e[x].bv;
			}
		}

		memset(vist,0,sizeof(vist));
	
		//找环

		for (i=0;i<N;++i)
		{
			if(!vist[i])
			{
				vist[i]=true;
				hash[i]=Cnt;
				st=i;
				if(c_dfs(i))
				{
					++clen;
					++Cnt;
					continue;
				}
			//	vist[i]=false;
				++Cnt;
			}
		}

		for (i=0;i<N;++i)
		{
			res+=In[i];
		}
		//clen 记录的是环的个数 当环部存在时跳出 
		if (clen==0)
		{
			break;
		}

		//缩点并改边
		for (i=0;i<eid;++i)
		{
			int ff,tt;
			ff=e[i].rt;
			tt=e[i].v;
			e[i].rt=hash[e[i].rt];
			e[i].v=hash[e[i].v];

			if (e[i].rt!=e[i].v)
			{
				e[i].cost-=In[tt];
			}
		}

		N=Cnt;
		rt=hash[rt];
	}

	if(ct!=1) return -1;
	return res-w;
}
int main()
{
	while (scanf("%d%d",&N,&M)!=EOF)
	{
		init();
		w=0;
		while (M--)
		{
			int ff,tt,vv;
			scanf("%d%d%d",&ff,&tt,&vv);
			insert(ff,tt,vv);
			w+=vv;
		}

		int ans=Rtree();

		if (ans!=-1)
		{
			printf("%d %d\n",ans,fit);
		}
		else
		{
			puts("impossible");
		}

		puts("");

	}
	return 0;
}
