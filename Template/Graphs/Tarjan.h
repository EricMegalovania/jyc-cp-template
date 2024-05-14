#include<bits/stdc++.h>
using namespace std;

namespace Tarjan{
	vector<int>dfn(n+1),low(n+1),inStack(n+1),scc(n+1),siz(n+1);
	int timStamp=0,col=0;
	stack<int>stk;
	auto tarjan=[&](auto self,int u)->void{
		low[u]=dfn[u]=++timStamp;
		stk.push(u),inStack[u]=1;
		for(int v:e[u]){
			if(!dfn[v]){
				self(self,v);
				low[u]=min(low[u],low[v]);
			}
			else if(inStack[v]){
				low[u]=min(low[u],low[v]);
			}
		}
		if(dfn[u]==low[u]){
			++col;
			while(stk.top()!=u){
				siz[scc[stk.top()]=col]++;
				inStack[stk.top()]=0; stk.pop();
			}
			siz[scc[stk.top()]=col]++;
			inStack[stk.top()]=0; stk.pop();
		}
	};
}
