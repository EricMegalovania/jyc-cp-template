template<typename T>
struct ODT{
	map<int,T>mp;	
	ODT(){}
	void init(){
		map<int,T>().swap(mp);
		mp[1]=0;
	}
	void split(int x) {
		auto it = prev(mp.upper_bound(x)); //找到左端点小于等于 x 的区间。
		mp[x] = it->second; //设立新的区间，并将上一个区间储存的值复制给本区间。
	}
	void assign(int l, int r, T v) { //注意，这里的r是区间右端点+1
		split(l), split(r);
		auto it = mp.find(l);
		while (it->first != r) {
			it = mp.erase(it);
		}
		mp[l] = v;
	}
	void perform(int l, int r, T v) { //注意，这里的r是区间右端点+1
		split(l), split(r);
		auto it = mp.find(l);
		while (it->first != r) {
			//Perform Operations here
			
		}
	}
}
