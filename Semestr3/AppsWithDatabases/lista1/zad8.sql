EXEC sp_helpconstraint 'SalesLT.SalesOrderHeader';

-- to disable the constraint:
ALTER TABLE SalesLT.SalesOrderHeader NOCHECK CONSTRAINT CK_SalesOrderHeader_ShipDate;

INSERT INTO SalesLT.SalesOrderHeader (OrderDate, ShipDate, DueDate, CustomerID, BillToAddressID, ShipToAddressID, Status, SubTotal, TaxAmt, Freight, Comment, ShipMethod)
VALUES ('2021-01-01', '2020-12-31', '2021-05-02', 1, 653, 1092, 1, 1, 1, 1, 'test', 1);
--error if constraint is enabled

-- to enable the constraint:
ALTER TABLE SalesLT.SalesOrderHeader CHECK CONSTRAINT CK_SalesOrderHeader_ShipDate;

SELECT TOP 10 * FROM [SalesLT].[SalesOrderHeader]
DBCC CHECKCONSTRAINTS

DELETE FROM SalesLT.SalesOrderHeader WHERE OrderDate='2021-01-01' AND ShipDate='2020-12-31';

SELECT TOP 10 * FROM [SalesLT].[SalesOrderHeader]
DBCC CHECKCONSTRAINTS



-- to create a new constraint:
-- ALTER TABLE table_name
-- ADD CONSTRAINT constraint_name constraint_definition;