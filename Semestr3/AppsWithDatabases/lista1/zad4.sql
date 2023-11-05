-- INSERT INTO SalesLT.ProductCategory (Name, ParentProductCategoryID) VALUES ('bike', 5)
-- INSERT INTO SalesLT.Product (Name, ProductCategoryID, ProductNumber, StandardCost, ListPrice, SellStartDate)
-- VALUES ('bike1', 42, 'bk-001', 100, 200, '2016-01-01')

SELECT prod.Name, cat.Name
FROM SalesLT.Product as prod LEFT JOIN SalesLT.ProductCategory as cat
ON prod.ProductCategoryID = cat.ProductCategoryID
WHERE cat.ProductCategoryID IN (SELECT ParentProductCategoryID FROM SalesLT.ProductCategory)