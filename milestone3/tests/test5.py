class dog :
    def __init__(self,dog_color : str , dog_type : str):
        self.color : str = dog_color
        self.breed : str = dog_type

    def which_color(self) -> None:
        print(self.color)

    def which_breed(self) -> None :
        print(self.breed)

def main() :
    a : str = "biege"
    b : str = "labrador"
    d1 : dog = dog(a,b)
    a  = "black"
    b  = "german shephard"
    d2 : dog = dog(a,b)
    a = "brown"
    b = "doberman"
    d3 : dog = dog(a,b)
    a = "white"
    b = "husky"
    d4 : dog = dog(a,b)
    a = "black"
    b = "koushik"
    d5 : dog = dog(a,b)
    a = "golden"
    b = "retriever"
    d6 : dog = dog(a,b)
    list_of_dogs : list[dog] = [d1,d2,d3,d4,d5,d6]

    i : int
    temp_dog : dog
    leng : int = len(list_of_dogs)
    print("No of dogs:")
    print(leng)
    for i in range(leng) : 
        temp_dog = list_of_dogs[i]
        temp_dog.which_color()
        temp_dog.which_breed()

if __name__ == "__main__" :
    main()
