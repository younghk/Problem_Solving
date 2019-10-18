#include <iostream>
#include <algorithm>

using namespace std;

int gcd(int x, int y){
    if(y==0) return x;
    x%=y;
    return gcd(y,x);
}

int cal_bit(int k){
    int ret=0;
    for(int i=0; i<32; i++){
        ret+=k%2;
        k=k>>1;
    }
    return ret;
}

int main(){
    int A, B, C;
    cin >> A >> B >> C;
    int q=(A+B+C)/(gcd(A, gcd(B,C)));
    cout << (q%3==0 && cal_bit(q/3)==1);
    return 0;
}