
from collections import Counter

def chk(d):
	if len(d) != 2:
		return False
	if not(1 in d.values()):
		return False
	k = d.keys()
	d1=sorted(d.items(), key=(lambda x:x[1]), reverse=True)
	#print('---->',d1,':', d1[0][0], ',', d1[0][1], ':', d1[1][0],',',d1[1][1])

	if d1[0][0]+1 == d1[1][0] or d1[1][0] == 1 or (d1[0][1]==1 and d1[1][1]==1) or (d1[0][1]==1 and d1[0][0]-1==d1[1][0]):
		return True
	return False



class Solution:
    def maxEqualFreq(self, nums: List[int]) -> int:
        cnt_nums = Counter(nums)
        i=0
        for n in reversed(nums):
            i=i+1
            cnt_cnts = Counter(cnt_nums.values())
            #print(cnt_cnts)
            if (chk(cnt_cnts)):
                return (len(nums)-i+1)
            
            cnt_nums[n] = cnt_nums[n]-1
            if (cnt_nums[n] == 0):
                cnt_nums.pop(n)
        if (len(cnt_nums)==0):
            return (len(nums))
