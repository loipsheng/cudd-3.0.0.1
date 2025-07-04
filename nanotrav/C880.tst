# Nanotrav Version #0.13, Release date 2015/7/15
# nanotrav/nanotrav -p 1 -ordering dfs -autodyn -automethod sifting -reordering sifting -drop ./nanotrav/C880.blif
# CUDD Version 3.0.0
BDD reordering with sifting: from 3974 to ... 2432 nodes in 0 sec
BDD reordering with sifting: from 4893 to ... 3549 nodes in 0.02 sec
BDD reordering with sifting: from 7133 to ... 6246 nodes in 0.03 sec
BDD reordering with sifting: from 12522 to ... 6465 nodes in 0.05 sec
Order before final reordering
86GAT(18) 85GAT(17) 90GAT(22) 89GAT(21) 88GAT(20) 87GAT(19) 1GAT(0) 51GAT(8) 
75GAT(15) 26GAT(4) 268GAT(59) 36GAT(6) 29GAT(5) 80GAT(16) 59GAT(10) 42GAT(7) 
156GAT(39) 17GAT(3) 74GAT(14) 55GAT(9) 8GAT(1) 219GAT(50) 210GAT(49) 91GAT(23) 
101GAT(25) 138GAT(33) 96GAT(24) 171GAT(42) 152GAT(37) 146GAT(35) 116GAT(28) 189GAT(45) 
149GAT(36) 121GAT(29) 195GAT(46) 153GAT(38) 126GAT(30) 261GAT(57) 201GAT(47) 143GAT(34) 
111GAT(27) 183GAT(44) 130GAT(31) 135GAT(32) 106GAT(26) 177GAT(43) 165GAT(41) 207GAT(48) 
159GAT(40) 228GAT(51) 237GAT(52) 246GAT(53) 73GAT(13) 72GAT(12) 68GAT(11) 13GAT(2) 
260GAT(56) 267GAT(58) 259GAT(55) 255GAT(54) 
Number of inputs = 60
BDD reordering with sifting: from 6204 to ... 4623 nodes in 0.02 sec
New order
135GAT(32) 207GAT(48) 130GAT(31) 86GAT(18) 85GAT(17) 89GAT(21) 90GAT(22) 88GAT(20) 
87GAT(19) 1GAT(0) 51GAT(8) 26GAT(4) 268GAT(59) 29GAT(5) 80GAT(16) 59GAT(10) 
42GAT(7) 75GAT(15) 156GAT(39) 36GAT(6) 17GAT(3) 74GAT(14) 55GAT(9) 8GAT(1) 
210GAT(49) 91GAT(23) 138GAT(33) 165GAT(41) 96GAT(24) 159GAT(40) 101GAT(25) 171GAT(42) 
152GAT(37) 149GAT(36) 146GAT(35) 116GAT(28) 189GAT(45) 121GAT(29) 195GAT(46) 153GAT(38) 
143GAT(34) 126GAT(30) 201GAT(47) 261GAT(57) 111GAT(27) 106GAT(26) 183GAT(44) 177GAT(43) 
219GAT(50) 246GAT(53) 237GAT(52) 228GAT(51) 73GAT(13) 72GAT(12) 68GAT(11) 13GAT(2) 
260GAT(56) 267GAT(58) 259GAT(55) 255GAT(54) 
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
Next reordering threshold: 9340
**** CUDD non-modifiable parameters ****
Memory in use: 4927272
Peak number of nodes: 19418
Peak number of live nodes: 12568
Number of BDD variables: 60
Number of ZDD variables: 0
Number of cache entries: 65536
Number of cache look-ups: 59159
Number of cache hits: 28638
Number of cache insertions: 30600
Number of cache collisions: 2537
Number of cache deletions: 28063
Cache used slots = 18.10% (expected 0.00%)
Soft limit for cache size: 62464
Number of buckets in unique table: 15616
Used buckets in unique table: 21.03% (expected 20.96%)
Number of BDD and ADD nodes: 4671
Number of ZDD nodes: 0
Number of dead BDD and ADD nodes: 0
Number of dead ZDD nodes: 0
Total number of nodes allocated: 32671
Total number of nodes reclaimed: 1974
Garbage collections so far: 5
Time for garbage collection: 0.00 sec
Reorderings so far: 5
Time for reordering: 0.12 sec
Final size: 4623
total time = 0.13 sec
Runtime Statistics
------------------
Machine name: ubuntuBDD
User time      0.1 seconds
System time    0.0 seconds

Average resident text size       =     0K
Average resident data+stack size =     0K
Maximum resident size            =  6156K

Virtual memory limit             = unlimited (unlimited)
Major page faults = 0
Minor page faults = 1624
Swaps = 0
Input blocks = 8
Output blocks = 8
Context switch (voluntary) = 1
Context switch (involuntary) = 0
