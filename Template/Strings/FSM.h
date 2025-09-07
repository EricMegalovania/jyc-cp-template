struct DFA {
	int m,n,q0;
	vector<vector<int>>trans;
	vector<int>acc;
	DFA(){}
	DFA(int m,int n=0,int q0=0)
	: m(m), n(n), q0(q0), trans(m,vector<int>(n)), acc(n) {}
	void hop(DFA& res) const;
	void deb() const{
		debug("m=%d n=%d q0=%d\n",m,n,q0);
		for(int i=0;i<n;++i){
			debug("acc[%d]=%d\n",i,acc[i]);
			for(int j=0;j<m;++j){
				debug("\ttrans[%d][%d]=%d\n",i,j,trans[j][i]);
			}
		}
	}
};

const int LEN=20;
vector<int>tab[LEN];
bool check(int l,int x){
	if(tab[l][x]!=-1) return tab[l][x];
	if(x==1 && l==1) return 1;
	static const bool rua[]={0,0,0,1,0,1,1,1};
	for(int i=2;i<l;++i){
		int y=(x>>(i+1))<<(i-1);
		y|=x&((1<<(i-2))-1);
		y|=rua[(x>>(i-2))&7]<<(i-2);
		if(check(l-2,y)) return tab[l][x]=1;
	}
	return tab[l][x]=0;
}
void build_table(){
	tab[0]={0};
	tab[1]={0,1};
	for(int l=2;l<LEN;++l){
		tab[l].assign(1<<l,-1);
		for(int i=0;i<(1<<l);++i){
			check(l,i);
		}
	}
}

const int ckl=7;
void build_dfa(DFA& dfa){
	build_table();
	dfa.m=2; dfa.n=1; dfa.q0=0;
	map<ai2,int>states; // {len,x}, id
	auto& trans=dfa.trans;
	auto& acc=dfa.acc;
	auto& n=dfa.n;
	states[{0,0}]=0;
	trans.resize(2);
	trans[0]={-1},trans[1]={-1};
	acc={0};
	queue<ai3>q;
	q.push({0,0,0}); // [len,x,id]
	vector<ai2>allz;
	for(int l=0;l<ckl;++l){
		for(int i=0;i<(1<<l);++i){
			allz.push_back({l,i});
		}
	}
	while(q.size()){
		const auto [LX,X,nw]=q.front();
		q.pop();
		for(int c:{0,1}){
			const int lx=LX+1;
			const int x=(X<<1)|c;
			int found=-1;
			for(auto& [s,id]:states) if(id!=nw){
				const int& ly=s[0];
				const int& y=s[1];
				bool ok=1;
				for(const auto& [lz,z]:allz){
					int lxx=lx+lz;
					int xx=(x<<lz)|z;
					int lyy=ly+lz;
					int yy=(y<<lz)|z;
					if(tab[lxx][xx]!=tab[lyy][yy]){
						ok=0;
						break;
					}
				}
				if(ok){
					found=id;
					break;
				}
			}
			if(found!=-1){
				trans[c][nw]=found;
			}
			else{
				states[{lx,x}]=n;
				trans[0].push_back(-1);
				trans[1].push_back(-1);
				acc.push_back(tab[lx][x]);
				q.push({lx,x,n});
				trans[c][nw]=n;
				++n;
			}
		}
	}
}

// O(n * m * log(n))
void DFA::hop(DFA& res) const{
	vector<vector<int>>pre(m),pos(m);
	for(int c=0;c<m;++c){
		pre[c].assign(n,0);
		pos[c].assign(n+1,0);
		for (int i=0;i<n;++i) ++pos[c][trans[c][i]];
		for (int i=0;i<n;++i) pos[c][i+1]+=pos[c][i];
		for (int i=0;i<n;++i) pre[c][--pos[c][trans[c][i]]]=i;
	}
	struct Node{
		int os,sz,cnt;
		Node(int os,int sz,int cnt):os(os),sz(sz),cnt(cnt){}
	};
	vector<Node>ec;
	vector<int>ids(n);
	vector<int>par(n);
	vector<bool>tag(n);
	queue<int>evid;
	iota(ids.begin(),ids.end(),0);
	sort(ids.begin(),ids.end(),[&](int l,int r){
		return acc[l]<acc[r];
	});
	for(int l=0,r;l<n;l=r){
		for(r=l;r<n && acc[ids[r]]==acc[ids[l]];++r)
			par[ids[r]]=ec.size();
		if(l) evid.push(ec.size());
		ec.emplace_back(l,r-l,0);
	}
	while(!evid.empty()){
		int cr=evid.front();
		evid.pop();
		for(int c=0;c<m;++c){
			vector<int>todo;
			for(int i=ec[cr].os;i<ec[cr].os+ec[cr].sz;++i){
				for(int k=pos[c][ids[i]];k<pos[c][ids[i]+1];++k){
					int j=pre[c][k];
					if(!tag[j]){
						if(!ec[par[j]].cnt) todo.push_back(par[j]);
						++ec[par[j]].cnt;
						tag[j]=true;
					}
				}
			}
			for(int i:todo){
				int ti=i;
				if(ec[i].cnt!=ec[i].sz){
					bool mjtg=(ec[i].cnt*2>=ec[i].sz);
					int mid =
					partition(ids.begin()+ec[i].os,
						ids.begin()+ec[i].os+ec[i].sz,
						[&](int x){return tag[x]==mjtg;}) -
					ids.begin() - ec[i].os;
					for (int j=ec[i].os+mid;j<ec[i].os+ec[i].sz;++j)
						par[ids[j]]=ec.size();
					evid.push(ec.size());
					if(!mjtg) ti=ec.size();
					ec.emplace_back(ec[i].os+mid,ec[i].sz-mid,0);
					ec[i].sz = mid;
				}
				ec[i].cnt=0;
				for(int j=ec[ti].os;j<ec[ti].os+ec[ti].sz;++j)
					tag[ids[j]]=false;
			}
		}
	}
	res=DFA(m,ec.size(),par[q0]);
	for(const auto& e:ec){
		int i=ids[e.os];
		res.acc[par[i]]=acc[i];
		for(int c=0;c<m;++c) res.trans[c][par[i]]=par[trans[c][i]];
	}
}

bool dfaeq(const DFA& aa,const DFA& bb){
	if(aa.m!=bb.m || aa.n!=bb.n) return 0;
	const int n=aa.n;
	const int m=aa.m;
	if(!n) return 1;
	vector<int>pp(n,-1);
	vector<int>qq(n,-1);
	queue<pair<int,int>>q;
	pp[aa.q0]=bb.q0;
	qq[bb.q0]=aa.q0;
	q.emplace(aa.q0,bb.q0);
	while(!q.empty()){
		auto [s1,s2]=q.front();
		q.pop();
		if(aa.acc[s1] != bb.acc[s2]) return 0;
		for(int c=0;c<m;++c){
			int t1=aa.trans[c][s1];
			int t2=bb.trans[c][s2];
			if (pp[t1]==-1 && qq[t2]==-1){
				pp[t1]=t2;
				qq[t2]=t1;
				q.emplace(t1,t2);
			}
			else if(pp[t1]!=t2 || qq[t2]!=t1){
				return 0;
			}
		}
	}
	for(int i=0;i<n;++i){
		if(pp[i]==-1) return 0; 
	}
	return 1;
}
