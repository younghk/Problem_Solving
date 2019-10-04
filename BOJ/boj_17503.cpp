#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;
typedef long long ll;

const int MAX = 2e5;

struct Beer{
    int v, c;

    bool operator<(const Beer &x)const{
        return{ c<x.c || (c==x.c && v<x.v)};
    }
};

priority_queue<int, vector<int>, greater<int> > pq;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int N, M, K;
    vector<Beer> beer;
    int sum[MAX]={0,};

    cin >> N >> M >> K;
    for(int i=0; i<K; i++){
        Beer k;
        cin >> k.v >> k.c;
        beer.push_back(k);
    }
    sort(beer.begin(),beer.end());
    sum[0]=beer[0].v;
    pq.push(beer[0].v);
    int ans=-1;
    for(int i=1; i<K; i++){
        int k = 0;
        pq.push(beer[i].v);
        if(i>=N){
            k = pq.top();
            pq.pop();
        }
        sum[i]=sum[i-1]-k+beer[i].v;
        if(sum[i]>=M && i>=N-1){
            ans=beer[i].c;
            break;
        }
    }
    
    cout << ans;
    
    return 0;
}