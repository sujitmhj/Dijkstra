#include<iostream>
#include<omp.h>
int vertxQ[100],Qhd=0,Qtl=0;
using namespace std;
void enQ(int);
int dQ();
int main()
{
    int n,S,minDist[100],wt[100][100];
    cout<<"Enter No. of Nodes:";
    cin>>n;
    for(int i=0;i<n;i++)
    {
        minDist[i]=1000;
        for(int j=0;j<n;j++)
        {
            if(i==j) {wt[i][j]=0;continue;}
            cout<<"wt. for edge "<<i+1<<"-"<<j+1<<":(1000 if not connected/directed)";
            cin>>wt[i][j];
        }
    }
    cout<<"Source Node?:";
    cin>>S;
    S=S-1;
    minDist[S]=0;
    enQ(S);
    int cur;
    while((cur = dQ())!=-1)
    {
        #pragma omp parallel for
        for(int j=0;j<n;j++)
        {
            if(minDist[j] > (minDist[cur] + wt[cur][j]))
            {
                minDist[j] = (minDist[cur] + wt[cur][j]);
                enQ(j);
            }
        }
    }
    cout<<"min dists from node "<<S+1<<" = ";
    for(int k=0;k<n;k++)       cout<<minDist[k]<<" ";
    return 0;
}
void enQ(int x)
{
    if((Qtl+1)%100==Qhd) {cout<<"Q Full"; return;}
    vertxQ[Qtl] = x;
    Qtl = (Qtl+1)%100;
}
int dQ()
{
    if(Qhd==Qtl) {return -1;}
    int x = vertxQ[Qhd];
    Qhd = (Qhd+1)%100;
    return x;
}