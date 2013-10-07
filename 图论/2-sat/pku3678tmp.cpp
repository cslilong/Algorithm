#include<iostream>
#include<vector>
using namespace std;
const int MAXN    = 10010;
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
