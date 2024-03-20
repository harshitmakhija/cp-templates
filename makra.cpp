#include<bits/stdc++.h>
using namespace std;
#define endl "\n"
#define int  int64_t
#define mod 1000000007
#define map unordered_map
#define debug3(x,y,z) cout<<"p1:"<<x<<" p2: "<<y<<" p3: "<<z<<endl;
#define debug2(x,y) cout<<"p1:"<<x<<" p2: "<<y<<endl;
int n=1000001;
bool prime[N+5];
vector<int>P;
void init(){
		 
  for(int i=2;i<=N;i++){
	  prime[i]=true;
  }
  
    for (int p=2; p*p<=N; p++) 
    { 
        // If prime[p] is not changed, then it is a prime 
        if (prime[p] == true) 
        { 
  
            for (int i=p*p; i<=N; i += p) 
                prime[i] = false; 
        } 
	}
	for(int i=2;i<=N;i++){
		if(prime[i]==true)
		P.push_back(i);
	}

}//sieve of erasthosis
int Pow(int x,int y){
	if(!y){
		return 1;
	}
	int sa=Pow(x,y/2);
	if(y&1ll){
		return sa*sa*x;
	}
	else{
		return sa*sa;
	}
}
int Max(int a,int b){
	return a>b?a:b;
}
int Min(int a,int b){
	return a<b?a:b;
}
int gcd(int a, int b) {
   if((max(a,b)%min(a,b))==0)
        return min(a,b);
    return gcd(min(a,b),(max(a,b)%min(a,b)));
} //log(max(a,b)) complexity
bool is_sorted(int *a,int n){
	for(int i=0;i<n-1;i++){
		if(a[i]>a[i+1])
		return false;
	}
	return true;
}
/*************************************************************/
bool comp(pair<int,int>a,pair<int,int>b){
	if(a.first==b.first)
	return a.second<b.second;
	return a.first>b.first;
}
void testcase(){

int n;
cin>>n;
vector<pair<int,int>>v(n);
for(int i=0;i<n;i++){
	cin>>v[i].first;
}
for(int i=0;i<n;i++){
	cin>>v[i].second;
}
//cout<<v[0].first;
sort(v.begin(),v.end(),comp);
int ans=0;
int  i;
//cout<<v[0].first;
//
for( i=0;i<n;i++){
	if(ans+v[i].second>=v[i].first){
		break;
	}
	else{
	ans+=v[i].second;
}
}
if(i==n){
	cout<<ans<<endl;return;
}
//cout<<v[i].first<<endl;
cout<<max(v[i].first,ans)<<endl;
return ;
}
int32_t main(){
ios_base::sync_with_stdio(false);//4 1 3 1
cin.tie(NULL);
cout.tie(NULL);
cout<<((840*9)/gcd(840,9));
int t=1,k=1;
cin>>t;
while(t--){
	//cout<<"Case #"<<k<<":"<<" ";
testcase();
//k++;
}
return 0;
}


