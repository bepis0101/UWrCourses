SELECT 
    soh.SalesOrderID, 
    soh.SalesOrderNumber, 
    soh.PurchaseOrderNumber,
    SUM(sod.LineTotal) as PriceWithDiscount,
    SUM(sod.LineTotal/(1-sod.UnitPriceDiscount)) as PriceWithoutDiscount,
    SUM(sod.OrderQty)
FROM ([SalesLT].[SalesOrderHeader] AS soh LEFT JOIN [SalesLT].[SalesOrderDetail] AS sod
ON soh.SalesOrderID = sod.SalesOrderID)
GROUP BY soh.SalesOrderID, soh.SalesOrderNumber, soh.PurchaseOrderNumber