struct ByAngleLL {
    // 半平面: 极角落在 [0, pi) -> 0, [pi, 2pi) -> 1
    static constexpr int half(const PLL &v) {
        return (v.y > 0 || (v.y == 0 && v.x > 0)) ? 0 : 1;
    }
    // 严格弱序: 极角升序; 同向按 |v| 升序 (给出确定性 tie-break, 避免 std::sort 行为不定)
    bool operator()(const PLL &p, const PLL &q) const {
        const int hp = half(p), hq = half(q);
        if (hp != hq) return hp < hq;
        const LL c = cross(p, q);
        if (c) return c > 0; // cross(p,q) > 0 <=> q 在 p 的逆时针侧 <=> ang(p) < ang(q)
        return dot(p, p) < dot(q, q); // 共线同向 (含 p == q)
    }
};
struct ByAngleLD {
    // 半平面: 极角落在 [0, pi) -> 0, [pi, 2pi) -> 1
    static constexpr int half(const PDD &v) {
        const int sx = sign(v.x), sy = sign(v.y);
        return (sy == 1 || (sy == 0 && sx == 1)) ? 0 : 1;
    }
    // 严格弱序: 极角升序; 同向按 |v| 升序 (给出确定性 tie-break, 避免 std::sort 行为不定)
    bool operator()(const PDD &p, const PDD &q) const {
        const int hp = half(p), hq = half(q);
        if (hp != hq) return hp < hq;
        const int c = sign(cross(p, q));
        if (c != 0) return c > 0; // cross(p,q) > 0 <=> q 在 p 的逆时针侧 <=> ang(p) < ang(q)
        return dcmp(dot(p, p), dot(q, q)) == -1; // 共线同向 (含 p == q)
    }
};