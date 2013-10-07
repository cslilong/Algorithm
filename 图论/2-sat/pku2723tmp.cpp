#include<iostream>
#include<vector>
using namespace std;
const int MAXN    = 4010;
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
int opp[MAXN]; //opp[i]��ʾ��i��ͻ��Ԫ�ء���ͬ���Կ�ס�

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
	for(int i=0;i<n;++i) if(belg[i]==belg[opp[i]]) return false;
	return true;
}

bool check(int ans)
{
	for(int i=0;i<n;i++) adj[i].clear();    
    for(int i=0;i<ans;i++)//��ͼ�� ����Ҫ���Կ����a��bʱ�����Ǿ�����~a->b,~b->a 
    {//��ǰans���ŵ�Կ�ף�����һ��ͼ��
        adj[dr[i].x].push_back(opp[dr[i].y]);
        adj[dr[i].y].push_back(opp[dr[i].x]);
    }
    Tarjan();
    for(int i=0;i<n;++i) if(belg[i]==belg[opp[i]]) return false;
	return true;
}

void input(){
    int a,b;
    for(int i=0;i<n;i++){//n��Կ��         
        scanf("%d%d",&a,&b);
        opp[a] = b;//opp��ʾ���飬ì�ܵ� 
        opp[b] = a;
    }
    for(int i=0;i<m;i++)//����Ϣ����dr[] 
        scanf("%d%d",&dr[i].x,&dr[i].y);    
}

int main(){
    while(scanf("%d%d",&n,&m)!=EOF){//�������������� 
        if(n==0) break;
		input();
        n=n<<1;
        int left=1, right=m, mid;//rΪ��࿪����������ʼ��ΪM���� ��r=rigth l=left 
        while(left<right)// ���ִ𰸣��� 
        {
            if(left==right-1){
                if(!check(right))
                    right = left;
                break;
            }
            mid = (left + right)/2;
            if(check(mid))
                left = mid;//��k���У�˵���������ұߣ���left��Ϊk 
            else
                right = mid-1;//�������������ߣ�right��Ϊk 
        }
        //cout<<right<<endl;
        printf("%d\n",right);
    }
    return 0;
}
