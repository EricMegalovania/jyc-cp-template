template<class S,int K>
struct bitTrie{
	static_assert(std::is_integral_v<S>);
	static_assert(K<=sizeof(S)*8);
	vector<array<S,2>>trie;
	vector<int>cnt; // record prefix's number
	bitTrie(){init();}
	void init(){
		trie.assign(1,{0,0});
		cnt.assign(1,0);
	}
	void insert(const S x,const int add=1){
		int p=0;
		for(int i=K-1,j;i>=0;--i){
			j=x>>i&1;
			if(!trie[p][j]){
				trie[p][j]=trie.size();
				trie.push_back({0,0});
				cnt.push_back(0);
			}
			cnt[p=trie[p][j]]+=add;
		}
	}
	S find_xor_max(const S x){
		int p=0; S r=0;
		for(int i=K-1,j;i>=0;--i){
			j=x>>i&1;
			if(cnt[trie[p][!j]]>0){
				r|=S(1)<<i;
				p=trie[p][!j];
			}
			else p=trie[p][j];
		}
		return r;
	}
};
