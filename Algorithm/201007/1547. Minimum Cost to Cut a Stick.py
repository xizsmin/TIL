
'''
Given a wooden stick of length n units. The stick is labelled from 0 to n. For example, a stick of length 6 is labelled as follows:

|---|---|---|---|---|---|
0   1   2   3   4   5   6

Given an integer array cuts where cuts[i] denotes a position you should perform a cut at.

You should perform the cuts in order, you can change the order of the cuts as you wish.

The cost of one cut is the length of the stick to be cut, the total cost is the sum of costs of all cuts. 
When you cut a stick, it will be split into two smaller sticks (i.e. the sum of their lengths is the length of the stick before the cut). 
Please refer to the first example for a better explanation.

Return the minimum total cost of the cuts.
'''

# TBD: optimization by pruning
# ....

cuts = [1,3,4,5]
visited = []
N = 7 

cuts = [5,6,1,4,2]
N=9
ans = 1000000
dp = dict((x, 1000000) for x in range(0, len(cuts)))

print(dp)

def find_my_pos(idx, cutlist):
    for _clist in cutlist:
        if idx >= _clist[0] and idx <= _clist[1]:
            #print('--> return (', _clist[0], ',', _clist[1], ')')
            return _clist


def f(idx, cuts, visited, cutlist, cost, depth):#: int, cuts: List[int], visited: List[int]):
    for i in range(0, depth):
	    print(' ', end='')
    print(cuts[idx], '--->', cost)
    if len(visited) == len(cuts):
        print('!! cost:', cost)
        return cost
    ret = 1000000
    for i in range(0, len(cuts)):
        if (idx != i) and (i not in visited):
            my_pos = find_my_pos(cuts[i], cutlist)
            cutlist.remove(my_pos)
            cutlist.append([my_pos[0], cuts[i]])
            cutlist.append([cuts[i], my_pos[1]])
            ret = min(ret, f(i, cuts, visited+[i], cutlist, cost+(my_pos[1]-my_pos[0]), depth+1))
            cutlist.append(my_pos)
            cutlist.remove([my_pos[0], cuts[i]])
            cutlist.remove([cuts[i], my_pos[1]])

            dp[i] = ret


    return ret

'''
cutlist = [[0,3],[3,N]]
ans = 1000000
ans = f(1, cuts, visited+[1], cutlist, N, 0)
'''
ans = 1000000
for i in range(0, len(cuts)):
    cutlist = [[0, cuts[i]],[cuts[i], N]]
    ans = min(ans, f(i, cuts, visited+[i], cutlist, N, 0))
print('ans:', ans)
    
    
