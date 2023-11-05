DROP FUNCTION IF EXISTS dbo.gotOverDeadline
GO;

CREATE FUNCTION dbo.gotOverDeadline(@days INT)
RETURNS TABLE
    RETURN SELECT PESEL, COUNT(*) as cntOfBooks
    FROM ((SELECT DISTINCT Czytelnik_ID FROM Wypozyczenie WHERE Liczba_Dni > @days) AS w
        INNER JOIN Czytelnik ON w.Czytelnik_ID = Czytelnik.Czytelnik_ID) 
        LEFT JOIN Wypozyczenie ON Wypozyczenie.Czytelnik_ID = Czytelnik.Czytelnik_ID
    WHERE w.Czytelnik_ID IS NOT NULL
    GROUP BY PESEL
GO

SELECT * FROM dbo.gotOverDeadline(30)