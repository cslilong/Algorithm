AC�Զ���

��������
AC�Զ�����Aho-Corasick��,��һ��������Զ�������ͨ����tire�������һЩ����ı���ɣ�����Ĳ����Ǻ�׺�ڵ�Ĺ�����
AC�Զ�����Ҫ�����������һ��മƥ������⣺
�������ģʽ��s1,s2,...,Sn��ȷ������S���Ƿ��������һ��ģʽ����
·���ַ���
��tire���ϣ�ĳ���ڵ��·���ַ�����ָ��tire�ĸ��ڵ㵽�ýڵ��·���ϵı��ϵ��ַ����������γɵ��ַ�����
��׺�ڵ�
��tire���У�һ���ڵ�x�ĺ�׺�ڵ�Ϊtire���ϵ�һ���Ǳ���ڵ�y������y��·���ַ���Ϊx��·���ַ��������к�׺�г�����tire���ϵ����һ������׺�ڵ�ĸ����KMP�е�ǰ׺��������ƣ��乹�췽��Ҳ���ơ�
����ͼ��5�Žڵ��Ӧ�ַ���Ϊabab����������tire���ϵ����׺Ϊab����Ӧ�ڵ�3�Žڵ㡣
AC�Զ����Ĺ��죺
��1������һ��tire��
��2������ÿ���ڵ�ĺ�׺�ڵ�
���룺tire��
�����tire���ĺ�׺�ڵ�����
α���룺
��root�����
pre[root]=-1;
while(���в�Ϊ��) {
     x = �����ײ�
     for( x�ı��Ϊc�Ķ���i ) {
          tmp = pre[x];
          while(tmp��=-1 &&��tmp�����б��Ϊc�Ķ���) tmp = pre[tmp];
          if(tmp==-1) pre[i]=root;
          else tmp = tmp�ı��Ϊc�Ķ��ӽڵ�
          ��i�����     
     }
}

ƥ�����
��ͷ��βƥ������������������ɨ�赽���ַ�ͬ������AC�Զ����б�����ÿ����һ�������ڵ�ͱ�ʾ�����г�����ĳ��ģʽ��������ͼ��ģʽ��Ϊ"a","aaa","aba","baa","bb", ����Ϊ��aabababbaaa��,��ô���������Ľڵ���1��2��3��7��8��7��7��5��9��10��6

AC�Զ���ģ��
#include <cstdio>
#include <cstdlib>
#include <queue>

using namespace std;
/*
HDU2222 http://acm.hdu.edu.cn/showproblem.php?pid=2222
AC�Զ���
��1��������Ӵ��ǿ�����ͬ�ģ���ʱTrie��ÿ�����Ҫ��һ��mulֵ����ʾ�ý���Ӧ���ַ����������Ӵ����ظ��Ĵ�����
���⣬��ҪΪ��ʡ�ռ��mul�����char�ͣ��п������е��ַ���ȫ��ͬ�������Ҫ�����int����ʵ֤�����ᱬ�ռ䣩�����Ǳ�ɳ�豻��ĥ����ô�õ���Ҫԭ��
��2��Trie���þ�̬�洢��0�Ž����Ϊ�ս�㣨NULL������������Ľ���Ŵ�1��ʼ������rootһ�㶼��1�Ž�㣻
��3��ע���ڽ����Զ����Լ�ƥ���ʱ������Ҫ��fail���ݵĵط�����߽綼��0��NULL��ע�ⲻ��root�������ҵ�һ���ж�Ӧ�ӽ��Ľ�㡣
ע�⵽0��û���ҵ��Ĵ��������ڽ����Զ�����ʱ�򣬽�T[j]��Ϊroot����ƥ���ʱ�򣬽�x��Ϊroot��
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
// tire ���Ĳ���
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
          //ƥ������е�һ�����Ż��ĵط�������һ����x�Լ��������з��ؽ�㣨�������������x��ʧ��ָ�벻������ֱ��root·���ϵĽ�㶼��Ϊ���ؽ�㣩�����ڲ����ظ����������Խ����ǵ�mulֵ��Ϊԭ��mulֵ���෴����-mul����������0����ʾ�ý���Ѿ�ͳ�ƹ�����������һ��y�����ݹ�����һ������һ��mulֵΪ���ĵ�Ͳ��ü��������ˣ���Ϊ����ĵ�һ��Ҳ�Ѿ�ͳ�ƹ��ˡ�
          //��Ȼ��������ڵ�����������Ƕ���������Ҫ��ÿ��ƥ��֮ǰ��Trie�������н���mulֵ������Ǹ����ĵĻ���ȫ������ȡ����Ϊ�˽�ʡʱ�䣬������ƥ������а�����ͳ�ƹ��ģ�mulֵ��Ϊ�����ģ����ȫ���Ž�һ�������Ķ����Ȼ��ȡ��ʱֻҪ��������еĽ������ˡ�
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

