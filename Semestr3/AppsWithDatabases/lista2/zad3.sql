DROP PROCEDURE IF EXISTS dbo.addReader;
GO

CREATE PROCEDURE dbo.addReader 
    @pesel VARCHAR(11),
    @lastname VARCHAR(50),
    @city VARCHAR(50),
    @birthdate DATE
AS
BEGIN
    IF @pesel LIKE '[0-9][0-9][0-1][0-9][0-3][0-9][0-9][0-9][0-9][0-9][0-9]'
    BEGIN
        ;THROW 50001, 'Invalid PESEL', 1; 
        RETURN;
    END
    IF @lastname NOT LIKE '[A-Z][A-Za-z]%' COLLATE Latin1_General_CI_AS
    BEGIN
        ;THROW 50002, 'Invalid lastname', 1; 
        RETURN;
    END
    IF @birthdate > GETDATE()
    BEGIN
        ;THROW 50003, 'Invalid birthdate', 1; 
        RETURN;
    END

    INSERT INTO Czytelnik (PESEL, Nazwisko, Miasto, Data_Urodzenia)
    VALUES (@pesel, @lastname, @city, @birthdate);
END
GO

EXEC dbo.addReader '05124111119', 'Kowalski', 'Warszawa', '1990-01-01';
GO
EXEC dbo.addReader '47124111119', 'Adamiak', 'Warszawa', '1950-02-23';
GO

SELECT * FROM Czytelnik;
GO

DELETE FROM Czytelnik
WHERE PESEL = '05124111119';
DELETE FROM Czytelnik
WHERE PESEL = '47124111119';
GO