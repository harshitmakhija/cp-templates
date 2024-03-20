/**********FACTORS in sqrt(n) complxity*******************/
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
/************************************************************/
/*********FACTORS in log(n) query but before that we have to generate sieve which will store smallest prime factor for each number(N*log(n)*log(n))******/

vector<int>spf(N+2);
void spf_sieve(){
for(int i=1;i<=N;i++){
	spf[i]=i;
}
for(int i=2;i<=sqrt(N);i++){
	if(spf[i]!=i){
		continue;
	}
	for(int j=i*i;j<=N;j++){
		if(spf[j]==j){
			spf[j]=i;
		}
	}
}
}
vector<int>Factorise(int n){
	
	vector<int>v;
	while(n>1){
		v.push_back(spf[n]);
		n/=spf[n];
	}
	return v;
}
/*******************************************************************************************************************************************************/
/*****************************------------------DSU------------*********************************************/
int Root(int v){
	if(v==parent[v])
	return v;
	return parent[v]=Root(parent[v]);
}
void Unite(int a,int b){
    a = Root(a);
    b = Root(b);
    if (a != b) {
        if (size[a] < size[b])
            swap(a, b);
        parent[b] = a;
        size[a] += size[b];
    }
	return ;
}
//initialy parent[i]=i and size[i]=1
/*******************************************************************************************************/
/*****************UNIFORM_DISTRIBUTION***********************************************/
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());//along with <bits/stdc++.h>
int rand_index(int l,int r){
	/*int width=((r-l)+1);
	return (l+(rand()%width));*/
	auto dist=uniform_int_distribution<int>(l,r);
	return dist(rng);
}
/******************************************************************************************************/
/************************------------------------KMP-------------------------*************************/
vector<int>prefix_function(string s){
	vector<int>pi(s.size(),0);//pi[i] tells length of longest prefix in (0....i) which is also of suffix of (0....i) 
	int n=s.size();
	for(int i=1;i<n;i++){
		int j=pi[i-1];
		while(j>0&&s[i]!=s[j]){
			j=pi[j-1];
		}
		if(s[i]==s[j])
		j++;
		pi[i]=j;
	}
	return pi;
}
/****************************************************************************************************/
/*******************************-------------LCA USING SPARSE TABLE( only for TREES)----------------******************/
 int LOG=28;
 vector<int>dist;
 vector<vector<int>>g;
 vector<int>euler,first;
 void dfs(int node,int parent,int d){
	 dist[node]=d;
	 first[node]=euler.size();
	 euler.push_back(node);
	 for(auto child:g[node]){
		 if(child!=parent){
			 dfs(child,node,d+1);
			 euler.push_back(node);
		 }
	 }
	 return ;
 }
void testcase(){
 int n,x;
 cin>>n>>x;
 x--;
 dist.resize(n,0);
 first.resize(n);
 g.resize(n);
 for(int i=0;i<(n-1);i++){
	 int u,v;
	 cin>>u>>v;
	 u--;v--;
	 g[u].push_back(v);
	 g[v].push_back(u);
 }
 dfs(0,-1,0);;
 int sz=euler.size();
 vector<vector<pair<int,int>>>m(LOG,vector<pair<int,int>>(sz));
 for(int i=0;i<sz;i++){
	 int node=euler[i];
	 m[i][0]={dist[node],node};
 }
 auto tell=[&](pair<int,int>x,pair<int,int>y){
	 if(x.first<=y.first){
		 return x;
	 }
	 return y;
 };
 for(int j=1;j<LOG;j++){
	 for(int i=0;i+(1<<j)-1<sz;i++){
		m[i][j]=tell(m[i][j-1],m[i+(1<<(j-1))][j-1]); 
	 }
 }
 vector<int>Log(sz+2);
// cerr<<sz<<"\n";
 Log[1]=0;
 for(int i=2;i<=sz;i++){
	 Log[i]=Log[i/2]+1;
 }
 auto query=[&](int L,int R){
	 int length=(R-L)+1;
	 int k=Log[length];
	 
	 return tell(m[L][k],m[R-(1<<k)+1][k]);
 };
 auto Dist=[&](int u,int v)->pair<int,int>{
	 int L=min(first[u],first[v]);
	 int R=max(first[u],first[v]);
	 int lca_node=query(L,R).second;
	 int distance=dist[u]-dist[lca_node]+dist[v] - dist[lca_node];
	 return {lca_node,distance};
 };
 // suppose u want to find lca of node u and node v (0 indexing)
 //lca(u,v)=Dist(u,v).first
 //distamce b/w two nodes=Dist(u,v).second;
return ;

}
/*******************************************************************************************************************************/
/*********************-LCA,min_edge,distance b/w two nodes all using binary lifting********************************************/
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
#include<iomanip> //for memset
#include<queue>
#include<stack>

