const int N = 1000050;
int trie[N][26];
int cnt[N];
int id;

void insert(string s)
{
	int p = 0;
	for (int i = 0; i < s.size(); i++)
	{
		int x = s[i] - 'a';
		if (trie[p][x] == 0) trie[p][x] = ++id;
		p = trie[p][x];
	}
	cnt[p]++;
}

int  find(string s)
{
	int p = 0;
	for (int i = 0; i < s.size(); i++)
	{
		int x = s[i] - 'a';
		if (trie[p][x] == 0)return 0;
		p = trie[p][x];
	}
	return cnt[p];
}
