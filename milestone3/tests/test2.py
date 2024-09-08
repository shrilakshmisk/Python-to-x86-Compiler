
class Person:
    def __init__(self, name: str, age: int) :
        self.name: str = name
        self.age: int = age

    def introduce(self) -> None:
        print("Hello, my name is Shrilakshmi and I am 16 years old.")

class Student(Person):
    def __init__(self, name: str, age: int, student_id: str) :
        Person.__init__(self, name, age)
        self.student_id: str = student_id
        self.student_list: list[int] = [1,2,3,4,5]
        self.smartness: int

    def study(self) -> None:
        print("Shrilakshmi is studying.")

    def calc_smartness(self) -> None:
        self.smartness = self.age * 2

    def update_list(self) -> None:
        i : int 
        for i in range(0,5):
          self.student_list[i] = self.student_list[i]+1
        

class GraduateStudent(Student):
    def __init__(self, name: str, age: int, student_id: str, thesis_topic: str) :
            Student.__init__(self, name, age, student_id)
            self.thesis_topic: str = thesis_topic

    def research(self) -> None:
        print("Shrilakshmi is researching on Advanced theory of computation.")


def main():
    student1: Student = Student("Alice", 20, "S1001")
    grad_student1: GraduateStudent = GraduateStudent("Charlie", 24, "GS1001", "Quantum Computing")
    student1.introduce()
    grad_student1.research()
    student2: Student = Student("Shrilakshmi", 20, "S10290")
    i : int = 0
    print("list before update:")
    while i < 5:
      print(student2.student_list[i])
      i = i+1
    i = 0
    student2.update_list()
    print("list after update:")
    for i in range(5):
        print(student2.student_list[i])

if __name__ == "__main__":
  main()
  
