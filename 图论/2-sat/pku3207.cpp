/*pku 3207 3207 -- Ikki's Story IV - Panda's Trick
��Ŀԭ����������̫�����, ����˵��. һ��Բ�̵ı�������n����, �±��0��ʼ, ��m��
������2m��������ͬ�ĵ�, �߿��Դ�Բ������һ���, Ҫ�����������߲����ཻ. ����m��
��(����������), ���Ƿ����һ�ָ�ÿ���ߵ�������ķ��䷽��, ʹ����Ҫ��.
 

������2-SAT(2�ж�������(http://en.wikipedia.org/wiki/2-satisfiability))�Ļ�����,
�ؼ����ڽ�ͼ.
 

���i����(i��0��ʼ)������Ϊ��2i������, �ڷ���Ϊ��2i+1������. ����i���ߺ͵�j����
����һ���ı��ε������Խ���, ����2i��2j+1֮����һ��˫���, 2i+1��2j֮����һ��˫��
��. ������ͼ����ǿ��ͨ����, ����2i�͵�2i+1�Ƿ���ͬһ��ǿ��ͨ������, ֻҪ��, ��˵
��������Ҫ��, ���û��������.
 

����Խ�ͼ�ķ�ʽ��һ�����. ����, ����֪������i���ߺ͵�j���߹���һ���ı��ε�����
�Խ���, ��2i��2j������, ��2i��2i+1�б������һ��, ��2j��2j+1�б������һ��, ����
����˵2i+1��2j+1�����ٳ���һ��, �����2-SAT�ĺ�ȡʽ�е�"��"����·. ���仰˵, ��
2i��2j+1��һ������߱�ʾ���ѡ����2i�ͱ���ѡ��2j+1, ��2j��2i+1��һ������߱�ʾ��
��ѡ����2j�ͱ���ѡ��2i+1, ͬ�����2i+1��2j+1�Ĳ�����Ҳ���������������, �������
����������������˫���.
*/
#include<iostream>
#include<vector>
using namespace std;
const int MAXN    = 1010;
const char NOTVIS = 0x00;   //����û�з��ʹ���״̬
const char VIS     = 0x01;   //������ʹ�,��û��ɾ����״̬
const char OVER    = 0x02;   //����ɾ����״̬

vector<int> adj[MAXN]; //�����ڽӱ�
int num[MAXN];
int n,m;

char     flag[MAXN];         //���ڱ�Ƕ���״̬,״̬��NOTVIS,VIS,OVER
int      belg[MAXN];         //�洢ǿ��ͨ����,����belg[i]��ʾ����i���ڵ�belg[i]��ǿ��ͨ����
int      stck[MAXN];         //��ջ,��������
int      mlik[MAXN];         //�ܹؼ�,�����ڽӵ�δɾ���������С����ʱ��
int      indx[MAXN];         //�������ʱ��
struct{int x,y;}dr[MAXN];   //��¼door�ϵ������� 
#define opp(x) ((x)^1)
//opp[i]��ʾ��i��ͻ��Ԫ�ء���ͬ���Կ�ס�

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
         if ( mlik[cur]>indx[adj[cur][i]] ) 
		  //�ò��ֵ�indxӦ����mlik,���Ǹ����㷨������,ʹ��indxҲ����,��ʱ�����
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
//Tarjan�㷨,���belg[1..n],�ҷ���ǿ��ͨ��������,
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
	for(int i=0;i<n;++i) if(belg[i]==belg[opp(i)]) return false;
	return true;
}



int main()
{
	int i,j;
	while(scanf("%d%d",&m,&n)!=EOF)
    {
      for(i=0;i<n;++i) scanf("%d%d",&dr[i].x,&dr[i].y);
      n=n<<1;
      for(i=0;i<n;++i) adj[i].clear();
      n=n>>1;
      for(i=0;i<n;++i) {
		for(j=i+1;j<n;++j) {
			if (   (dr[i].x>dr[j].x&&dr[i].y>dr[j].y&&dr[j].y>dr[i].x)
			   ||(dr[j].y>dr[i].y&&dr[j].x>dr[i].y&&dr[i].y>dr[j].x)   )
			{
				adj[i+i].push_back(opp(j+j));
				adj[opp(j+j)].push_back(i+i);
				adj[j+j].push_back(opp(i+i));
				adj[opp(i+i)].push_back(j+j);
			}
		}	
	  }
	  n=n<<1;
	  Tarjan();
	  if(judge()) printf("panda is telling the truth...\n");
	  else printf("the evil panda is lying again\n");
    }
    return 0;
}
