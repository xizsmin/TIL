# https://leetcode.com/problems/check-array-formation-through-concatenation/

'''
You are given an array of distinct integers arr and an array of integer arrays pieces, 
where the integers in pieces are distinct. Your goal is to form arr by concatenating the arrays in pieces in any order. 
However, you are not allowed to reorder the integers in each array pieces[i].

Return true if it is possible to form the array arr from pieces. Otherwise, return false.


--> NO TRICK AT ALL, JUST SIMPLE IMPLEMENTATION PROBLEM.
--> WARNING: TRY NOT TO REMOVE ITEM FROM A LIST WHILE ITERATING IT !!

'''

class Solution:
    def canFormArray(self, arr: List[int], pieces: List[List[int]]) -> bool:
        if len(pieces) == 1:
            return arr ==pieces[0]
        cnt = 0
        
        for p in pieces:
            if p[0] in arr:
                i = 0
                j = arr.index(p[0])
                
                found = True
                for i in range(0, len(p)):
                    if j >= len(arr) or i >= len(p):
                        found = False
                        break
            
                    if p[i] != arr[j]:
                        found = False
                        break
                    j += 1

                if found == True:
                    print('removing', p)
                    cnt += 1
                    
        return len(pieces) == cnt
    
                
