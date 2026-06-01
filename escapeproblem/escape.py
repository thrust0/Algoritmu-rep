import random
from collections import deque

# Lenteles sukurimas
n = random.randint(4, 10)
grid = [[False] * n for _ in range(n)]

# Sudedame triusius atsitiktinai
for i in range(n):
    for j in range(n):
        if random.random() < 0.5:
            grid[i][j] = True

def is_border(i, j, n):
    return i == 0 or i == n-1 or j == 0 or j == n-1

def neighbours(i, j, n):
    result = []
    for di, dj in [(-1,0),(1,0),(0,-1),(0,1)]:  # up down left right
        ni, nj = i+di, j+dj
        if 0 <= ni < n and 0 <= nj < n:
            result.append((ni, nj))
    return result

# atspausdinimas lenteles
def print_grid():
    print()
    for i in range(n):
        row = ""
        for j in range(n):
            if grid[i][j]:
                row += "R "
            elif is_border(i, j, n):
                row += "* "
            else:
                row += ". "
        print(row)
    print()

# node id
# kiekvienas langelis yra suskirstytas i node_in ir node_out
# tai suteikia kievienam langeliui unikalu id
def node_in(i, j):   return i * n + j
def node_out(i, j):  return n*n + i*n + j

total_nodes = 2*n*n + 2
source = 2*n*n       # s
sink   = 2*n*n + 1   # t

# sukuriame flow graph
# capacity[u][v] = how much flow can still go from u to v
capacity = [[0] * total_nodes for _ in range(total_nodes)]

def add_edge(u, v, cap):
    capacity[u][v] += cap

# 1. each cell: node_in → node_out with capacity 1
#    this enforces only 1 rabbit can pass through a cell
for i in range(n):
    for j in range(n):
        add_edge(node_in(i,j), node_out(i,j), 1)

# 2. connect neighbours: node_out → node_in of neighbour
#    this lets rabbits move between cells
for i in range(n):
    for j in range(n):
        for ni, nj in neighbours(i, j, n):
            add_edge(node_out(i,j), node_in(ni,nj), 1)

# 3. connect source to each rabbit
for i in range(n):
    for j in range(n):
        if grid[i][j]:
            add_edge(source, node_in(i,j), 1)

# 4. connect each border cell to sink
for i in range(n):
    for j in range(n):
        if is_border(i, j, n):
            add_edge(node_out(i,j), sink, 1)

# --- BFS: find a path from source to sink ---
# returns the path if found, otherwise None
def bfs():
    visited = [-1] * total_nodes   # visited[v] = which node we came from
    visited[source] = source
    queue = deque([source])

    while queue:
        u = queue.popleft()
        for v in range(total_nodes):
            # visit v if not visited and there is remaining capacity
            if visited[v] == -1 and capacity[u][v] > 0:
                visited[v] = u
                if v == sink:
                    return visited   # found a path!
                queue.append(v)

    return None  # no path found

# --- Edmonds-Karp max flow ---
# keeps finding paths and pushing flow through until no path exists
def max_flow():
    flow = 0

    while True:
        visited = bfs()
        if visited is None:
            break  # no more paths, we're done

        # trace back the path from sink to source
        # find the minimum capacity along the path (bottleneck)
        path_flow = float('inf')
        v = sink
        while v != source:
            u = visited[v]
            path_flow = min(path_flow, capacity[u][v])
            v = u

        # update capacities along the path
        # forward edge loses capacity, backward edge gains it
        # (backward edge lets the algorithm "undo" a bad choice later)
        v = sink
        while v != source:
            u = visited[v]
            capacity[u][v] -= path_flow
            capacity[v][u] += path_flow
            v = u

        flow += path_flow  # one more rabbit escaped

    return flow

# --- Run it ---
rabbits = sum(grid[i][j] for i in range(n) for j in range(n))

print(f"Lenteles dydis: {n}x{n}")
print(f"Triusiu kiekis: {rabbits}")
print_grid()

result = max_flow()

print(f"Maksimalus srautas: {result}")
if result == rabbits:
    print("Visi triusiai gali istrukti!")
else:
    print(f"Tik {result} is {rabbits} triusiu gali istrukti.")