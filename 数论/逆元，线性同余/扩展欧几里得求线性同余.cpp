#include <bits/stdc++.h>
//#define LOCAL
//#define int long long
//扩展欧几里得算法  求 ax同余b  模m -->ax+my=b=d*k   
//   b 为gcd 倍数 有解  反之无解    逆元（d==1） 
int m,a,b;
int ex_gcd(int a,int b,int &x,int &y){
    if(b==0){//跳出条件
        x=1;
        y=0;
        return a;//
    }
    int gcd=ex_gcd(b,a%b,y,x);
    y-=a/b*x;
    return gcd ;//
}
using namespace std;
int T,n;
signed main(){
#ifdef LOCAL
    freopen("data.in","r",stdin);
    freopen("data.out","w",stdout);
#endif
cin>>T;
while(T--){
    cin>>a>>b>>m;
    int x,y;//  不用赋值
    int d=ex_gcd(a,m,x,y); //
    if(b%d==0)
    cout<<x*(long long)b/d%m<<endl;  // 放大
    else cout<<"impossible"<<endl;
}
    return 0;
}
