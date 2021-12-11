"""
https://leetcode.com/problems/merge-two-sorted-lists/

You are given the heads of two sorted linked lists list1 and list2.

Merge the two lists in a one sorted list. The list should be made by splicing together the nodes of the first two lists.

Return the head of the merged linked list.

 

Example 1:


Input: list1 = [1,2,4], list2 = [1,3,4]
Output: [1,1,2,3,4,4]
"""

# Definition for singly-linked list.
# class ListNode:
#     def __init__(self, val=0, next=None):
#         self.val = val
#         self.next = next
class Solution:
    def mergeTwoLists(self, list1: Optional[ListNode], list2: Optional[ListNode]) -> Optional[ListNode]:
        if list1 == None:
            return list2
        if list2 == None:
            return list1

        ret = None
        p = list1
        q = list2
        
        if list1.val < list2.val:
            ret = list1
            p = list1.next
        else:
            ret = list2
            q = list2.next
            
        ans = ret
        while True:
            if p is None:
                ret.next = q
                break
            if q  is None:
                ret.next = p
                break
            if p.val < q.val:
                ret.next = p
                ret = ret.next
                p = p.next
            else:
                ret.next = q
                ret = ret.next
                q = q.next
        return ans
      
      
