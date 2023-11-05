SELECT FirstName, LastName, ROUND(SUM(UnitPriceDiscount*UnitPrice*OrderQty), 2) as DiscountSum
FROM ([SalesLT].[Customer] AS cus LEFT JOIN [SalesLT].[SalesOrderHeader] AS soh
ON cus.CustomerID = soh.CustomerID) RIGHT JOIN [SalesLT].[SalesOrderDetail] AS sod
ON soh.SalesOrderID = sod.SalesOrderID
GROUP BY FirstName, LastName
ORDER BY DiscountSum DESC