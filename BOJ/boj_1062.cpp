/*#include <iostream>
#define NMAX 50

using namespace std;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int N, K, a[NMAX]={0, };
    bool check[NMAX][26]={0, };
    cin >> N >> K;
    if(K<5) cout << 0;
    else{
        for(int i=0; i<N; i++){
            string w;
            cin >> w;
            int mask=(0<<1)+(0<<3)+(0<<9)+(0<<14)+(0<<20);
            // a  n  t  a  t  i  c  a
            // 0 13 19  0 19  8  2  0
            check[i][0]=check[i][2]=check[i][8]=check[i][13]=check[i][19]=true;
            for(int j=4; j<w.length()-4; j++){
                if(!check[w[j]-'a']){
                    mask+=(0<<(w[j]-'a'+1));
                    a[i]++;
                    check[i][w[j]-'a']=true;
                }
            }
        }
    }
    return 0;
}*/

#include <iostream>
#include <string>
#include <algorithm>
#include <memory.h>
#define NMAX 50
#define max2(x,y) (x>y?x:y)

using namespace std;

int N, K, a[NMAX], ans;
string w[NMAX];
bool check[26];
void combination(int lev, int lim, int li){
    if(lev==lim){
        int cnt=0;
        for(int i=0; i<N; i++){
            if(a[i]<=lim){
                int j;
                for(j=4; j<w[i].length()-4; j++){
                    if(!check[w[i][j]-'a']) break;
                }
                if(j==w[i].length()-4){
                    cnt++;
                }
            }
        }
        ans=max2(ans,cnt);
        return;
    }
    for(int i=li; i<26; i++){
        if(!check[i]){
            check[i]=true;
            combination(lev+1,lim, i+1);
            check[i]=false;
        }
    }
}
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N >> K;
    check['a'-'a']=check['c'-'a']=check['i'-'a']=check['n'-'a']=check['t'-'a']=true;
    for(int i=0; i<N; i++){
        cin >> w[i];
        bool c[26]={0, };
        memcpy(c,check,sizeof(check));
        for(int j=4; j<w[i].length()-4; j++){
            if(!c[w[i][j]-'a']){
                a[i]++;
                c[w[i][j]-'a']=true;
            }
        }
    }
    combination(0,K-5,1);
    cout << ans;
    return 0;
}
