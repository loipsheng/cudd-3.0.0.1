# Nanotrav Version #0.13, Release date 2015/7/15
# nanotrav/nanotrav -p 1 -ordering dfs -reordering win4 -verify ./nanotrav/s27.blif ./nanotrav/s27b.blif
# CUDD Version 3.0.0
Order before final reordering
G0 G6 G1 G7 G3 G5 G2 
Number of inputs = 7
BDD reordering with window: from 11 to ... 11 nodes in 0 sec
New order
G0 G6 G1 G7 G3 G5 G2 
Testing equivalence
G17: 7 nodes 1 leaves 106 minterms
G10: 6 nodes 1 leaves 60 minterms
G11: 7 nodes 1 leaves 22 minterms
G13: 4 nodes 1 leaves 48 minterms
Verification succeeded
**** CUDD modifiable parameters ****
Hard limit for cache size: 2796202
Cache hit threshold for resizing: 30%
Garbage collection enabled: yes
Limit for fast unique table growth: 1677721
Maximum number of variables sifted per reordering: 1000000
Maximum number of variable swaps per reordering: 1000000000
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
Symmetry violation threshold: 10
Arc violation threshold: 10
GA population size: 0
Number of crossovers for GA: 0
Next reordering threshold: 36
**** CUDD non-modifiable parameters ****
Memory in use: 3183048
Peak number of nodes: 1022
Peak number of live nodes: 29
Number of BDD variables: 7
Number of ZDD variables: 0
Number of cache entries: 32768
Number of cache look-ups: 27
Number of cache hits: 8
Number of cache insertions: 19
Number of cache collisions: 0
Number of cache deletions: 19
Cache used slots = 0.06% (expected 0.00%)
Soft limit for cache size: 8192
Number of buckets in unique table: 2048
Used buckets in unique table: 1.27% (expected 1.25%)
Number of BDD and ADD nodes: 26
Number of ZDD nodes: 0
Number of dead BDD and ADD nodes: 7
Number of dead ZDD nodes: 0
Total number of nodes allocated: 36
Total number of nodes reclaimed: 10
Garbage collections so far: 1
Time for garbage collection: 0.00 sec
Reorderings so far: 1
Time for reordering: 0.00 sec
Final size: 11
total time = 0.00 sec
Runtime Statistics
------------------
Machine name: ubuntuBDD
User time      0.0 seconds
System time    0.0 seconds

Average resident text size       =     0K
Average resident data+stack size =     0K
Maximum resident size            =  6152K

Virtual memory limit             = unlimited (unlimited)
Major page faults = 0
Minor page faults = 908
Swaps = 0
Input blocks = 8
Output blocks = 8
Context switch (voluntary) = 1
Context switch (involuntary) = 0
