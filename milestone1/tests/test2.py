def custom_operation(a : int,
                     b : int, x : int, y : int ,z : int) -> int:   
    return (x ** 2) + (y | x) * (a-b-x) / (x+y**z+a+b*x*y)

def combine_operations_and_functions(a : int, b : int , c : int , d : int
                                     ,e : int,f : int ,
                                     g :int) -> int:
    result = custom_operation(abs(a - b * c) + custom_operation(a, b ,
                                               custom_operation(a ,b ,c ,d ,e) , custom_operation(a ,b ,c ,d ,e) ** custom_operation(a ,b ,c ,d ,e)),
                                               a+b+c+d*custom_operation(a ,b ,c ,d 
                                                                        ,f)/e/a)
     
    return round(result)

def custom_2_operation(a : int,
                     b : int, x : int, y : int ,z : int) -> int:   
    return (x ** b ** 2) + (y & x) * (a-b-x) / (x**y**z**a*b*x*y)

def main():
    a : int = 8 
    b : int = 2
    c : int = -3
    x : int = 9
    y : int = -10
    z : int = -8
    p : int = -8
    q : int = -10
    d : int = custom_operation(a, b, c, x, y)
    s : int = custom_2_operation(a, b, c, x, y)
    addition : int = a + b
    multiplication_then_subtraction : int = a * b - c
    comb_op : int = (a ** b ** c * x / y + z - c) | c & x ^ a | ~d | x ^ y ^ z & ~a & b

    combined_function_call : int = combine_operations_and_functions(a, b, c)

    print("""Addition: """ )
    print("""Multiplication "then" Subtraction: """ )
    print(comb_op)
    print(d)
    print(s)
    print("""Bitwise OR with 'Exponentiation': """ )
    print(combined_function_call)
    print("""Custom Operation R
        esult: """ )
    print("""Combined Function Cal\
        l Result: """ )

if __name__ == "__main__":
    main()
