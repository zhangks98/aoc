from sys import stdin
import sys

sys.setrecursionlimit(100000)

grid = []
for line in stdin:
    grid.append(line.strip())
n = len(grid)
m = len(grid[0])
vis = [[False] * m for _ in range(n)]

pipe_dict = {
    '|': [(-1, 0), (1, 0)],
    '-': [(0, -1), (0, 1)],
    'L': [(-1, 0), (0, 1)],
    'J': [(-1, 0), (0, -1)],
    '7': [(1, 0), (0, -1)],
    'F': [(1, 0), (0, 1)],
}

dir_dict = {
    (1, 0): ('|', 'L', 'J'),
    (-1, 0): ('|', '7', 'F'),
    (0, -1): ('-', 'L', 'F'),
    (0, 1): ('-', 'J', '7'),
}


def dfs(i, j, step, path: list[tuple[int, int]], allowed_pipes, res):
    if i < 0 or i >= n or j < 0 or j >= m or grid[i][j] == '.':
        return

    if grid[i][j] == 'S':
        if step > res['step']:
            res['step'] = step
            res['path'] = path.copy()
        return
    if vis[i][j]:
        return
    if grid[i][j] not in allowed_pipes:
        return

    vis[i][j] = True
    for di, dj in pipe_dict[grid[i][j]]:
        path.append((i + di, j + dj))
        dfs(i + di, j + dj, step + 1, path, dir_dict[(di, dj)], res)
        path.pop()


def get_start() -> tuple[int, int]:
    for i in range(n):
        for j in range(m):
            if grid[i][j] == 'S':
                return i, j
    return 0, 0


si, sj = get_start()
res = {'step': 0, 'path': []}
for di, dj in [(-1, 0), (1, 0), (0, -1), (0, 1)]:
    i = si + di
    j = sj + dj
    if i < 0 or i >= n or j < 0 or j >= m:
        continue
    if grid[i][j] in dir_dict[(di, dj)]:
        path = [(i, j)]
        dfs(i, j, 1, path, dir_dict[(di, dj)], res)

print(res['step'] // 2)

path = [['.'] * m for _ in range(n)]
for (i, j) in res['path']:
    path[i][j] = grid[i][j]


def set_start_pipe():
    for pipe, dirs in pipe_dict.items():
        is_valid = True
        for di, dj in dirs:
            i = si + di
            j = sj + dj
            if i < 0 or i >= n or j < 0 or j >= m:
                is_valid = False
                continue
            if path[i][j] not in dir_dict[(di, dj)]:
                is_valid = False
        if is_valid:
            return pipe
    return ''


path[si][sj] = set_start_pipe()
num_included = 0
for i, row in enumerate(path):
    included = 0
    keep_state = ''
    for j, pipe in enumerate(row):
        if included == 1 and pipe == '.':
            num_included += 1
            path[i][j] = '*'

        if pipe == '|':
            included = 1 - included
            keep_state = ''
        if pipe == 'F' or pipe == 'L':
            keep_state = pipe
        if pipe == 'J':
            if keep_state == 'F':
                included = 1 - included
            keep_state = ''
        if pipe == '7':
            if keep_state == 'L':
                included = 1 - included
            keep_state = ''


# print()
# for row in path:
#     print(' '.join(row))
print(num_included)
