class Trie{
private:
	vector<array<int,26>>trie;
	vector<int>end,cnt; //end标记有多少个模式串以此为结尾
	//cnt记录当前状态是多少个模式串的前缀
public:
	Trie(){init();}
	void init(){
		trie.assign(1,{});
		end.assign(1,0);
		cnt.assign(1,0);
	}
	void insert(const string& s){
		int p=0;
		for(auto c:s){
			int i=c-'a';
			if(!trie[p][i]){
				trie[p][i]=trie.size();
				trie.push_back({});
				end.push_back(0);
				cnt.push_back(0);
			}
			cnt[p=trie[p][i]]++;
		}
		end[p]++;
	}
	bool find(const string& s){ //找Trie里是否有s
		int p=0;
		for(auto c:s){
			int i=c-'a';
			if(!trie[p][i]) return 0;
			p=trie[p][i];
		}
		return end[p]>0;
	}
	int query(const string& s){ //找s是多少个模式串的前缀
		int p=0;
		for(auto c:s){
			int i=c-'a';
			if(!trie[p][i]) return 0;
			p=trie[p][i];
		}
		return cnt[p];
	}
};
