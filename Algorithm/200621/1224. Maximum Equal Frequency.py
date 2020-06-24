from collections import Counter

#nums = [2,2,1,1,5,3,3,5]
nums = [10,2,8,9,3,8,1,5,2,3,7,6]
count = Counter(nums)
print(count)


num_len = len(nums)
count_dict = Counter(nums)
for i in range(num_len):
	count_dict[nums[num_len-i-1]] = count_dict[nums[num_len-i-1]]-1
	print(count_dict)
