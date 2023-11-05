SELECT [SalesLT].[Product].[Name], COUNT(Product.ProductModelID) AS Cnt
FROM [SalesLT].[Product]
GROUP BY Name
HAVING COUNT(Product.ProductModelID) > 1
