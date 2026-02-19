@dataclass(slots=True)
class DSU:
    n: int
    fa: List[int]
    sz: List[int]

    def __init__(self, n: int) -> None:
        self.n = n
        self.fa = list(range(n))
        self.sz = [1] * n

    def get(self, x: int) -> int:
        while x != self.fa[x]:
            x = self.fa[x] = self.fa[self.fa[x]]
        return x

    def same(self, x: int, y: int) -> bool:
        return self.get(x) == self.get(y)

    def merge(self, x: int, y: int) -> bool:
        x, y = self.get(x), self.get(y)
        if x == y:
            return False
        if self.sz[x] < self.sz[y]:
            x, y = y, x
        self.sz[x] += self.sz[y]
        self.fa[y] = x
        return True

    def size(self, x: int) -> int:
        return self.sz[self.get(x)]