#include <iostream>
using namespace std;
#define MAX_VERTICES 50
#define true 1
#define false 0
#define MIN(x,y) ((x) < (y) ? (x) : (y))
typedef struct node *node_pointer;
struct node {
         int vertex;
         struct node *link;        
};

node_pointer graph[MAX_VERTICES];

int n = 0;
int dfn[MAX_VERTICES];
int low[MAX_VERTICES];

typedef struct {
    int v;
    int w;  
}edge;
edge edges[100];
int top = 0;


int num = 0;

void printG() {
     int i;
     node_pointer e;
     for(i=0;i<=n;i++) {
         printf("[%d]",i);
        for(e=graph[i];e;e=e->link)
           printf(" (%d)->",e->vertex);
         printf("\n");
     }    
}

void printDfnLow() {
     int i = 0;
     while(i<=n) {
         printf("[%d]: dfn:%d   low:%d\n", i, dfn[i], low[i]);
         ++i;
     }    
}


void addEdge(int v, int w) {
     node_pointer e = (node_pointer)malloc(sizeof(struct node));
     e->vertex = w;
     e->link = graph[v];
     graph[v] = e;
}
//����ͼ��һ�������ڽӱ��ж�Ӧ�����ڵ㣬1->2,2->1
void addREdge(int v,int w){
     addEdge(v,w);
     addEdge(w,v);    
}


void init() {
   int i = 0;
   n = 9; //0 to n
   while(i<=n) {
       graph[i] = 0;
      
       dfn[i] = low[i] = -1;
       i++;
   }
  
   num = 0;
  

   addREdge(3,5);
   addREdge(5,7);
   addREdge(5,6);
  
   addREdge(6,7);
   addREdge(7,9);
   addREdge(7,8);
   addREdge(0,1);
   addREdge(1,2);
   addREdge(1,3);
   addREdge(2,4);
   addREdge(4,3);
  
}

void dfnlow(int u, int v) {
     node_pointer ptr;
     int w;
     dfn[u] = low[u] = num++;
     for(ptr = graph[u]; ptr; ptr = ptr->link) {
         w = ptr->vertex;
         if(dfn[w] < 0) {
             dfnlow(w, u);
             low[u] = MIN(low[u], low[w]);          
         } else if( w != v)
             low[u] = MIN(low[u], dfn[w]);      
      }
 }

 void bicon(int u, int v) {
      node_pointer ptr;
      int w;
      edge e;
      dfn[u] = low[u] = num++;
     
      for(ptr = graph[u]; ptr; ptr = ptr->link) {
          w = ptr->vertex;

          if(v!=w && dfn[w] < dfn[u]) { //v!=w   to avoid 1->2 2->1 in undirected graph
                                        // dfn[w] < dfn[u] to avoid visited vertex who is decendant of u
                  edges[top].v = u; // �±�ѹջ,v!=w�Ƿ�ֹ�ظ���������ͼ��ͬһ����
                                      //dfn[w]<dfn[u] �Ƿ�ֹ�ظ�������˱�,��Ϊdfs������,
                                    //�����Ķ���ֻ���������,dfn[w]=-1�µ�, dfn[w]<dfn[u]
                                      //u,w �ǻ��˱ߡ����ߵĹ�ͬ���� dfn[w] < dfn[u],������
                                    //�߰�����G�����б�,��˶������ߵķ������ظ��ġ�
                  edges[top].w = w;
                  ++top;
                  if(dfn[w]< 0) { //������¶���(δ���ʹ�)
                      bicon(w,u);     //�ݹ����            
                      low[u] = MIN(low[u], low[w]);// ���µ�ǰu��low
                     
                      if(low[w] >= dfn[u]) { //�������u�ĺ���w ����������˵��u�ǹؽڵ�
                          printf("New biconnected component:\n");
                          do{
                              e = edges[--top]; //��ʱջ���������biconѹ��ķ��ʹ��ı�,
                                                //���ùؽڵ��µ������ߺͻ��˱�
                              printf("<%d,%d>", e.v, e.w);
                          }while( !(e.v == u && e.w == w));
                          printf("\n");
                        }        
                  } else if (w!=v){
                        low[u] = MIN(low[u], dfn[w]);
                  }    
          }
      }    
 }
 int main(){
      init();
      printG();
     //dfnlow(3,-1);
      bicon(3,-1);
      printDfnLow();
      getchar();
 }
