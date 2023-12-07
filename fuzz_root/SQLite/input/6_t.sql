CREATE TABLE t0 (c0, c1 AS (1), c2, c3);
CREATE VIRTUAL TABLE vt0 USING fts4(c0);
PRAGMA foreign_keys = true;
PRAGMA fullfsync = true;
PRAGMA fullfsync = false;
CREATE INDEX i0 ON t0(c0) WHERE c0 > 0;
INSERT INTO vt0 VALUES (0), (NULL), (-1);
REPLACE INTO t0(c3, c2, c0) VALUES (0, 0, 0), (NULL, 0, NULL);
INSERT INTO t0(c0, c2, c2) VALUES (0, 8, 10), (-1, 1, 2), (1, 2.2, 3333), (0.0001, 1, 0), (-0, 233, 1.6), ('0', 1, 4), ('-0', 0, 0);
SELECT * FROM t0;
SELECT * FROM t0 NATURAL JOIN vt0;