using namespace std;

#define int long long
#define double long  double

#define SHATABDI 	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
const int N=1e3+103;
const int mod=1e9 +7;
const int inf=1e17 - 3;
int LOG=20;
vector<vector<int>>up,nin;
vector<vector<pair<int,int>>>g;
vector<int>depth;
void dfs(int node,int parent,int d){
	depth[node]=d;
	//cerr<<"dfs\n";
	for(auto child:g[node]){
		if(child.first==parent){
			continue;
		}
	//	cerr<<" "<<child.first<<" "<<node<<"\n";
		up[child.first][0]=node;
		nin[child.first][0]=child.second;
		for(int j=1;j<LOG;j++){
		//	cerr<<j<<" "<<child.first<<" "<<node<<"\n";
			up[child.first][j]=up[up[child.first][j-1]][j-1];
			nin[child.first][j]=min(nin[up[child.first][j-1]][j-1],nin[child.first][j-1]);
		}
		dfs(child.first,node,d+1);
	}
	return ;
}
void testcase(int Case){
 int n,m;
 cin>>n>>m;
 assert(m==n-1);
 g.resize(n);
 depth.resize(n,0);
 up.resize(n,vector<int>(LOG,0));//0 indexing
 nin.resize(n,vector<int>(LOG,inf));
 //cerr<<up.size()<<" "<<up[0].size()<<" "<<inf<<"\n";
for(int i=0;i<(n-1);i++){
	int u,v,w;
	cin>>u>>v>>w;
	u--;
	v--;
	g[u].push_back({v,w});
	g[v].push_back({u,w});
	
}

 dfs(0,-1,0);
 auto kth_ancesstor=[&](int node,int k){
	 //assert(k<=depth[node]);
	 int ans=node;
	 for(int j=LOG-1;j>=0;j--){
		 if((1LL<<j)&k){
			 ans=up[ans][j];
		 }
	 }
	 return ans;


 };
 auto LCA=[&](int u,int v){
	 if(depth[u]<depth[v]){
		 swap(u,v);
	 }
	 int k=depth[u] - depth[v];
	     u=kth_ancesstor(u,k);
	 	 if(u==v){
		 return u;
	     }
	 for(int j=LOG-1;j>=0;j--){
		 if(up[u][j]!=up[v][j]){
			 u=up[u][j];
			 v=up[v][j];
		 }
	 }
	 return up[u][0];
	 
 };
 auto Dist=[&](int u,int v){
	 int lca_node=LCA(u,v);
	 int distance=depth[u] - depth[lca_node]+depth[v] -depth[lca_node];
	 return distance;
 };
 auto get_min=[&](int u,int k){
	 int mn=inf;
	 for(int j=0;j<LOG;j++){
		 if(k&(1LL<<j)){
			 mn=min(mn,nin[u][j]);
			 u=up[u][j];
		 }
	 }
	 return mn;
 };
 auto min_edge=[&](int u,int v){
	 int lca_node=LCA(u,v);
	 int dist=depth[u]-depth[lca_node];
	 int c1=get_min(u,dist);
	 int dist2=depth[v] - depth[lca_node];
	 int c2=get_min(v,dist2);
	 return min(c1,c2);
 };

 int q;
 cin>>q;
 while(q--){
	 int u,v;
	 cin>>u>>v;
	 u--;
	 v--;
	 cout<<min_edge(u,v)<<"\n";
 }


  
 return;
}
signed main(){
    SHATABDI
    int  t=1,Case=0;
    //init();
	
    //cin>>t;

    while(t--){
        testcase(++Case);
    }
	
	return 0;
}




