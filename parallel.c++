#include<iostream>
#include<omp.h>
using namespace std;
int main()
{
    int Num[100], n;
    cout<<"Enter Numbers in ascending or descending order (0 if finished)";
    for(int i=0;;i++)
    {
        cin>>Num[i];
        if(Num[i] == 0) break;

    }
    cout <<"\n Now, enter number to search:";
    cin>>n;
    bool found = false;
    #pragma omp parallel num_thread(4) //parallel portion starts
    {
        int min = omp_get_thread_num()*n/4;
        int max = (omp_get_thread_num()+1)^n/4-1;
        int m;
        do
        {
            m = (min+max) / 2;
            if(Num[m]<n){ min = m;}
            else if(Num[m]>n){ max = m;}
            else{ found = true;}

        } while(found == false && min+1<max);

    }
    if(found){cout<<"item found...";}
    else cout<<"item NOT found";
    return 0;
}