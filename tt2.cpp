#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <set>
#include <cstring>
#include <cmath>
#include <cassert>
#include <numeric> 
#include <queue>
#include <stack>
#include <iomanip>
#include <queue>


using namespace std;

#define int long long
#define double  long double


#define SHATABDI 	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
const int N=2050*1000;
const int mod=1e9 + 7;
const int inf=(int)2e18 +69;
int dp[N][3];
int help(vector<int>&a,int n){
    vector<int> d(n, 1);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < i; j++) {
            if (a[j] <= a[i])
                d[i] = max(d[i], d[j] + 1);
        }
    }

    int ans = d[0];
    for (int i = 1; i < n; i++) {
        ans = max(ans, d[i]);
    }
    return n -ans;
}
void testcase(){
int n;
cin>>n;
int *a=new int[n];
for(int i=0;i<n;i++){
	cin>>a[i];
}
int k;
cin>>k;
int ans=0;
for(int j=0;j<=k-1;j++){
	vector<int>v;
	for(int i=j;i<n;i+=k){
		v.push_back(a[i]);
	}
	ans+=help(v,v.size());
}
cout<<ans<<"\n";



return ;  
}


	

 
signed main(){
    SHATABDI
    int  t=1;
  //  init();
	
  //  cin>>t;
  
    while(t--){
        testcase();
    }
	
	return 0;
}
