#include <iostream>
#include<vector>
#include<map>
#include<algorithm>
#include<set>
#include<cstring>
#include<cmath>
#include<climits>
#include<cassert>
#include<numeric> 
#include<queue>
#include<stack>

using namespace std;
#define double long  double
#define int  long long

#define debug3(x,y,z) cerr<<"[p1:"<<x<<"]  [p2: "<<y<<"] [p3: "<<z<<"]"<<endl;
#define debug2(x,y) cerr<<"[p1:"<<x<<"]  [p2: "<<y<<"]"<<endl;

const int N=1e3+5;
const int inf=1e17 +3;
const int mod=1e9+7;
#define int long long
class segtree{
public:
int  size;
vector<int>sums;
void init(int n){
size=1;
while(size<n){
size*=2;
}
sums.assign(2*size,0);
}
int getsum(int l,int r,int node,int lx,int rx){
if(lx>=r||rx<=l)
return 0;
if(lx>=l&&rx<=r){
return sums[node];
}
int mid=(lx+rx)/2;
int s1=getsum(l,r,node*2 + 1,lx,mid);
int s2=getsum(l,r,node*2 + 2,mid,rx);
return s1+s2;
}
 
int  getsum(int l,int  r){
return getsum(l,r,0,0,size);
}
void set(int pos,int val,int node,int lx,int rx){
 
if((rx-lx)==1){
	
sums[node]=val;
	//cout<<node<<" "<<sums[node]<<endl;
return;
}
int mid=(lx+rx)/2;
if(pos<mid){
set(pos,val,2*node + 1,lx,mid);
}
else{
set(pos,val,2*node + 2,mid,rx);
}
sums[node]=sums[2*node + 2]+sums[2*node + 1];
 
return;
}
void set(int pos,int val){
set(pos,val,0,0,size);
}
 
};



void testcase(){
  int n,q,p;
  cin>>n>>q>>p;
  int *a=new int[n];
  for(int i=0;i<n;i++){
	  cin>>a[i];
  }

  vector<segtree>st(5);
  auto cal=[&](int x,int s){
	  int md=x%p;
	  int val=x;
	  for(int i=2;i<=s;i++){
		  val*=x;
	  }
	  int val2=md;
	  for(int i=2;i<=s;i++){
		  val2*=md;
	  }
	  int nval=val - val2;
	  int ans=0;
	  if(nval)
	  while((nval%p)==0){
		  nval/=p;
		  ++ans;
		  //cerr<<ans<<" "<<p<<"\n";
	  }
	  return ans;
  };
  auto process=[&](int s){
	  st[s].init(n);
	  for(int i=0;i<n;i++){
		  int val=cal(a[i],s);
		  st[s].set(i,val);
	  }
  };
  auto update=[&](int idx,int val){
	  int temp=val;
	  for(int s=1;s<=4;s++){
		  val=cal(temp,s);
		  st[s].set(idx-1,val);
	  }
  };
  auto get=[&](int s,int l,int r){
	  l--;
	//  cerr<<l<<" "<<r<<"\n";
	  int ans=st[s].getsum(l,r);
	  return ans;
  };
  for(int i=1;i<=4;i++){
	//  cerr<<i<<"\n";
	  process(i);
  }
 // cerr<<"heloo\n";
  
  for(int i=0;i<q;i++){
	  int type;
	  cin>>type;
	 // cerr<<i<<"qyehih\n";
	  if(type==1){
		  int idx,val;
		  cin>>idx>>val;
		  update(idx,val);
	  }
	  else{
		  int s,l,r;
		  cin>>s>>l>>r;
		  assert(s<=4);
		  int ans=get(s,l,r);
		  cout<<ans<<" ";
	  }
  }
 
  
  cout<<"\n";

 
 return;
}
int32_t main(){
ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
int t=1,k=1;
cin>>t;
while(t--){
cout<<"Case #"<<k<<":"<<" ";
testcase();
k++;
}
return 0;
}


