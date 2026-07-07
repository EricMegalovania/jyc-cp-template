template <typename T>
class fhqTreap {
private:
    struct Node {
        int l, r, siz; T val; bool lazy;
        Node() : l(0), r(0), siz(0), val(T{}), lazy(0) {}
        Node(T val_) : l(0), r(0), siz(1), val(val_), lazy(0) {}
    };
    vector<Node> q; vector<int> roots;
    int New(T val) {
        Node new_node = Node(val);
        q.push_back(new_node);
        return q.size() - 1;
    }
    int clone(int id) {
        if (!id) return 0;
        q.push_back(q[id]);
        return q.size() - 1;
    }
    void update(int id) { q[id].siz = q[q[id].l].siz + q[q[id].r].siz + 1; }
    void spread(int id) {
        if (!id || !q[id].lazy) return;
        if (q[id].l) {
            const int u = clone(q[id].l);
            q[id].l = u;
            q[u].lazy ^= 1;
        }
        if (q[id].r) {
            const int u = clone(q[id].r);
            q[id].r = u;
            q[u].lazy ^= 1;
        }
        swap(q[id].l, q[id].r);
        q[id].lazy = 0;
    }
    void split(int id, int key, int &x, int &y) {
        if (!id) { x = y = 0; return; }
        spread(id);
        if (q[q[id].l].siz + 1 <= key) {
            x = clone(id);
            int nr; // IMPORTANT
            split(q[x].r, key - q[q[x].l].siz - 1, nr, y);
            q[x].r = nr;
            update(x);
        } else {
            y = clone(id);
            int nl; // IMPORTANT
            split(q[y].l, key, x, nl);
            q[y].l = nl;
            update(y);
        }
    }
    int merge(int l, int r) {
        if (l == 0 || r == 0) return l + r;
        // IMPORTANT, maintain heap-like structure
        if (int(rng() % (q[l].siz + q[r].siz)) < q[r].siz) {
            r = clone(r); spread(r);
            q[r].l = merge(l, q[r].l);
            update(r); return r;
        } else {
            l = clone(l); spread(l);
            q[l].r = merge(q[l].r, r);
            update(l); return l;
        }
    }
    void print(vector<T> &a, int u) {
        if (!u) return;
        spread(u);
        print(a, q[u].l);
        a.push_back(q[u].val);
        print(a, q[u].r);
    }
    int build(int l, int r, const vector<T> &a) {
        if (l > r) return 0;
        const int mid = (l + r) >> 1;
        int u = New(a[mid]);
        q[u].l = build(l, mid - 1, a);
        q[u].r = build(mid + 1, r, a);
        update(u);
        return u;
    }
public:
    fhqTreap() { clear(); }
    void clear() {
        q.clear(); roots.clear();
        Node empty_node = Node();
        q.push_back(empty_node);
        roots.push_back(0);
    }
    int init(const vector<T> &a) {
        roots.push_back(build(0, int(a.size()) - 1, a));
        return roots.back();
    }
    int insert(const int ver, const T x) {
        const int nr = merge(roots[ver], New(x));
        roots.push_back(nr);
        return roots.size() - 1;
    }
    int reverse(const int ver, const int l, const int r) {
        int rootX, rootY, rootZ;
        split(roots[ver], l - 1, rootX, rootZ);
        split(rootZ, r - l + 1, rootY, rootZ);
        q[rootY].lazy ^= 1;
        const int nr = merge(merge(rootX, rootY), rootZ);
        roots.push_back(nr);
        return roots.size() - 1;
    }
    // work() use _q to avoid shadow
    int work(const int ver, const int p, const int _q) {
        int rootX, rootY, rootZ;
        // set rootY to [p+1,2p]
        split(roots[ver], p * 2, rootX, rootZ);
        split(rootX, p, rootX, rootY);
        // set rootX to [1,q]
        split(roots[ver], _q, rootX, rootZ);
        const int nr = merge(rootY, rootX);
        assert(q[nr].siz == q[roots[ver]].siz);
        roots.push_back(nr);
        return roots.size() - 1;
    }
    T get(const int ver, int rank) {
        int id = roots[ver];
        while (1) {
            spread(id);
            if (q[q[id].l].siz >= rank) id = q[id].l;
            else if (q[q[id].l].siz + 1 == rank) return q[id].val;
            else {
                rank -= (q[q[id].l].siz + 1);
                id = q[id].r;
            }
        }
    }
    void to_ary(const int ver,vector<T> &a){ a.clear();print(a, roots[ver]); }
};

int main() {
#ifndef LOCAL
    cin.tie(nullptr)->sync_with_stdio(false);
#endif
    int n; cin >> n;
    vector<int> a(n); for (auto &x : a) cin >> x;
    fhqTreap<int> treap; int ver = [&]() -> int {
        vector<int> v(n * 2 + 1);
        iota(all(v), 0);
        return treap.init(v);
    }();
    vector<int> ans(n);
    for (int i = 0; auto p : a | views::reverse) {
        ver = treap.work(ver, p, n * 2 - p + 1);
        ans[i++] = treap.get(ver, 1);
    }
    for (auto x : ans) cout << x << ' ';
    return 0;
}

/*
把它当成函数的来看待
F(x) 表示初始有 x 块钱, 经过一系列过程后, 剩余多少钱
一开始, F(x) := x
假设现在在开头新增了一个数 p
G(x) :=
- F(x-p) for x>=p
- F(x+p) for x<p
G(0) G(1)   G(2)   ... G(p-1)  G(p) G(p+1) ... G(2n)
F(p) F(p+1) F(p+2) ... F(2p-1) F(0) F(1)   ... F(2n-p)
然后每次查询 F(0) 即可
现在如何从 F -> G 呢? 我们不可能直接进行复制, 加上这是 edu
于是我们想到了可持久化平衡树
把上面的转成 1-index
G(1)   G(2)   G(3)   ... G(p)  G(p+1) G(p+2) ... G(2n+1)
F(p+1) F(p+2) F(p+3) ... F(2p) F(1)   F(2)   ... F(2n-p+1)
*/
