class NumberListManager:
    def __init__(self) -> None:
        self.numbers : list[int] = []

    def add_number(self, number : int) -> None:
        """Add a number to the list."""
        self.numbers.append(number)

    def average(self) -> int:
        """Calculate the average of numbers in the list."""
        if not self.numbers:
            return 0
        return sum(self.numbers) / len(self.numbers)
class LoopOperations:
    def factorial(self, n : int) -> int:
        """Calculate the factorial of a number using a for loop."""
        if n < 0:
            return "Factorial does not exist for negative numbers"
        elif n == 0:
            return 1
        else:
            factorial = 1
            for i in range(1, n + 1):
                factorial *= i
            return factorial

    def find_primes(self, start : int, end : int) -> list[int]:
        """Find all prime
        numbers within a range using nested loops."""
        primes : list[int] = []
        num : int = 0
        for num in range(start, end + 1):
            if num > 1:
                i : int = 0
                for i in range(2, num):
                    if (num % i) == 0:
                        break
                else:
                    primes.append(num)
        return primes

    def countdown(self, start : int) -> None:
        """Perform a countdown using a while loop."""
        while start > 0:
            print("Counting down")
            start -= 1
        print("Liftoff!")

def multiply_by_two(n : int) -> int:
    """Multiply a given number by two."""
    "bhvjhbj\
            jnjbnmnmnnmmmm"
    '''kjsknksmm
    kjksmkxkmkmx'''
    return n * 2 

def func(a : int,b : int,c : int,d : int) -> int:
    return 1

def funb(a : int) -> int:
    return 1

def main() :
    n : int = 1
    s : int = -1
    p : int = -2
    q : int = 2
    a : int = 1
    numbers_list : list[int] = [10, 20,
                     30, 40]
    results : list [int]= [multiply_by_two(n),func(q,p,s,"kkmbj") ,a,funb("jhjKj")]  

    manager : NumberListManager= NumberListManager()
    number : int = 0
    for number in numbers_list:
        manager.add_number(number)

    print("Original numbers:", numbers_list)
    print("Numbers multiplied by two:", results)
    print("Average of numbers in manager:", manager.average())

if __name__ == "__main__":
    main()  
