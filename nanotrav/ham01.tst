# Nanotrav Version #0.13, Release date 2015/7/15
# nanotrav/nanotrav -p 1 -reordering linear ./nanotrav/ham01.blif
# CUDD Version 3.0.0
Order before final reordering
x2 y2 x1 y1 x0 y0 
Number of inputs = 6
BDD reordering with linear sifting: from 12 to ... 8 nodes in 0 sec
New order
y1 x2 x1 y2 x0 y0 
x2 : 2 nodes 1 leaves 32 minterms
y2 : 2 nodes 1 leaves 32 minterms
x1 : 2 nodes 1 leaves 32 minterms
y1 : 4 nodes 1 leaves 32 minterms
x0 : 2 nodes 1 leaves 32 minterms
y0 : 2 nodes 1 leaves 32 minterms
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
Next reordering threshold: 28
**** CUDD non-modifiable parameters ****
Memory in use: 3183096
Peak number of nodes: 1022
Peak number of live nodes: 20
Number of BDD variables: 6
Number of ZDD variables: 0
Number of cache entries: 32768
Number of cache look-ups: 5
Number of cache hits: 0
Number of cache insertions: 5
Number of cache collisions: 0
Number of cache deletions: 5
Cache used slots = 0.02% (expected 0.00%)
Soft limit for cache size: 7168
Number of buckets in unique table: 1792
Used buckets in unique table: 0.89% (expected 0.89%)
Number of BDD and ADD nodes: 16
Number of ZDD nodes: 0
Number of dead BDD and ADD nodes: 1
Number of dead ZDD nodes: 0
Total number of nodes allocated: 21
Total number of nodes reclaimed: 2
Garbage collections so far: 0
Time for garbage collection: 0.00 sec
Reorderings so far: 1
Time for reordering: 0.00 sec
Final size: 8
total time = 0.00 sec
Runtime Statistics
------------------
Machine name: ubuntuBDD
User time      0.0 seconds
System time    0.0 seconds

Average resident text size       =     0K
Average resident data+stack size =     0K
Maximum resident size            =  6084K

Virtual memory limit             = unlimited (unlimited)
Major page faults = 0
Minor page faults = 905
Swaps = 0
Input blocks = 0
Output blocks = 8
Context switch (voluntary) = 0
Context switch (involuntary) = 0
