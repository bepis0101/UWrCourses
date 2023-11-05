SELECT DISTINCT [City]
FROM [SalesLT].[SalesOrderHeader] as soh
LEFT JOIN [SalesLT].[Address] as ad ON soh.[ShipToAddressID] = ad.[AddressID]
WHERE [ShipToAddressID] IS NOT NULL
ORDER BY [City] ASC