import collections

#edges = [[1,2],[2,3],[2,4]]
edges = [[1,2],[2,3],[2,4],[3,5],[1,6],[6,7]]

queue = collections.deque([])

queue.append((1, 1))

max_lev = 1
while len(queue) > 0:
    x = queue.popleft()
    max_lev = x[1]

    for e in edges:
        if e[0] == x[0]:
            queue.append((e[1], x[1]+1))

print(max_lev)


