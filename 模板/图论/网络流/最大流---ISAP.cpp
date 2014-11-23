#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<cmath>
#include<vector>
#include<queue>
#include<map>
#include<algorithm>

using namespace std;

const int maxn=500;
const int maxm=500;
const int inf=0x3f3f3f3f;

int n,m;
struct Edge
{
    int from,to,next;
    int cap,flow;
}edge[maxm<<1];

int e,head[maxn];
int dis[maxn],num[maxn];
int p[maxn],cur[maxn];

void init()
{
    e=0;
    memset(head,-1,sizeof(head));
}

void addedge(int u,int v,int w)
{
    Edge e1={u,v,head[u],w,0};
    edge[e]=e1;head[u]=e++;

    Edge e2={v,u,head[v],0,0};
    edge[e]=e2;head[v]=e++;
}

void BFS(int s,int t)
{
    memset(dis,-1,sizeof(dis));
    memset(num,0,sizeof(num));
    queue<int> q;

    q.push(t); dis[t]=0;num[0]=1;

    while (!q.empty())
    {
        int u=q.front();q.pop();
        for(int i=head[u];~i;i=edge[i].next)
        {
            int v=edge[i].to;
            if(dis[v]==-1)
            {
                dis[v]=dis[u]+1;
                num[dis[v]]++;
                q.push(v);
            }
        }
    }
}

int augment(int s,int t)
{
    int flow=inf;
    int x=t;

    while (x!=s)
    {
        flow=min(flow,edge[p[x]].cap-edge[p[x]].flow);
        x=edge[p[x]].from;
    }
    x=t;
    while (x!=s)
    {
        edge[p[x]].flow+=flow;
        edge[p[x]^1].flow-=flow;
        x=edge[p[x]].from;
    }

    return flow;
}


int isap(int s,int t)
{
    BFS(s,t);
    memcpy(cur,head,sizeof(head));


    int u=s,flow=0;
    while (dis[s]<n)
    {
        if(u==t)
        {
            flow+=augment(s,t);
            u=s;
        }

        int ok=0;
        for(int i=cur[u];~i;i=edge[i].next)
        {
            int v=edge[i].to;
            if(dis[u]==dis[v]+1&&edge[i].cap>edge[i].flow)
            {
                ok=1;
                p[v]=i;
                cur[u]=i;
                u=v;
                break;
            }
        }

        if(!ok)
        {
            int m=n-1;
            for(int i=head[u];~i;i=edge[i].next)
            {
                int v=edge[i].to;
                if(edge[i].cap>edge[i].flow) m=min(m,dis[v]);
            }

            if(--num[dis[u]]==0) break;

            num[dis[u]=m+1]++;
            cur[u]=head[u];
            if(u!=s) u=edge[p[u]].from;
        }
    }
    return flow;
}


int main()
{
    int u,v,w;
    while (~scanf("%d%d",&m,&n))
    {
        init();
        while (m--)
        {
            scanf("%d%d%d",&u,&v,&w);
            addedge(u,v,w);
        }

        int maxflow=isap(1,n);

        printf("%d\n",maxflow);

    }
	return 0;
}

