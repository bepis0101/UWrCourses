DROP PROCEDURE IF EXISTS UpdateProductDate
GO

CREATE PROCEDURE UpdateProductDate
    @ids NVARCHAR(max),
    @date DATE
AS
BEGIN
    DECLARE @message NVARCHAR(max)
    DECLARE @id NVARCHAR(50)
    DECLARE ProductCursor CURSOR FOR
        SELECT value FROM STRING_SPLIT(@ids, ',')
    
    OPEN ProductCursor
    FETCH NEXT FROM ProductCursor INTO @id

    WHILE @@FETCH_STATUS = 0
    BEGIN
        IF EXISTS (SELECT * FROM SalesLT.Product 
                    WHERE ProductID = @id AND DiscontinuedDate IS NULL)
        BEGIN
            UPDATE SalesLT.Product
            SET DiscontinuedDate = @date
            WHERE ProductID = @id
        END
        ELSE
        BEGIN
            SET @Message = CONCAT(@Message, 'Product with id: ', @id, 'already is discounted or doesnt exist.', CHAR(15))
        END

        FETCH NEXT FROM ProductCursor INTO @id
    END
    CLOSE ProductCursor
    DEALLOCATE ProductCursor

    PRINT @Message
END
GO

SET IDENTITY_INSERT SalesLT.Product ON;
GO

INSERT INTO SalesLT.Product (ProductID, DiscontinuedDate, Name, ProductNumber, StandardCost, ListPrice, SellStartDate) VALUES
    (1, NULL, 'Test product 1', '1', 1, 1, '2019-01-01'),
    (2, NULL, 'Test product 2', '2', 1, 1, '2019-01-01'),
    (3, NULL, 'Test product 3', '3', 1, 1, '2019-01-01'),
    (4, '1999-01-01', 'Test product 4', '4', 1, 1, '2019-01-01'),
    (5, NULL, 'Test product 5', '5', 1, 1, '2019-01-01'),
    (6, NULL, 'Test product 6', '6', 1, 1, '2019-01-01'),
    (7, '2010-01-01', 'Test product 7', '7', 1, 1, '2019-01-01'),
    (8, NULL, 'Test product 8', '8', 1, 1, '2019-01-01'),
    (9, '1998-01-01', 'Test product 9', '9', 1, 1, '2019-01-01'),
    (10, NULL, 'Test product 10', '10', 1, 1, '2019-01-01')
GO

SET IDENTITY_INSERT SalesLT.Product OFF;
GO

SELECT ProductID, DiscontinuedDate FROM SalesLT.Product WHERE ProductID < 11
GO

DECLARE @ids NVARCHAR(max) = '1,2,3,4,5,6,7,8,9,10'
EXEC UpdateProductDate @ids = '1,2,3,4,5,6,7,8,9,10', @date = '2023-10-25'
GO

SELECT ProductID, DiscontinuedDate FROM SalesLT.Product WHERE ProductID < 11
GO

DELETE FROM SalesLT.Product WHERE ProductID < 11
GO