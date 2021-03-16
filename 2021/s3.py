# Read C++ code for comments (same idea) and watch youtube video for more details


import sys

input = sys.stdin.readline


p = []
w = []
d = []

n = int(input())

def move(c: int) -> int:
    time = 0
    for a in range(n):
        leftRange = p[a]-d[a]
        rightRange = p[a]+d[a]

        if c >= leftRange and c<= rightRange:
            continue

        closest = rightRange
        if abs(c-leftRange) < abs(c-rightRange):
            closest = leftRange
        time += w[a]*abs(closest-c)
    return time


if __name__ == '__main__':
    l = 1e9
    r = 0
    for a in range(n):
        data = input().strip()
        data = data.split()
        p.append(int(data[0]))
        w.append(int(data[1]))
        d.append(int(data[2]))
        l = min(l, p[a])
        r = max(r, p[a])

    best = 1e18
    for _ in range(60):
        delta = int((r-l)/3)
        m1 = l+delta
        m2 = r-delta
        x1 = move(m1)
        x2 = move(m2)
        best = min(best, x1)
        best = min(best, x2)
        if x1 < x2:
            r = m2
        else:
            l = m1
    
    print(best)

    
