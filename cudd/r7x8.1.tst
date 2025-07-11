# TestCudd Version #1.0, Release date 3/17/01
# cudd/testcudd -p 2 ./cudd/r7x8.1.mat
:name: ./cudd/r7x8.1.mat: 7 rows 9 columns
:1: M: 63 nodes 5 leaves 52 minterms
000000--  1
000001-0  1
000001-1  4
000010-0  4
000010-1  3
000011-0  2
000011-1  4
000100--  3
000101-0  3
000110-0  1
000110-1  2
000111-0  4
001000--  1
001001-0  4
001010-0  2
001010-1  1
001011-1  4
001100-0  2
001100-1  3
001101-0  3
001110-0  4
001110-1  1
0100-0-0  3
011000-0  3
011010-0  1
100000-0  2
100000-1  3
100001-0  2
100001-1  4
100010--  3
100011--  4
100100--  1
100101-0  2
100110-0  1
100110-1  3
100111-0  3
101000-1  1
101001-0  1
101001-1  4
101100-0  2
101100-1  4
101101-0  4
110000-0  2
110010-0  4
111000-0  2

:2: time to read the matrix = 0.00 sec
:3: C: 22 nodes 1 leaves 52 minterms
0000----  1
0001-0--  1
0001-1-0  1
001000--  1
001001-0  1
001010--  1
001011-1  1
001100--  1
001101-0  1
001110--  1
01-0-0-0  1
1000----  1
1001-0--  1
1001-1-0  1
101000-1  1
101001--  1
101100--  1
101101-0  1
1100-0-0  1
111000-0  1

Testing iterator on cubes:
000000-- 1
000001-0 1
000001-1 4
000010-0 4
000010-1 3
000011-0 2
000011-1 4
000100-- 3
000101-0 3
000110-0 1
000110-1 2
000111-0 4
001000-- 1
001001-0 4
001010-0 2
001010-1 1
001011-1 4
001100-0 2
001100-1 3
001101-0 3
001110-0 4
001110-1 1
0100-0-0 3
011000-0 3
011010-0 1
100000-0 2
100000-1 3
100001-0 2
100001-1 4
100010-- 3
100011-- 4
100100-- 1
100101-0 2
100110-0 1
100110-1 3
100111-0 3
101000-1 1
101001-0 1
101001-1 4
101100-0 2
101100-1 4
101101-0 4
110000-0 2
110010-0 4
111000-0 2

Testing prime expansion of cubes:
-000---- 1
-00--0-- 1
0--0-0-0 1
--00-0-0 1
-0-100-- 1
10-001-- 1
-00----0 1
00---0-- 1
-1-000-0 1
-0--01-0 1
-0--00-1 1
00-01--1 1

Testing iterator on primes (CNF):
-0-0---- 1
-0---0-- 1
0-0-0--- 1
-0-----0 1
---0-0-0 1
0101-1-1 1
--0-00-1 1
1-0-10-0 1

xor1: 14 nodes 1 leaves 28 minterms
000--1-1  1
001-11-1  1
01---0-0  1
100--1-1  1
101-00-0  1
101-01-1  1
110--0-0  1
111-00-0  1

Chosen minterm for Hamming distance test: : 9 nodes 1 leaves 1 minterms
11110010  1

Minimum Hamming distance = 1
ycube: 5 nodes 1 leaves 8 minterms
-0-0-0-0  1

CP: 11 nodes 1 leaves 7 minterms
00-0-0-0  1
1000-0-0  1
101000-1  1

:4: ineq: 10 nodes 1 leaves 42 minterms
001000--  1
00101---  1
1000----  1
100100--  1
10011---  1
101-----  1
111000--  1
11101---  1

10------ 1
-01----- 1
1-1----- 1
-0-0---- 1
1--0---- 1
-0--10-- 1
--1010-- 1
1---10-- 1

:4: ess: 1 nodes 1 leaves 128 minterms
--------  1

:5: shortP: 7 nodes 1 leaves 2 minterms
000000--  1

:5b: largest: 4 nodes 1 leaves 16 minterms
01-1----  1

The value of M along the chosen shortest path is 1
:6: shortP: 5 nodes 1 leaves 8 minterms
0000----  1

Support of f: : 8 nodes 1 leaves 2 minterms
111111-1  1

Size of the support of f: 7
Size of the support of f: 7
Support of f and g: : 8 nodes 1 leaves 2 minterms
111111-1  1

Size of the support of f and g: 7
Size of the support of f and g: 7
Support common to f and g: : 5 nodes 1 leaves 16 minterms
-1-1-1-1  1

Support private to f: : 4 nodes 1 leaves 32 minterms
1-1-1---  1

Support private to g: : 1 nodes 1 leaves 256 minterms
--------  1

