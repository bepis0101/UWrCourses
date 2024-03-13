class Tree:
    def __init__(self, val, left=None, right=None):
        self.left = left
        self.right = right
        self.val = val
    
    def height(self):
        if self is None:
            return 0
        if self.left is None and self.right is None:
            return 1
        if self.left is None:
            return 1 + self.right.height()
        if self.right is None:
            return 1 + self.left.height()
        return 1 + max(self.left.height(), self.right.height())
    
    def maks_dist(self):
        if self is None:
            return 0
        if self.left is None and self.right is None:
            return 0
        if self.left is None:
            return self.right.height()
        if self.right is None:
            return self.left.height()
        return self.left.height() + self.right.height()
        


test = Tree(1, Tree(2, Tree(3, Tree(4), Tree(5))))
print(test.maks_dist())