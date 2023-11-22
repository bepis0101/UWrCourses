DROP TRIGGER IF EXISTS SalesLT.UpdateModifiedDate
GO

CREATE TRIGGER UpdateModifiedDate
ON SalesLT.Customer
AFTER UPDATE
AS
BEGIN
    UPDATE SalesLT.Customer
    SET ModifiedDate = GETDATE()
    FROM inserted
END
GO

-- TEST:
INSERT INTO SalesLT.Customer (FirstName, LastName, CompanyName, Phone, PasswordHash, PasswordSalt) 
    VALUES ('Barry', 'Werter', 'workworkwork', '123456789', 'hash', 'salt');

SELECT FirstName, ModifiedDate FROM SalesLT.Customer
WHERE LastName = 'Werter' AND Phone = '123456789';
GO

WAITFOR DELAY '00:00:01';
GO

UPDATE SalesLT.Customer
SET FirstName = 'Allan'
WHERE LastName = 'Werter' AND Phone = '123456789';

SELECT FirstName, ModifiedDate FROM SalesLT.Customer
WHERE LastName = 'Werter' AND Phone = '123456789';

DELETE FROM SalesLT.Customer
WHERE LastName = 'Werter' AND Phone = '123456789';
GO