Average distance: 8240.18
Number of variables =      8	Number of slots     =   2304
Number of keys      =    999	Number of min dead  =   9216
walsh1: 16 nodes 2 leaves 256 minterms
-0--0--0--0-  1
-0--0--0--10  1
-0--0--0--11 -1
-0--0--10-0-  1
-0--0--10-10  1
-0--0--10-11 -1
-0--0--11-0- -1
-0--0--11-10 -1
-0--0--11-11  1
-0--10-0--0-  1
-0--10-0--10  1
-0--10-0--11 -1
-0--10-10-0-  1
-0--10-10-10  1
-0--10-10-11 -1
-0--10-11-0- -1
-0--10-11-10 -1
-0--10-11-11  1
-0--11-0--0- -1
-0--11-0--10 -1
-0--11-0--11  1
-0--11-10-0- -1
-0--11-10-10 -1
-0--11-10-11  1
-0--11-11-0-  1
-0--11-11-10  1
-0--11-11-11 -1
-10-0--0--0-  1
-10-0--0--10  1
-10-0--0--11 -1
-10-0--10-0-  1
-10-0--10-10  1
-10-0--10-11 -1
-10-0--11-0- -1
-10-0--11-10 -1
-10-0--11-11  1
-10-10-0--0-  1
-10-10-0--10  1
-10-10-0--11 -1
-10-10-10-0-  1
-10-10-10-10  1
-10-10-10-11 -1
-10-10-11-0- -1
-10-10-11-10 -1
-10-10-11-11  1
-10-11-0--0- -1
-10-11-0--10 -1
-10-11-0--11  1
-10-11-10-0- -1
-10-11-10-10 -1
-10-11-10-11  1
-10-11-11-0-  1
-10-11-11-10  1
-10-11-11-11 -1
-11-0--0--0- -1
-11-0--0--10 -1
-11-0--0--11  1
-11-0--10-0- -1
-11-0--10-10 -1
-11-0--10-11  1
-11-0--11-0-  1
-11-0--11-10  1
-11-0--11-11 -1
-11-10-0--0- -1
-11-10-0--10 -1
-11-10-0--11  1
-11-10-10-0- -1
-11-10-10-10 -1
-11-10-10-11  1
-11-10-11-0-  1
-11-10-11-10  1
-11-10-11-11 -1
-11-11-0--0-  1
-11-11-0--10  1
-11-11-0--11 -1
-11-11-10-0-  1
-11-11-10-10  1
-11-11-10-11 -1
-11-11-11-0- -1
-11-11-11-10 -1
-11-11-11-11  1

wtw: 14 nodes 2 leaves 16 minterms
0-00-00-00-0  16
0-00-00-01-1  16
0-00-01-10-0  16
0-00-01-11-1  16
0-01-10-00-0  16
0-01-10-01-1  16
0-01-11-10-0  16
0-01-11-11-1  16
1-10-00-00-0  16
1-10-00-01-1  16
1-10-01-10-0  16
1-10-01-11-1  16
1-11-10-00-0  16
1-11-10-01-1  16
1-11-11-10-0  16
1-11-11-11-1  16

Average length of non-empty lists = 1
**** CUDD modifiable parameters ****
Hard limit for cache size: 2796202
Cache hit threshold for resizing: 30%
Garbage collection enabled: yes
Limit for fast unique table growth: 1677721
Maximum number of variables sifted per reordering: 1000
Maximum number of variable swaps per reordering: 2000000
Maximum growth while sifting a variable: 1.2
Dynamic reordering of BDDs enabled: no
Default BDD reordering method: 4
Dynamic reordering of ZDDs enabled: no
Default ZDD reordering method: 4
Realignment of ZDDs to BDDs enabled: no
Realignment of BDDs to ZDDs enabled: no
Dead nodes counted in triggering reordering: no
Group checking criterion: 7
Recombination threshold: 0
Symmetry violation threshold: 0
Arc violation threshold: 0
GA population size: 0
Number of crossovers for GA: 0
Next reordering threshold: 4004
**** CUDD non-modifiable parameters ****
Memory in use: 2256072
Peak number of nodes: 2044
Peak number of live nodes: 119
Number of BDD variables: 9
Number of ZDD variables: 0
Number of cache entries: 2048
Number of cache look-ups: 2562
Number of cache hits: 727
Number of cache insertions: 2002
Number of cache collisions: 762
Number of cache deletions: 1236
Cache used slots = 60.55% (expected 62.38%)
Soft limit for cache size: 13312
Number of buckets in unique table: 2560
Used buckets in unique table: 0.51% (expected 0.51%)
Number of BDD and ADD nodes: 13
Number of ZDD nodes: 0
Number of dead BDD and ADD nodes: 0
Number of dead ZDD nodes: 0
Total number of nodes allocated: 1097
Total number of nodes reclaimed: 965
Garbage collections so far: 1
Time for garbage collection: 0.00 sec
Reorderings so far: 0
Time for reordering: 0.00 sec
total time = 0.00 sec
Runtime Statistics
------------------
Machine name: ubuntuBDD
User time      0.0 seconds
System time    0.0 seconds

Average resident text size       =     0K
Average resident data+stack size =     0K
Maximum resident size            =  4960K

Virtual memory limit             = unlimited (unlimited)
Major page faults = 0
Minor page faults = 660
Swaps = 0
Input blocks = 8
Output blocks = 16
Context switch (voluntary) = 1
Context switch (involuntary) = 0
