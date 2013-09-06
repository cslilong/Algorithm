AC自动机

基本概念
AC自动机（Aho-Corasick）,是一种特殊的自动机，是通过在tire树上添加一些额外的边组成，其核心部分是后缀节点的构建。
AC自动机主要解决的问题是一类多串匹配的问题：
给定多个模式串s1,s2,...,Sn，确定主串S中是否包含任意一个模式串。
路径字符串
在tire树上，某个节点的路径字符串是指从tire的根节点到该节点的路径上的边上的字符串连起来形成的字符串。
后缀节点
在tire树中，一个节点x的后缀节点为tire树上的一个非本身节点y，并且y的路径字符串为x的路径字符串的所有后缀中出现在tire树上的最长的一个。后缀节点的概念和KMP中的前缀数组很相似，其构造方法也相似。
如下图，5号节点对应字符串为abab，它出现在tire树上的最长后缀为ab，对应节点3号节点。
AC自动机的构造：
（1）建立一棵tire树
（2）计算每个节点的后缀节点
输入：tire树
输出：tire树的后缀节点数组
伪代码：
将root如队列
pre[root]=-1;
while(队列不为空) {
     x = 队列首部
     for( x的标记为c的儿子i ) {
          tmp = pre[x];
          while(tmp！=-1 &&　tmp不含有标记为c的儿子) tmp = pre[tmp];
          if(tmp==-1) pre[i]=root;
          else tmp = tmp的标记为c的儿子节点
          将i入队列     
     }
}

匹配过程
重头到尾匹配主串，根据主串中扫描到的字符同步的在AC自动机中遍历，每经过一个结束节点就表示主串中出现了某个模式串。如下图，模式串为"a","aaa","aba","baa","bb", 主串为”aabababbaaa“,那么遍历经过的节点有1，2，3，7，8，7，7，5，9，10，6

AC自动机模板
#include <cstdio>
#include <cstdlib>
#include <queue>

using namespace std;
/*
HDU2222 http://acm.hdu.edu.cn/showproblem.php?pid=2222
AC自动机
（1）本题的子串是可以相同的，此时Trie的每个结点要设一个mul值，表示该结点对应的字符串在所有子串中重复的次数，
另外，不要为了省空间把mul定义成char型，有可能所有的字符串全相同，因此需要定义成int（事实证明不会爆空间），这是本沙茶被折磨了这么久的主要原因；
（2）Trie采用静态存储，0号结点作为空结点（NULL），因此真正的结点编号从1开始，另外root一般都是1号结点；
（3）注意在建立自动机以及匹配的时候，所有要沿fail上溯的地方，其边界都是0（NULL，注意不是root）或者找到一个有对应子结点的结点。
注意到0还没有找到的处理方法：在建立自动机的时候，将T[j]置为root；在匹配的时候，将x置为root；
*/
typedef struct {
     int mark;  // attention
     int son[26];
     int suffix;
}Node;

const int MAXN=5000001;
Node T[MAXN];
int root,num;
char str[1000010];
// tire 树的插入
void insert(char* s)
{
     int len = strlen(s);
     int index = root;
     for(int i=0;i<len;++i) {
          if(T[index].son[s[i]-'a']==0) {
               num++;
               T[num].mark=0;
               for(int j=0;j<26;++j) T[num].son[j]=0;
               if(i==len-1) T[num].mark++;
               T[index].son[s[i]-'a']=num;
               index = num;
          } else {
               index = T[index].son[s[i]-'a'];
               if(i==len-1) T[index].mark++;
          }
     }    
}

void MakeSuffix()
{
     queue<int> q;
     int x,k,tmp;
     q.push(root);
     while(!q.empty()) {
          x=q.front(); q.pop();
          for(int i=0;i<26;++i) {
               k = T[x].son[i];
               if(k>0) {
                    tmp = T[x].suffix;
                    while(tmp!=-1 && T[tmp].son[i]==0) tmp=T[tmp].suffix;
                    if(tmp==-1) T[k].suffix=root;
                    else T[k].suffix= T[tmp].son[i];
                    q.push(k);
               }
          }
     }
}

int sovle(char *s)
{
     int k,res=0;
     int len = strlen(s);
     int c,tmp,index = root;
     for(int i=0;i<len;++i) {
          c=s[i]-'a';
          while(index>0 && T[index].son[c]==0) index=T[index].suffix;
          if(index==-1) index = root;
          else index = T[index].son[c];
          tmp = index;
          //匹配过程中的一个可优化的地方：对于一个点x以及它的所有返回结点（这里把所有沿着x的失败指针不断上溯直到root路径上的结点都称为返回结点），由于不可重复计数，可以将它们的mul值置为原来mul值的相反数（-mul），而不是0，表示该结点已经统计过。这样在下一次y的上溯过程中一旦发现一个mul值为负的点就不用继续上溯了，因为上面的点一定也已经统计过了。
          //当然，这仅限于单主串，如果是多主串则需要在每次匹配之前把Trie树中所有结点的mul值（如果是负数的的话）全部重新取反。为了节省时间，可以在匹配过程中把所有统计过的（mul值改为负数的）结点全部放进一个辅助的队列里，然后取反时只要处理队列中的结点就行了。
          while(tmp>0 && T[tmp].mark>=0) {
               res+=T[tmp].mark;
               T[tmp].mark=-T[tmp].mark;
               tmp = T[tmp].suffix;
          }
     }
     return res;
}


/*
input :
1
5
she
he
say
shr
her
yasherhs
output:
3
*/
int main()
{
     int ncase,n;
     char s[55];
     scanf("%d",&ncase);
     while(ncase--) {
          root=1;num=1;
          T[root].mark=0;T[root].suffix=-1;
          for(int j=0;j<26;++j) T[root].son[j]=0;
          scanf("%d",&n);
          while(n--) {
               scanf("%s",s);
               insert(s);
          }
          MakeSuffix();
          scanf("%s",str);
          printf("%d\n",sovle(str));
     }
     return 0;
}

