#include<bits/stdc++.h>
using namespace std;
#define int  long long 
#define ll  long long 
#define mod 998244353
#define endl "\n"
int mat[1000][1000];
const int N=1000000;
using namespace std;
ll factorialNumInverse[N + 1];
 
// array to precompute inverse of 1! to N!
ll naturalNumInverse[N + 1];
 
// array to store factorial of first N numbers
ll fact[N + 1];
 
// Function to precompute inverse of numbers
void InverseofNumber(ll p)
{
    naturalNumInverse[0] = naturalNumInverse[1] = 1;
    for (int i = 2; i <= N; i++)
        naturalNumInverse[i] = naturalNumInverse[p % i] * (p - p / i) % p;
}
// Function to precompute inverse of factorials
void InverseofFactorial(ll p)
{
    factorialNumInverse[0] = factorialNumInverse[1] = 1;
 
    // precompute inverse of natural numbers
    for (int i = 2; i <= N; i++)
        factorialNumInverse[i] = (naturalNumInverse[i] * factorialNumInverse[i - 1]) % p;
}
 
// Function to calculate factorial of 1 to N
void factorial(ll p)
{
    fact[0] = 1;
 
    // precompute factorials
    for (int i = 1; i <= N; i++) {
        fact[i] = (fact[i - 1] * i) % p;
    }
}
 
// Function to return nCr % p in O(1) time
ll Binomial(ll N, ll R, ll p)
{ 
	if(N<R)
	return 0ll;
    // n C r = n!*inverse(r!)*inverse((n-r)!)
    ll ans = ((fact[N] * factorialNumInverse[R])
              % p * factorialNumInverse[N - R])
             % p;
    return ans;
}
int help(int n,int m){
	if(n<=2){
		return 0;
	}
	if(n==3){
		int ans=0;
		for(int j=2;j<=m;j++){
			ans+=(j-1);
			ans%=mod;
		}
		return ans;
	}
	int sa=help(n-1,m);
	sa*=(m-(n-2));
	sa%=mod;
	sa*=2;
	sa%=mod;
	
	for(int i=1;i<=m-1;i++){
		int grt=m-i;
		sa+=Binomial(grt,n-2,mod);
		sa%=mod;
	}
	return sa;
	
	
} 
void testcase(){
int n,m;
cin>>n>>m;
cout<<Binomial(3,3,mod)<<" "<<Binomial(12,23,mod)<<"\n";
cout<<help(n,m)<<"\n";
//ans=(ans + Binomial(len,m-1,mod))%mod;// binomial -> ncr
 //i++;
 

return;
}
int32_t main(){
	ios_base::sync_with_stdio(false); 
   cin.tie(NULL);
 cout.tie(NULL); 
  InverseofNumber(mod);// pre computations
    InverseofFactorial(mod);// pre computations
    factorial(mod);// pre computations
int t=1;
//cin>>t;
while(t--){
	testcase();
}     
return 0;
}


