CREATE TABLE t0(c0);
CREATE TABLE t1(c0, c1 AS(1));
INSERT INTO t0 VALUES(0), (-1), (-0), ('0'), (NULL), (1);
INSERT INTO t1 VALUES(1), ('-0'), (NULL), ('a'), ('-1'), (0);
CREATE INDEX i1 ON t1(c0) WHERE c0 ISNULL;
SELECT t1.c1 = TRUE FROM t0 LEFT JOIN t1 WHERE t1.c0=-0;
SELECT t0.c0, t1.c0 FROM t0 LEFT JOIN t1 ON t1.c0=t0.c0;
SELECT t0.c0, r2.c1 FROM t0 AS r1 JOIN t1 AS r2 ON r1.c0 = r2.c1 JOIN t0;
SELECT * FROM t1 WHERE c0 IS NULL;
DELETE FROM t0 where c0=0;
SELECT * FROM t0 where c0=0 OR c0 IS NULL;