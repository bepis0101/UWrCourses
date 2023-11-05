IF OBJECT_ID('dbo.Test', 'U') IS NOT NULL
    DROP TABLE Test;
CREATE TABLE Test
(
    id int IDENTITY(1000, 10)
)
INSERT Test DEFAULT VALUES;
INSERT Test DEFAULT VALUES;
INSERT Test DEFAULT VALUES;
INSERT Test DEFAULT VALUES;

-- @@IDENTITY - last identity value generated for any table in the current session, across all tables
-- IDENT_CURRENT(name) - last identity value generated for a specific table in any session for a specific table

CREATE TABLE Test2
(
    id int IDENTITY(1, 1)
)
INSERT Test2 DEFAULT VALUES;

SELECT * FROM Test;

SELECT @@IDENTITY;
SELECT IDENT_CURRENT('Test');