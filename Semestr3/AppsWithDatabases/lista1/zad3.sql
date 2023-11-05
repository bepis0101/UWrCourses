SELECT City, COUNT(cus.CustomerID), COUNT(DISTINCT SalesPerson)
FROM ([SalesLT].[Customer] AS cus LEFT JOIN [SalesLT].[CustomerAddress] AS cusadd
ON cus.CustomerID = cusadd.CustomerID) LEFT JOIN [SalesLT].[Address] as ad
ON ad.AddressID = cusadd.AddressID
GROUP BY City 