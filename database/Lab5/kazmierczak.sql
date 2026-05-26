-- 1)
SELECT customerName, addressLine1, addressLine2, postalCode, city, country
FROM customers
WHERE
    customerNumber = (
        SELECT customerNumber
        FROM orders
        WHERE orderNumber = 10100
    )

-- 2)
SELECT customers.customerName, SUM(payments.amount) AS Suma
FROM payments
JOIN customers ON payments.customerNumber=customers.customerNumber
GROUP BY customers.customerNumber
ORDER BY Suma DESC
LIMIT 10

-- 3)
SELECT *
FROM (
    SELECT customers.customerName, COUNT(*) AS Liczba
    FROM orders
    JOIN customers ON orders.customerNumber=customers.customerNumber
    GROUP BY orders.customerNumber
    ORDER BY Liczba DESC
    LIMIT 5
) AS top5
ORDER BY customerName

-- 4)
SELECT customers.customerName, payments.paymentDate, payments.amount
FROM (
    SELECT customerNumber, paymentDate, amount
    FROM (
        SELECT customerNumber, COUNT(customerNumber) AS Liczba, paymentDate, amount
        FROM payments
        GROUP BY customerNumber
    ) AS query1
    WHERE Liczba = 1
) AS payments
JOIN customers ON payments.customerNumber=customers.customerNumber

-- 5)
SELECT firstName, lastName
FROM employees
UNION ALL
SELECT contactFirstName, contactLastName
FROM customers

-- 6)
SELECT employees.firstName, employees.lastName, employees.jobTitle, offices.country
FROM employees
JOIN offices ON employees.officeCode=offices.officeCode
ORDER BY country

-- 7)
SELECT products.productName, SUM(orderdetails.quantityOrdered)
FROM orderdetails
JOIN products ON orderdetails.productCode=products.productCode
GROUP BY products.productCode

-- 8)
SELECT city, COUNT(*) AS cnt
FROM (
    SELECT city
    FROM customers
    UNION ALL
    SELECT city
    FROM offices
) AS _
GROUP BY city
ORDER BY cnt DESC

-- 9) a
SELECT customers.customerName, employees.firstName, employees.lastName, employees.jobTitle
FROM customers
LEFT JOIN employees ON customers.salesRepEmployeeNumber=employees.employeeNumber

-- 9) b
SELECT customers.customerName, employees.firstName, employees.lastName, employees.jobTitle
FROM customers
RIGHT JOIN employees ON customers.salesRepEmployeeNumber=employees.employeeNumber