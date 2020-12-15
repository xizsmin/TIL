# https://leetcode.com/problems/intersection-of-two-linked-lists/
'''
Write a program to find the node at which the intersection of two singly linked lists begins.

   a1 -> a2
           \
            c1 -> c2 -> c3
            /
b1 -> b2 ->b3 

TRICK:
Iterate over to lists at the same time, as follows:

  a1 a2 c1 c2 c3 b1 b2 b3 c1 c2 c3
  b1 b2 b3 c1 c2 c3 a1 a2 c1 c2 c3
                          !!

You must find they meet at the position marked as !! .

'''


class Solution:
    def getIntersectionNode(self, headA: ListNode, headB: ListNode) -> ListNode:
        p1 = headA
        p2 = headB
        if p1 == None or p2 == None:
            return None
        flag1 = False
        flag2 = False
        while p1 != p2:
            p1 = p1.next
            p2 = p2.next
            if p1 == None:
                if not flag1:
                    p1 = headB
                    flag1 = True
                else:
                    break
            if p2 == None:
                if not flag2:
                    p2 = headA
                    flag2 = True
                else:
                    break
            
        return p1
