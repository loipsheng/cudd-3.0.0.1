# Nanotrav Version #0.13, Release date 2015/7/15
# nanotrav/nanotrav -p 1 -trav -image depend -depend ./nanotrav/s27c.blif
# CUDD Version 3.0.0
Order before final reordering
G5 G6 G7 
Number of inputs = 3
Building transition relation. Time = 0.00 sec
Transition relation: 3 parts 3 latches 4 nodes
Traversing. Time = 0.00 sec
S0: 4 nodes 1 leaves 1 minterms
Eliminated 3 vars. Transition function 1 nodes.
Extracted 2 repeated parts in 1 factors.
new factor of 2 nodes
Merging 3 factors. Independent image: 1 nodes
new factor 2 nodes
new factor 4 nodes
From[1]: 4 nodes 1 leaves 1 minterms
Reached[1]: 3 nodes 1 leaves 2 minterms
2
2
Eliminated 3 vars. Transition function 1 nodes.
Extracted 2 repeated parts in 1 factors.
new factor of 2 nodes
Merging 3 factors. Independent image: 1 nodes
new factor 2 nodes
new factor 4 nodes
depth = 1
R: 3 nodes 1 leaves 2 minterms
Analyzing latch dependencies
G5 is stuck at 0
G7 is stuck at 0
new reached: 1 nodes 1 leaves 2 minterms
2 latches are redundant
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
Symmetry violation threshold: 10
Arc violation threshold: 10
GA population size: 0
Number of crossovers for GA: 0
Next reordering threshold: 4004
**** CUDD non-modifiable parameters ****
Memory in use: 3183088
Peak number of nodes: 1022
Peak number of live nodes: 25
Number of BDD variables: 6
Number of ZDD variables: 0
Number of cache entries: 32768
Number of cache look-ups: 88
Number of cache hits: 33
Number of cache insertions: 48
Number of cache collisions: 5
Number of cache deletions: 0
Cache used slots = 0.13% (expected 0.15%)
Soft limit for cache size: 7168
Number of buckets in unique table: 1792
Used buckets in unique table: 1.51% (expected 1.60%)
Number of BDD and ADD nodes: 29
Number of ZDD nodes: 0
Number of dead BDD and ADD nodes: 17
Number of dead ZDD nodes: 0
Total number of nodes allocated: 29
Total number of nodes reclaimed: 15
Garbage collections so far: 0
Time for garbage collection: 0.00 sec
Reorderings so far: 0
Time for reordering: 0.00 sec
Final size: 4
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
Minor page faults = 906
Swaps = 0
Input blocks = 8
Output blocks = 8
Context switch (voluntary) = 1
Context switch (involuntary) = 0
