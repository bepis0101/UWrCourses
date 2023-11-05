DROP TABLE IF EXISTS firstnames;
DROP TABLE IF EXISTS lastnames;
DROP TABLE IF EXISTS fldata;
GO
CREATE TABLE firstnames (
    id INT PRIMARY KEY,
    firstname VARCHAR(50)
);

CREATE TABLE lastnames (
    id INT PRIMARY KEY,
    lastname VARCHAR(50)
);

CREATE TABLE fldata (
    firstname VARCHAR(50),
    lastname VARCHAR(50),
    PRIMARY KEY (firstname, lastname)
);

INSERT INTO firstnames VALUES
    (1, 'John'),
    (2, 'Barrack'),
    (3, 'Jan'),
    (4, 'Marcin'),
    (5, 'Waldemar');

INSERT INTO lastnames VALUES
    (1, 'Smith'),
    (2, 'Obama'),
    (3, 'Kowalski'),
    (4, 'Nowak'),
    (5, 'Kowal');
GO

DROP PROCEDURE IF EXISTS dbo.generateNames;
GO

CREATE PROCEDURE dbo.generateNames @n INT AS
BEGIN
    DECLARE @first INT, @last INT;
    SET @first = (SELECT COUNT(*) FROM firstnames);
    SET @last = (SELECT COUNT(*) FROM lastnames);
    IF @n > @first * @last
    BEGIN
        -- RAISERROR('Too many names requested', 16, 1);
        -- RETURN;
        ;THROW 50000, 'Too many names requested', 1; 
    END

    DELETE FROM fldata;
    INSERT INTO fldata
        SELECT TOP (@n) firstname, lastname
        FROM firstnames, lastnames
        ORDER BY NEWID();
END
GO
-- testing
EXEC dbo.generateNames 10;
SELECT * FROM fldata;
EXEC dbo.generateNames 4;
SELECT * FROM fldata;
EXEC dbo.generateNames 1000;
SELECT * FROM fldata;

    