/****************************************************************************************************************************/




/************-----decimal to base b -------------******************/
int b,m;
cin>>b>>m;
vector<int>v;
while(m){
	v.push_back(m%b);
	m/=b;
}
//m=v[0]*b^0 + v[1]*b^1 + v[2]*b^3 ........
/*****************************************************************************************************************************/
/*----------------------------------------------NCR works for n^2-----------------------------------------------------------------------*/
void init(){
	ncr[0][0]=1;
	for(int i=0;i<N;i++){
		for(int j=0;j<11;j++){
			if(j>i){
				ncr[i][j]=0;
			}
			else if(j==0){
				ncr[i][j]=1;
			}
			else{
				ncr[i][j]=ncr[i-1][j-1] + ncr[i-1][j];
			}
		}
	}
}
/**************************************************************************************************/
//For floyd warshall grah can be directed undirected but no negative cycle
/***Floyd warshall pseudo code for finding shortest distance from x to all other nodes*****/
for (int i = 1; i <= n; i++) distance[i] = INF;
distance[x] = 0;
for (int i = 1; i <= n-1; i++) {
for (auto e : edges) {
int a, b, w;
tie(a, b, w) = e;
distance[b] = min(distance[b], distance[a]+w);
}
}
//O(n*m)
/**************************************************************************************************/


/****--------Floud warshall for shortest path b/w each pair---------*********/
for (int k = 0; k < n; ++k) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            d[i][j] = min(d[i][j], d[i][k] + d[k][j]); 
        }
    }
}

//O(n*n*n)
/********************************************************************************************/


















