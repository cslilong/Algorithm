/*
---title: [PKU][2723][Get Luffy Out]
----link: http://acm.pku.edu.cn/JudgeOnline/problem?id=2723
-problem: 有m道门, 开了前一道才能开后一道, 每道门上两把锁, 开一把就能开门, 这些锁并不是完全不同. 有2n把不同的钥匙, 每把对应一种锁, 这些钥匙被分成n对, 每对钥匙只能取其中的一把, 取其中一把, 另一把就会消失, 问最多能开几道门.

solution: 2-SAT, 二分
直接解并不容易, 但是容易注意到, 
若最优解能开x道门, 那么就肯定能开y道门(y<=x), 这样问题的解就具有单调性, 可以二分答案然后判断是否存在矛盾. 

按照2-SAT标准步骤, 把每把钥匙对应到图中的两个顶点, 分别表示取和不取,
 还是老样子, 理解了(┐avb)与(a->b)的等价关系就不难, 用文字描述也就是要满足以下几个逻辑式(假设要开k道门):
1. 前k道门, 每道门上的锁至少要打开一把.
2. 每对钥匙中至少要有一把不取. (听起来有点别扭)
还有第三条, 是可加可不加的: 每对钥匙中至少取一把. 这个逻辑式存在与否并不会影响最终结果.
知道怎么建图之后就是二分答案, 每次重新建图, 套模板, 判矛盾.
这题WA了好几次, 因为二分的上界少了1. 注意做测试数据的时候尽量取极端数据, 这里就是取门全开的情况排错.
*/
#include<iostream>
#include<vector>
using namespace std;
const int MAXN = 4000;

vector<int> mapA[MAXN],mapB[MAXN]; //mapB是mapA的反向图 
struct{int x,y;}dr[MAXN];   //记录door上的两把锁 
int opp[MAXN]; //opp[i]表示与i冲突的元素。即同组的钥匙。

bool vist[MAXN];    //dfs用 
int path[MAXN];     //dfs用，存路径 
int belong[MAXN];   //dfs用，存各点所属的SCC号

int n,m,cnt,c_id;   //cnt用以路径计数、c_id为连通分量的标号


void dfsA(int v){ //针对2N个钥匙结点，进行DFS。遍历所有联通分量 
    vist[v]=1;
    for(int i=0;i<mapA[v].size();i++)
        if(vist[mapA[v][i]]==0)
            dfsA(mapA[v][i]);
    path[cnt++]=v;
}

void dfsB(int v){//在反图上DFS，找出所有点所属的SCC标号，存入belong[] 
    vist[v]=1;
    belong[v] = c_id;//用c_id对联通分量进行编号。 
    for(int i=0;i<mapB[v].size();i++)
        if(vist[mapB[v][i]]==0)
            dfsB(mapB[v][i]);
}

bool check(int ans)    //2-SAT主体,检验ans是否为可行答案 
{
    for(int i=0;i<2*n;i++){//两张图清空 
        mapA[i].clear();
        mapB[i].clear();
    }
    
    for(int i=0;i<ans;i++)//建图。 当门要求的钥匙是a或b时，我们就添置~a->b,~b->a 
    {//把前ans个门的钥匙，建成一张图。
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
        if(belong[i] == belong[opp[i]])//发现矛盾，整个SCC不成立 
            return false;
    return true;
}

void input(){
    int a,b;
    for(int i=0;i<n;i++){//n把钥匙 
        //cin>>a>>b;
        scanf("%d%d",&a,&b);
        opp[a] = b;//opp表示分组，矛盾点 
        opp[b] = a;
    }
    for(int i=0;i<m;i++)//门信息存入dr[] 
        //cin>>dr[i].x>>dr[i].y;
        scanf("%d%d",&dr[i].x,&dr[i].y);
    
}

int main(){
    while(scanf("%d%d",&n,&m)!=EOF){//锁子组数、门数 
        if(n==0) break;
		input();
        
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
