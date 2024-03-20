#include<bits/stdc++.h>
using namespace std;
#define endl "\n"
#define int long long
#define mod 1000000007
//#define map unordered_map
#define debug3(x,y,z) cout<<"p1:"<<x<<" p2: "<<y<<" p3: "<<z<<endl;
#define debug2(x,y) cout<<"p1:"<<x<<" p2: "<<y<<endl;
//     v.resize(unique(v.begin(), v.end()) - v.begin());
//https://codeforces.com/blog/entry/81181 -> for set comparators
struct com{
	bool operator()(int &a,int &b)const{
		//conditions
	}
};
int Max(int a,int b){
	return a>b?a:b;
}
int Min(int a,int b){
	return a<b?a:b;
}
int gcd(int a, int b) 
{ 
    if (a == 0) 
        return b; 
    return gcd(b % a, a); 
} //log(a.b) complexity
int mat[301][301];
int dx[4]={1,-1,0,0};
int dy[4]={0,0,-1,1};
 
int dxx[8]={-1, -1, 0, 1, 1, 1, 0, -1};
int dyy[8]={0, 1, 1, 1, 0, -1, -1, -1};
int m,n;
bool valid(int i,int j ){
	if(i<0||i>=m||j<0||j>=n)
	return false;
	return true;
}
vector<int>FACTORS(int n){
  vector<int>v;
    while (n % 2 == 0) 
    { 
        v.push_back(2);
        n = n/2; 
    } 
  
    for (int i = 3; i <= sqrt(n); i = i + 2) 
    { 
       
        while (n % i == 0) 
        {  
            v.push_back(i);
            n = n/i; 
        } 
    } 

    if (n > 2) 
       v.push_back(n);
	return v;
	
}

/*************************************************************/

class comp{
	public:
	bool op()(int &a,int &b){
		return a<b;
	}
};
/*int *ptr=(int *)calloc(n,sizeof(int));//dynamic allocation in C
for(int i=0;i<n;i++){
	//cin>>ptr[i];
	//scanf("%d",ptr+i);
}*/

void testcase(){
	vector<int>v;
	//sort(v.begin(),v.end(),comp);
   priority_queue<int,vector<int>,comp>pq;
	
return;
}
int32_t main(){
ios_base::sync_with_stdio(false); 
   cin.tie(NULL);
 cout.tie(NULL); 
int t=1,k=1;
cin>>t;
do{
//cout<<"Case #"<<k<<":"<<" ";
testcase();
k++;
t--;
}while(t>0);
 
return 0;
}
