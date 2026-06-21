#define sz (int(a.size()))
template <typename T> // 用来代替 deque, 解决 deque 容易 MLE 的问题
struct rbf { // Ring Buffer
    std::vector<T> a;
    int head = 0, len = 0; // head: 逻辑下标 0 对应的物理下标
    void reserve(const int n) { // 自动扩容到至少 n 个元素
        if (sz >= n) return;
        int m = sz ? sz : 4;
        while (m < n) m <<= 1;
        std::vector<T> buf(m);
        for (int i = 0; i < len; ++i) buf[i] = (*this)[i];
        std::swap(a, buf); head = 0;
    }
    int size() const { return len; }
    T &operator[](int idx) {
        if ((idx += head) >= sz) idx -= sz;
        return a[idx];
    }
    T &front() { return (*this)[0]; }
    T &back() { return (*this)[len - 1]; }
    void push_front(const T &v) { reserve(len + 1);
        if (--head < 0) head += sz;
        a[head] = v, ++len;
    }
    void push_back(const T &v) { reserve(len + 1);
        int x = head + len;
        if (x >= sz) x -= sz;
        a[x] = v, ++len;
    }
    void pop_front() { --len; if (++head >= sz) head = 0; }
    void pop_back() { --len; }
    void resize(const int n, const T &v = T{}) {
        if (n <= len) return;
        reserve(n);
        while (len < n) push_back(v);
    }
    void assign(const int n, const T &v=T{}){ a.assign(n,v); head=0,len=n; }
    void swap(rbf &o) {
        std::swap(a, o.a);
        std::swap(head, o.head);
        std::swap(len, o.len);
    }
};
#undef sz