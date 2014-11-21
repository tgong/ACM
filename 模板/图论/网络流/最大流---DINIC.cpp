/****************************************************
*DINIC+当前弧度优化
*
******************************************************/
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<cmath>
#include<vector>
#include<queue>
#include<map>
#include<algorithm>

using namespace std;

const int maxn=10010;
const int maxm=100010;
const int inf=0x3f3f3f3f;

int n,m;
struct Edge
{
    int from,to,next;
    int cap;
}edge[maxm<<1];

int e,head[maxn];

int dist[maxn],cur[maxn];


void init()
{
    e=0;
    memset(head,-1,sizeof(head));
}

void addedge(int u,int v,int c)
{
    Edge e1={u,v,head[u],c};
    edge[e]=e1;head[u]=e++;

    Edge e2={v,u,head[v],0};
    edge[e]=e2;head[v]=e++;
}


int BFS(int s,int t)
{
    memset(dist,-1,sizeof(dist));
    queue<int> q;
    q.push(s);dist[s]=0;

    while (!q.empty())
    {
        int u=q.front();q.pop();
        for(int i=head[u];~i;i=edge[i].next)
        {
            int v=edge[i].to;
            if(dist[v]==-1&&edge[i].cap>0)
            {
                dist[v]=dist[u]+1;
                if(v==t) return 1;
                q.push(v);
            }
        }
    }
    return 0;
}

int DFS(int u,int maxf,int t)
{
    if(u==t||maxf==0) return maxf;

    int f,ans=0;
    for(int &i=cur[u];~i;i=edge[i].next) //注意这里的引用，使用了当前弧的优化
    {
        int v=edge[i].to;
        if(dist[v]==dist[u]+1&&(f=DFS(v,min(maxf,edge[i].cap),t))>0)
        {
            edge[i].cap-=f;
            edge[i^i].cap+=f;
            maxf-=f;
            ans+=f;
            if(maxf==0) return ans;
        }
    }
    return ans;
}


int dinic(int s,int t)
{
    int maxflow=0;
    while (BFS(s,t))
    {
        memcpy(cur,head,sizeof(head));
        maxflow+=DFS(s,inf,t);
    }
    return maxflow;
}


int main()
{
    int u,v,c;
    while (~scanf("%d%d",&n,&m))
    {
        init();
        while (m--)
        {
            scanf("%d%d%d",&u,&v,&c);
            addedge(u,v,c);
        }

        int maxflow=dinic(1,n);

        printf("%d\n",maxflow);
    }
	return 0;
}

