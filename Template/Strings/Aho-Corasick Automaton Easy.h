class AC{ //Aho-Corasick Automaton
private:
	vector<array<int,26>>trie;
	vector<int>cnt,fail; //cnt是有多少个模式串是这个状态
public:
	AC(){init();}
	void init(){
		trie.assign(1,{});
		cnt.assign(1,0);
	}
	void insert(const string& s){
		int p=0;
		for(auto c:s){
			int i=c-'a';
			if(!trie[p][i]){
				trie[p][i]=trie.size();
				trie.push_back({});
				cnt.push_back(0);
			}
			p=trie[p][i];
		}
		cnt[p]++;
	}
	void build(){
		fail.resize(trie.size());
		queue<int>q;
		fail[0]=0;
		for(int i=0;i<26;i++){
			fail[trie[0][i]]=0;
			if(trie[0][i]) q.push(trie[0][i]);
		}
		while(q.size()){
			int p=q.front(); q.pop();
			int Fail=fail[p];
			for(int i=0;i<26;i++){
				int &j=trie[p][i];
				if(!j){
					j=trie[Fail][i];
					continue;
				}
				fail[j]=trie[Fail][i];
				cnt[j]+=cnt[trie[Fail][i]];
				q.push(j);
			}
		}
	}
	int query(const string& s){
		int res=0,p=0;
		for(auto c:s){
			int i=c-'a';
			res+=cnt[p=trie[p][i]];
		}
		return res;
	}
};
