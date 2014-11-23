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
    int from,to,next; //表示起点、终点、下一条边
    int cap,flow;    //边的容量、边的流量
}edge[maxm<<1];

int e,head[maxn];

void init()
{
    e=0;
    memset(head,-1,sizeof(head));
}

void addedge(int u,int v,int c)
{
    Edge e1={u,v,head[u],c,0};
    edge[e]=e1;head[u]=e++;

    Edge e2={v,u,head[v],0,0};
    edge[e]=e2;head[v]=e++;
}


int pre[maxn],path[maxm];

int BFS(int s,int t)
{
    memset(pre,-1,sizeof(pre));
    queue<int> q;
    q.push(s);
    while (!q.empty())
    {
        int u=q.front();q.pop();
        for(int i=head[u];~i;i=edge[i].next)
        {
            int v=edge[i].to;
            if(pre[v]==-1&&edge[i].cap>edge[i].flow)
            {
                pre[v]=u;
                path[v]=i;
                if(v==t) return 1;
                q.push(v);
            }
        }
    }
    return 0;
}


int ek(int s,int t)
{
    int maxflow=0,flow;

    while (BFS(s,t))
    {
        flow=inf;
        for(int i=t;i!=s;i=pre[i])
            flow=min(flow,edge[path[i]].cap-edge[path[i]].flow);

        for(int i=t;i!=s;i=pre[i])
        {
            int e=path[i];
            edge[e].flow+=flow;
            edge[e^1].flow-=flow;
        }
        maxflow+=flow;
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

        int maxflow=ek(1,n);

        printf("%d\n",maxflow);

    }
	return 0;
}


