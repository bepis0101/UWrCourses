import itertools
con = '∧'
disj = '∨'
neg = '¬'

class Formula:
    def __init__(self, formula):
        pass
    def eval(self, vars):
        pass
    def __str__(self):
        pass
    def __mul__(w1, w2):
        return And(w1, w2)
    def __add__(w1, w2):
        return Or(w1, w2)
    def tautology(self): # checks if formula is tautology
        variables = self.get_variables(set())
        for assignment in itertools.product([True, False], repeat=len(variables)):
            result = self.eval(dict(zip(variables, assignment)))
            if not result:
                return False
        return True
    def get_variables(self, variables):
        if isinstance(self, Var):
            variables.add(self.name)
        elif isinstance(self, Not):
            self.w.get_variables(variables)
        elif isinstance(self, And) or isinstance(self, Or):
            self.l.get_variables(variables)
            self.r.get_variables(variables)
        return variables
        
class And(Formula):
    def __init__(self, w1, w2):
        self.l = w1
        self.r = w2
    def eval(self, vars):
        return self.l.eval(vars) and self.r.eval(vars)
    def __str__(self):
        return f'({str(self.l)} {con} {str(self.r)})'
    def simplify(self):
        if isinstance(self.l, Constant) and self.l.eval({}) == False:
            return Constant(False)
        if isinstance(self.r, Constant) and self.r.eval({}) == False:
            return Constant(False)
        if isinstance(self.l, Constant) and self.l.eval({}) == True:
            return self.r
        if isinstance(self.r, Constant) and self.r.eval({}) == True:
            return self.l
        return self
    
class Or(Formula):
    def __init__(self, w1, w2):
        self.l = w1
        self.r = w2
    def eval(self, vars):
        return self.l.eval(vars) or self.r.eval(vars)
    def __str__(self):
        return f'({str(self.l)} {disj} {str(self.r)})'
    def simplify(self):
        if isinstance(self.l, Constant) and self.l.eval({}) == False:
            return self.r
        if isinstance(self.r, Constant) and self.r.eval({}) == False:
            return self.l
        if isinstance(self.l, Constant) and self.l.eval({}) == True:
            return Constant(True)
        if isinstance(self.r, Constant) and self.r.eval({}) == True:
            return Constant(True)
        return self

class Not(Formula):
    def __init__(self, w):
        self.w = w
    def eval(self, vars):
        return not self.w.eval(vars)
    def __str__(self):
        return f'{neg}{str(self.w)}'

class Var(Formula):
    def __init__(self, name):
        self.name = name
    def eval(self, vars):
        if self.name not in vars:
            raise NotValidVariable(self.name)
        return vars[self.name]
    def __str__(self):
        return self.name

class Constant(Formula):
    def __init__(self, value):
        self.value = value
    def eval(self, vars):
        return self.value
    def __str__(self):
        return str(self.value).lower()

class NotValidVariable(Exception):
    def __init__(self, name):
        self.name = name
    def __str__(self) -> str:
        return f'No declared variable {self.name}'


formula = Or(And(Var('x'), Var('y')), Constant(True)).simplify()
print(formula)
print(formula.tautology())
formula = Or(And(Var('x'), Var('y')), Constant(False)).simplify()
print(formula)
print(formula.tautology())
formula = Or(And(Var('x'), Var('y')), Not(Var('x'))).simplify()
print(formula)
print(formula.eval({'x': True, 'y': False}))
print(formula.tautology())