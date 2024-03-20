
#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>

using namespace std;


int main(){
int cols;
cin>>cols;
int rows;
cin>>rows;
vector<string>v(cols);
int idx;
for(int i=0;i<cols;i++){
	cin>>v[i];
	if(v[i]=="comp"){
		idx=i;
	   swap(v[0],v[i]);
    }
    /*int sz=v[i].size();
    int x =stoi(v[i].substr(sz-3));
    if(x>=193&&x<=195)
    c.push_back(v[i]);*/
}
//vector<map<string,int>>mp;
vector<vector<string>>V;
for(int i=0;i<rows-1;i++){
	vector<string>cur(cols);
	for(int j=0;j<cols;j++){
		cin>>cur[j];
		if(j==idx){
			swap(cur[0],cur[j]);
		}
	}

	V.push_back(cur);
	//key.push_back(cur[0]);
	
}

cout<<"\n";
int cnt=rows-1;
for(int i=0;i<4;i++){
    cout<<v[i]<<" ";
}
cout<<"period a b c\n";

for(int i=0;i<cnt;i++){
	vector<string>&now=V[i];
	for(int j=193;j<=195;j++){
		for(int k=0;k<4;k++){
			cout<<now[k]<<" ";
		}
		cout<<j<<" ";
		for(int k=4;k<cols;k++){
			int sz=v[k].size();
			string sufx=v[k].substr(sz-3);
			//cerr<<"db"<<sufx<<"db\n";
			if(sufx==to_string(j)){
				cout<<now[k]<<" ";
			}
		}
		cout<<"\n";
	}
}
/*13
4
accn name pcn comp a193 a194 a195 b193 b194 b195 c193 c194 c195
12 harshit 11 1 100 200 300 400 500 600 700 800 900
13 nikhil 14 2 50 55 60 65 70 80 90 98 99
14 rohit 17 3 1000 2000 3000 3111 3122 3123 999 9999 9999


*/

 
    
}


