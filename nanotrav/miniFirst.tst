# Nanotrav Version #0.13, Release date 2015/7/15
# nanotrav/nanotrav -p 1 -second ./nanotrav/miniSecond.blif ./nanotrav/miniFirst.blif
# CUDD Version 3.0.0
Order before final reordering
a b c d 
Number of inputs = 4
Testing BDD minimization algorithms
TEST-MINI: Constrain (B) 4 nodes
TEST-MINI:: A
T-M    : 7 nodes 1 leaves 3 minterms
T-M L1 : 5 nodes 1 leaves 6 minterms
T-M M1 : 5 nodes 1 leaves 6 minterms
T-M R1 : 5 nodes 1 leaves 6 minterms
T-M C1 : 5 nodes 1 leaves 6 minterms
TEST-MINI: (lb,ub) : (7,7) nodes
T-M S1 : 5 nodes 1 leaves 6 minterms
T-M N1 : 7 nodes 1 leaves 3 minterms
T-M A1 : 7 nodes 1 leaves 3 minterms
TEST-MINI: f 7 comp 5 mini 5 rest 5 cons 5 sque 5 na 7 and 7
TEST-MINI:: A
T-M    : 7 nodes 1 leaves 3 minterms
T-M L0 : is the zero DD
T-M M0 : is the zero DD
T-M R0 : is the zero DD
T-M C0 : is the zero DD
TEST-MINI: (lb,ub) : (1,4) nodes
T-M S0 : is the zero DD
T-M N0 : is the zero DD
T-M A0 : is the zero DD
TEST-MINI: f 7 comp 1 mini 1 rest 1 cons 1 sque 1 na 1, and 1
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
Memory in use: 3183048
Peak number of nodes: 1022
Peak number of live nodes: 22
Number of BDD variables: 4
Number of ZDD variables: 0
Number of cache entries: 32768
Number of cache look-ups: 86
Number of cache hits: 23
Number of cache insertions: 60
Number of cache collisions: 0
Number of cache deletions: 0
Cache used slots = 0.18% (expected 0.18%)
Soft limit for cache size: 5120
Number of buckets in unique table: 1280
Used buckets in unique table: 2.97% (expected 3.21%)
Number of BDD and ADD nodes: 42
Number of ZDD nodes: 0
Number of dead BDD and ADD nodes: 28
Number of dead ZDD nodes: 0
Total number of nodes allocated: 42
Total number of nodes reclaimed: 17
Garbage collections so far: 0
Time for garbage collection: 0.00 sec
Reorderings so far: 0
Time for reordering: 0.00 sec
Final size: 9
total time = 0.00 sec
Runtime Statistics
------------------
Machine name: ubuntuBDD
User time      0.0 seconds
System time    0.0 seconds

Average resident text size       =     0K
Average resident data+stack size =     0K
Maximum resident size            =  6048K

Virtual memory limit             = unlimited (unlimited)
Major page faults = 0
Minor page faults = 904
Swaps = 0
Input blocks = 16
Output blocks = 8
Context switch (voluntary) = 2
Context switch (involuntary) = 1
