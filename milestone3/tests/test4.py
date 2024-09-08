class array_algos:
    def __init__(self):
        self.nums : list[int] = [1,-2,-29,20,30,49,29,9,13]
        self.leng : int = len(self.nums)

    def insertion_sort(self) -> None:  
        i : int
        j : int
        a : int
        for i in range(1, self.leng):  
            a = self.nums[i]  
            j = i - 1 
            while j >= 0 and a < self.nums[j]:  
                self.nums[j + 1] = self.nums[j]  
                j -= 1 
                 
            self.nums[j + 1] = a  

    def maxSubArray(self) -> int:
        ans : int = -9999999
        i : int
        j : int
        cur_sum : int
        for i in range(self.leng):
            cur_sum = 0
            for j in range(i, self.leng):
                cur_sum += self.nums[j]
                if ans < cur_sum :
                    ans = cur_sum
        return ans

def main() :
    test : array_algos = array_algos()
    max_sub_array_sum : int = test.maxSubArray()
    print("maximum subarray sum:")
    print(max_sub_array_sum)
    test.insertion_sort()
    i : int
    print("sorted array")
    for i in range(test.leng) :
        print(test.nums[i])

if __name__ == "__main__" :
    main()