%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Original author:
% Rahul Chauhan (http://rahulchauhan.net)
%
% Original repository:
% https://github.com/rahulworld/rahulworld-Resume
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

\documentclass[]{rahulworld-resume}


\begin{document}

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%     COLUMN ONE
%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

\begin{minipage}[t]{0.33\textwidth} 
\begin{large}
	\headername{Harshit Makhija}\\
\end{large}
Pre-Final Year (B.E)\\
Computer Engineering\\ 
Thapar University\\ 
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%     LINKS
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
\section{Links} 
\noindent\rule{5cm}{0.4pt}

Github:// \href{https://github.com/harshitmakhija}{\custombold{harshit-github}} \\
LinkedIn://  \href{https://www.linkedin.com/in/harshit-makhija-10030a171/}{\custombold{harshit-linkedin}} \\

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%     SKILLS
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
\section{Skills}
\noindent\rule{5cm}{0.4pt}
\subsection{OS}
GNU/Linux, Windows
\vspace{6pt}
\subsection{Languages}
C/C++
\vspace{6pt}
\subsection{Framework}
Node.js,
\vspace{6pt}
\subsection{Databases}
 MangoDB
\vspace{6pt}
\subsection{Others}
Visual Studio Code\\Geany Text Editor\\MS-WORD

\sectionsep
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%     COURSEWORK
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
\section{Coursework}
\noindent\rule{5cm}{0.4pt}

Data Structures\\
Algorithm\\
Computer Networks\\
Discrete Mathematics\\
Operating Systems\\
Optimization Techniques\\
DBMS\\
\sectionsep
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%     EDUCATION
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
\section{Education} 
\noindent\rule{5cm}{0.4pt}\\
\datecolor{2018-2022(EXPECTED)}
\subsection{B.E in Computer Engineering}
THAPAR UNIVERSITY ,PATIALA\\
CGPA : 8.83/10\\
\vspace{8pt}
\datecolor{2016-2018}
\subsection{Intermediate}
BHARTIYAM VIDYA NIKETAN GWALIOR\\
Percentage: 79.8\%\\
\vspace{8pt}
\datecolor{2014-2016}
\subsection{High School}
BHARTIYAM VIDYA NIKETAN GWALIOR\\
CGPA: 10/10
\sectionsep
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%     COLUMN TWO
%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

\end{minipage} 
\hfill
\begin{minipage}[t]{0.66\textwidth} 
% \descript{BS in Computer ence}
\hspace*{0pt}\hfill    \\
\hspace*{0pt}\hfill    \\
\hspace*{0pt}\hfill TF-3, Saya Terrace, HarishankarPuram \\
\hspace*{0pt}\hfill Gwalior, India \\
\hspace*{0pt}\hfill Mob.: +91-7999645052 \\
\hspace*{0pt}\hfill Email.:\textbf{\href{mailto:rahulnitsxr@gmail.com}{harshitmakhija12042001@gmail.com}} \\
\hspace*{0pt}\hfill 
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%     EXPERIENCE
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
\section{Experience}
\noindent\rule{12.5cm}{0.4pt}


\datecolor{Feb 2021 - June 2021 } \runsubsection{Coding Ninjas,New Delhi}
\descript{Teaching Assistant}
\noindent
\hspace{5em}%
\begin{minipage}{0.85\textwidth\vspace{2pt}}
Worked on debugging codes of other person and help them by clearing their doubts
\end{minipage}
\descriptright{Android, Mysql, Google map}
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%     AWARDS
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
\section{Achievements/Certificates} 
\noindent\rule{12.5cm}{0.4pt}
\subsection{GOOGLE KICKSTART ROUND H | RANK : 489}\newline
\vspace{5pt}
\subsection{CODEFORCES |Rating :1552 (Specialist)}\newline
\vspace{5pt}
\subsection{CODECHEF   |Rating :1887 (4 stars)}\newline
\vspace{5pt}
\subsection{LEETCODE   |Rating :1661 }\newline
\vspace{5pt}
\subsection{CODEX BY SCALER  |RANK :  661}\newline
\vspace{5pt}
\subsection{CODERUSH INTER-COLLEGE CODING COMPETETION  |RANK :  12}\newline
\vspace{5pt}
\subsection{ELC HACKATHON |RUNNERUPS}\newline
\vspace{5pt}
\subsection{CERTIFICATE OF MERIT in CLASS 10th}\newline
\vspace{5pt}
\subsection{CERTIFICATE OF EXCELLENCE in Data Structures and Algorithms by Coding Ninjas}\newline
\vspace{4pt}

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%     SIDE PROJECT
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
\section{Projects}
\noindent\rule{12.5cm}{0.4pt}
\datecolor{2020} \runsubsection{Plagarism detector using C++}
\noindent
\hspace{5em}%
\begin{minipage}{0.85\textwidth\vspace{5pt}}
This Detector takes two doc files and tells their plagarism percentage
\end{minipage}

\datecolor{2020} \runsubsection{Contact diary using Nodejs ,MongeDb}
\noindent
\hspace{5em}%
\begin{minipage}{0.85\textwidth\vspace{5pt}}
This is just a basic contact diary which will store ,delete ,update your contacts
\end{minipage}

\datecolor{2020} \runsubsection{Simple Text Editor Using C++}
\noindent
\hspace{5em}%
\begin{minipage}{0.85\textwidth\vspace{5pt}}
This editor is simple c++ program which will let you to write code
\end{minipage}

\end{minipage} 
\end{document}  \documentclass[]{article}
/*******************************************************************************************************************/
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Original author:
% Rahul Chauhan (http://rahulchauhan.net)
%
% Original repository:
% https://github.com/rahulworld/rahulworld-Resume
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

\documentclass[]{rahulworld-resume}


\begin{document}

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%     COLUMN ONE
%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

\begin{minipage}[t]{0.33\textwidth} 
\begin{large}
	\headername{Harshit Makhija}\\
\end{large}
Pre-Final Year (B.E)\\
Computer Engineering\\ 
Thapar University\\ 
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%     LINKS
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
\section{Links} 
\noindent\rule{5cm}{0.4pt}

Github:// \href{https://github.com/harshitmakhija}{\custombold{harshit-github}} \\
LinkedIn://  \href{https://www.linkedin.com/in/harshit-makhija-10030a171/}{\custombold{harshit-linkedin}} \\

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%     EDUCATION
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
\section{Education} 
\noindent\rule{5cm}{0.4pt}\\
\datecolor{2018-2022(EXPECTED)}
\subsection{B.E in Computer Engineering}
THAPAR UNIVERSITY ,PATIALA\\
CGPA : 8.83\\
\vspace{8pt}
\datecolor{2016-2018}
\subsection{Intermediate}
BHARTIYAM VIDYA NIKETAN GWALIOR\\
Percentage: 79.8\%\\
\vspace{8pt}
\datecolor{2014-2016}
\subsection{High School}
BHARTIYAM VIDYA NIKETAN GWALIOR\\
CGPA: 10
\sectionsep
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%     COURSEWORK
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
\section{Coursework}
\noindent\rule{5cm}{0.4pt}

Data Structures\\
Algorithm\\
Computer Networks\\
Discrete Mathematics\\
Operating Systems\\
Optimization Techniques\\
DBMS\\
\sectionsep

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%     SKILLS
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
\section{Skills}
\noindent\rule{5cm}{0.4pt}
\subsection{OS}
GNU/Linux, Windows
\vspace{6pt}
\subsection{Languages}
C/C++
\vspace{6pt}
\subsection{Framework}
Node.js,
\vspace{6pt}
\subsection{Databases}
 MangoDB
\vspace{6pt}
\subsection{Others}
Visual Studio Code\\Geany Text Editor\\MS-WORD

\sectionsep
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%     COLUMN TWO
%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

\end{minipage} 
\hfill
\begin{minipage}[t]{0.66\textwidth} 
% \descript{BS in Computer ence}
\hspace*{0pt}\hfill    \\
\hspace*{0pt}\hfill    \\
\hspace*{0pt}\hfill TF-3, Saya Terrace, HarishankarPuram \\
\hspace*{0pt}\hfill Gwalior, India \\
\hspace*{0pt}\hfill Mob.: +91-7999645052 \\
\hspace*{0pt}\hfill Email.:\textbf{\href{mailto:harshitmakhija12042001@gmail.com}{harshitmakhija12042001@gmail.com}} \\
\hspace*{0pt}\hfill 
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%     EXPERIENCE
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
\section{Experience}
\noindent\rule{12.5cm}{0.4pt}


\datecolor{Feb 2021 - Apr 2021 } \runsubsection{Coding Ninjas,New Delhi}
\descript{Teaching Assistant}
\noindent
\hspace{5em}%
\begin{minipage}{0.85\textwidth\vspace{2pt}}
Worked on debugging codes of other person and help them by clearing their doubts
\end{minipage}

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%     AWARDS
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
\section{Achievements/Certificates} 
\noindent\rule{12.5cm}{0.4pt}
\subsection{GOOGLE KICKSTART ROUND H | RANK : 489}\newline
\vspace{5pt}
\subsection{CODEFORCES |Rating :1552 (Specialist)}\newline
\vspace{5pt}
\subsection{CODECHEF   |Rating :1887 (4 stars)}\newline
\vspace{5pt}
\subsection{LEETCODE   |Rating :1661 }\newline
\vspace{5pt}
\subsection{CODEX BY SCALER  |RANK :  661}\newline
\vspace{5pt}
\subsection{CODERUSH INTER-COLLEGE CODING COMPETETION  |RANK :  12}\newline
\vspace{5pt}
\subsection{ELC HACKATHON |RUNNERUPS}\newline
\vspace{5pt}
\subsection{CERTIFICATE OF MERIT in CLASS 10th}\newline
\vspace{5pt}
\subsection{CERTIFICATE OF EXCELLENCE in Data Structures and Algorithms by Coding Ninjas}\newline
\vspace{4pt}

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%     SIDE PROJECT
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
\section{Projects}
\noindent\rule{12.5cm}{0.4pt}
 \runsubsection{Plagarism detector using C++}
\noindent
\hspace{5em}%
\begin{minipage}{0.85\textwidth\vspace{5pt}}
This Detector takes two doc files and tells their plagarism percentage
\end{minipage}

 \runsubsection{Contact diary using Nodejs ,MongeDb}
\noindent
\hspace{5em}%
\begin{minipage}{0.85\textwidth\vspace{5pt}}
This is just a basic contact diary which will store ,delete ,update your contacts
\end{minipage}

 \runsubsection{Simple Text Editor Using C++}
\noindent
\hspace{5em}%
\begin{minipage}{0.85\textwidth\vspace{5pt}}
This editor is simple c++ program which will let you to write code
\end{minipage}

\end{minipage} 
\end{document}  \documentclass[]{article}
/**************************************************************************************************************?
