/*
---title: [PKU][2723][Get Luffy Out]
----link: http://acm.pku.edu.cn/JudgeOnline/problem?id=2723
-problem: ��m����, ����ǰһ�����ܿ���һ��, ÿ������������, ��һ�Ѿ��ܿ���, ��Щ����������ȫ��ͬ. ��2n�Ѳ�ͬ��Կ��, ÿ�Ѷ�Ӧһ����, ��ЩԿ�ױ��ֳ�n��, ÿ��Կ��ֻ��ȡ���е�һ��, ȡ����һ��, ��һ�Ѿͻ���ʧ, ������ܿ�������.

solution: 2-SAT, ����
ֱ�ӽⲢ������, ��������ע�⵽, 
�����Ž��ܿ�x����, ��ô�Ϳ϶��ܿ�y����(y<=x), ��������Ľ�;��е�����, ���Զ��ִ�Ȼ���ж��Ƿ����ì��. 

����2-SAT��׼����, ��ÿ��Կ�׶�Ӧ��ͼ�е���������, �ֱ��ʾȡ�Ͳ�ȡ,
 ����������, �����(��avb)��(a->b)�ĵȼ۹�ϵ�Ͳ���, ����������Ҳ����Ҫ�������¼����߼�ʽ(����Ҫ��k����):
1. ǰk����, ÿ�����ϵ�������Ҫ��һ��.
2. ÿ��Կ��������Ҫ��һ�Ѳ�ȡ. (�������е��Ť)
���е�����, �ǿɼӿɲ��ӵ�: ÿ��Կ��������ȡһ��. ����߼�ʽ������񲢲���Ӱ�����ս��.
֪����ô��ͼ֮����Ƕ��ִ�, ÿ�����½�ͼ, ��ģ��, ��ì��.
����WA�˺ü���, ��Ϊ���ֵ��Ͻ�����1. ע�����������ݵ�ʱ����ȡ��������, �������ȡ��ȫ��������Ŵ�.
*/
#include<iostream>
#include<vector>
using namespace std;
const int MAXN = 4000;

vector<int> mapA[MAXN],mapB[MAXN]; //mapB��mapA�ķ���ͼ 
struct{int x,y;}dr[MAXN];   //��¼door�ϵ������� 
int opp[MAXN]; //opp[i]��ʾ��i��ͻ��Ԫ�ء���ͬ���Կ�ס�

bool vist[MAXN];    //dfs�� 
int path[MAXN];     //dfs�ã���·�� 
int belong[MAXN];   //dfs�ã������������SCC��

int n,m,cnt,c_id;   //cnt����·��������c_idΪ��ͨ�����ı��


void dfsA(int v){ //���2N��Կ�׽�㣬����DFS������������ͨ���� 
    vist[v]=1;
    for(int i=0;i<mapA[v].size();i++)
        if(vist[mapA[v][i]]==0)
            dfsA(mapA[v][i]);
    path[cnt++]=v;
}

void dfsB(int v){//�ڷ�ͼ��DFS���ҳ����е�������SCC��ţ�����belong[] 
    vist[v]=1;
    belong[v] = c_id;//��c_id����ͨ�������б�š� 
    for(int i=0;i<mapB[v].size();i++)
        if(vist[mapB[v][i]]==0)
            dfsB(mapB[v][i]);
}

bool check(int ans)    //2-SAT����,����ans�Ƿ�Ϊ���д� 
{
    for(int i=0;i<2*n;i++){//����ͼ��� 
        mapA[i].clear();
        mapB[i].clear();
    }
    
    for(int i=0;i<ans;i++)//��ͼ�� ����Ҫ���Կ����a��bʱ�����Ǿ�����~a->b,~b->a 
    {//��ǰans���ŵ�Կ�ף�����һ��ͼ��
        mapA[dr[i].x].push_back(opp[dr[i].y]);
        mapA[dr[i].y].push_back(opp[dr[i].x]);
        mapB[opp[dr[i].y]].push_back(dr[i].x);
        mapB[opp[dr[i].x]].push_back(dr[i].y);
    }
    
    memset(vist,0,sizeof(vist));
    cnt=0;
    for(int i=0;i<2*n;i++)
        if(vist[i]==0)
            dfsA(i);

    memset(vist,0,sizeof(vist));        
    c_id=1;
    for(int i=cnt-1;i>=0;i--)
        if(vist[path[i]]==0){
            c_id++;
            dfsB(path[i]);
        }

    for(int i=0;i<2*n;i++)
        if(belong[i] == belong[opp[i]])//����ì�ܣ�����SCC������ 
            return false;
    return true;
}

void input(){
    int a,b;
    for(int i=0;i<n;i++){//n��Կ�� 
        //cin>>a>>b;
        scanf("%d%d",&a,&b);
        opp[a] = b;//opp��ʾ���飬ì�ܵ� 
        opp[b] = a;
    }
    for(int i=0;i<m;i++)//����Ϣ����dr[] 
        //cin>>dr[i].x>>dr[i].y;
        scanf("%d%d",&dr[i].x,&dr[i].y);
    
}

int main(){
    while(scanf("%d%d",&n,&m)!=EOF){//�������������� 
        if(n==0) break;
		input();
        
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
