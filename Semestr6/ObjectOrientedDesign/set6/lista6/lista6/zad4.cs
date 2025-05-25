using System;
using System.Linq.Expressions;
using System.Linq;
namespace lista6
{

    public class PrintExpressionVisitor : ExpressionVisitor
    {
        protected override Expression VisitLambda<T>(Expression<T> expression)
        {
            var parameters = string.Join(", ", expression.Parameters.Select(p => p.Name));
            Console.WriteLine("[LAMBDA] {0} -> {1}", parameters, expression.Body);
            return base.VisitLambda(expression);
        }

        protected override Expression VisitConstant(ConstantExpression node)
        {
            Console.WriteLine("[CONST] Wartość: {0}", node.Value);
            return base.VisitConstant(node);
        }

        protected override Expression VisitParameter(ParameterExpression node)
        {
            Console.WriteLine("[PARAM] Nazwa: {0}, Typ: {1}", node.Name, node.Type.Name);
            return base.VisitParameter(node);
        }

    }

}
