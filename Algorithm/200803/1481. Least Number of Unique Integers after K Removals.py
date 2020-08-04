'''
solution:
1. Sort given list in asc.order by each item's appearance frequency
2. Decrement each appearance counter value until k >= 0
3. Count the rest.
'''

class Solution:
    def findLeastNumOfUniqueInts(self, arr: List[int], k: int) -> int:
        cnt_list = dict(Counter(arr))
        #print(cnt_list)
        sorted_list = { k:v for (k, v) in sorted(cnt_list.items(), key=lambda item: item[1] )}
        #print(sorted_list)
        for (key,val) in sorted_list.items():
            if val <= k:
                k = k-val
                sorted_list[key]=0
                #sorted_list.pop(key)
            else:
                break
        #print(sorted_list)
            
        return sum(1 for x in sorted_list.values() if x > 0)
