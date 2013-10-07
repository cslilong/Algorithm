#include<iostream>
#include<vector>
using namespace std;
const int MAXN    = 10010;
const char NOTVIS = 0x00;   //����û�з��ʹ���״̬
const char VIS     = 0x01;   //������ʹ�,��û��ɾ����״̬
const char OVER    = 0x02;   //����ɾ����״̬

vector<int> adj[MAXN]; //�����ڽӱ�
int num[MAXN];
int n;

char     flag[MAXN];         //���ڱ�Ƕ���״̬,״̬��NOTVIS,VIS,OVER
int      belg[MAXN];         //�洢ǿ��ͨ����,����belg[i]��ʾ����i���ڵ�belg[i]��ǿ��ͨ����
int      stck[MAXN];         //��ջ,��������
int      mlik[MAXN];         //�ܹؼ�,�����ڽӵ�δɾ���������С����ʱ��
int      indx[MAXN];         //�������ʱ��

//���ѹ���,���㷨�����嶼������
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
          if ( mlik[cur]>indx[adj[cur][i]] ) //�ò��ֵ�indxӦ����mlik,���Ǹ����㷨������,ʹ��indxҲ����,��ʱ�����
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
//Tarjan�㷨,���belg[1..n],�ҷ���ǿ��ͨ��������,
int Tarjan()
{
   int i, sig, scc_num;
   memset(flag+1,NOTVIS,sizeof(char)*n);
   sig = 0; scc_num = 0; stck[0] = 0;
   for ( i=1; i<=n; ++i )
   {
      if ( NOTVIS==flag[i] )
      {
          Visit(i,sig,scc_num);
      }
   }
   for(i=1;i<=n;++i) num[i]=0;
   for(i=1;i<=n;++i) ++num[belg[i]];
    int	maxsum=0;
	for(i=1;i<=n;++i) if(num[i]>maxsum) maxsum=num[i];
	//printf("%d\n",maxsum);
	return maxsum;
   //return scc_num;
} 


int main()
{
	int m,i,x,y;
	while(scanf("%d",&n)!=EOF) {
		scanf("%d",&m);
		for(i=1;i<=n;++i) { adj[i].clear();  }
		while(m--) {
			scanf("%d%d",&x,&y);			
			adj[x].push_back(y);			
		}
		printf("%d\n",Tarjan());
	}	
	return 0;
}
