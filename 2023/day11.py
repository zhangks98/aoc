from sys import stdin
from itertools import combinations

universe = []
for line in stdin:
    universe.append([c for c in line.strip()])

row_expand = []
col_expand = []
for i, row in enumerate(universe):
    if all(s == '.' for s in row):
        row_expand.append(i)

for j in range(len(universe[0])):
    if all(s == '.' for s in [row[j] for row in universe]):
        col_expand.append(j)


def lower_bound(a, val):
    l = 0
    r = len(a)
    while l < r:
        mid = l + (r - l) // 2
        if (a[mid] < val):
            l = mid + 1
        else:
            r = mid
    return l


def upper_bound(a, val):
    l = 0
    r = len(a)
    while l < r:
        mid = l + (r - l) // 2
        if (a[mid] <= val):
            l = mid + 1
        else:
            r = mid
    return l

# Given a sorted array a, find the number of insertecting element within [lo, hi].


def num_intersect(a, lo, hi):
    l = lower_bound(a, lo)
    r = upper_bound(a, hi)
    return r - l


galaxies = []
for i, row in enumerate(universe):
    for j, c in enumerate(row):
        if c == '#':
            galaxies.append((i, j))
dist_sum = 0
factor = 1000000
for x, g1 in enumerate(galaxies):
    for y in range(x + 1, len(galaxies)):
        g2 = galaxies[y]
        i0, j0 = g1
        i1, j1 = g2
        if i1 < i0:
            i0, i1 = i1, i0
        if j1 < j0:
            j0, j1 = j1, j0
        dist = i1 - i0 + j1 - j0
        dist += num_intersect(row_expand, i0, i1) * (factor - 1)
        dist += num_intersect(col_expand, j0, j1) * (factor - 1)
        dist_sum += dist

print(dist_sum)
