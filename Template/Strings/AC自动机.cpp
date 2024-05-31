#include<bits/stdc++.h>
#define N 500010
using namespace std;
namespace AC{
	int nex[N][26],num[N],fail[N],c;
	void init(){
		c=0;
		memset(nex[c],0,sizeof nex[c]);
		fail[c]=num[c]=0;
	}
	void ins(char *s,int n){
		int rt=0;
		for(int i=0;i<n;i++){
			int v=s[i]-'a';
			if(!nex[rt][v]){
				nex[rt][v]=++c;
				memset(nex[c],0,sizeof nex[c]);
				fail[c]=num[c]=0;
			}
			rt=nex[rt][v];
		}
		num[rt]++;
	}
	void build(){
		queue<int>q;
		for(int i=0;i<26;i++){
			if(nex[0][i]){
				fail[nex[0][i]]=0,q.push(nex[0][i]);
			}
		}
		while(!q.empty()){
			int u=q.front();q.pop();
			for(int i=0;i<26;i++){
				if(nex[u][i])fail[nex[u][i]]=nex[fail[u]][i],q.push(nex[u][i]);
				else nex[u][i]=nex[fail[u]][i];
			}
		}
	}
	int query(char *s,int n){
		int rt=0,ans=0;
		for(int i=0;i<n;i++){
			rt=nex[rt][s[i]-'a'];
			for(int j=rt;j && ~num[j];j=fail[j]){//防止重搜
				ans+=num[j],num[j]=-1;
			}
		}
		return ans;
	}
};
using namespace AC;
int n;
char p[1000005];
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%s",p);
		ins(p,strlen(p));
	}
	build();
	scanf("%s",p);
	printf("%d\n",query(p,strlen(p)));
	return 0;
}
