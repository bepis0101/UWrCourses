/*
Borys Adamiak
Lista 5 - Java
Programowanie Obiektowe
javac Expressions.java     java Program.class
zadania 2 i 4
*/

class Expression
{
    public int evaluate()
    {
        return 0;
    }
    public String toString()
    {
        String s = "";
        return s;
    }
    public int val()
    {
        return 0;
    }
    public Expression derivative()
    {
        return new Expression();
    }
}
class Const extends Expression
{
    int x;
    public Const(int x)
    {
        this.x = x;
    }
    public int val()
    {
        return x;
    }
    public String toString()
    {
        String s = Integer.toString(x);
        return s;
    }
    public Expression derivative()
    {
        return new Const(0);
    }
}
class Var extends Expression
{
    String var;
    int value;
    public Var(String var)
    {
        this.var = var;
        value = 0;
    }
    public void insert(int value)
    {
        this.value = value;
    }
    public int val()
    {
        return value;
    }
    public String toString()
    {
        return var;
    }
    public Expression derivative() 
    {
        return new Const(1);
    }
}
class Add extends Expression
{
    Expression a;
    Expression b;
    public Add(Expression a, Expression b)
    {
        this.a = a;
        this.b = b;
    }
    public int evaluate()
    {
        int x = a.val(), y = b.val();
        return x + y;
    }
    public String toString()
    {
        String s = String.join(" + ", a.toString(), b.toString());
        return s;
    }
    public Expression derivative() 
    {
        return new Add(a.derivative(), b.derivative());
    }
}
class Mult extends Expression
{
    Expression a, b;
    public Mult(Expression a, Expression b)
    {
        this.a = a;
        this.b = b;
    }
    public int evaluate()
    {
        int x = a.val(), y = b.val();
        return x * y;
    }
    public String toString()
    {
        String s = String.join(" * ", a.toString(), b.toString());
        return s;
    }
    public Expression derivative() 
    {
        if(a instanceof Var && b instanceof Var)
        {
            return new Mult(new Const(2), a);
        }
        else if(a instanceof Var && b instanceof Const)
        {
            return b;
        }
        else if(a instanceof Const && b instanceof Var)
        {
            return a;
        }
        else
        {
            return new Const(0);
        }

    }
}

class Program
{
    public static void main(String[] args)
    {
        Var x = new Var("x");
        x.insert(6);
        Expression E = new Add(x, new Const(9));
        System.out.println(E);
        System.out.println(E.evaluate());
        Expression E1 = new Mult(new Const(9), x);
        System.out.println(E1);
        System.out.println(E1.evaluate());
        System.out.println(E1.derivative());
        Expression E2 = new Mult(x, x);
        System.out.println(E2);
        System.out.println(E2.derivative());
    }
}