#include<iostream>
using namespace std;
int visit[1100],low[1100];
int cs=1,n,result;
int map[1100][1100];
bool cute[1100];
int tot[1100];
bool flag[1100];
void init(){
      memset(visit,0,sizeof(visit));
      memset(cute,0,sizeof(cute));
      memset(tot,0,sizeof(tot));
      memset(map,0,sizeof(map));
      n=0;
}
void dfs(int k,int sign){
     visit[k]=sign;
     int mins=sign;
     for(int i=1;i<=map[k][0];i++){
         if(visit[map[k][i]]==0){
             tot[k]++;
             dfs(map[k][i],sign+1);
             if(low[map[k][i]]<mins) mins=low[map[k][i]];
             if(k!=1 && low[map[k][i]]>=visit[k]) cute[k]=true;
             if(k==1 && tot[k]>1) cute[k]=true;
         }
         else if(visit[map[k][i]]<mins) mins=visit[map[k][i]];
     }
     low[k]=mins;
}
void dfs1(int k){
     flag[k]=true;
     for(int i=1;i<=map[k][0];i++)
          if(!flag[map[k][i]])
               dfs1(map[k][i]);       
}
void solve(){
     bool ok=false;
     dfs(1,1);
     for(int i=1;i<=n;i++){
          if(cute[i]){
               ok=true;
               memset(flag,0,sizeof(flag));
               flag[i]=true; result=0;
               for(int j=1;j<=map[i][0];j++){
                     if(!flag[map[i][j]]){
                         dfs1(map[i][j]);
                         result++;
                     }       
               }    
               printf("  SPF node %d leaves %d subnets\n",i,result);   
          }       
     }
     if(!ok) printf("  No SPF nodes\n");
     printf("\n");
}
int main(){
    int x,y;
    while(true){
         scanf("%d",&x);
         if(x==0) break;
         init();
         scanf("%d",&y);
         map[x][++map[x][0]]=y;
         map[y][++map[y][0]]=x;
         if(x>n) n=x;
         if(y>n) n=y;
         while(true){
              scanf("%d",&x);
              if(x==0) break;
              scanf("%d",&y);
              map[x][++map[x][0]]=y;
              map[y][++map[y][0]]=x;
              if(x>n) n=x;
              if(y>n) n=y;        
         }     
         printf("Network #%d\n",cs++);
         solve();    
         //printf("\n");
    }
    //system("pause");
    return 0;
}