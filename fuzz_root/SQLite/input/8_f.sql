CREATE TABLE IF NOT EXISTS t1(a int, b, c GENERATED ALWAYS AS (a*abs(b)));
CREATE TABLE t2(e PRIMARY KEY , d, f UNIQUE);
CREATE TABLE t3(z1 PRIMARY KEY, z2, z3) WITHOUT rowid;
CREATE VIRTUAL TABLE t4 USING fts4(c1 INT, c2 VARCHAR, c3 VARCHAR);
CREATE VIRTUAL TABLE intrtree USING rtree_i32(id,x0,x1,y0,y1,z0,z1);
CREATE VIEW v1(c1, c2) as select e, f from t2;
CREATE unique INDEX IF NOT EXISTS i1 on t2(e, f);
CREATE INDEX i2 ON t2(d) where d IS NOT NULL;
CREATE unique index IF NOT EXISTS i3 on t2(e) where d > 1;
INSERT INTO t1 VALUES (3, 4), (2, 0), (4, 6), (-2, 3);
INSERT INTO t2(f, d, e) VALUES (2, 5, 8), (3, 2.0, 4), (0, NULL, 3), (7, -3.2, 2);
INSERT INTO t3 VALUES (3, 'xzr13', 'cf23'), (2, 'sa3423cxz', 'mucity'), (7, 'forx1', 'line2');
INSERT INTO t4 VALUES (3, 'xzr13', 'cf23'), (2, 'sa3423cxz', 'mucity'), (7, 'forx1', 'line2');
INSERT INTO intrtree VALUES(1, -80.7749, -80.7747, 35.3776, 35.3778, 23.1, 34.1), (2, -81.0, -79.6, 35.0, 36.2, -12.23, 89.9);
REINDEX;

SELECT e FROM t2 LEFT JOIN t1 ON a=e WHERE (b=5 AND e=7) OR (e=10 AND a=4);
SELECT DISTINCT b FROM t1 EXCEPT SELECT cast(1=1 as int) UNION SELECT cast('avd'='acd' as int) ORDER BY b;
SELECT * FROM t2 WHERE t2.a > (select AVG(j2) FROM (SELECT cast('avd'='acd' as int) as j2 UNION SELECT b FROM t1 where t2.d EXCEPT SELECT cast(1=1 as int) as j1 ORDER BY j2));
SELECT * FROM v1 WHERE v1.c2>(SELECT AVG(ca5) FROM (SELECT CAST('29'='1995-09-01' AS INT) AS ca5 UNION SELECT b FROM t1 WHERE v1.c2 EXCEPT SELECT CAST(1<UC AS INT) AS ca4 ORDER BY ca4));
SELECT * from (t2, t1 INDEXED by i1 on t1.a = t2.a);
SELECT sum(UC) OVER( ORDER BY UC+UC) FROM (t2,t1 INDEXED BY i1 ON t1.a=t2.a);
SELECT a, cc, (SELECT MAX(z.cc+ j.f) from (select f from t2 where z.a) as j), a in (select d from t2) from (select a, c as cc from t1) as z where cc > (select t2.f from t2 where z.a >= t2.a);
SELECT a,b=count(*),'y' FROM t1 GROUP BY CASE WHEN c NOT IN(3,127,0) THEN '23' ELSE '1995-09-01' END;
SELECT COUNT(id) FILTER (WHERE double_price > 42) OVER() FROM (
  SELECT id, (price * 2) as double_price FROM item
);
SELECT likelihood('PROMO%%', 0.9),EXISTS(SELECT 16 FROM t1 ORDER BY sum(b) OVER()),a FROM t2 LEFT JOIN v1 ON substr(a,-128,-128)='31';
-- SELECT c1/2, c2+255 FROM v1 LEFT JOIN t2 ON UC=UC LEFT JOIN t1 ON c2=c2;
SELECT sum(c) OVER( ORDER BY c2 + c1) FROM UT LEFT JOIN UT ON UC=UC LEFT JOIN UT ON UC=UC + 1;
SELECT likely(e) FROM main.t2 LEFT JOIN t1 ON e>=(SELECT min((SELECT count(z3) FROM t3)) FROM v1) AND f=-128;