import sys
from array import array
from dataclasses import dataclass


@dataclass(slots=True)
class SCC(Graph):

    def __init__(self, n: int) -> None:
        Graph.__init__(self, n)

    def build(self) -> array:
        """
        return an array of (n+1) elements
        the last one is total colors
        others are color of each node
        """
        n = self.n
        sys.setrecursionlimit(max(n + 1000, sys.getrecursionlimit()))

        dfn = array('i', [-1] * n)
        low = array('i', [-1] * n)
        instack = array('b', [0] * n)
        scc = array('i', [-1] * (n + 1))
        tim = col = 0
        stk = array('i', [0] * n)
        top = 0

        def tarjan(u: int) -> None:
            nonlocal tim, col, top

            low[u] = dfn[u] = tim
            tim += 1
            stk[top] = u
            instack[u] = 1
            top += 1

            for v in self.iterate(u):  # CHECK v
                if dfn[v] == -1:
                    tarjan(v)
                    low[u] = low[u] if low[u] < low[v] else low[v]
                elif instack[v]:
                    low[u] = low[u] if low[u] < low[v] else low[v]

            if dfn[u] == low[u]:
                while True:
                    top -= 1
                    v = stk[top]
                    scc[v] = col
                    instack[v] = 0
                    if v == u:
                        break
                col += 1

        for u in range(n):
            if dfn[u] == -1:
                tarjan(u)

        scc[-1] = col
        return scc
