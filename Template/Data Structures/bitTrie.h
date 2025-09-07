struct bitTrie{
	vector<array<int,2>>trie;
	vector<int>cnt; //record prefix's number
	bitTrie(){init();}
	void init(){
		trie.assign(1,{0,0});
		cnt.assign(1,0);
	}
	void insert(const int& x,const int& add=1){
		int p=0;
		for(int i=30,j;i>=0;i--){
			j=x>>i&1;
			if(!trie[p][j]){
				trie[p][j]=trie.size();
				trie.push_back({0,0});
				cnt.push_back(0);
			}
			cnt[p=trie[p][j]]+=add;
		}
	}
	int find_xor_max(const int& x){
		int p=0,ret=0;
		for(int i=30,j;i>=0;i--){
			j=x>>i&1;
			if(cnt[trie[p][!j]]>0){
				ret|=1<<i;
				p=trie[p][!j];
			}
			else p=trie[p][j];
		}
		return ret;
	}
};
