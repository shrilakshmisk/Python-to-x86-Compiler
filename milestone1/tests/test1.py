
class ListNode:
    def __init__(self, val : int) -> None:
        self.val = val
        self.next : ListNode = None

class Solution:
    def mergeKLists(self, 
                    lists : list[ListNode]) -> ListNode:
        if len(lists) == 0 or lists is None:
            return None
        
        def merge_2_linkedlist(l1: ListNode, 
                               l2 : ListNode) -> ListNode:
            dummy : ListNode= ListNode()
            tail : ListNode= dummy
            while l1 and l2:
                if l1.val > l2.val:
                    tail.next = l2
                    l2 = l2.next
                else:
                    tail.next = l1
                    l1 = l1.next
                tail = tail.next

            if l1:
                tail.next = l1

            if l2:
                tail.next = l2

            return dummy.next
                
        while len(lists) > 1:
            answer : list[ListNode]= []
            i : int = 0
            for i in range(0, len(lists), 2):
                l1 = lists[i]
                if i+1 < len(lists) : 
                    l2 = lists[i+1]
                else:
                    l2 = None
                merged_list : ListNode = merge_2_linkedlist(l1, l2)
                answer.append(merged_list)
            lists = answer

        return lists[0]

def main():
    l1 :ListNode = ListNode(1)
    l1.next = ListNode(4)
    l1.next.next = ListNode(5)

    l2 : ListNode= ListNode(1)
    l2.next = ListNode(3)
    l2.next.next = ListNode(4)

    solution : Solution= Solution()


    merged_list : ListNode= solution.mergeKLists([l1, l2])

    while merged_list:
        print(merged_list.val, end=''' ''')
        print("""merge
              d""")
        merged_list = merged_list.next

if __name__ == "__main__":
    main()


