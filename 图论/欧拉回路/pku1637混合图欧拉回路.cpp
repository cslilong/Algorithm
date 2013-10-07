/*
混合图欧拉回路 //转自某位牛人blog 
原来混合图欧拉回路用的是网络流。 
把该图的无向边随便定向，计算每个点的入度和出度。如果有某个点出入度之差为奇数，那么肯定不存在欧拉回路。
因为欧拉回路要求每点入度 = 出度，也就是总度数为偶数，存在奇数度点必不能有欧拉回路。 
好了，现在每个点入度和出度之差均为偶数。那么将这个偶数除以2，得x。
也就是说，对于每一个点，只要将x条边改变方向（入>出就是变入，出>入就是变出），就能保证出 = 入。
如果每个点都是出 = 入，那么很明显，该图就存在欧拉回路。 
现在的问题就变成了：我该改变哪些边，可以让每个点出 = 入？构造网络流模型。
首先，有向边是不能改变方向的，要之无用，删。
一开始不是把无向边定向了吗？定的是什么向，就把网络构建成什么样，边长容量上限1。
另新建s和t。对于入 > 出的点u，连接边(u, t)、容量为x，对于出 > 入的点v，连接边(s, v)，容量为x（注意对不同的点x不同）。
之后，察看是否有满流的分配。有就是能有欧拉回路，没有就是没有。欧拉回路是哪个？
察看流值分配，将所有流量非 0（上限是1，流值不是0就是1）的边反向，就能得到每点入度 = 出度的欧拉图。 
由于是满流，所以每个入 > 出的点，都有x条边进来，将这些进来的边反向，OK，入 = 出了。
对于出 > 入的点亦然。那么，没和s、t连接的点怎么办？和s连接的条件是出 > 入，和t连接的条件是入 > 出，
那么这个既没和s也没和t连接的点，自然早在开始就已经满足入 = 出了。那么在网络流过程中，这些点属于“中间点”。
我们知道中间点流量不允许有累积的，这样，进去多少就出来多少，反向之后，自然仍保持平衡。 
所以，就这样，混合图欧拉回路问题，解了。 
*/ 
#include <iostream>
#include <algorithm>
#include <cstring>
#include <cstdio>
using namespace std;
const int MAXN = 210;
const int MAXM = 4000;
const int INF = 1 << 30;
struct Edge {
     int idx, flow;
     Edge *next, *opp;
};
Edge *adj[MAXN], memo[MAXM];
int mset, lv[MAXN];
void addEdgeProcess(int u, int v, int w) {
     Edge *ptr = &memo[mset ++];
     ptr -> idx = v;
     ptr -> flow = w;
     ptr -> next = adj[u];
     adj[u] = ptr;
}
void addEdge(int u, int v, int w) {
     addEdgeProcess(u, v, w);
     addEdgeProcess(v, u, 0);
     adj[u] -> opp = &memo[mset - 1];
     adj[v] -> opp = &memo[mset - 2];
}
bool bfs(int s, int t) {
     int head, tail, q[MAXN];
     head = tail = 0;
     q[tail ++] = s;
     for(int i = s; i <= t; i ++) lv[i] = -1;
     lv[s] = 0;
     while(head < tail) {
          int u = q[head ++];
          for(Edge *ptr = adj[u]; ptr; ptr = ptr -> next) {
               int v = ptr -> idx;
               if(lv[v] == -1 && ptr -> flow > 0) {
                    lv[v] = lv[u] + 1;
                    q[tail ++] = v;
                    if(v == t) return true;
               }
          }
     }
     return false;
}
int dicnic(int s, int t) {
     int max_flow = 0;
     int i, u, top, p[MAXM];
     Edge *pre[MAXN], *cur[MAXN];
     while(bfs(s, t)) {
          p[top = 1] = u = s;
          for(i = s; i <= t; i ++) cur[i] = adj[i];
          while(cur[s]) {
                if(u != t && cur[u] && cur[u] -> flow > 0 && lv[u] + 1 == lv[cur[u] -> idx]) {
                      int v = cur[u] -> idx; p[++ top] = v;
                      pre[v] = cur[u];
                      u = v;
                }else if(u == t) {
                      int mn = INF;
                      for(i = top; i > 1; i --) {
                            mn = min(mn, pre[p[i]] -> flow);
                      }
                      for(i = top; i > 1; i --) {
                            pre[p[i]] -> flow -= mn;
                            pre[p[i]] -> opp -> flow += mn;
                            if(pre[p[i]] -> flow == 0) top = i - 1;
                      }
                      u = p[top];
                      max_flow += mn;
                }else {
                      while(u != s && cur[u] == NULL) u = p[-- top];
                      cur[u] = cur[u] -> next;
                }
          }
     }
     return max_flow;
}
int main() {
     int casn;
     scanf("%d", &casn);
     while(casn --) {
          int i, m, n;
          int in[MAXN], out[MAXN];
          memset(in, 0, sizeof(in));
          memset(out, 0, sizeof(out));
          scanf("%d %d", &m, &n);
          int s = 0, t = m + 1;
          for(i = s; i <= t; i ++) adj[i] = 0;
          int u, v, tag;
          mset = 0;
          for(i = 1; i <= n; i ++) {
               scanf("%d %d %d", &u, &v, &tag);
               if(u == v) continue;
               in[v] ++; out[u] ++;
               if(tag == 0) addEdge(u, v, 1);
          }
          int sum = 0;
          for(i = 1; i <= m; i ++) {
               out[i] -= in[i];
               if(out[i] & 1) break;
               out[i] >>= 1;
               if(out[i] > 0) {
                     sum += out[i];
                     addEdge(s, i, out[i]);
               }else if(out[i] < 0) {
                     addEdge(i, t, -out[i]);
               }
          }
          if(i == m + 1 && sum == dicnic(s, t)) printf("possible\n");
          else printf("impossible\n");
     }
     return(0);
}

