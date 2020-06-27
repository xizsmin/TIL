from collections import Counter

nums = [2,2,1,1,5,3,3,5]
#nums = [10,2,8,9,3,8,1,5,2,3,7,6]

cnt_nums = Counter(nums)
cnt_cnts = Counter(cnt_nums.values())

len_nums = len(nums)
for i in range(len_nums):
	index = len_nums-i-1
	cnt = cnt_nums[nums[index]]
	cnt_nums[nums[index]] = cnt-1
	cnt_cnts = Counter(cnt_nums.values())

	if 0 in cnt_cnts:
		cnt_cnts.pop(0)
	print(cnt_nums)
	print(cnt_cnts)

	if len(cnt_cnts)==2 and 1 in cnt_cnts.values():
		print('****',index)
		break

	
	
	
'''
cnt_nums = Counter(nums)
max_cnt = max(cnt_nums.values())
min_cnt = min(cnt_nums.values())
print('max_cnt:',max_cnt,'min_cnt:',min_cnt)


i=0
for n in reversed(nums):
	print('removing', n)
	cnt_nums[n] = cnt_nums[n]-1
	print('  cnt_nums[',n,']:', cnt_nums[n]+1,'---->', cnt_nums[n])

	print('max_cnt:',max_cnt,'min_cnt:',min_cnt)
	if max_cnt == min_cnt+1:
		print(Counter(cnt_nums.values()))
		if (Counter(cnt_nums.values())[max_cnt] == 1):
			print('****', len(nums)-i-1)
			break
	if cnt_nums[n] == 0:
		cnt_nums.pop(n)
	elif cnt_nums[n] < min_cnt:
		min_cnt = cnt_nums[n]


	i = i+1
'''
