using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace lista6
{
    public class Context
    {
        private readonly Dictionary<string, bool> variables = [];
        public bool GetValue(string key)
        {
            if(!variables.TryGetValue(key, out bool value))
            {
                throw new InvalidOperationException();
            }
            return value;
        }
        public bool SetValue(string key, bool value)
        {
            variables[key] = value; 
            return true;
        }
    }
    public abstract class AbstractExpression
    {
        public abstract bool Interpret(Context context);
    }

    public class ConstExpression : AbstractExpression
    {
        private readonly bool _value;
        public ConstExpression(bool value)
        {
            _value = value;
        }
        public override bool Interpret(Context context)
        {
            return _value;
        }
    }

    public class UnaryExpression : AbstractExpression
    {
        private readonly string _name;
        public UnaryExpression(string name)
        {
            _name = name;
        }
        public override bool Interpret(Context context)
        {
            return context.GetValue(_name);
        }
    }

    public enum BinaryOperator { And, Or }
    public class BinaryExpression : AbstractExpression
    {
        private readonly AbstractExpression _left;
        private readonly AbstractExpression _right;
        private readonly BinaryOperator _operator;
        public BinaryExpression(AbstractExpression left, AbstractExpression right, BinaryOperator op)
        {
            _left = left;
            _right = right;
            _operator = op;
        }
        public override bool Interpret(Context context)
        {
            var left = _left.Interpret(context);
            var right = _right.Interpret(context);
            return _operator switch
            {
                BinaryOperator.And => left && right,
                BinaryOperator.Or => left || right,
                _ => throw new NotImplementedException()
            };
        }
    }

}
