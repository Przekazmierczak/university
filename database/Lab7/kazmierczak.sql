-- I 1
DELIMITER //

CREATE FUNCTION firstLastName(customerId INTEGER)
RETURNS VARCHAR(30)
BEGIN
    DECLARE fullName VARCHAR(30);

    SELECT CONCAT(contactFirstName, ' ', contactLastName)
    INTO fullName
    FROM customers
    WHERE customerNumber = customerId;

    return fullName;
END //

DELIMITER ;

SELECT contactFirstName, contactLastName, firstLastName(customerNumber)
FROM customers

-- I 2
DELIMITER //

CREATE FUNCTION limitKredytowy(wartosc FLOAT)
RETURNS VARCHAR(6)
BEGIN
    IF wartosc < 100000 THEN
        RETURN 'maly';
    ELSEIF wartosc >= 200000 THEN
        RETURN 'duzy';
    ELSE
        RETURN 'sredni';
    END IF;
END //

DELIMITER ;

SELECT creditLimit, limitKredytowy(creditLimit)
FROM customers

-- I 4
DELIMITER //

CREATE FUNCTION wskaznik(a DOUBLE, b DOUBLE)
RETURNS DOUBLE
BEGIN
    DECLARE wynik DOUBLE;
    SET wynik = (a + b) * (2 * a + b);
    SET wynik = MOD(wynik, 10);

    IF wynik < 5 THEN
        SET wynik = wynik / 10;
    ELSE
        SET wynik = wynik / 10 + 1;
    END IF;

    RETURN wynik;
END //

DELIMITER ;

-- II 1
DELIMITER //

CREATE PROCEDURE emails()
BEGIN
    SELECT jobTitle, firstName, lastName, CONCAT(LOWER(LEFT(firstName, 1)), RIGHT(firstName,1), '.', LOWER(lastName), '@motoshop.biz') AS 'Nowy_email'
    FROM employees
    ORDER BY lastName;
END //

DELIMITER ;

-- II 2
DELIMITER //

CREATE PROCEDURE emailId(IN id INT)
BEGIN
    SELECT jobTitle, firstName, lastName, CONCAT(LOWER(LEFT(firstName, 1)), RIGHT(firstName,1), '.', LOWER(lastName), '@motoshop.biz') AS 'Nowy_email'
    FROM employees
    WHERE employeeNumber = id;
END //

DELIMITER ;

-- II 3
DELIMITER //

CREATE PROCEDURE countOrders(OUT res INT)
BEGIN
    SELECT COUNT(orderNumber)
    INTO res
    FROM orders;
END //

DELIMITER ;

CALL countOrders(@res);
SELECT @res;

-- II 4
DELIMITER //

CREATE PROCEDURE orderDiff(OUT res INT)
BEGIN
    DECLARE ordersCount INT;
    DECLARE paymentsCount INT;

    SELECT COUNT(*)
    INTO ordersCount
    FROM orders;

    SELECT COUNT(*)
    INTO paymentsCount
    FROM payments;

    SET res = ordersCount - paymentsCount;
END //

DELIMITER ;

CALL orderDiff(@res);
SELECT @res;

-- II 5
DELIMITER //

CREATE PROCEDURE makeOrder(
    IN customerId INT,
    IN productId varchar(15),
    IN quantity INT,
    IN margin FLOAT,
    OUT sellPrice FLOAT
    )
BEGIN
    DECLARE oldPrice FLOAT;
    DECLARE newPrice FLOAT;
    DECLARE oldQuanity INT;
    DECLARE newQuantity INT;
    DECLARE newOrderId INT;
    DECLARE orderProductLine VARCHAR(50);

    SELECT buyPrice, quantityInStock, productLine
    INTO oldPrice, oldQuanity, orderProductLine
    FROM products
    WHERE productCode = productId;

    SET newQuantity = oldQuanity - quantity;

    IF newQuantity >= 0 THEN
        SET newPrice = oldPrice + (oldPrice * margin);

        UPDATE products
        SET quantityInStock = newQuantity
        WHERE productCode = productId;

        SELECT MAX(orderNumber)
        INTO newOrderId
        FROM orders;

        SET newOrderId = newOrderId + 1;

        INSERT INTO orders (
            orderNumber,
            orderDate,
            requiredDate,
            status,
            customerNumber
        )
        VALUES (
            newOrderId,
            CURDATE(),
            DATE_ADD(CURDATE(), INTERVAL 1 WEEK),
            'In process',
            customerId
        );

        INSERT INTO orderdetails (
            orderNumber,
            productCode,
            quantityOrdered,
            priceEach,
            orderLineNumber
        )
        VALUES (
            newOrderId,
            productId,
            quantity,
            newPrice,
            orderProductLine
        );

        SET sellPrice = newPrice * quantity;
    ELSE
        SET sellPrice = 0;
    END IF;

END //

DELIMITER ;

CALL makeOrder(
    103,
    'S10_1949',
    5,
    20,
    @res
    );
SELECT @res;

SELECT *
FROM orders
ORDER BY orderNumber DESC
LIMIT 5;

SELECT *
FROM orderdetails
ORDER BY orderNumber DESC
LIMIT 5;