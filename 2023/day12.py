from sys import stdin
from functools import lru_cache


def get_pattern(row):
    i = 0
    p = []
    while i < len(row):
        while i < len(row) and row[i] == '.':
            i += 1
        if i == len(row):
            break
        start = i
        while i < len(row) and row[i] == '#':
            i += 1
        p.append(i - start)
    return p


def all_mutations(a, idx, subset, data):
    if idx == len(a):
        row = data['row'].copy()
        for i in subset:
            row[i] = '#'
        if get_pattern(row) == data['pattern']:
            data['matched'] += 1
        return

    all_mutations(a, idx + 1, subset[:], data)
    all_mutations(a, idx + 1, subset + [a[idx]], data)


def match_patterns_bruteforce(row, pattern):
    print(row, pattern)
    clean_row = [s for s in row]
    unknowns = []
    for i, s in enumerate(row):
        if s == '?':
            unknowns.append(i)
            clean_row[i] = '.'
    data = {
        'row': clean_row,
        'pattern': pattern,
        'matched': 0
    }
    all_mutations(unknowns, 0, [],  data)
    return data['matched']


@lru_cache
def match_patterns(row, pattern) -> int:
    if len(pattern) == 0:
        return 1 if '#' not in row else 0
    if sum(pattern) + len(pattern) - 1 > len(row):
        return 0

    if row[0] == '.':
        return match_patterns(row[1:], pattern)

    curr = pattern[0]
    num_matches = 0
    if row[0] == '?':
        num_matches += match_patterns(row[1:], pattern)

    if curr <= len(row) and '.' not in row[:curr]:
        has_known_neighbor = curr < len(row) and row[curr] == '#'
        if not has_known_neighbor:
            num_matches += match_patterns(row[curr + 1:], pattern[1:])
    return num_matches


total = 0
for line in stdin:
    row, pattern = line.split()
    pattern = [int(v) for v in pattern.split(',')]
    row = '?'.join([row] * 5)
    pattern *= 5
    total += match_patterns(row, tuple(pattern))

print(total)
