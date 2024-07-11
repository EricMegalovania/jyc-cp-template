class AC{ //Aho-Corasick Automaton
private:
	vector<array<int,26>>trie;
	vector<vector<int>>idx; //模式串的编号
	vector<int>fail,in,cnt; //cnt是每个状态被匹配了多少次
public:
	AC(){init();}
	void init(){
		trie.assign(1,{});
		idx.assign(1,{});
	}
	void insert(const string& s,const int& id){
		int p=0;
		for(auto c:s){
			int i=c-'a';
			if(!trie[p][i]){
				trie[p][i]=trie.size();
				trie.push_back({});
				idx.push_back({});
			}
			p=trie[p][i];
		}
		idx[p].push_back(id);
	}
	void build(){
		fail.resize(trie.size());
		in.assign(trie.size(),0);
		cnt.assign(trie.size(),0);
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
				in[trie[Fail][i]]++;
				q.push(j);
			}
		}
	}
	void query(const string& s){
		int p=0;
		for(auto c:s){
			int i=c-'a';
			cnt[p=trie[p][i]]++;
		}
	}
	void topo(vector<int>& ans){
		queue<int>q;
		for(int i=0;i<trie.size();i++){
			if(!in[i]) q.push(i);
		}
		while(q.size()){
			int p=q.front(); q.pop();
			for(auto id:idx[p]) ans[id]=cnt[p];
			cnt[fail[p]]+=cnt[p];
			if(!--in[fail[p]]) q.push(fail[p]);
		}
	}
};
