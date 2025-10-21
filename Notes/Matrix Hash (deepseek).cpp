#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
using ll = long long;

class Double2DHash {
private:
	int n, m;
	ll mod1, mod2;
	int base_row1, base_col1;
	int base_row2, base_col2;
	
	vector<ll> pow_row1, pow_col1;
	vector<ll> pow_row2, pow_col2;
	vector<ll> inv_row1, inv_col1;
	vector<ll> inv_row2, inv_col2;
	vector<vector<ll>> H1, H2;
	
	// 快速幂取模
	ll mod_pow(ll base, ll exp, ll mod) {
		ll result = 1;
		base %= mod;
		while (exp) {
			if (exp & 1) 
				result = (result * base) % mod;
			base = (base * base) % mod;
			exp >>= 1;
		}
		return result;
	}
	
	// 预处理幂和逆元数组
	void precompute_pows(int max_n, int max_m) {
		// 第一套哈希的幂
		pow_row1[0] = pow_col1[0] = 1;
		for (int i = 1; i <= max_n; ++i) {
			pow_row1[i] = (pow_row1[i-1] * base_row1) % mod1;
		}
		for (int j = 1; j <= max_m; ++j) {
			pow_col1[j] = (pow_col1[j-1] * base_col1) % mod1;
		}
		
		// 第二套哈希的幂
		pow_row2[0] = pow_col2[0] = 1;
		for (int i = 1; i <= max_n; ++i) {
			pow_row2[i] = (pow_row2[i-1] * base_row2) % mod2;
		}
		for (int j = 1; j <= max_m; ++j) {
			pow_col2[j] = (pow_col2[j-1] * base_col2) % mod2;
		}
		
		// 第一套哈希的逆元
		ll inv_base_row1 = mod_pow(base_row1, mod1-2, mod1);
		ll inv_base_col1 = mod_pow(base_col1, mod1-2, mod1);
		inv_row1[0] = inv_col1[0] = 1;
		for (int i = 1; i <= max_n; ++i) {
			inv_row1[i] = (inv_row1[i-1] * inv_base_row1) % mod1;
		}
		for (int j = 1; j <= max_m; ++j) {
			inv_col1[j] = (inv_col1[j-1] * inv_base_col1) % mod1;
		}
		
		// 第二套哈希的逆元
		ll inv_base_row2 = mod_pow(base_row2, mod2-2, mod2);
		ll inv_base_col2 = mod_pow(base_col2, mod2-2, mod2);
		inv_row2[0] = inv_col2[0] = 1;
		for (int i = 1; i <= max_n; ++i) {
			inv_row2[i] = (inv_row2[i-1] * inv_base_row2) % mod2;
		}
		for (int j = 1; j <= max_m; ++j) {
			inv_col2[j] = (inv_col2[j-1] * inv_base_col2) % mod2;
		}
	}
	
public:
	Double2DHash(vector<vector<int>>& matrix, 
				 int br1 = 131, int bc1 = 13331, 
				 ll m1 = 1000000007,
				 int br2 = 313, int bc2 = 33331, 
				 ll m2 = 999999937)
	: base_row1(br1), base_col1(bc1), mod1(m1),
	base_row2(br2), base_col2(bc2), mod2(m2) {
		
		n = matrix.size();
		m = n ? matrix[0].size() : 0;
		
		// 初始化数组大小
		pow_row1.resize(n+1); pow_col1.resize(m+1);
		pow_row2.resize(n+1); pow_col2.resize(m+1);
		inv_row1.resize(n+1); inv_col1.resize(m+1);
		inv_row2.resize(n+1); inv_col2.resize(m+1);
		H1.assign(n+1, vector<ll>(m+1, 0));
		H2.assign(n+1, vector<ll>(m+1, 0));
		
		// 预处理幂和逆元
		precompute_pows(n, m);
		
		// 构建哈希前缀表
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < m; ++j) {
				// 第一套哈希前缀
				ll val1 = matrix[i][j] * pow_row1[i] % mod1 * pow_col1[j] % mod1;
				H1[i+1][j+1] = ((H1[i][j+1] + H1[i+1][j] - H1[i][j] + val1) % mod1 + mod1) % mod1;
				
				// 第二套哈希前缀
				ll val2 = matrix[i][j] * pow_row2[i] % mod2 * pow_col2[j] % mod2;
				H2[i+1][j+1] = ((H2[i][j+1] + H2[i+1][j] - H2[i][j] + val2) % mod2 + mod2) % mod2;
			}
		}
	}
	
	// 获取子矩阵[r1,r2] x [c1,c2]的双哈希值
	pair<ll, ll> get_hash(int r1, int c1, int r2, int c2) {
		// 第一套哈希
		ll area1 = (H1[r2+1][c2+1] - H1[r1][c2+1] - H1[r2+1][c1] + H1[r1][c1]) % mod1;
		area1 = (area1 + mod1) % mod1;
		area1 = area1 * inv_row1[r1] % mod1 * inv_col1[c1] % mod1;
		
		// 第二套哈希
		ll area2 = (H2[r2+1][c2+1] - H2[r1][c2+1] - H2[r2+1][c1] + H2[r1][c1]) % mod2;
		area2 = (area2 + mod2) % mod2;
		area2 = area2 * inv_row2[r1] % mod2 * inv_col2[c1] % mod2;
		
		return {area1, area2};
	}
};

// 示例用法
int main() {
	// 示例矩阵
	vector<vector<int>> mat1 = {
{1, 2, 3},
	{4, 5, 6},
	{7, 8, 9}
};
	
	vector<vector<int>> mat2 = {
		{1, 2, 3},
		{4, 5, 6},
		{7, 8, 9}
	};
	
	// 初始化哈希对象
	Double2DHash hash1(mat1);
	Double2DHash hash2(mat2);
	
	// 查询子矩阵是否相同 (以左上角(0,0)到右下角(1,1)为例)
	auto h1 = hash1.get_hash(0, 0, 1, 1);
	auto h2 = hash2.get_hash(0, 0, 1, 1);
	
	if (h1 == h2) {
		cout << "子矩阵相同" << endl;
	} else {
		cout << "子矩阵不同" << endl;
	}
	
	// 查询更大区域 (整个矩阵)
	h1 = hash1.get_hash(0, 0, 2, 2);
	h2 = hash2.get_hash(0, 0, 2, 2);
	
	if (h1 == h2) {
		cout << "全矩阵相同" << endl;
	} else {
		cout << "全矩阵不同" << endl;
	}
	
	return 0;
}
