#include<bits/stdc++.h>
using namespace std;
#define endl "\n"
#define int long long
#define mod 1000000007
int gcd(int a, int b) 
{ 
    if (a == 0) 
        return b; 
    return gcd(b % a, a); 
} //log(a+b) complexity
int Max(int a,int b){
	return a>b?a:b;
}
void testcase(){
int h,w;
cin>>h>>w;
int ch,cw;
cin>>ch>>cw;
int dh,dw;
cin>>dh>>dw;
for(int i=0;i<h;i++){
	for(int j=0;j<w;j++){
}
}
int *a=new int[n];
for(int i=0;i<n;i++){
	cin>>a[i];
}
int  mx=a[0],ans=0;
for(int i=1;i<n;i++){
	if(a[i]<mx){
		ans+=mx-a[i];
	}
	mx=Max(mx,a[i]);
}
cout<<ans<<endl;
return;
}
int32_t main(){
ios_base::sync_with_stdio(false); 
   cin.tie(NULL);
 cout.tie(NULL); 
int t=1,k=1;
//cin>>t;
do{
//cout<<"Case #"<<k<<":"<<" ";
testcase();
k++;
t--;
}while(t>0);

return 0;
}
