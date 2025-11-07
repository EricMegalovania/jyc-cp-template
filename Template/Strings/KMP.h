#define vi vector<int>
void kmp(const auto& s,vi& pi) {
	const int n=(int)s.size();
	pi.assign(n,0);
	for(int i=1;i<n;++i){
		int j=pi[i-1];
		while(j>0 && s[i]!=s[j]) j=pi[j-1];
		if(s[i]==s[j]) ++j;
		pi[i]=j;
	}
}
// s is text, t is pattern to be found
void kmp(const auto& s,const auto& t,vi& v,const auto& sep){
#define TP(x) std::decay_t<decltype(x)>
	static_assert(std::is_same_v<TP(s),TP(t)>);
	static_assert(std::is_same_v<TP(s[0]),TP(sep)>);
#undef TP
	const int n=(int)s.size();
	const int m=(int)t.size();
	auto cur=t; cur.push_back(sep);
	cur.insert(cur.end(),all(s));
	vi lps; kmp(cur,lps); clr(v);
	for(int i=m+1;i<=n+m;++i){
		if(lps[i]==m) v.emplace_back(i-2*m);
	}
}
#undef vi
