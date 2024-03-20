#include <iostream>
#include<vector>
#include<map>
#include<algorithm>
#include<set>
#include<cstring>
#include<cmath>
#include<cassert>
#include<numeric> 
#include<queue>
#include<stack>
#include<iomanip>
#include<queue>
using namespace std;

#define int long long
#define double  long double
#define debug3(x,y,z) cerr<<"p1:"<<x<<" p2: "<<y<<" p3: "<<z<<endl;

#define SHATABDI                        ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
const int N=205*100;
const int mod=1e9 + 7;
const int inf=(int)1e16 +69;

int dx[8]={-1, -1, 0, 1, 1, 1, 0, -1};
int dy[8]={0, 1, 1, 1, 0, -1, -1, -1};
vector<string>V;
vector<vector<char>>v(3,vector<char>(3));
vector<vector<bool>>visited(3,vector<bool>(3,false));
bool isValid(int i, int j){
	return i>=0 && j>=0 && i<3 && j<3;
}
void recurse(int ii, int jj, string s){
	if(s.size() == 3){
		V.push_back(s);
		return;
	}
	for(int i=0;i<8;i++){
		int row = ii + dx[i];  
		int col = jj + dy[i];
		if(isValid(row,col) && !visited[row][col]){
			visited[row][col] = true;
			recurse(row,col,s + v[row][col]);
			visited[row][col] = false;
		}
 	}
 	return ;
	
}

void testcase(){

for(int i=0;i<3;i++){
	for(int j=0;j<3;j++){
		cin>>v[i][j];
	}
}
for(int i=0;i<3;i++){
	for(int j=0;j<3;j++){
		visited[i][j]=true;
		string temp = "";
		temp = temp + v[i][j];
		recurse(i,j,temp);
		visited[i][j]=false;
	}
}
sort(V.begin(),V.end());

cout<<V[0]<<"\n";
V.clear();
visited.clear();
}
signed main(){
    SHATABDI
    int  t=1;
    //init();
	
   // cin>>t;
  
    while(t--){
        testcase();
    }
  
	
	return 0;
}
