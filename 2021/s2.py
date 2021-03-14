import sys

# This is faster than input() and just redefines the function so you can use input() to get input like normal
input = sys.stdin.readline

m = int(input())
n = int(input())
k = int(input())

# Sets for the 2 strokes
leftright = set()
updown = set()

# Stroke Algorithm
for _ in range(k):
    line = input()
    line = line.split()
    optype = line[0]
    x = int(line[1])
    # 2 strokes cancel out
    if(optype=='R'):
        if x in leftright:
            leftright.remove(x)
        else:
            leftright.add(x)
    else:
        if x in updown:
            updown.remove(x)
        else:
            updown.add(x)

# Total formula, watch youtube video for explanation
total = 0

total += m * len(updown)
total += n * len(leftright)
total -= 2 * len(updown) * len(leftright)

print(total)

