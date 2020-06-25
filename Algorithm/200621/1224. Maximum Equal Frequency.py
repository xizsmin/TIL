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
	print('------------------------')
	
	
	
