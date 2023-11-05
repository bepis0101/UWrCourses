DROP PROCEDURE IF EXISTS daysBorrowed;
DROP TYPE IF EXISTS dbo.czytelnikID;
GO

CREATE TYPE dbo.czytelnikID as TABLE (
    Czytelnik_ID INT
);
GO

CREATE PROCEDURE daysBorrowed 
    @readerID dbo.czytelnikID READONLY
AS
BEGIN
    SELECT r.Czytelnik_ID, SUM(w.Liczba_Dni) AS SumOfDays
    FROM @readerID AS r RIGHT JOIN Wypozyczenie AS w
    ON r.Czytelnik_ID = w.Czytelnik_ID
    GROUP BY r.Czytelnik_ID
END
GO

DECLARE @readerId dbo.czytelnikID;
INSERT INTO @readerId (Czytelnik_ID)
    SELECT Czytelnik_ID FROM Czytelnik;

EXEC daysBorrowed @readerID = @readerId;
GO
