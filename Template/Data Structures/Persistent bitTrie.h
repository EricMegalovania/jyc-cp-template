struct pbitTrie{
	vector<array<int,2>>trie;
	vector<int>cnt,root; //cnt record prefix's number
	pbitTrie(){init();}
	void init(){
		trie.assign(1,{0,0});
		cnt.assign(1,0);
		root={0};
	}
	int New(){
		trie.push_back({0,0});
		cnt.push_back(0);
		return trie.size()-1;
	}
	void add_root(const int& x){
		root.push_back(x);
	}
	int insert(int id,const int& x,const int& add=1){
		int new_id=New(),ret=new_id;
		for(int i=30,j;i>=0;i--){
			j=x>>i&1;
			trie[new_id][j]=New();
			trie[new_id][!j]=trie[id][!j];
			new_id=trie[new_id][j];
			id=trie[id][j];
			cnt[new_id]=cnt[id]+add;
		}
		return ret;
	}
	int find_xor_max(int l,int r,const int& x){
		int ret=0;
		for(int i=30,j;i>=0;i--){
			j=x>>i&1;
			if(cnt[trie[r][!j]]-cnt[trie[l][!j]]){
				ret+=(1<<i);
				l=trie[l][!j],r=trie[r][!j];
			}
			else{
				l=trie[l][j],r=trie[r][j];
			}
		}
		return ret;
	}
};
