# Nanotrav Version #0.13, Release date 2015/7/15
# nanotrav/nanotrav -p 1 -ordering hw -reordering annealing -trav ./nanotrav/s27.blif
# CUDD Version 3.0.0
Order before final reordering
G0 G1 G2 G3 G5 G6 G7 
Number of inputs = 7
BDD reordering with annealing: from 16 to ... 10 nodes in 0 sec
New order
G0 G5 G6 G3 G2 G7 G1 
Building transition relation. Time = 0.00 sec
@@@
Transition relation: 1 parts 3 latches 9 nodes
Traversing. Time = 0.00 sec
S0: 4 nodes 1 leaves 1 minterms
From[1]: 5 nodes 1 leaves 4 minterms
Reached[1]: 5 nodes 1 leaves 5 minterms
5
5
From[2]: 4 nodes 1 leaves 1 minterms
Reached[2]: 3 nodes 1 leaves 6 minterms
6
6
depth = 2
R: 3 nodes 1 leaves 6 minterms
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
Memory in use: 3183088
Peak number of nodes: 1022
Peak number of live nodes: 51
Number of BDD variables: 10
Number of ZDD variables: 0
Number of cache entries: 32768
Number of cache look-ups: 151
Number of cache hits: 30
Number of cache insertions: 115
Number of cache collisions: 1
Number of cache deletions: 24
Cache used slots = 0.35% (expected 0.28%)
Soft limit for cache size: 11264
Number of buckets in unique table: 2816
Used buckets in unique table: 3.34% (expected 3.33%)
Number of BDD and ADD nodes: 96
Number of ZDD nodes: 0
Number of dead BDD and ADD nodes: 67
Number of dead ZDD nodes: 0
Total number of nodes allocated: 111
Total number of nodes reclaimed: 21
Garbage collections so far: 1
Time for garbage collection: 0.00 sec
Reorderings so far: 1
Time for reordering: 0.00 sec
Final size: 10
total time = 0.00 sec
Runtime Statistics
------------------
Machine name: ubuntuBDD
User time      0.0 seconds
System time    0.0 seconds

Average resident text size       =     0K
Average resident data+stack size =     0K
Maximum resident size            =  5964K

Virtual memory limit             = unlimited (unlimited)
Major page faults = 0
Minor page faults = 904
Swaps = 0
Input blocks = 8
Output blocks = 8
Context switch (voluntary) = 1
Context switch (involuntary) = 0
