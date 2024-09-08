class Student:
    def __init__(self, student_id: str, name: str, grades: list[int]):
        self.student_id : str = student_id
        self.name : str = name
        self.grades : list[int] = grades

    def display_grades(self) -> None:
      print("Grades:")
      i : int
      leng : int = len(self.grades)
      for i in range(leng):
          print(self.grades[i])
    
    def display_student(self) -> None:
        print("Student ID:")
        print(self.student_id)
        print("Name:")
        print(self.name)
        self.display_grades()

    def calculate_average(self) -> int:
        if len(self.grades) == 0:
            return 0
        total : int = 0
        i : int
        leng : int = len(self.grades)
        for i in leng:
            total += self.grades[i]
        return total / leng

    def highest_grade(self) -> int:
        i : int
        leng : int = len(self.grades)
        highest : int = self.grades[0]
        for i in range(leng):
            if not self.grades[i]:
              return 0
            if self.grades[i] > highest:
                highest = self.grades[i]
        return highest

    def lowest_grade(self) -> int:
        lowest : int = self.grades[0]
        i : int
        leng : int = len(self.grades)
        for i in range(leng):
            if not self.grades[i]:
              return 0
            if self.grades[i] < lowest:
                lowest = self.grades[i]
        return lowest

def main():

    student1 : Student = Student("S001", "Alice Smith", [88, 92, 77, 90])
    student2 : Student = Student("S002", "Bob Brown", [84, 76, 88, 85])
    student3 : Student = Student("S003", "Carol Jones", [90, 90, 92, 93])
    student4 : Student = Student("S004", "Dave Wilson", [78, 82, 80, 85])

    list_of_students : list[Student]= [student1, student2, student3, student4]

    leng : int = len(list_of_students)
    i : int
    for i in range(leng):
        temp_student : Student = list_of_students[i]
        temp_student.display_student()
        average : int = temp_student.calculate_average()
        print("Highest Grade:")
        print(temp_student.highest_grade())
        print("Lowest Grade:")
        print(temp_student.lowest_grade())

if __name__ == "__main__":
    main()
