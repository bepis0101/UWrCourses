-- IF COL_LENGTH('SalesLT.Customer', 'CreditCardNumber') IS NOT NULL
--     ALTER TABLE SalesLT.Customer DROP COLUMN CreditCardNumber;
-- ALTER TABLE SalesLT.Customer ADD CreditCardNumber VARCHAR(20) NOT NULL DEFAULT '0000-0000-0000-0000';

-- UPDATE TOP(3) SalesLT.SalesOrderHeader
-- SET CreditCardApprovalCode = '123'
-- WHERE CreditCardApprovalCode IS NULL;

-- UPDATE SalesLT.Customer
-- SET CreditCardNumber = 'X'
-- FROM SalesLT.Customer as c JOIN SalesLT.SalesOrderHeader as soh ON c.CustomerID = soh.CustomerID
-- WHERE c.CreditCardNumber is not NULL;

SELECT cus.CustomerID, cus.CreditCardNumber, soh.CreditCardApprovalCode
FROM SalesLT.Customer as cus
LEFT JOIN SalesLT.SalesOrderHeader as soh 
ON cus.CustomerID = soh.CustomerID
WHERE CreditCardApprovalCode IS NOT NULL;