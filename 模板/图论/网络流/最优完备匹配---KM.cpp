#include<iostream>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<cmath>
#include<vector>
#include<stack>
#include<queue>
#include<map>
#include<set>
#include<algorithm>

#define inf 0x3f3f3f3f

using namespace std;

const int maxn=10010;

int n,m;
int w[maxn][maxn];
int match[maxn];
int lx[maxn],ly[maxn];
bool sx[maxn],sy[maxn];


bool DFS(int u)
{
    sx[u]=1;
    for(int j=0;j<m;j++)
    {
        if(!sy[j]&&lx[u]+ly[j]==w[u][j])
        {
            sy[j]=1;
            if(match[j]==-1&&DFS(j))
            {
                match[j]=u;
                return true;
            }
        }
    }
    return false;
}



int km()
{
    memset(match,-1,sizeof(match));
    memset(ly,0,sizeof(ly));
    for(int i=0;i<n;i++)
    {
        lx[i]=-inf;
        for(int j=0;j<m;j++)
            if(lx[i]<w[i][j]) lx[i]=w[i][j];
    }

    for(int x=0;x<n;x++)
    {
        memset(sx,0,sizeof(sx));
        memset(sy,0,sizeof(sy));

        if(DFS(x)) break;

        int d=inf;
        for(int i=0;i<n;i++) if(sx[i])
        for(int j=0;j<m;j++) if(!sy[j])
            d=min(d,lx[i]+ly[j]-w[i][j]);

        for(int i=0;i<n;i++) if(sx[i])
            lx[i]-=d;
        for(int j=0;j<m;j++) if(sy[j])
            ly[j]+=d;
    }


}





int main()
{
	return 0;
}

