# Nanotrav Version #0.13, Release date 2015/7/15
# ./nanotrav -reordering sifting -autodyn ./rcn25.blif
# CUDD Version 3.0.0
Order before final reordering
n0 n1 n2 n3 n4 n5 n6 n7 
n8 n9 n10 n11 n12 n13 n14 n15 
n16 n17 n18 n19 n20 n21 n22 n23 
n24 
Number of inputs = 25
BDD reordering with sifting: from 869 to ... 731 nodes in 0 sec
New order
n0 n5 n3 n2 n1 n4 n7 n6 
n9 n8 n11 n10 n13 n12 n15 n14 
n17 n16 n19 n18 n21 n20 n23 n24 
n22 
**** CUDD modifiable parameters ****
Hard limit for cache size: 2796202
Cache hit threshold for resizing: 30%
Garbage collection enabled: yes
Limit for fast unique table growth: 1677721
Maximum number of variables sifted per reordering: 1000000
Maximum number of variable swaps per reordering: 1000000000
Maximum growth while sifting a variable: 1.2
Dynamic reordering of BDDs enabled: yes
Default BDD reordering method: 4
Dynamic reordering of ZDDs enabled: no
Default ZDD reordering method: 4
Realignment of ZDDs to BDDs enabled: no
Realignment of BDDs to ZDDs enabled: no
Dead nodes counted in triggering reordering: no
Group checking criterion: 7
Recombination threshold: 0
Symmetry violation threshold: 10
Arc violation threshold: 10
GA population size: 0
Number of crossovers for GA: 0
Next reordering threshold: 1468
**** CUDD non-modifiable parameters ****
Memory in use: 3323816
Peak number of nodes: 4088
Peak number of live nodes: 2555
Number of BDD variables: 25
Number of ZDD variables: 0
Number of cache entries: 32768
Number of cache look-ups: 9293
Number of cache hits: 4337
Number of cache insertions: 4957
Number of cache collisions: 435
Number of cache deletions: 4522
Cache used slots = 13.80% (expected 0.00%)
Soft limit for cache size: 26624
Number of buckets in unique table: 6656
Used buckets in unique table: 10.31% (expected 10.28%)
Number of BDD and ADD nodes: 735
Number of ZDD nodes: 0
Number of dead BDD and ADD nodes: 0
Number of dead ZDD nodes: 0
Total number of nodes allocated: 3594
Total number of nodes reclaimed: 301
Garbage collections so far: 1
Time for garbage collection: 0.00 sec
Reorderings so far: 1
Time for reordering: 0.00 sec
Final size: 731
total time = 0.00 sec
Runtime Statistics
------------------
Machine name: itcat
User time      0.0 seconds
System time    0.0 seconds

Average resident text size       =     0K
Average resident data+stack size =     0K
Maximum resident size            =  5632K

Virtual memory limit             = unlimited (unlimited)
Major page faults = 0
Minor page faults = 988
Swaps = 0
Input blocks = 0
Output blocks = 8
Context switch (voluntary) = 1
Context switch (involuntary) = 0
