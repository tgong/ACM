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
const int INF=0x3f3f3f3f;

int n,m;
struct Edge
{
    int from,to,next;
    int cap;
}edge[maxm];
int e,head[maxn];

int pre[maxn],vis[maxn],path[maxm];

void init()
{
    e=0;
    memset(head,-1,sizeof(head));
}

void addedge(int u,int v,int w)
{
    edge[e].from=u;edge[e].to=v;edge[e].cap=w;
    edge[e].next=head[u];head[u]=e++;

    edge[e].from=v;edge[e].to=u;edge[e].cap=0;
    edge[e].next=head[v];head[v]=e++;
}

int BFS(int s,int t)
{
    memset(vis,0,sizeof(vis));
    queue<int> q;
    q.push(s);vis[s]=1;

    int u,v;
    while (!q.empty())
    {
        u=q.front();q.pop();

        for(int i=head[u];i!=-1;i=edge[i].next)
        {
            v=edge[i].to;
            if(!vis[v]&&edge[i].cap>0)
            {
                q.push(v);vis[v]=1;
                pre[v]=u;path[v]=i;
                if(v==t) return 1;
            }
        }
    }
    return 0;
}

int ek(int s,int t)
{
    int aug,maxflow=0;
    while (BFS(s,t))
    {
        aug=INF;
        for(int i=t;i!=s;i=pre[i])
            aug=min(aug,edge[path[i]].cap);

        for(int i=t;i!=s;i=pre[i])
        {
            edge[path[i]].cap-=aug;
            edge[path[i]^1].cap+=aug;
        }

        maxflow+=aug;
    }
    return maxflow;
}


int main()
{
    int u,v,w;
    while (~scanf("%d%d",&n,&m))
    {
        init();
        while (m--)
        {
            scanf("%d%d%d",&u,&v,&w);
            addedge(u,v,w);
        }


        int maxflow=ek(1,n);

        printf("%d\n",maxflow);


    }
	return 0;
}

