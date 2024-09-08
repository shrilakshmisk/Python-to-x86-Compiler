class Node:
    def __init__(self, data : int, color : str) -> None:
        self.data : int = data
        self.color : str= color
        self.parent : Node = None
        self.left : Node = None
        self.right : Node = None

class RedBlackTree:
    def __init__(self) -> None:
        self.root : Node = self.NIL

    def insert(self, data : int) -> None:
        new_node : Node = Node(data)
        new_node.left = self.NIL
        new_node.right = self.NIL

        parent : Node = None
        current : Node = self.root

        while current != self.NIL:
            parent = current
            if new_node.data < current.data:
                current = current.left
            else:
                current = current.right

        new_node.parent = parent

        if parent is None: 
            self.root = new_node
        elif new_node.data < parent.data:
            parent.left = new_node
        else:
            parent.right = new_node

        new_node.color = "red" 
        self.fix_insert(new_node)

    def fix_insert(self, node: Node) -> None:
        while node != self.root and node.parent.color == "red":
            uncle : Node = None
            if node.parent == node.parent.parent.left:
                uncle = node.parent.parent.right
                if uncle.color == "red":  
                    node.parent.color = "black"
                    uncle.color = "black"
                    node.parent.parent.color = "red"
                    node = node.parent.parent
                else:
                    if node == node.parent.right:  
                        node = node.parent
                        self.left_rotate(node)
                    node.parent.color = "black"
                    node.parent.parent.color = "red"
                    self.right_rotate(node.parent.parent)
            else:  
                uncle = node.parent.parent.left
                if uncle.color == "red":
                    node.parent.color = "black"
                    uncle.color = "black"
                    node.parent.parent.color = "red"
                    node = node.parent.parent
                else:
                    if node == node.parent.left:
                        node = node.parent
                        self.right_rotate(node)
                    node.parent.color = "black"
                    node.parent.parent.color = "red"
                    self.left_rotate(node.parent.parent)
        self.root.color = "black"

    def left_rotate(self, x : Node)-> None:
        y : Node= x.right
        x.right = y.left
        if y.left != self.NIL:
            y.left.parent = x
        y.parent = x.parent
        if x.parent is None:
            self.root = y
        elif x == x.parent.left:
            x.parent.left = y
        else:
            x.parent.right = y
        y.left = x
        x.parent = y

    def right_rotate(self, x: Node)-> None:
        y : Node= x.left
        x.left = y.right
        if y.right != self.NIL:
            y.right.parent = x
        y.parent = x.parent
        if x.parent is None:
            self.root = y
        elif x == x.parent.right:
            x.parent.right = y
        else:
            x.parent.left = y
        y.right = x
        x.parent = y

def main() :
    rbt : RedBlackTree = RedBlackTree()
    rbt.insert(7)
    rbt.insert(3)
    rbt.insert(18)
    rbt.insert(10)
    rbt.insert(22)
    rbt.insert(8)
    rbt.insert(11)
    rbt.insert(26)

if __name__ == "__main__":
    main()
