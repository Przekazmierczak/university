-- 1.1a)
SELECT DATE_FORMAT(DATE_ADD(CURDATE(), INTERVAL 120 DAY), '%d-%M-%y-%W')
-- 1.1b)
SELECT DATE_FORMAT(DATE_ADD(MAKEDATE(YEAR(CURDATE()), 1), INTERVAL 204 DAY), '%W')
-- 1.1c)
SELECT DATE_SUB(CURDATE(), INTERVAL 15 WEEK)

-- 1.2a)
SELECT DATE_FORMAT(orderDate, '%Y, %M %d-- %W')
FROM orders
-- 1.2b)
SELECT DATE_FORMAT(orderDate, '%Y, %M %d-- %W')
FROM orders

-- 1.3)
SELECT TIMEDIFF('23:31:10', '12:01:20')

-- 1.4)
SELECT orderNumber, DATE_FORMAT(orderDate, '%W %Y.%M.%d'), status
FROM orders
WHERE DAYNAME(orderDate) = 'Friday'
ORDER BY MONTH(orderDate)

-- 1.5)
SELECT YEAR(orderDate), WEEK(orderDate), COUNT(*)
FROM orders
WHERE WEEK(orderDate, 1) BETWEEN 12 AND 15
GROUP BY YEAR(orderDate), WEEK(orderDate, 1)

-- 1.6)
SELECT customers.customerNumber, customers.customerName, SUM(payments.amount) as kwota
FROM customers
JOIN payments ON customers.customerNumber= payments.customerNumber
WHERE QUARTER(payments.paymentDate) = 4
GROUP BY customers.customerNumber, customers.customerName
ORDER BY kwota DESC
LIMIT 5

-- 1.7)
SELECT orderNumber, orderDate, shippedDate, DATEDIFF(shippedDate, orderDate) AS Dni_do_Wysylki
FROM orders
ORDER BY Dni_do_Wysylki DESC, orderNumber
LIMIT 5

-- 2.1)
SELECT productCode, productName, LENGTH(productName) AS dlugosc_nazwy
FROM products
ORDER BY dlugosc_nazwy DESC
LIMIT 25

-- 2.2)
SELECT REPLACE(productLine, 'a', '<A>')
FROM productlines

-- 2.3)
SELECT productName, productScale, productVendor
FROM products
WHERE productDescription LIKE '%wood%'
ORDER BY productVendor

-- 2.4)
SELECT jobTitle, firstName, lastName, CONCAT(LOWER(LEFT(firstName, 1)), RIGHT(firstName,1), '.', LOWER(lastName), '@motoshop.biz') AS 'Nowy_email'
FROM employees
ORDER BY lastName

-- 2.5)
SELECT productName, SUBSTR(productName, 1, 4) AS rok, SUBSTR(productName, 5, LENGTH(productName)) AS model
FROM products
WHERE productLine = 'Motorcycles'
ORDER BY rok

-- 2.6)
SELECT customerName, country, city, COALESCE(state, 'brak danych') AS stan
FROM customers
ORDER BY country, stan

-- 2.7)
SELECT
    e.officeCode AS 'Kod biura',
    o.city AS 'Miasto',
    e.firstName AS 'Imie sprzedawcy',
    e.lastName AS 'Nazwisko sprzedawcy',
    o.country AS 'Kraj',
    CASE
        WHEN o.territory = 'NA' THEN 'Ameryka Polnocna'
        WHEN o.territory = 'EMEA'THEN 'Europa'
        ELSE 'reszta swiata'
    END AS 'Kod terytorium'
FROM employees e
JOIN offices o ON e.officeCode=o.officeCode
ORDER BY e.officeCode, e.lastName

-- 3.1)
SELECT TRUNCATE(POW(buyPrice,3), 2)
FROM products
WHERE productCode = 'S24_2972'

-- 3.2)
SELECT ROUND(SQRT(SUM(amount)), 4)
FROM payments
WHERE customerNumber = 131

-- 3.3)
SELECT POW(COUNT(*), 1/3)
FROM payments
WHERE customerNumber = 124

-- 3.4)
SELECT DISTINCT o.city
FROM offices o
WHERE EXISTS (
    SELECT 1
    FROM employees e
    WHERE e.officeCode = o.officeCode AND e.jobTitle <> 'Sales Rep'
);

-- 3.5)
SELECT DISTINCT p.productName
FROM products p
WHERE EXISTS (
    SELECT 1
    FROM orderdetails o
    WHERE p.productCode=o.productCode AND o.quantityOrdered >= 90
)

-- 3.6)
SELECT COUNT(*)
FROM (
    SELECT customerNumber
    FROM customers
    WHERE MOD(customerNumber, 2) = 1
) AS _

-- 3.7)
SELECT SUM(ROUND(amount)) - SUM(amount) AS SUM_ROUND
FROM payments