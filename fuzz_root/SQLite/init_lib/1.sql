SELECT * FROM fdt WHERE c1 IN (1, 2, 3);
SELECT * FROM fdt WHERE c1 IN (SELECT c1 FROM t2);
SELECT * FROM fdt WHERE c1 IN (SELECT c3 FROM t2 WHERE c2 = fdt.c1 + 10);
SELECT * FROM fdt WHERE c1 BETWEEN (SELECT c3 FROM t2 WHERE c2 = fdt.c1 + 10) AND 100;
SELECT * FROM fdt WHERE EXISTS (SELECT c1 FROM t2 WHERE c2 > fdt.c1);
SELECT * FROM test1;
SELECT x FROM test1 GROUP BY x;
SELECT x, sum(y) FROM test1 GROUP BY x;
SELECT product_id, p.name, (sum(s.units) * p.price) AS sales FROM products p LEFT JOIN sales s USING (product_id) GROUP BY product_id, p.name, p.price;
SELECT x, sum(y) FROM test1 GROUP BY x HAVING sum(y) > 3;
SELECT x, sum(y) FROM test1 GROUP BY x HAVING x < 'c';
SELECT product_id, p.name, (sum(s.units) * (p.price - p.cost)) AS profit FROM products p LEFT JOIN sales s USING (product_id) WHERE s.datex > CURRENT_DATE - INTERVAL '4 weeks' GROUP BY product_id, p.name, p.price, p.cost HAVING sum(p.price * s.units) > 5000;
SELECT a, b, c FROM t;
SELECT tbl1.a, tbl2.a, tbl1.b FROM t;
SELECT tbl1.*, tbl2.a FROM t;
SELECT a AS value, b + c AS sum FROM t;
SELECT a "value", b + c AS sum FROM t;
SELECT DISTINCT select_list t;
VALUES (1, 'one'), (2, 'two'), (3, 'three');
SELECT 1 AS column1, 'one' AS column2 UNION ALL SELECT 2, 'two' UNION ALL SELECT 3, 'three';
SELECT CNTRYCODE, COUNT(*) AS NUMCUST, SUM(C_ACCTBAL) AS TOTACCTBAL FROM (SELECT SUBSTRING(C_PHONE,1,2) AS CNTRYCODE, C_ACCTBAL  FROM CUSTOMER WHERE SUBSTRING(C_PHONE,1,2) IN ('13', '31', '23', '29', '30', '18', '17') AND  C_ACCTBAL > (SELECT AVG(C_ACCTBAL) FROM CUSTOMER WHERE C_ACCTBAL > 0.00 AND   SUBSTRING(C_PHONE,1,2) IN ('13', '31', '23', '29', '30', '18', '17')) AND  NOT EXISTS ( SELECT * FROM ORDERS WHERE O_CUSTKEY = C_CUSTKEY)) AS CUSTSALE GROUP BY CNTRYCODE ORDER BY CNTRYCODE;
SELECT * FROM orders;
SELECT a FROM foo WHERE a > 12 OR b > 3 AND NOT c LIMIT 10;
SELECT a FROM some_schema.foo WHERE a > 12 OR b > 3 AND NOT c LIMIT 10;
SELECT col1 AS myname, col2, 'test' FROM "table", foo AS t WHERE age > 12 AND zipcode = 12345 GROUP BY col1;
SELECT * from "table" JOIN table2 ON a = b WHERE (b OR NOT a) AND a = 12.5
(SELECT a FROM foo WHERE a > 12 OR b > 3 AND c NOT LIKE 's%' LIMIT 10);
SELECT * FROM "table" LIMIT 10 OFFSET 10; SELECT * FROM another;
SELECT * FROM t1 UNION SELECT * FROM t2 ORDER BY col1;
SELECT * FROM (SELECT * FROM t1);
SELECT * FROM t1 UNION (SELECT * FROM t2 UNION SELECT * FROM t3) ORDER BY col1;
SELECT * FROM t1 ORDER BY col1, col2;
SELECT a, MAX(b), MAX(c, d), CUSTOM(q, UP(r)) AS f FROM t1;
SELECT * FROM t WHERE a BETWEEN 1 and c;
SELECT * FROM t WHERE a = 1 AND b = 1.2;
SELECT City.name, Product.category, SUM(price) FROM fact INNER JOIN City ON fact.city_id = City.id INNER JOIN Product ON fact.product_id = Product.id GROUP BY City.name, Product.category;
SELECT SUBSTR(a, 3, 5) FROM t;
SELECT t1.a, t1.b, t2.c FROM "table" AS t1 JOIN (SELECT * FROM foo JOIN bar ON foo.id = bar.id) t2 ON t1.a = t2.b WHERE (t1.b OR NOT t1.a) AND t2.c = 12.5
SELECT * FROM t1 JOIN t2 ON c1 = c2;
SELECT a, SUM(b) FROM t2 GROUP BY a HAVING SUM(b) > 100;
CREATE TABLE "table" FROM TBL FILE 'students.tbl'
CREATE TABLE IF NOT EXISTS "table" FROM TBL FILE 'students.tbl'
CREATE TABLE students (name TEXT, student_number INTEGER, city TEXT, grade DOUBLE)
CREATE TABLE teachers (name VARCHAR(30), student_number LONG, city CHAR(10), grade FLOAT)
CREATE TABLE students_2 AS SELECT * FROM students
CREATE TABLE students_3 AS SELECT city, grade FROM students WHERE grade > 3.0
CREATE TABLE "table" FROM TBL FILE 'students.tbl'; SELECT * FROM "table";
TRUNCATE students;
UPDATE students SET grade = 1.3 WHERE name = 'Max Mustermann';
UPDATE students SET grade = 1.3, name='Felix Fürstenberg' WHERE name = 'Max Mustermann';
UPDATE students SET grade = 1.0;
UPDATE some_schema.students SET grade = 1.0;
DROP TABLE students;
DROP TABLE IF EXISTS students;
DROP VIEW IF EXISTS students;
PREPARE prep_inst FROM '!INSERT INTO test VALUES (1, 'a', 1.2)';
PREPARE prep2 FROM '!INSERT INTO test VALUES (1, 0, 0); !INSERT INTO test VALUES (0, 1, 0); !INSERT INTO test VALUES (0, 0, null);';
EXECUTE prep_inst(1, 2, 3);
EXECUTE prep;
DEALLOCATE PREPARE prep;
SELECT * FROM test WITH HINT(NO_CACHE);
SELECT * FROM test WITH HINT(NO_CACHE, NO_SAMPLING);
SELECT * FROM test WITH HINT(NO_CACHE, SAMPLE_RATE(0.1), OMW(1.0, 'test'));
SHOW TABLES;
SHOW COLUMNS students;
DESCRIBE students;
SELECT L_RETURNFLAG, L_LINESTATUS, SUM(L_QUANTITY) AS SUM_QTY,  SUM(L_EXTENDEDPRICE) AS SUM_BASE_PRICE, SUM(L_EXTENDEDPRICE*(1-L_DISCOUNT)) AS SUM_DISC_PRICE,  SUM(L_EXTENDEDPRICE*(1-L_DISCOUNT)*(1+L_TAX)) AS SUM_CHARGE, AVG(L_QUANTITY) AS AVG_QTY,  AVG(L_EXTENDEDPRICE) AS AVG_PRICE, AVG(L_DISCOUNT) AS AVG_DISC, COUNT(*) AS COUNT_ORDER FROM LINEITEM WHERE L_SHIPDATE <= dateadd(dd, -90, cast('1998-12-01' as datetime)) GROUP BY L_RETURNFLAG, L_LINESTATUS ORDER BY L_RETURNFLAG,L_LINESTATUS;
SELECT S_ACCTBAL, S_NAME, N_NAME, P_PARTKEY, P_MFGR, S_ADDRESS, S_PHONE, S_COMMENT FROM PART, SUPPLIER, PARTSUPP, NATION, REGION WHERE P_PARTKEY = PS_PARTKEY AND S_SUPPKEY = PS_SUPPKEY AND P_SIZE = 15 AND P_TYPE LIKE '%%BRASS' AND S_NATIONKEY = N_NATIONKEY AND N_REGIONKEY = R_REGIONKEY AND R_NAME = 'EUROPE' AND PS_SUPPLYCOST = (SELECT MIN(PS_SUPPLYCOST) FROM PARTSUPP, SUPPLIER, NATION, REGION  WHERE P_PARTKEY = PS_PARTKEY AND S_SUPPKEY = PS_SUPPKEY  AND S_NATIONKEY = N_NATIONKEY AND N_REGIONKEY = R_REGIONKEY AND R_NAME = 'EUROPE') ORDER BY S_ACCTBAL DESC, N_NAME, S_NAME, P_PARTKEY;
SELECT L_ORDERKEY, SUM(L_EXTENDEDPRICE*(1-L_DISCOUNT)) AS REVENUE, O_ORDERDATE, O_SHIPPRIORITY FROM CUSTOMER, ORDERS, LINEITEM WHERE C_MKTSEGMENT = 'BUILDING' AND C_CUSTKEY = O_CUSTKEY AND L_ORDERKEY = O_ORDERKEY AND O_ORDERDATE < '1995-03-15' AND L_SHIPDATE > '1995-03-15' GROUP BY L_ORDERKEY, O_ORDERDATE, O_SHIPPRIORITY ORDER BY REVENUE DESC, O_ORDERDATE;
SELECT O_ORDERPRIORITY, COUNT(*) AS ORDER_COUNT FROM ORDERS WHERE O_ORDERDATE >= '1993-07-01' AND O_ORDERDATE < dateadd(mm,3, cast('1993-07-01' as datetime)) AND EXISTS (SELECT * FROM LINEITEM WHERE L_ORDERKEY = O_ORDERKEY AND L_COMMITDATE < L_RECEIPTDATE) GROUP BY O_ORDERPRIORITY ORDER BY O_ORDERPRIORITY;
SELECT N_NAME, SUM(L_EXTENDEDPRICE*(1-L_DISCOUNT)) AS REVENUE FROM CUSTOMER, ORDERS, LINEITEM, SUPPLIER, NATION, REGION WHERE C_CUSTKEY = O_CUSTKEY AND L_ORDERKEY = O_ORDERKEY AND L_SUPPKEY = S_SUPPKEY AND C_NATIONKEY = S_NATIONKEY AND S_NATIONKEY = N_NATIONKEY AND N_REGIONKEY = R_REGIONKEY AND R_NAME = 'ASIA' AND O_ORDERDATE >= '1994-01-01' AND O_ORDERDATE < DATEADD(YY, 1, cast('1994-01-01' as datetime)) GROUP BY N_NAME ORDER BY REVENUE DESC;
SELECT SUM(L_EXTENDEDPRICE*L_DISCOUNT) AS REVENUE FROM LINEITEM WHERE L_SHIPDATE >= '1994-01-01' AND L_SHIPDATE < dateadd(yy, 1, cast('1994-01-01' as datetime)) AND L_DISCOUNT BETWEEN .06 - 0.01 AND .06 + 0.01 AND L_QUANTITY < 24;
SELECT SUPP_NATION, CUST_NATION, L_YEAR, SUM(VOLUME) AS REVENUE FROM ( SELECT N1.N_NAME AS SUPP_NATION, N2.N_NAME AS CUST_NATION, datepart(yy, L_SHIPDATE) AS L_YEAR,  L_EXTENDEDPRICE*(1-L_DISCOUNT) AS VOLUME  FROM SUPPLIER, LINEITEM, ORDERS, CUSTOMER, NATION N1, NATION N2  WHERE S_SUPPKEY = L_SUPPKEY AND O_ORDERKEY = L_ORDERKEY AND C_CUSTKEY = O_CUSTKEY  AND S_NATIONKEY = N1.N_NATIONKEY AND C_NATIONKEY = N2.N_NATIONKEY AND  ((N1.N_NAME = 'FRANCE' AND N2.N_NAME = 'GERMANY') OR  (N1.N_NAME = 'GERMANY' AND N2.N_NAME = 'FRANCE')) AND  L_SHIPDATE BETWEEN '1995-01-01' AND '1996-12-31' ) AS SHIPPING GROUP BY SUPP_NATION, CUST_NATION, L_YEAR ORDER BY SUPP_NATION, CUST_NATION, L_YEAR;
SELECT O_YEAR, SUM(CASE WHEN NATION = 'BRAZIL' THEN VOLUME ELSE 0 END)/SUM(VOLUME) AS MKT_SHARE FROM (SELECT datepart(yy,O_ORDERDATE) AS O_YEAR, L_EXTENDEDPRICE*(1-L_DISCOUNT) AS VOLUME, N2.N_NAME AS NATION  FROM "PART", SUPPLIER, LINEITEM, ORDERS, CUSTOMER, NATION N1, NATION N2, REGION  WHERE P_PARTKEY = L_PARTKEY AND S_SUPPKEY = L_SUPPKEY AND L_ORDERKEY = O_ORDERKEY  AND O_CUSTKEY = C_CUSTKEY AND C_NATIONKEY = N1.N_NATIONKEY AND  N1.N_REGIONKEY = R_REGIONKEY AND R_NAME = 'AMERICA' AND S_NATIONKEY = N2.N_NATIONKEY  AND O_ORDERDATE BETWEEN '1995-01-01' AND '1996-12-31' AND P_TYPE= 'ECONOMY ANODIZED STEEL') AS ALL_NATIONS GROUP BY O_YEAR ORDER BY O_YEAR;
SELECT NATION, O_YEAR, SUM(AMOUNT) AS SUM_PROFIT FROM (SELECT N_NAME AS NATION, datepart(yy, O_ORDERDATE) AS O_YEAR,  L_EXTENDEDPRICE*(1-L_DISCOUNT)-PS_SUPPLYCOST*L_QUANTITY AS AMOUNT  FROM "PART", SUPPLIER, LINEITEM, PARTSUPP, ORDERS, NATION  WHERE S_SUPPKEY = L_SUPPKEY AND PS_SUPPKEY= L_SUPPKEY AND PS_PARTKEY = L_PARTKEY AND  P_PARTKEY= L_PARTKEY AND O_ORDERKEY = L_ORDERKEY AND S_NATIONKEY = N_NATIONKEY AND  P_NAME LIKE '%%green%%') AS PROFIT GROUP BY NATION, O_YEAR ORDER BY NATION, O_YEAR DESC
SELECT C_CUSTKEY, C_NAME, SUM(L_EXTENDEDPRICE*(1-L_DISCOUNT)) AS REVENUE, C_ACCTBAL, N_NAME, C_ADDRESS, C_PHONE, C_COMMENT FROM CUSTOMER, ORDERS, LINEITEM, NATION WHERE C_CUSTKEY = O_CUSTKEY AND L_ORDERKEY = O_ORDERKEY AND O_ORDERDATE>= '1993-10-01' AND O_ORDERDATE < dateadd(mm, 3, cast('1993-10-01' as datetime)) AND L_RETURNFLAG = 'R' AND C_NATIONKEY = N_NATIONKEY GROUP BY C_CUSTKEY, C_NAME, C_ACCTBAL, C_PHONE, N_NAME, C_ADDRESS, C_COMMENT ORDER BY REVENUE DESC;
SELECT PS_PARTKEY, SUM(PS_SUPPLYCOST*PS_AVAILQTY) AS VALUE FROM PARTSUPP, SUPPLIER, NATION WHERE PS_SUPPKEY = S_SUPPKEY AND S_NATIONKEY = N_NATIONKEY AND N_NAME = 'GERMANY' GROUP BY PS_PARTKEY HAVING SUM(PS_SUPPLYCOST*PS_AVAILQTY) > (SELECT SUM(PS_SUPPLYCOST*PS_AVAILQTY) * 0.0001000000  FROM PARTSUPP, SUPPLIER, NATION  WHERE PS_SUPPKEY = S_SUPPKEY AND S_NATIONKEY = N_NATIONKEY AND N_NAME = 'GERMANY') ORDER BY VALUE DESC;
SELECT L_SHIPMODE, SUM(CASE WHEN O_ORDERPRIORITY = '1-URGENT' OR O_ORDERPRIORITY = '2-HIGH' THEN 1 ELSE 0 END) AS HIGH_LINE_COUNT, SUM(CASE WHEN O_ORDERPRIORITY <> '1-URGENT' AND O_ORDERPRIORITY <> '2-HIGH' THEN 1 ELSE 0 END ) AS LOW_LINE_COUNT FROM ORDERS, LINEITEM WHERE O_ORDERKEY = L_ORDERKEY AND L_SHIPMODE IN ('MAIL','SHIP') AND L_COMMITDATE < L_RECEIPTDATE AND L_SHIPDATE < L_COMMITDATE AND L_RECEIPTDATE >= '1994-01-01' AND L_RECEIPTDATE < dateadd(mm, 1, cast('1995-09-01' as datetime)) GROUP BY L_SHIPMODE ORDER BY L_SHIPMODE;
SELECT C_COUNT, COUNT(*) AS CUSTDIST FROM (SELECT C_CUSTKEY, COUNT(O_ORDERKEY)  FROM CUSTOMER left outer join ORDERS on C_CUSTKEY = O_CUSTKEY  AND O_COMMENT not like '%%special%%requests%%'  GROUP BY C_CUSTKEY) AS C_ORDERS (C_CUSTKEY, C_COUNT) GROUP BY C_COUNT ORDER BY CUSTDIST DESC, C_COUNT DESC;
SELECT 100.00* SUM(CASE WHEN P_TYPE LIKE 'PROMO%%' THEN L_EXTENDEDPRICE*(1-L_DISCOUNT) ELSE 0 END) / SUM(L_EXTENDEDPRICE*(1-L_DISCOUNT)) AS PROMO_REVENUE FROM LINEITEM, PART WHERE L_PARTKEY = P_PARTKEY AND L_SHIPDATE >= '1995-09-01' AND L_SHIPDATE < dateadd(mm, 1, '1995-09-01');
CREATE VIEW REVENUE0 (SUPPLIER_NO, TOTAL_REVENUE) AS SELECT L_SUPPKEY, SUM(L_EXTENDEDPRICE*(1-L_DISCOUNT)) FROM LINEITEM WHERE L_SHIPDATE >= '1996-01-01' AND L_SHIPDATE < dateadd(mm, 3, cast('1996-01-01' as datetime)) GROUP BY L_SUPPKEY;
SELECT S_SUPPKEY, S_NAME, S_ADDRESS, S_PHONE, TOTAL_REVENUE FROM SUPPLIER, REVENUE0 WHERE S_SUPPKEY = SUPPLIER_NO AND TOTAL_REVENUE = (SELECT MAX(TOTAL_REVENUE) FROM REVENUE0) ORDER BY S_SUPPKEY;
DROP VIEW REVENUE0;
SELECT SUM(L_EXTENDEDPRICE)/7.0 AS AVG_YEARLY FROM LINEITEM, "PART" WHERE P_PARTKEY = L_PARTKEY AND P_BRAND = 'Brand#23' AND P_CONTAINER = 'MED BOX' AND L_QUANTITY < (SELECT 0.2*AVG(L_QUANTITY) FROM LINEITEM WHERE L_PARTKEY = P_PARTKEY);
SELECT C_NAME, C_CUSTKEY, O_ORDERKEY, O_ORDERDATE, O_TOTALPRICE, SUM(L_QUANTITY) FROM CUSTOMER, ORDERS, LINEITEM WHERE O_ORDERKEY IN (SELECT L_ORDERKEY FROM LINEITEM GROUP BY L_ORDERKEY HAVING  SUM(L_QUANTITY) > 300) AND C_CUSTKEY = O_CUSTKEY AND O_ORDERKEY = L_ORDERKEY GROUP BY C_NAME, C_CUSTKEY, O_ORDERKEY, O_ORDERDATE, O_TOTALPRICE ORDER BY O_TOTALPRICE DESC, O_ORDERDATE;
SELECT SUM(L_EXTENDEDPRICE* (1 - L_DISCOUNT)) AS REVENUE FROM LINEITEM, "PART" WHERE (P_PARTKEY = L_PARTKEY AND P_BRAND = 'Brand#12' AND P_CONTAINER IN ('SM CASE', 'SM BOX', 'SM PACK', 'SM PKG') AND L_QUANTITY >= 1 AND L_QUANTITY <= 1 + 10 AND P_SIZE BETWEEN 1 AND 5 AND L_SHIPMODE IN ('AIR', 'AIR REG') AND L_SHIPINSTRUCT = 'DELIVER IN PERSON') OR (P_PARTKEY = L_PARTKEY AND P_BRAND ='Brand#23' AND P_CONTAINER IN ('MED BAG', 'MED BOX', 'MED PKG', 'MED PACK') AND L_QUANTITY >=10 AND L_QUANTITY <=10 + 10 AND P_SIZE BETWEEN 1 AND 10 AND L_SHIPMODE IN ('AIR', 'AIR REG') AND L_SHIPINSTRUCT = 'DELIVER IN PERSON') OR (P_PARTKEY = L_PARTKEY AND P_BRAND = 'Brand#34' AND P_CONTAINER IN ( 'LG CASE', 'LG BOX', 'LG PACK', 'LG PKG') AND L_QUANTITY >=20 AND L_QUANTITY <= 20 + 10 AND P_SIZE BETWEEN 1 AND 15 AND L_SHIPMODE IN ('AIR', 'AIR REG') AND L_SHIPINSTRUCT = 'DELIVER IN PERSON');
SELECT S_NAME, S_ADDRESS FROM SUPPLIER, NATION WHERE S_SUPPKEY IN (SELECT PS_SUPPKEY FROM PARTSUPP  WHERE PS_PARTKEY in (SELECT P_PARTKEY FROM "PART" WHERE P_NAME like 'forest%%') AND  PS_AVAILQTY > (SELECT 0.5*sum(L_QUANTITY) FROM LINEITEM WHERE L_PARTKEY = PS_PARTKEY AND   L_SUPPKEY = PS_SUPPKEY AND L_SHIPDATE >= '1994-01-01' AND   L_SHIPDATE < dateadd(yy,1,'1994-01-01'))) AND S_NATIONKEY = N_NATIONKEY AND N_NAME = 'CANADA' ORDER BY S_NAME;
SELECT S_NAME, COUNT(*) AS NUMWAIT FROM SUPPLIER, LINEITEM L1, ORDERS, NATION WHERE S_SUPPKEY = L1.L_SUPPKEY AND O_ORDERKEY = L1.L_ORDERKEY AND O_ORDERSTATUS = 'F' AND L1.L_RECEIPTDATE> L1.L_COMMITDATE AND EXISTS (SELECT * FROM LINEITEM L2 WHERE L2.L_ORDERKEY = L1.L_ORDERKEY  AND L2.L_SUPPKEY <> L1.L_SUPPKEY) AND NOT EXISTS (SELECT * FROM LINEITEM L3 WHERE L3.L_ORDERKEY = L1.L_ORDERKEY AND  L3.L_SUPPKEY <> L1.L_SUPPKEY AND L3.L_RECEIPTDATE > L3.L_COMMITDATE) AND S_NATIONKEY = N_NATIONKEY AND N_NAME = 'SAUDI ARABIA' GROUP BY S_NAME ORDER BY NUMWAIT DESC, S_NAME;
SELECT CNTRYCODE, COUNT(*) AS NUMCUST, SUM(C_ACCTBAL) AS TOTACCTBAL FROM (SELECT SUBSTRING(C_PHONE,1,2) AS CNTRYCODE, C_ACCTBAL  FROM CUSTOMER WHERE SUBSTRING(C_PHONE,1,2) IN ('13', '31', '23', '29', '30', '18', '17') AND  C_ACCTBAL > (SELECT AVG(C_ACCTBAL) FROM CUSTOMER WHERE C_ACCTBAL > 0.00 AND   SUBSTRING(C_PHONE,1,2) IN ('13', '31', '23', '29', '30', '18', '17')) AND  NOT EXISTS ( SELECT * FROM ORDERS WHERE O_CUSTKEY = C_CUSTKEY)) AS CUSTSALE GROUP BY CNTRYCODE ORDER BY CNTRYCODE;
SELECT DISTINCT zipfile (v1, v1, v1, v2) FROM v0; 