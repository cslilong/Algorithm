/*
��Ŀ���⣺

N����У֮����һЩ������������ӣ�N<100����������һ�����ʱ��ѧУi�յ����ʱ��
�����Խ�������͸����������ӵ���ѧУ������Ҫ�󷢲�һ�������������Ҫ�������ٸ�ѧУ��
ʹ������ѧУ�������յ����������A����������Ҫ��Ӷ����������������ӣ�
����ʹ�ý�������ⷢ��һ��ѧУ��ʹ������ѧУ�������յ�������B����

������
����������������A��������������Ļ���OIͼ�������н��ܹ�����������ͼ����С�����
���ȣ��������ͼ�ļ���ǿ��ͨ��������ͬһ��ǿ��ͨ�������ѧУ����һ���յ������
����ǿ��ͨ�������ѧУ�������յ�����ÿ��ǿ��ͨ��������һ���㣬����һ���µ������޻�ͼ��
��ǿ��ͨ����i�յ��������ôi�ɴ��ǿ��ͨ�����������յ������
���ǳ����Ϊ0��ǿ��ͨ����Ϊ���ǿ��ͨ��������Ȼ��ÿ�����ǿ��ͨ���������뵥������һ�������
������ǿ��ͨ����������ͨ�����ǿ��ͨ����������ԣ����ǿ��ͨ�����ĸ���Ҳ��������A�Ľ⡣
��������B���Ҳ²���MAX(���Ϊ0�ĵ�ĸ���,����Ϊ0�ĵ�ĸ���)��û�뵽��Ȼ���ˣ�Ҳû��ϸ֤����
ע����ǣ���ԭͼֻ��һ��ǿ��ͨ�����ǣ�����B�Ĵ���0��
*/

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
int in_num[MAXN],out_num[MAXN];

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
   int i,j,k, sig, scc_num;
   memset(flag+1,NOTVIS,sizeof(char)*n);
   sig = 0; scc_num = 0; stck[0] = 0;
   for ( i=1; i<=n; ++i )
   {
      if ( NOTVIS==flag[i] )
      {
          Visit(i,sig,scc_num);
      }
   }
   for(i=1;i<=n;++i){  in_num[i]=0; out_num[i]=0; }
   //for(i=1;i<=n;++i) ++num[belg[i]];
    //int	maxsum=0;
//	for(i=1;i<=n;++i) if(num[i]>maxsum) maxsum=num[i];
	//printf("%d\n",maxsum);

   for(i=1;i<=n;++i) {
	   int len = adj[i].size();
	   for(k=0;k<len;++k) {
		   j=adj[i][k];
		   if(belg[i]!=belg[j]) {
			   ++in_num[belg[j]];
			   ++out_num[belg[i]];
		   }
	   }
   }
   if(scc_num==1) {
	   printf("1\n0\n");
   } else {
   int in_sum=0;
   int out_sum=0;
   for(i=1;i<=scc_num;++i){
	   if(in_num[i]==0) in_sum++;
	   if(out_num[i]==0) out_sum++;
   }
   if(in_sum>out_sum) out_sum=in_sum;
   printf("%d\n%d\n",in_sum,out_sum);
   }
   return scc_num;
} 


int main()
{
	int m,i,x,y;
	while(scanf("%d",&n)!=EOF) {		
		for(i=1;i<=n;++i) { adj[i].clear();  }
		for(i=1;i<=n;++i) {
		while(scanf("%d",&m)==1) {
			if(m==0) break;		
			adj[i].push_back(m);			
		}
		}
		Tarjan();
	}	
	return 0;
}