# Nanotrav Version #0.13, Release date 2015/7/15
# nanotrav/nanotrav -p 1 -ordering dfs -reordering cogroup -drop -char2vect -cofest ./nanotrav/adj49.blif
# CUDD Version 3.0.0
Order before final reordering
CA OR NV AZ WA ID UT MT 
WY CO NM ND SD NE KS OK 
TX MN IA MO AR LA WI IL 
KY TN MS MI IN AL OH WV 
VA NC GA FL PA MD DC SC 
NY NJ DE VT NH MA CT ME 
RI 
Number of inputs = 49
BDD reordering with converging group sifting: from 431 to ... 338 nodes in 0.01 sec
New order
ID OR WA NV AZ CA UT NM 
WY MT CO SD MN ND NE IA 
KS MO TX OK LA WI AR MS 
KY MI IN IL AL TN FL NC 
SC GA WV OH MD DC VA PA 
NJ DE NY RI CT NH ME VT 
MA 
Testing char-to-vect
*** indep ***
f: 338 nodes 1 leaves 2.11955e+08 minterms
Vector Size: 49 components 1171 nodes
v[0]: 6 nodes 1 leaves 8.79609e+13 minterms
v[1]: 3 nodes 1 leaves 1.40737e+14 minterms
v[2]: 4 nodes 1 leaves 7.03687e+13 minterms
v[3]: 5 nodes 1 leaves 2.46291e+14 minterms
v[4]: 4 nodes 1 leaves 7.03687e+13 minterms
v[5]: 2 nodes 1 leaves 2.81475e+14 minterms
v[6]: 6 nodes 1 leaves 5.27766e+13 minterms
v[7]: 8 nodes 1 leaves 8.35629e+13 minterms
v[8]: 7 nodes 1 leaves 1.14349e+14 minterms
v[9]: 11 nodes 1 leaves 1.47335e+14 minterms
v[10]: 6 nodes 1 leaves 1.5833e+14 minterms
v[11]: 11 nodes 1 leaves 7.4217e+13 minterms
v[12]: 9 nodes 1 leaves 1.82519e+14 minterms
v[13]: 17 nodes 1 leaves 9.09846e+13 minterms
v[14]: 18 nodes 1 leaves 1.62315e+14 minterms
v[15]: 26 nodes 1 leaves 2.79388e+13 minterms
v[16]: 7 nodes 1 leaves 2.0231e+14 minterms
v[17]: 10 nodes 1 leaves 1.90216e+14 minterms
v[18]: 21 nodes 1 leaves 7.23616e+13 minterms
v[19]: 26 nodes 1 leaves 1.31478e+14 minterms
v[20]: 43 nodes 1 leaves 6.3558e+13 minterms
v[21]: 8 nodes 1 leaves 1.8032e+14 minterms
v[22]: 22 nodes 1 leaves 1.50186e+14 minterms
v[23]: 33 nodes 1 leaves 4.71217e+13 minterms
v[24]: 27 nodes 1 leaves 2.15736e+14 minterms
v[25]: 48 nodes 1 leaves 3.18125e+13 minterms
v[26]: 46 nodes 1 leaves 1.59536e+14 minterms
v[27]: 23 nodes 1 leaves 2.06382e+14 minterms
v[28]: 34 nodes 1 leaves 1.10876e+14 minterms
v[29]: 47 nodes 1 leaves 2.01707e+14 minterms
v[30]: 36 nodes 1 leaves 2.77189e+13 minterms
v[31]: 28 nodes 1 leaves 1.73607e+14 minterms
v[32]: 54 nodes 1 leaves 9.85629e+12 minterms
v[33]: 49 nodes 1 leaves 2.65569e+14 minterms
v[34]: 56 nodes 1 leaves 2.05894e+13 minterms
v[35]: 48 nodes 1 leaves 1.80621e+14 minterms
v[36]: 39 nodes 1 leaves 9.0406e+13 minterms
v[37]: 29 nodes 1 leaves 1.94672e+14 minterms
v[38]: 30 nodes 1 leaves 1.84139e+14 minterms
v[39]: 50 nodes 1 leaves 1.48691e+14 minterms
v[40]: 41 nodes 1 leaves 1.18136e+14 minterms
v[41]: 40 nodes 1 leaves 2.36272e+14 minterms
v[42]: 42 nodes 1 leaves 6.94681e+13 minterms
v[43]: 43 nodes 1 leaves 1.11203e+14 minterms
v[44]: 2 nodes 1 leaves 2.81475e+14 minterms
v[45]: 46 nodes 1 leaves 1.39004e+13 minterms
v[46]: 43 nodes 1 leaves 1.11203e+14 minterms
v[47]: 3 nodes 1 leaves 1.40737e+14 minterms
v[48]: 2 nodes 1 leaves 2.81475e+14 minterms
Testing BDD cofactor estimation algorithms
TEST-COF:: indep (49 vars): 338 nodes 1 leaves 2.11955e+08 minterms
T-c   : 13145
T-c E : 13619 42
T-c S : 14592 131
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
Next reordering threshold: 776
**** CUDD non-modifiable parameters ****
Memory in use: 3791944
Peak number of nodes: 17374
Peak number of live nodes: 3444
Number of BDD variables: 49
Number of ZDD variables: 0
Number of cache entries: 32768
Number of cache look-ups: 51762
Number of cache hits: 17182
Number of cache insertions: 25253
Number of cache collisions: 6743
Number of cache deletions: 1733
Cache used slots = 53.57% (expected 51.15%)
Soft limit for cache size: 51200
Number of buckets in unique table: 12800
Used buckets in unique table: 55.52% (expected 55.54%)
Number of BDD and ADD nodes: 16471
Number of ZDD nodes: 0
Number of dead BDD and ADD nodes: 16082
Number of dead ZDD nodes: 0
Total number of nodes allocated: 18850
Total number of nodes reclaimed: 1805
Garbage collections so far: 1
Time for garbage collection: 0.00 sec
Reorderings so far: 1
Time for reordering: 0.01 sec
Final size: 338
total time = 0.01 sec
Runtime Statistics
------------------
Machine name: ubuntuBDD
User time      0.0 seconds
System time    0.0 seconds

Average resident text size       =     0K
Average resident data+stack size =     0K
Maximum resident size            =  6704K

Virtual memory limit             = unlimited (unlimited)
Major page faults = 0
Minor page faults = 1071
Swaps = 0
Input blocks = 8
Output blocks = 8
Context switch (voluntary) = 1
Context switch (involuntary) = 0
