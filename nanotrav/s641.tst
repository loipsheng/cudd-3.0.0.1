# Nanotrav Version #0.13, Release date 2015/7/15
# nanotrav/nanotrav -p 1 -trav -autodyn -automethod group -drop -clauses -density -decomp -zdd ./nanotrav/s641.blif
# CUDD Version 3.0.0
Order before final reordering
G1 G2 G3 G4 G5 G6 G8 G9 
G10 G11 G12 G13 G14 G15 G16 G17 
G18 G19 G20 G21 G22 G23 G24 G25 
G26 G27 G28 G29 G30 G31 G32 G33 
G34 G35 G36 G64 G65 G66 G67 G68 
G69 G70 G71 G72 G73 G74 G75 G76 
G77 G78 G79 G80 G81 G82 
Building transition relation. Time = 0.00 sec
@@@@@BDD reordering with group sifting: from 3979 to ... 1316 nodes in 0.03 sec
@@BDD reordering with group sifting: from 2656 to ... 1332 nodes in 0.01 sec
@@BDD reordering with group sifting: from 2687 to ... 1855 nodes in 0.02 sec
@@@BDD reordering with group sifting: from 3708 to ... 2468 nodes in 0.03 sec
@@@@BDD reordering with group sifting: from 4224 to ... 2505 nodes in 0.03 sec
@@@
Transition relation: 1 parts 19 latches 721 nodes
Traversing. Time = 0.12 sec
S0: 20 nodes 1 leaves 1 minterms
From[1]: 20 nodes 1 leaves 1 minterms
Reached[1]: 25 nodes 1 leaves 2 minterms
2
2
From[2]: 23 nodes 1 leaves 7 minterms
Reached[2]: 23 nodes 1 leaves 9 minterms
9
9
From[3]: 45 nodes 1 leaves 56 minterms
Reached[3]: 48 nodes 1 leaves 65 minterms
65
65
From[4]: 134 nodes 1 leaves 649 minterms
Reached[4]: 111 nodes 1 leaves 714 minterms
714
714
From[5]: 163 nodes 1 leaves 560 minterms
Reached[5]: 153 nodes 1 leaves 1274 minterms
1274
1274
From[6]: 110 nodes 1 leaves 270 minterms
Reached[6]: 87 nodes 1 leaves 1544 minterms
1544
1544
depth = 6
R: 87 nodes 1 leaves 1544 minterms
Order at the end of reachability analysis
G81 G31 G79 G82 G32 G34 G17 G20 
G26 G15 G30 G36 G14 G28 G12 G16 
G1 G3 G11 G5 G25 G67 G6 G13 
G9 G10 G68 G78 G2 G66 G64 G76 
G8 G75 G24 G77 G74 G73 G23 G65 
G72 G33 G71 G70 G35 G69 G4 G22 
G80 G27 G19 G29 G21 G18 
Testing extraction of two literal clauses
*** G91 ***
 G27
*** G94 ***
 G29
*** G107 ***
 G18
~G4
 G79
*** G83 ***
 G19
 G80
~G4
*** G84 ***
~G4
 G20
 G81
*** G85 ***
 G21
~G4
 G82
*** G100BF ***
*** G98BF ***
*** G96BF ***
*** G92 ***
 G13
 G11
 G12
 G28
*** G87BF ***
*** G89BF ***
*** G101BF ***
*** G106BF ***
*** G97BF ***
*** G104BF ***
*** G88BF ***
*** G99BF ***
*** G105BF ***
*** G86BF ***
*** G95BF ***
*** G103BF ***
*** G90 ***
 G12
 G26
*** G380 ***
 G22 |  G75
 G11 |  G75
 G3 |  G22
 G3 |  G11
~G3 |  G75
~G2 |  G75
*** G262 ***
~G65 | ~G77
~G65 |  G76
~G65 | ~G78
 G23 | ~G77
 G23 |  G76
 G23 | ~G78
 G76 | ~G77
 G76 | ~G78
 G11 | ~G77
 G11 |  G76
 G11 | ~G78
 G3 | ~G65
 G3 |  G23
 G3 |  G76
 G3 |  G11
~G3 | ~G77
~G3 |  G76
~G3 | ~G78
~G2
*** G394 ***
 G77
 G3 |  G24
 G3 |  G11
*** G250 ***
~G2
 G78
 G3 | ~G67
 G3 |  G25
 G3 |  G11
*** G122 ***
 G68
~G67
 G25
 G3 |  G11
*** G133 ***
~G4 |  G70
 G69 |  G70
 G24 | ~G4
 G24 |  G69
*** G138 ***
*** G139 ***
~G4 |  G72
 G71 |  G72
~G65 | ~G4
~G65 |  G71
 G23 | ~G4
 G23 |  G71
*** G140 ***
*** G141 ***
~G4 |  G74
 G73 |  G74
~G4 |  G22
*** G142 ***
*** G125 ***
 G3 |  G11
~G2 |  G8
*** G126 ***
 G3 |  G11
~G2 |  G5
*** G127 ***
~G4 |  G77
 G69 |  G77
 G70 |  G77
 G6 |  G77
 G3 |  G11
~G2 |  G6
*** G128 ***
 G1 | ~G2
 G1 |  G78
*** G129 ***
 G22 | ~G77
 G22 |  G75
 G22 | ~G76
 G22 | ~G78
 G75 | ~G77
 G75 | ~G76
 G75 | ~G78
~G64 | ~G77
~G64 |  G75
~G64 | ~G76
~G64 | ~G78
 G11 | ~G77
 G11 |  G75
 G11 | ~G76
 G11 | ~G78
 G3 |  G22
 G3 |  G75
 G3 | ~G64
 G3 |  G11
~G3 | ~G77
~G3 |  G75
~G3 | ~G76
~G3 | ~G78
~G2
*** G130 ***
~G65 | ~G77
~G65 |  G76
~G65 | ~G78
 G23 | ~G77
 G23 |  G76
 G23 | ~G78
 G76 | ~G77
 G76 | ~G78
 G11 | ~G77
 G11 |  G76
 G11 | ~G78
 G3 | ~G65
 G3 |  G23
 G3 |  G76
 G3 |  G11
~G3 | ~G77
~G3 |  G76
~G3 | ~G78
~G2
*** G131 ***
 G77
 G24 | ~G78
~G66 | ~G78
 G11 | ~G78
 G3 |  G24
 G3 | ~G66
 G3 |  G11
~G3 | ~G78
~G2
*** G132 ***
~G2
 G78
 G3 | ~G67
 G3 |  G25
 G3 |  G11
Testing BDD density-related algorithms
TEST-DENSITY:: G91 (1 variables)
T-D    (0.5): 2 nodes 1 leaves 1 minterms
T-D APA 1
T-D ID (0.5): 2 nodes 1 leaves 1 minterms
T-D BU (0.5): 2 nodes 1 leaves 1 minterms
T-D HB (0.5): 2 nodes 1 leaves 1 minterms
T-D SP (0.5): 2 nodes 1 leaves 1 minterms
T-D UA (0.5): 2 nodes 1 leaves 1 minterms
T-D C1 (0.5): 2 nodes 1 leaves 1 minterms
T-D C2 (0.5): 2 nodes 1 leaves 1 minterms
TEST-DENSITY:: G94 (1 variables)
T-D    (0.5): 2 nodes 1 leaves 1 minterms
T-D APA 1
T-D ID (0.5): 2 nodes 1 leaves 1 minterms
T-D BU (0.5): 2 nodes 1 leaves 1 minterms
T-D HB (0.5): 2 nodes 1 leaves 1 minterms
T-D SP (0.5): 2 nodes 1 leaves 1 minterms
T-D UA (0.5): 2 nodes 1 leaves 1 minterms
T-D C1 (0.5): 2 nodes 1 leaves 1 minterms
T-D C2 (0.5): 2 nodes 1 leaves 1 minterms
TEST-DENSITY:: G107 (3 variables)
T-D    (0.25): 4 nodes 1 leaves 1 minterms
T-D APA 1
T-D ID (0.25): 4 nodes 1 leaves 1 minterms
T-D BU (0.25): 4 nodes 1 leaves 1 minterms
T-D HB (0.25): 4 nodes 1 leaves 1 minterms
T-D SP (0.25): 4 nodes 1 leaves 1 minterms
T-D UA (0.25): 4 nodes 1 leaves 1 minterms
T-D C1 (0.25): 4 nodes 1 leaves 1 minterms
T-D C2 (0.25): 4 nodes 1 leaves 1 minterms
TEST-DENSITY:: G83 (3 variables)
T-D    (0.25): 4 nodes 1 leaves 1 minterms
T-D APA 1
T-D ID (0.25): 4 nodes 1 leaves 1 minterms
T-D BU (0.25): 4 nodes 1 leaves 1 minterms
T-D HB (0.25): 4 nodes 1 leaves 1 minterms
T-D SP (0.25): 4 nodes 1 leaves 1 minterms
T-D UA (0.25): 4 nodes 1 leaves 1 minterms
T-D C1 (0.25): 4 nodes 1 leaves 1 minterms
T-D C2 (0.25): 4 nodes 1 leaves 1 minterms
TEST-DENSITY:: G84 (3 variables)
T-D    (0.25): 4 nodes 1 leaves 1 minterms
T-D APA 1
T-D ID (0.25): 4 nodes 1 leaves 1 minterms
T-D BU (0.25): 4 nodes 1 leaves 1 minterms
T-D HB (0.25): 4 nodes 1 leaves 1 minterms
T-D SP (0.25): 4 nodes 1 leaves 1 minterms
T-D UA (0.25): 4 nodes 1 leaves 1 minterms
T-D C1 (0.25): 4 nodes 1 leaves 1 minterms
T-D C2 (0.25): 4 nodes 1 leaves 1 minterms
TEST-DENSITY:: G85 (3 variables)
T-D    (0.25): 4 nodes 1 leaves 1 minterms
T-D APA 1
T-D ID (0.25): 4 nodes 1 leaves 1 minterms
T-D BU (0.25): 4 nodes 1 leaves 1 minterms
T-D HB (0.25): 4 nodes 1 leaves 1 minterms
T-D SP (0.25): 4 nodes 1 leaves 1 minterms
T-D UA (0.25): 4 nodes 1 leaves 1 minterms
T-D C1 (0.25): 4 nodes 1 leaves 1 minterms
T-D C2 (0.25): 4 nodes 1 leaves 1 minterms
TEST-DENSITY:: G100BF (3 variables)
T-D    (1.75): 4 nodes 1 leaves 7 minterms
T-D APA 7
T-D ID (2): 3 nodes 1 leaves 6 minterms
T-D BU (2): 3 nodes 1 leaves 6 minterms
T-D HB (1.75): 4 nodes 1 leaves 7 minterms
T-D SP (1.75): 4 nodes 1 leaves 7 minterms
T-D UA (2): 2 nodes 1 leaves 4 minterms
T-D C1 (2): 3 nodes 1 leaves 6 minterms
T-D C2 (2): 2 nodes 1 leaves 4 minterms
TEST-DENSITY:: G98BF (3 variables)
T-D    (1.75): 4 nodes 1 leaves 7 minterms
T-D APA 7
T-D ID (2): 3 nodes 1 leaves 6 minterms
T-D BU (2): 3 nodes 1 leaves 6 minterms
T-D HB (1.75): 4 nodes 1 leaves 7 minterms
T-D SP (1.75): 4 nodes 1 leaves 7 minterms
T-D UA (2): 2 nodes 1 leaves 4 minterms
T-D C1 (2): 3 nodes 1 leaves 6 minterms
T-D C2 (2): 2 nodes 1 leaves 4 minterms
TEST-DENSITY:: G96BF (3 variables)
T-D    (1.75): 4 nodes 1 leaves 7 minterms
T-D APA 7
T-D ID (2): 3 nodes 1 leaves 6 minterms
T-D BU (2): 3 nodes 1 leaves 6 minterms
T-D HB (1.75): 4 nodes 1 leaves 7 minterms
T-D SP (1.75): 4 nodes 1 leaves 7 minterms
T-D UA (2): 2 nodes 1 leaves 4 minterms
T-D C1 (2): 3 nodes 1 leaves 6 minterms
T-D C2 (2): 2 nodes 1 leaves 4 minterms
TEST-DENSITY:: G92 (4 variables)
T-D    (0.2): 5 nodes 1 leaves 1 minterms
T-D APA 1
T-D ID (0.2): 5 nodes 1 leaves 1 minterms
T-D BU (0.2): 5 nodes 1 leaves 1 minterms
T-D HB (0.2): 5 nodes 1 leaves 1 minterms
T-D SP (0.2): 5 nodes 1 leaves 1 minterms
T-D UA (0.2): 5 nodes 1 leaves 1 minterms
T-D C1 (0.2): 5 nodes 1 leaves 1 minterms
T-D C2 (0.2): 5 nodes 1 leaves 1 minterms
TEST-DENSITY:: G87BF (7 variables)
T-D    (13.125): 8 nodes 1 leaves 105 minterms
T-D APA 105
T-D ID (32): 3 nodes 1 leaves 96 minterms
T-D BU (32): 3 nodes 1 leaves 96 minterms
T-D HB (10.6667): 3 nodes 1 leaves 32 minterms
T-D SP (16): 4 nodes 1 leaves 64 minterms
T-D UA (16): 5 nodes 1 leaves 80 minterms
T-D C1 (32): 3 nodes 1 leaves 96 minterms
T-D C2 (16): 4 nodes 1 leaves 64 minterms
TEST-DENSITY:: G89BF (7 variables)
T-D    (10.5): 10 nodes 1 leaves 105 minterms
T-D APA 105
T-D ID (32): 3 nodes 1 leaves 96 minterms
T-D BU (32): 3 nodes 1 leaves 96 minterms
T-D HB (10.6667): 3 nodes 1 leaves 32 minterms
T-D SP (16): 4 nodes 1 leaves 64 minterms
T-D UA (12): 4 nodes 1 leaves 48 minterms
T-D C1 (32): 3 nodes 1 leaves 96 minterms
T-D C2 (16): 4 nodes 1 leaves 64 minterms
TEST-DENSITY:: G101BF (9 variables)
T-D    (40.75): 12 nodes 1 leaves 489 minterms
T-D APA 489
T-D ID (128): 3 nodes 1 leaves 384 minterms
T-D BU (128): 3 nodes 1 leaves 384 minterms
T-D HB (128): 2 nodes 1 leaves 256 minterms
T-D SP (80): 4 nodes 1 leaves 320 minterms
T-D UA (128): 2 nodes 1 leaves 256 minterms
T-D C1 (128): 3 nodes 1 leaves 384 minterms
T-D C2 (128): 2 nodes 1 leaves 256 minterms
TEST-DENSITY:: G106BF (9 variables)
T-D    (44.1): 10 nodes 1 leaves 441 minterms
T-D APA 441
T-D ID (128): 3 nodes 1 leaves 384 minterms
T-D BU (128): 3 nodes 1 leaves 384 minterms
T-D HB (128): 2 nodes 1 leaves 256 minterms
T-D SP (80): 4 nodes 1 leaves 320 minterms
T-D UA (128): 2 nodes 1 leaves 256 minterms
T-D C1 (128): 3 nodes 1 leaves 384 minterms
T-D C2 (128): 2 nodes 1 leaves 256 minterms
TEST-DENSITY:: G97BF (9 variables)
T-D    (48.9): 10 nodes 1 leaves 489 minterms
T-D APA 489
T-D ID (128): 3 nodes 1 leaves 384 minterms
T-D BU (128): 3 nodes 1 leaves 384 minterms
T-D HB (128): 2 nodes 1 leaves 256 minterms
T-D SP (80): 4 nodes 1 leaves 320 minterms
T-D UA (128): 2 nodes 1 leaves 256 minterms
T-D C1 (128): 3 nodes 1 leaves 384 minterms
T-D C2 (128): 2 nodes 1 leaves 256 minterms
TEST-DENSITY:: G104BF (9 variables)
T-D    (40.0909): 11 nodes 1 leaves 441 minterms
T-D APA 441
T-D ID (128): 3 nodes 1 leaves 384 minterms
T-D BU (128): 3 nodes 1 leaves 384 minterms
T-D HB (128): 2 nodes 1 leaves 256 minterms
T-D SP (80): 4 nodes 1 leaves 320 minterms
T-D UA (128): 2 nodes 1 leaves 256 minterms
T-D C1 (128): 3 nodes 1 leaves 384 minterms
T-D C2 (128): 2 nodes 1 leaves 256 minterms
TEST-DENSITY:: G88BF (11 variables)
T-D    (101.857): 14 nodes 1 leaves 1426 minterms
T-D APA 1426
T-D ID (512): 2 nodes 1 leaves 1024 minterms
T-D BU (512): 2 nodes 1 leaves 1024 minterms
T-D HB (170.667): 3 nodes 1 leaves 512 minterms
T-D SP (170.667): 3 nodes 1 leaves 512 minterms
T-D UA (170.667): 3 nodes 1 leaves 512 minterms
T-D C1 (512): 2 nodes 1 leaves 1024 minterms
T-D C2 (170.667): 3 nodes 1 leaves 512 minterms
TEST-DENSITY:: G99BF (13 variables)
T-D    (473.125): 16 nodes 1 leaves 7570 minterms
T-D APA 7570
T-D ID (2048): 3 nodes 1 leaves 6144 minterms
T-D BU (2048): 3 nodes 1 leaves 6144 minterms
T-D HB (2048): 2 nodes 1 leaves 4096 minterms
T-D SP (1280): 4 nodes 1 leaves 5120 minterms
T-D UA (2048): 2 nodes 1 leaves 4096 minterms
T-D C1 (2048): 3 nodes 1 leaves 6144 minterms
T-D C2 (2048): 2 nodes 1 leaves 4096 minterms
TEST-DENSITY:: G105BF (13 variables)
T-D    (437.125): 16 nodes 1 leaves 6994 minterms
T-D APA 6994
T-D ID (2048): 3 nodes 1 leaves 6144 minterms
T-D BU (2048): 3 nodes 1 leaves 6144 minterms
T-D HB (2048): 2 nodes 1 leaves 4096 minterms
T-D SP (1280): 4 nodes 1 leaves 5120 minterms
T-D UA (2048): 2 nodes 1 leaves 4096 minterms
T-D C1 (2048): 3 nodes 1 leaves 6144 minterms
T-D C2 (2048): 2 nodes 1 leaves 4096 minterms
TEST-DENSITY:: G86BF (17 variables)
T-D    (2303.68): 38 nodes 1 leaves 87540 minterms
T-D APA 87540
T-D ID (32768): 2 nodes 1 leaves 65536 minterms
T-D BU (32768): 2 nodes 1 leaves 65536 minterms
T-D HB (10922.7): 3 nodes 1 leaves 32768 minterms
T-D SP (10922.7): 3 nodes 1 leaves 32768 minterms
T-D UA (4915.2): 5 nodes 1 leaves 24576 minterms
T-D C1 (32768): 2 nodes 1 leaves 65536 minterms
T-D C2 (10922.7): 3 nodes 1 leaves 32768 minterms
TEST-DENSITY:: G95BF (19 variables)
T-D    (11725.8): 41 nodes 1 leaves 480756 minterms
T-D APA 480756
T-D ID (131072): 3 nodes 1 leaves 393216 minterms
T-D BU (131072): 3 nodes 1 leaves 393216 minterms
T-D HB (131072): 2 nodes 1 leaves 262144 minterms
T-D SP (81920): 4 nodes 1 leaves 327680 minterms
T-D UA (131072): 2 nodes 1 leaves 262144 minterms
T-D C1 (131072): 3 nodes 1 leaves 393216 minterms
T-D C2 (131072): 2 nodes 1 leaves 262144 minterms
TEST-DENSITY:: G103BF (19 variables)
T-D    (11174.1): 40 nodes 1 leaves 446964 minterms
T-D APA 446964
T-D ID (131072): 3 nodes 1 leaves 393216 minterms
T-D BU (131072): 3 nodes 1 leaves 393216 minterms
T-D HB (131072): 2 nodes 1 leaves 262144 minterms
T-D SP (81920): 4 nodes 1 leaves 327680 minterms
T-D UA (131072): 2 nodes 1 leaves 262144 minterms
T-D C1 (131072): 3 nodes 1 leaves 393216 minterms
T-D C2 (131072): 2 nodes 1 leaves 262144 minterms
TEST-DENSITY:: G90 (27 variables)
T-D    (599725): 55 nodes 1 leaves 3.29849e+07 minterms
T-D APA 32984868
T-D ID (1.92239e+06): 12 nodes 1 leaves 2.30687e+07 minterms
T-D BU (1.41476e+06): 20 nodes 1 leaves 2.82952e+07 minterms
T-D HB (4.1943e+06): 4 nodes 1 leaves 1.67772e+07 minterms
T-D SP (1.97616e+06): 13 nodes 1 leaves 2.56901e+07 minterms
T-D UA (4.1943e+06): 4 nodes 1 leaves 1.67772e+07 minterms
T-D C1 (1.92239e+06): 12 nodes 1 leaves 2.30687e+07 minterms
T-D C2 (4.1943e+06): 4 nodes 1 leaves 1.67772e+07 minterms
TEST-DENSITY:: G380 (18 variables)
T-D    (1982.67): 39 nodes 1 leaves 77324 minterms
T-D APA 77324
T-D ID (21845.3): 3 nodes 1 leaves 65536 minterms
T-D BU (21845.3): 3 nodes 1 leaves 65536 minterms
T-D HB (21845.3): 3 nodes 1 leaves 65536 minterms
T-D SP (7509.33): 9 nodes 1 leaves 67584 minterms
T-D UA (21845.3): 3 nodes 1 leaves 65536 minterms
T-D C1 (21845.3): 3 nodes 1 leaves 65536 minterms
T-D C2 (21845.3): 3 nodes 1 leaves 65536 minterms
TEST-DENSITY:: G262 (15 variables)
T-D    (49.3214): 28 nodes 1 leaves 1381 minterms
T-D APA 1381
T-D ID (170.667): 6 nodes 1 leaves 1024 minterms
T-D BU (170.667): 6 nodes 1 leaves 1024 minterms
T-D HB (170.667): 6 nodes 1 leaves 1024 minterms
T-D SP (77.7143): 14 nodes 1 leaves 1088 minterms
T-D UA (170.667): 6 nodes 1 leaves 1024 minterms
T-D C1 (170.667): 6 nodes 1 leaves 1024 minterms
T-D C2 (170.667): 6 nodes 1 leaves 1024 minterms
TEST-DENSITY:: G394 (12 variables)
T-D    (79.8667): 15 nodes 1 leaves 1198 minterms
T-D APA 1198
T-D ID (341.333): 3 nodes 1 leaves 1024 minterms
T-D BU (341.333): 3 nodes 1 leaves 1024 minterms
T-D HB (341.333): 3 nodes 1 leaves 1024 minterms
T-D SP (132): 8 nodes 1 leaves 1056 minterms
T-D UA (341.333): 3 nodes 1 leaves 1024 minterms
T-D C1 (341.333): 3 nodes 1 leaves 1024 minterms
T-D C2 (341.333): 3 nodes 1 leaves 1024 minterms
TEST-DENSITY:: G250 (9 variables)
T-D    (7.1): 10 nodes 1 leaves 71 minterms
T-D APA 71
T-D ID (16): 4 nodes 1 leaves 64 minterms
T-D BU (16): 4 nodes 1 leaves 64 minterms
T-D HB (16): 4 nodes 1 leaves 64 minterms
T-D SP (8.5): 8 nodes 1 leaves 68 minterms
T-D UA (16): 4 nodes 1 leaves 64 minterms
T-D C1 (16): 4 nodes 1 leaves 64 minterms
T-D C2 (16): 4 nodes 1 leaves 64 minterms
TEST-DENSITY:: G122 (8 variables)
T-D    (2.09091): 11 nodes 1 leaves 23 minterms
T-D APA 23
T-D ID (3.2): 5 nodes 1 leaves 16 minterms
T-D BU (3.2): 5 nodes 1 leaves 16 minterms
T-D HB (3.2): 5 nodes 1 leaves 16 minterms
T-D SP (2.22222): 9 nodes 1 leaves 20 minterms
T-D UA (3.2): 5 nodes 1 leaves 16 minterms
T-D C1 (3.2): 5 nodes 1 leaves 16 minterms
T-D C2 (3.2): 5 nodes 1 leaves 16 minterms
TEST-DENSITY:: G133 (14 variables)
T-D    (314.118): 17 nodes 1 leaves 5340 minterms
T-D APA 5340
T-D ID (327.111): 9 nodes 1 leaves 2944 minterms
T-D BU (396.8): 10 nodes 1 leaves 3968 minterms
T-D HB (327.111): 9 nodes 1 leaves 2944 minterms
T-D SP (396.8): 10 nodes 1 leaves 3968 minterms
T-D UA (327.111): 9 nodes 1 leaves 2944 minterms
T-D C1 (327.111): 9 nodes 1 leaves 2944 minterms
T-D C2 (396.8): 10 nodes 1 leaves 3968 minterms
TEST-DENSITY:: G138 (14 variables)
T-D    (759.412): 17 nodes 1 leaves 12910 minterms
T-D APA 12910
T-D ID (4096): 3 nodes 1 leaves 12288 minterms
T-D BU (4096): 3 nodes 1 leaves 12288 minterms
T-D HB (204.8): 5 nodes 1 leaves 1024 minterms
T-D SP (512): 4 nodes 1 leaves 2048 minterms
T-D UA (966.4): 10 nodes 1 leaves 9664 minterms
T-D C1 (4096): 3 nodes 1 leaves 12288 minterms
T-D C2 (4096): 2 nodes 1 leaves 8192 minterms
TEST-DENSITY:: G139 (10 variables)
T-D    (27.4545): 11 nodes 1 leaves 302 minterms
T-D APA 302
T-D ID (28): 8 nodes 1 leaves 224 minterms
T-D BU (27.4545): 11 nodes 1 leaves 302 minterms
T-D HB (22.8571): 7 nodes 1 leaves 160 minterms
T-D SP (29.3333): 9 nodes 1 leaves 264 minterms
T-D UA (28): 8 nodes 1 leaves 224 minterms
T-D C1 (28): 8 nodes 1 leaves 224 minterms
T-D C2 (28): 8 nodes 1 leaves 224 minterms
TEST-DENSITY:: G140 (10 variables)
T-D    (71.9091): 11 nodes 1 leaves 791 minterms
T-D APA 791
T-D ID (256): 3 nodes 1 leaves 768 minterms
T-D BU (256): 3 nodes 1 leaves 768 minterms
T-D HB (12.8): 5 nodes 1 leaves 64 minterms
T-D SP (51.2): 5 nodes 1 leaves 256 minterms
T-D UA (74): 8 nodes 1 leaves 592 minterms
T-D C1 (256): 3 nodes 1 leaves 768 minterms
T-D C2 (256): 2 nodes 1 leaves 512 minterms
TEST-DENSITY:: G141 (20 variables)
T-D    (6715.54): 52 nodes 1 leaves 349208 minterms
T-D APA 349208
T-D ID (16384): 6 nodes 1 leaves 98304 minterms
T-D BU (14745.6): 10 nodes 1 leaves 147456 minterms
T-D HB (11702.9): 7 nodes 1 leaves 81920 minterms
T-D SP (14043.4): 7 nodes 1 leaves 98304 minterms
T-D UA (15360): 8 nodes 1 leaves 122880 minterms
T-D C1 (16384): 6 nodes 1 leaves 98304 minterms
T-D C2 (14043.4): 7 nodes 1 leaves 98304 minterms
TEST-DENSITY:: G142 (20 variables)
T-D    (18443.6): 45 nodes 1 leaves 829964 minterms
T-D APA 829964
T-D ID (262144): 3 nodes 1 leaves 786432 minterms
T-D BU (262144): 3 nodes 1 leaves 786432 minterms
T-D HB (13107.2): 5 nodes 1 leaves 65536 minterms
T-D SP (32768): 4 nodes 1 leaves 131072 minterms
T-D UA (49152): 7 nodes 1 leaves 344064 minterms
T-D C1 (262144): 3 nodes 1 leaves 786432 minterms
T-D C2 (262144): 2 nodes 1 leaves 524288 minterms
TEST-DENSITY:: G125 (22 variables)
T-D    (11894.8): 78 nodes 1 leaves 927796 minterms
T-D APA 927796
T-D ID (157286): 5 nodes 1 leaves 786432 minterms
T-D BU (157286): 5 nodes 1 leaves 786432 minterms
T-D HB (52428.8): 5 nodes 1 leaves 262144 minterms
T-D SP (65536): 6 nodes 1 leaves 393216 minterms
T-D UA (65536): 6 nodes 1 leaves 393216 minterms
T-D C1 (157286): 5 nodes 1 leaves 786432 minterms
T-D C2 (157286): 5 nodes 1 leaves 786432 minterms
TEST-DENSITY:: G126 (22 variables)
T-D    (15155.4): 58 nodes 1 leaves 879012 minterms
T-D APA 879012
T-D ID (131072): 4 nodes 1 leaves 524288 minterms
T-D BU (131072): 4 nodes 1 leaves 524288 minterms
T-D HB (131072): 4 nodes 1 leaves 524288 minterms
T-D SP (131072): 4 nodes 1 leaves 524288 minterms
T-D UA (87381.3): 6 nodes 1 leaves 524288 minterms
T-D C1 (131072): 4 nodes 1 leaves 524288 minterms
T-D C2 (131072): 4 nodes 1 leaves 524288 minterms
TEST-DENSITY:: G127 (22 variables)
T-D    (13692): 67 nodes 1 leaves 917364 minterms
T-D APA 917364
T-D ID (131072): 4 nodes 1 leaves 524288 minterms
T-D BU (131072): 4 nodes 1 leaves 524288 minterms
T-D HB (65536): 6 nodes 1 leaves 393216 minterms
T-D SP (87381.3): 6 nodes 1 leaves 524288 minterms
T-D UA (87381.3): 6 nodes 1 leaves 524288 minterms
T-D C1 (131072): 4 nodes 1 leaves 524288 minterms
T-D C2 (157286): 5 nodes 1 leaves 786432 minterms
TEST-DENSITY:: G128 (20 variables)
T-D    (3404.18): 66 nodes 1 leaves 224676 minterms
T-D APA 224676
T-D ID (32768): 4 nodes 1 leaves 131072 minterms
T-D BU (32768): 4 nodes 1 leaves 131072 minterms
T-D HB (32768): 4 nodes 1 leaves 131072 minterms
T-D SP (16384): 8 nodes 1 leaves 131072 minterms
T-D UA (13107.2): 5 nodes 1 leaves 65536 minterms
T-D C1 (32768): 4 nodes 1 leaves 131072 minterms
T-D C2 (28086.9): 7 nodes 1 leaves 196608 minterms
TEST-DENSITY:: G129 (18 variables)
T-D    (154.512): 43 nodes 1 leaves 6644 minterms
T-D APA 6644
T-D ID (585.143): 7 nodes 1 leaves 4096 minterms
T-D BU (585.143): 7 nodes 1 leaves 4096 minterms
T-D HB (585.143): 7 nodes 1 leaves 4096 minterms
T-D SP (272): 16 nodes 1 leaves 4352 minterms
T-D UA (585.143): 7 nodes 1 leaves 4096 minterms
T-D C1 (585.143): 7 nodes 1 leaves 4096 minterms
T-D C2 (585.143): 7 nodes 1 leaves 4096 minterms
TEST-DENSITY:: G130 (15 variables)
T-D    (49.3214): 28 nodes 1 leaves 1381 minterms
T-D APA 1381
T-D ID (170.667): 6 nodes 1 leaves 1024 minterms
T-D BU (170.667): 6 nodes 1 leaves 1024 minterms
T-D HB (170.667): 6 nodes 1 leaves 1024 minterms
T-D SP (77.7143): 14 nodes 1 leaves 1088 minterms
T-D UA (170.667): 6 nodes 1 leaves 1024 minterms
T-D C1 (170.667): 6 nodes 1 leaves 1024 minterms
T-D C2 (170.667): 6 nodes 1 leaves 1024 minterms
TEST-DENSITY:: G131 (12 variables)
T-D    (18): 17 nodes 1 leaves 306 minterms
T-D APA 306
T-D ID (51.2): 5 nodes 1 leaves 256 minterms
T-D BU (51.2): 5 nodes 1 leaves 256 minterms
T-D HB (51.2): 5 nodes 1 leaves 256 minterms
T-D SP (24.7273): 11 nodes 1 leaves 272 minterms
T-D UA (51.2): 5 nodes 1 leaves 256 minterms
T-D C1 (51.2): 5 nodes 1 leaves 256 minterms
T-D C2 (51.2): 5 nodes 1 leaves 256 minterms
TEST-DENSITY:: G132 (9 variables)
T-D    (7.1): 10 nodes 1 leaves 71 minterms
T-D APA 71
T-D ID (16): 4 nodes 1 leaves 64 minterms
T-D BU (16): 4 nodes 1 leaves 64 minterms
T-D HB (16): 4 nodes 1 leaves 64 minterms
T-D SP (8.5): 8 nodes 1 leaves 68 minterms
T-D UA (16): 4 nodes 1 leaves 64 minterms
T-D C1 (16): 4 nodes 1 leaves 64 minterms
T-D C2 (16): 4 nodes 1 leaves 64 minterms
Testing BDD decomposition algorithms
TEST-DECOMP:: G91 (1 variables)
T-d    : 2 nodes 1 leaves 1 minterms
T-d SS : 2 nodes
T-d GS : 2 nodes 1 leaves 1 minterms
T-d HS : 1 nodes 1 leaves 2 minterms
T-d SI : 2 nodes
T-d GI : 2 nodes 1 leaves 1 minterms
T-d HI : 1 nodes 1 leaves 2 minterms
T-d SD : 2 nodes
T-d GD : 2 nodes 1 leaves 1 minterms
T-d HD : 1 nodes 1 leaves 2 minterms
T-d SQ : 2 nodes
T-d GQ : 2 nodes 1 leaves 1 minterms
T-d HQ : 1 nodes 1 leaves 2 minterms
TEST-DECOMP:: G94 (1 variables)
T-d    : 2 nodes 1 leaves 1 minterms
T-d SS : 2 nodes
T-d GS : 2 nodes 1 leaves 1 minterms
T-d HS : 1 nodes 1 leaves 2 minterms
T-d SI : 2 nodes
T-d GI : 2 nodes 1 leaves 1 minterms
T-d HI : 1 nodes 1 leaves 2 minterms
T-d SD : 2 nodes
T-d GD : 2 nodes 1 leaves 1 minterms
T-d HD : 1 nodes 1 leaves 2 minterms
T-d SQ : 2 nodes
T-d GQ : 2 nodes 1 leaves 1 minterms
T-d HQ : 1 nodes 1 leaves 2 minterms
TEST-DECOMP:: G107 (3 variables)
T-d    : 4 nodes 1 leaves 1 minterms
T-d SS : 4 nodes
T-d GS : 3 nodes 1 leaves 2 minterms
T-d HS : 2 nodes 1 leaves 4 minterms
T-d SI : 4 nodes
T-d GI : 4 nodes 1 leaves 1 minterms
T-d HI : 1 nodes 1 leaves 8 minterms
T-d SD : 4 nodes
T-d GD : 4 nodes 1 leaves 1 minterms
T-d HD : 1 nodes 1 leaves 8 minterms
T-d SQ : 5 nodes
T-d GQ : 2 nodes 1 leaves 4 minterms
T-d HQ : 4 nodes 1 leaves 5 minterms
TEST-DECOMP:: G83 (3 variables)
T-d    : 4 nodes 1 leaves 1 minterms
T-d SS : 4 nodes
T-d GS : 3 nodes 1 leaves 2 minterms
T-d HS : 2 nodes 1 leaves 4 minterms
T-d SI : 4 nodes
T-d GI : 4 nodes 1 leaves 1 minterms
T-d HI : 1 nodes 1 leaves 8 minterms
T-d SD : 4 nodes
T-d GD : 4 nodes 1 leaves 1 minterms
T-d HD : 1 nodes 1 leaves 8 minterms
T-d SQ : 5 nodes
T-d GQ : 4 nodes 1 leaves 5 minterms
T-d HQ : 2 nodes 1 leaves 4 minterms
TEST-DECOMP:: G84 (3 variables)
T-d    : 4 nodes 1 leaves 1 minterms
T-d SS : 4 nodes
T-d GS : 3 nodes 1 leaves 2 minterms
T-d HS : 2 nodes 1 leaves 4 minterms
T-d SI : 4 nodes
T-d GI : 4 nodes 1 leaves 1 minterms
T-d HI : 1 nodes 1 leaves 8 minterms
T-d SD : 4 nodes
T-d GD : 4 nodes 1 leaves 1 minterms
T-d HD : 1 nodes 1 leaves 8 minterms
T-d SQ : 5 nodes
T-d GQ : 2 nodes 1 leaves 4 minterms
T-d HQ : 4 nodes 1 leaves 5 minterms
TEST-DECOMP:: G85 (3 variables)
T-d    : 4 nodes 1 leaves 1 minterms
T-d SS : 4 nodes
T-d GS : 3 nodes 1 leaves 2 minterms
T-d HS : 2 nodes 1 leaves 4 minterms
T-d SI : 4 nodes
T-d GI : 4 nodes 1 leaves 1 minterms
T-d HI : 1 nodes 1 leaves 8 minterms
T-d SD : 4 nodes
T-d GD : 4 nodes 1 leaves 1 minterms
T-d HD : 1 nodes 1 leaves 8 minterms
T-d SQ : 5 nodes
T-d GQ : 2 nodes 1 leaves 4 minterms
T-d HQ : 4 nodes 1 leaves 5 minterms
TEST-DECOMP:: G100BF (3 variables)
T-d    : 4 nodes 1 leaves 7 minterms
T-d SS : 4 nodes
T-d GS : 4 nodes 1 leaves 7 minterms
T-d HS : 1 nodes 1 leaves 8 minterms
T-d SI : 4 nodes
T-d GI : 4 nodes 1 leaves 7 minterms
T-d HI : 1 nodes 1 leaves 8 minterms
T-d SD : 4 nodes
T-d GD : 4 nodes 1 leaves 7 minterms
T-d HD : 1 nodes 1 leaves 8 minterms
T-d SQ : 4 nodes
T-d GQ : 4 nodes 1 leaves 7 minterms
T-d HQ : 1 nodes 1 leaves 8 minterms
TEST-DECOMP:: G98BF (3 variables)
T-d    : 4 nodes 1 leaves 7 minterms
T-d SS : 4 nodes
T-d GS : 4 nodes 1 leaves 7 minterms
T-d HS : 1 nodes 1 leaves 8 minterms
T-d SI : 4 nodes
T-d GI : 4 nodes 1 leaves 7 minterms
T-d HI : 1 nodes 1 leaves 8 minterms
T-d SD : 4 nodes
T-d GD : 4 nodes 1 leaves 7 minterms
T-d HD : 1 nodes 1 leaves 8 minterms
T-d SQ : 4 nodes
T-d GQ : 4 nodes 1 leaves 7 minterms
T-d HQ : 1 nodes 1 leaves 8 minterms
TEST-DECOMP:: G96BF (3 variables)
T-d    : 4 nodes 1 leaves 7 minterms
T-d SS : 4 nodes
T-d GS : 4 nodes 1 leaves 7 minterms
T-d HS : 1 nodes 1 leaves 8 minterms
T-d SI : 4 nodes
T-d GI : 4 nodes 1 leaves 7 minterms
T-d HI : 1 nodes 1 leaves 8 minterms
T-d SD : 4 nodes
T-d GD : 4 nodes 1 leaves 7 minterms
T-d HD : 1 nodes 1 leaves 8 minterms
T-d SQ : 4 nodes
T-d GQ : 4 nodes 1 leaves 7 minterms
T-d HQ : 1 nodes 1 leaves 8 minterms
TEST-DECOMP:: G92 (4 variables)
T-d    : 5 nodes 1 leaves 1 minterms
T-d SS : 5 nodes
T-d GS : 3 nodes 1 leaves 4 minterms
T-d HS : 3 nodes 1 leaves 4 minterms
T-d SI : 5 nodes
T-d GI : 5 nodes 1 leaves 1 minterms
T-d HI : 1 nodes 1 leaves 16 minterms
T-d SD : 5 nodes
T-d GD : 5 nodes 1 leaves 1 minterms
T-d HD : 1 nodes 1 leaves 16 minterms
T-d SQ : 6 nodes
T-d GQ : 2 nodes 1 leaves 8 minterms
T-d HQ : 5 nodes 1 leaves 9 minterms
TEST-DECOMP:: G87BF (7 variables)
T-d    : 8 nodes 1 leaves 105 minterms
T-d SS : 9 nodes
T-d GS : 4 nodes 1 leaves 112 minterms
T-d HS : 8 nodes 1 leaves 121 minterms
T-d SI : 8 nodes
T-d GI : 8 nodes 1 leaves 105 minterms
T-d HI : 1 nodes 1 leaves 128 minterms
T-d SD : 8 nodes
T-d GD : 8 nodes 1 leaves 105 minterms
T-d HD : 1 nodes 1 leaves 128 minterms
T-d SQ : 9 nodes
T-d GQ : 8 nodes 1 leaves 121 minterms
T-d HQ : 4 nodes 1 leaves 112 minterms
TEST-DECOMP:: G89BF (7 variables)
T-d    : 10 nodes 1 leaves 105 minterms
T-d SS : 11 nodes
T-d GS : 4 nodes 1 leaves 112 minterms
T-d HS : 8 nodes 1 leaves 121 minterms
T-d SI : 10 nodes
T-d GI : 10 nodes 1 leaves 105 minterms
T-d HI : 1 nodes 1 leaves 128 minterms
T-d SD : 14 nodes
T-d GD : 7 nodes 1 leaves 122 minterms
T-d HD : 8 nodes 1 leaves 108 minterms
T-d SQ : 11 nodes
T-d GQ : 8 nodes 1 leaves 121 minterms
T-d HQ : 4 nodes 1 leaves 112 minterms
TEST-DECOMP:: G101BF (9 variables)
T-d    : 12 nodes 1 leaves 489 minterms
T-d SS : 14 nodes
T-d GS : 6 nodes 1 leaves 496 minterms
T-d HS : 10 nodes 1 leaves 505 minterms
T-d SI : 12 nodes
T-d GI : 12 nodes 1 leaves 489 minterms
T-d HI : 1 nodes 1 leaves 512 minterms
T-d SD : 12 nodes
T-d GD : 12 nodes 1 leaves 489 minterms
T-d HD : 1 nodes 1 leaves 512 minterms
T-d SQ : 14 nodes
T-d GQ : 10 nodes 1 leaves 505 minterms
T-d HQ : 6 nodes 1 leaves 496 minterms
TEST-DECOMP:: G106BF (9 variables)
T-d    : 10 nodes 1 leaves 441 minterms
T-d SS : 12 nodes
T-d GS : 4 nodes 1 leaves 448 minterms
T-d HS : 10 nodes 1 leaves 505 minterms
T-d SI : 10 nodes
T-d GI : 10 nodes 1 leaves 441 minterms
T-d HI : 1 nodes 1 leaves 512 minterms
T-d SD : 10 nodes
T-d GD : 10 nodes 1 leaves 441 minterms
T-d HD : 1 nodes 1 leaves 512 minterms
T-d SQ : 10 nodes
T-d GQ : 10 nodes 1 leaves 441 minterms
T-d HQ : 1 nodes 1 leaves 512 minterms
TEST-DECOMP:: G97BF (9 variables)
T-d    : 10 nodes 1 leaves 489 minterms
T-d SS : 12 nodes
T-d GS : 6 nodes 1 leaves 496 minterms
T-d HS : 10 nodes 1 leaves 505 minterms
T-d SI : 10 nodes
T-d GI : 10 nodes 1 leaves 489 minterms
T-d HI : 1 nodes 1 leaves 512 minterms
T-d SD : 10 nodes
T-d GD : 10 nodes 1 leaves 489 minterms
T-d HD : 1 nodes 1 leaves 512 minterms
T-d SQ : 10 nodes
T-d GQ : 10 nodes 1 leaves 489 minterms
T-d HQ : 1 nodes 1 leaves 512 minterms
TEST-DECOMP:: G104BF (9 variables)
T-d    : 11 nodes 1 leaves 441 minterms
T-d SS : 13 nodes
T-d GS : 4 nodes 1 leaves 448 minterms
T-d HS : 10 nodes 1 leaves 505 minterms
T-d SI : 11 nodes
T-d GI : 11 nodes 1 leaves 441 minterms
T-d HI : 1 nodes 1 leaves 512 minterms
T-d SD : 13 nodes
T-d GD : 4 nodes 1 leaves 448 minterms
T-d HD : 10 nodes 1 leaves 505 minterms
T-d SQ : 13 nodes
T-d GQ : 10 nodes 1 leaves 505 minterms
T-d HQ : 4 nodes 1 leaves 448 minterms
TEST-DECOMP:: G88BF (11 variables)
T-d    : 14 nodes 1 leaves 1426 minterms
T-d SS : 14 nodes
T-d GS : 14 nodes 1 leaves 1426 minterms
T-d HS : 1 nodes 1 leaves 2048 minterms
T-d SI : 14 nodes
T-d GI : 14 nodes 1 leaves 1426 minterms
T-d HI : 1 nodes 1 leaves 2048 minterms
T-d SD : 14 nodes
T-d GD : 14 nodes 1 leaves 1426 minterms
T-d HD : 1 nodes 1 leaves 2048 minterms
T-d SQ : 21 nodes
T-d GQ : 15 nodes 1 leaves 1750 minterms
T-d HQ : 11 nodes 1 leaves 1724 minterms
TEST-DECOMP:: G99BF (13 variables)
T-d    : 16 nodes 1 leaves 7570 minterms
T-d SS : 18 nodes
T-d GS : 8 nodes 1 leaves 7744 minterms
T-d HS : 16 nodes 1 leaves 8018 minterms
T-d SI : 16 nodes
T-d GI : 16 nodes 1 leaves 7570 minterms
T-d HI : 1 nodes 1 leaves 8192 minterms
T-d SD : 16 nodes
T-d GD : 16 nodes 1 leaves 7570 minterms
T-d HD : 1 nodes 1 leaves 8192 minterms
T-d SQ : 24 nodes
T-d GQ : 17 nodes 1 leaves 7894 minterms
T-d HQ : 13 nodes 1 leaves 7868 minterms
TEST-DECOMP:: G105BF (13 variables)
T-d    : 16 nodes 1 leaves 6994 minterms
T-d SS : 18 nodes
T-d GS : 4 nodes 1 leaves 7168 minterms
T-d HS : 16 nodes 1 leaves 8018 minterms
T-d SI : 16 nodes
T-d GI : 16 nodes 1 leaves 6994 minterms
T-d HI : 1 nodes 1 leaves 8192 minterms
T-d SD : 16 nodes
T-d GD : 16 nodes 1 leaves 6994 minterms
T-d HD : 1 nodes 1 leaves 8192 minterms
T-d SQ : 25 nodes
T-d GQ : 17 nodes 1 leaves 7606 minterms
T-d HQ : 14 nodes 1 leaves 7580 minterms
TEST-DECOMP:: G86BF (17 variables)
T-d    : 38 nodes 1 leaves 87540 minterms
T-d SS : 38 nodes
T-d GS : 5 nodes 1 leaves 106496 minterms
T-d HS : 36 nodes 1 leaves 90612 minterms
T-d SI : 38 nodes
T-d GI : 5 nodes 1 leaves 106496 minterms
T-d HI : 36 nodes 1 leaves 90612 minterms
T-d SD : 49 nodes
T-d GD : 27 nodes 1 leaves 130476 minterms
T-d HD : 26 nodes 1 leaves 88136 minterms
T-d SQ : 48 nodes
T-d GQ : 32 nodes 1 leaves 109972 minterms
T-d HQ : 35 nodes 1 leaves 108640 minterms
TEST-DECOMP:: G95BF (19 variables)
T-d    : 41 nodes 1 leaves 480756 minterms
T-d SS : 43 nodes
T-d GS : 8 nodes 1 leaves 495616 minterms
T-d HS : 39 nodes 1 leaves 487924 minterms
T-d SI : 41 nodes
T-d GI : 41 nodes 1 leaves 480756 minterms
T-d HI : 1 nodes 1 leaves 524288 minterms
T-d SD : 59 nodes
T-d GD : 36 nodes 1 leaves 520672 minterms
T-d HD : 29 nodes 1 leaves 484372 minterms
T-d SQ : 52 nodes
T-d GQ : 35 nodes 1 leaves 503188 minterms
T-d HQ : 38 nodes 1 leaves 501856 minterms
TEST-DECOMP:: G103BF (19 variables)
T-d    : 40 nodes 1 leaves 446964 minterms
T-d SS : 42 nodes
T-d GS : 4 nodes 1 leaves 458752 minterms
T-d HS : 39 nodes 1 leaves 512500 minterms
T-d SI : 40 nodes
T-d GI : 40 nodes 1 leaves 446964 minterms
T-d HI : 1 nodes 1 leaves 524288 minterms
T-d SD : 54 nodes
T-d GD : 19 nodes 1 leaves 447616 minterms
T-d HD : 37 nodes 1 leaves 523636 minterms
T-d SQ : 55 nodes
T-d GQ : 39 nodes 1 leaves 486454 minterms
T-d HQ : 36 nodes 1 leaves 484798 minterms
TEST-DECOMP:: G90 (27 variables)
T-d    : 55 nodes 1 leaves 3.29849e+07 minterms
T-d SS : 55 nodes
T-d GS : 3 nodes 1 leaves 3.35544e+07 minterms
T-d HS : 53 nodes 1 leaves 1.31939e+08 minterms
T-d SI : 55 nodes
T-d GI : 3 nodes 1 leaves 3.35544e+07 minterms
T-d HI : 53 nodes 1 leaves 1.31939e+08 minterms
T-d SD : 56 nodes
T-d GD : 28 nodes 1 leaves 3.32472e+07 minterms
T-d HD : 31 nodes 1 leaves 1.33168e+08 minterms
T-d SQ : 59 nodes
T-d GQ : 35 nodes 1 leaves 8.33167e+07 minterms
T-d HQ : 28 nodes 1 leaves 8.38859e+07 minterms
TEST-DECOMP:: G380 (18 variables)
T-d    : 39 nodes 1 leaves 77324 minterms
T-d SS : 35 nodes
T-d GS : 2 nodes 1 leaves 131072 minterms
T-d HS : 34 nodes 1 leaves 154648 minterms
T-d SI : 35 nodes
T-d GI : 2 nodes 1 leaves 131072 minterms
T-d HI : 34 nodes 1 leaves 154648 minterms
T-d SD : 54 nodes
T-d GD : 30 nodes 1 leaves 115720 minterms
T-d HD : 32 nodes 1 leaves 164480 minterms
T-d SQ : 54 nodes
T-d GQ : 39 nodes 1 leaves 168906 minterms
T-d HQ : 36 nodes 1 leaves 170562 minterms
TEST-DECOMP:: G262 (15 variables)
T-d    : 28 nodes 1 leaves 1381 minterms
T-d SS : 29 nodes
T-d GS : 4 nodes 1 leaves 20480 minterms
T-d HS : 26 nodes 1 leaves 4453 minterms
T-d SI : 28 nodes
T-d GI : 28 nodes 1 leaves 1381 minterms
T-d HI : 1 nodes 1 leaves 32768 minterms
T-d SD : 37 nodes
T-d GD : 19 nodes 1 leaves 9424 minterms
T-d HD : 19 nodes 1 leaves 7200 minterms
T-d SQ : 36 nodes
T-d GQ : 23 nodes 1 leaves 17608 minterms
T-d HQ : 24 nodes 1 leaves 16541 minterms
TEST-DECOMP:: G394 (12 variables)
T-d    : 15 nodes 1 leaves 1198 minterms
T-d SS : 15 nodes
T-d GS : 2 nodes 1 leaves 2048 minterms
T-d HS : 14 nodes 1 leaves 2396 minterms
T-d SI : 15 nodes
T-d GI : 2 nodes 1 leaves 2048 minterms
T-d HI : 14 nodes 1 leaves 2396 minterms
T-d SD : 16 nodes
T-d GD : 8 nodes 1 leaves 2272 minterms
T-d HD : 10 nodes 1 leaves 2608 minterms
T-d SQ : 24 nodes
T-d GQ : 17 nodes 1 leaves 2634 minterms
T-d HQ : 14 nodes 1 leaves 2660 minterms
TEST-DECOMP:: G250 (9 variables)
T-d    : 10 nodes 1 leaves 71 minterms
T-d SS : 10 nodes
T-d GS : 3 nodes 1 leaves 128 minterms
T-d HS : 8 nodes 1 leaves 284 minterms
T-d SI : 10 nodes
T-d GI : 3 nodes 1 leaves 128 minterms
T-d HI : 8 nodes 1 leaves 284 minterms
T-d SD : 11 nodes
T-d GD : 7 nodes 1 leaves 72 minterms
T-d HD : 5 nodes 1 leaves 480 minterms
T-d SQ : 11 nodes
T-d GQ : 10 nodes 1 leaves 263 minterms
T-d HQ : 4 nodes 1 leaves 320 minterms
TEST-DECOMP:: G122 (8 variables)
T-d    : 11 nodes 1 leaves 23 minterms
T-d SS : 10 nodes
T-d GS : 3 nodes 1 leaves 64 minterms
T-d HS : 8 nodes 1 leaves 92 minterms
T-d SI : 9 nodes
T-d GI : 4 nodes 1 leaves 32 minterms
T-d HI : 6 nodes 1 leaves 184 minterms
T-d SD : 12 nodes
T-d GD : 7 nodes 1 leaves 48 minterms
T-d HD : 7 nodes 1 leaves 120 minterms
T-d SQ : 12 nodes
T-d GQ : 9 nodes 1 leaves 135 minterms
T-d HQ : 5 nodes 1 leaves 144 minterms
TEST-DECOMP:: G133 (14 variables)
T-d    : 17 nodes 1 leaves 5340 minterms
T-d SS : 19 nodes
T-d GS : 10 nodes 1 leaves 8064 minterms
T-d HS : 17 nodes 1 leaves 13660 minterms
T-d SI : 17 nodes
T-d GI : 17 nodes 1 leaves 5340 minterms
T-d HI : 1 nodes 1 leaves 16384 minterms
T-d SD : 19 nodes
T-d GD : 10 nodes 1 leaves 8064 minterms
T-d HD : 17 nodes 1 leaves 13660 minterms
T-d SQ : 26 nodes
T-d GQ : 19 nodes 1 leaves 10836 minterms
T-d HQ : 15 nodes 1 leaves 10888 minterms
TEST-DECOMP:: G138 (14 variables)
T-d    : 17 nodes 1 leaves 12910 minterms
T-d SS : 17 nodes
T-d GS : 5 nodes 1 leaves 13312 minterms
T-d HS : 15 nodes 1 leaves 14776 minterms
T-d SI : 17 nodes
T-d GI : 5 nodes 1 leaves 13312 minterms
T-d HI : 15 nodes 1 leaves 14776 minterms
T-d SD : 17 nodes
T-d GD : 17 nodes 1 leaves 12910 minterms
T-d HD : 1 nodes 1 leaves 16384 minterms
T-d SQ : 26 nodes
T-d GQ : 19 nodes 1 leaves 14634 minterms
T-d HQ : 15 nodes 1 leaves 14660 minterms
TEST-DECOMP:: G139 (10 variables)
T-d    : 11 nodes 1 leaves 302 minterms
T-d SS : 13 nodes
T-d GS : 5 nodes 1 leaves 832 minterms
T-d HS : 11 nodes 1 leaves 494 minterms
T-d SI : 11 nodes
T-d GI : 11 nodes 1 leaves 302 minterms
T-d HI : 1 nodes 1 leaves 1024 minterms
T-d SD : 11 nodes
T-d GD : 11 nodes 1 leaves 302 minterms
T-d HD : 1 nodes 1 leaves 1024 minterms
T-d SQ : 12 nodes
T-d GQ : 11 nodes 1 leaves 654 minterms
T-d HQ : 7 nodes 1 leaves 672 minterms
TEST-DECOMP:: G140 (10 variables)
T-d    : 11 nodes 1 leaves 791 minterms
T-d SS : 11 nodes
T-d GS : 5 nodes 1 leaves 832 minterms
T-d HS : 9 nodes 1 leaves 860 minterms
T-d SI : 11 nodes
T-d GI : 6 nodes 1 leaves 800 minterms
T-d HI : 8 nodes 1 leaves 952 minterms
T-d SD : 11 nodes
T-d GD : 11 nodes 1 leaves 791 minterms
T-d HD : 1 nodes 1 leaves 1024 minterms
T-d SQ : 12 nodes
T-d GQ : 11 nodes 1 leaves 903 minterms
T-d HQ : 7 nodes 1 leaves 912 minterms
TEST-DECOMP:: G141 (20 variables)
T-d    : 52 nodes 1 leaves 349208 minterms
T-d SS : 55 nodes
T-d GS : 10 nodes 1 leaves 802816 minterms
T-d HS : 52 nodes 1 leaves 594968 minterms
T-d SI : 52 nodes
T-d GI : 52 nodes 1 leaves 349208 minterms
T-d HI : 1 nodes 1 leaves 1.04858e+06 minterms
T-d SD : 74 nodes
T-d GD : 26 nodes 1 leaves 837440 minterms
T-d HD : 51 nodes 1 leaves 557572 minterms
T-d SQ : 64 nodes
T-d GQ : 47 nodes 1 leaves 697560 minterms
T-d HQ : 50 nodes 1 leaves 700224 minterms
TEST-DECOMP:: G142 (20 variables)
T-d    : 45 nodes 1 leaves 829964 minterms
T-d SS : 45 nodes
T-d GS : 4 nodes 1 leaves 917504 minterms
T-d HS : 42 nodes 1 leaves 873496 minterms
T-d SI : 45 nodes
T-d GI : 7 nodes 1 leaves 851968 minterms
T-d HI : 41 nodes 1 leaves 962408 minterms
T-d SD : 67 nodes
T-d GD : 45 nodes 1 leaves 901164 minterms
T-d HD : 25 nodes 1 leaves 977376 minterms
T-d SQ : 57 nodes
T-d GQ : 40 nodes 1 leaves 938604 minterms
T-d HQ : 43 nodes 1 leaves 939936 minterms
TEST-DECOMP:: G125 (22 variables)
T-d    : 78 nodes 1 leaves 927796 minterms
T-d SS : 79 nodes
T-d GS : 3 nodes 1 leaves 3.14573e+06 minterms
T-d HS : 77 nodes 1 leaves 1.06609e+06 minterms
T-d SI : 78 nodes
T-d GI : 78 nodes 1 leaves 927796 minterms
T-d HI : 1 nodes 1 leaves 4.1943e+06 minterms
T-d SD : 104 nodes
T-d GD : 66 nodes 1 leaves 2.15491e+06 minterms
T-d HD : 54 nodes 1 leaves 2.16694e+06 minterms
T-d SQ : 94 nodes
T-d GQ : 54 nodes 1 leaves 2.10725e+06 minterms
T-d HQ : 43 nodes 1 leaves 3.01485e+06 minterms
TEST-DECOMP:: G126 (22 variables)
T-d    : 58 nodes 1 leaves 879012 minterms
T-d SS : 60 nodes
T-d GS : 5 nodes 1 leaves 2.62144e+06 minterms
T-d HS : 56 nodes 1 leaves 1.23169e+06 minterms
T-d SI : 58 nodes
T-d GI : 58 nodes 1 leaves 879012 minterms
T-d HI : 1 nodes 1 leaves 4.1943e+06 minterms
T-d SD : 83 nodes
T-d GD : 56 nodes 1 leaves 1.40178e+06 minterms
T-d HD : 39 nodes 1 leaves 3.06502e+06 minterms
T-d SQ : 65 nodes
T-d GQ : 50 nodes 1 leaves 2.10372e+06 minterms
T-d HQ : 17 nodes 1 leaves 2.9696e+06 minterms
TEST-DECOMP:: G127 (22 variables)
T-d    : 67 nodes 1 leaves 917364 minterms
T-d SS : 68 nodes
T-d GS : 3 nodes 1 leaves 3.14573e+06 minterms
T-d HS : 66 nodes 1 leaves 1.04522e+06 minterms
T-d SI : 67 nodes
T-d GI : 67 nodes 1 leaves 917364 minterms
T-d HI : 1 nodes 1 leaves 4.1943e+06 minterms
T-d SD : 86 nodes
T-d GD : 57 nodes 1 leaves 1.04469e+06 minterms
T-d HD : 39 nodes 1 leaves 3.65808e+06 minterms
T-d SQ : 80 nodes
T-d GQ : 55 nodes 1 leaves 2.10725e+06 minterms
T-d HQ : 27 nodes 1 leaves 3.00442e+06 minterms
TEST-DECOMP:: G128 (20 variables)
T-d    : 66 nodes 1 leaves 224676 minterms
T-d SS : 64 nodes
T-d GS : 5 nodes 1 leaves 589824 minterms
T-d HS : 60 nodes 1 leaves 406816 minterms
T-d SI : 64 nodes
T-d GI : 5 nodes 1 leaves 589824 minterms
T-d HI : 60 nodes 1 leaves 406816 minterms
T-d SD : 71 nodes
T-d GD : 26 nodes 1 leaves 587184 minterms
T-d HD : 57 nodes 1 leaves 417376 minterms
T-d SQ : 74 nodes
T-d GQ : 57 nodes 1 leaves 530852 minterms
T-d HQ : 19 nodes 1 leaves 742400 minterms
TEST-DECOMP:: G129 (18 variables)
T-d    : 43 nodes 1 leaves 6644 minterms
T-d SS : 44 nodes
T-d GS : 4 nodes 1 leaves 163840 minterms
T-d HS : 41 nodes 1 leaves 18932 minterms
T-d SI : 43 nodes
T-d GI : 43 nodes 1 leaves 6644 minterms
T-d HI : 1 nodes 1 leaves 262144 minterms
T-d SD : 49 nodes
T-d GD : 32 nodes 1 leaves 76224 minterms
T-d HD : 22 nodes 1 leaves 46336 minterms
T-d SQ : 52 nodes
T-d GQ : 38 nodes 1 leaves 136596 minterms
T-d HQ : 38 nodes 1 leaves 132192 minterms
TEST-DECOMP:: G130 (15 variables)
T-d    : 28 nodes 1 leaves 1381 minterms
T-d SS : 29 nodes
T-d GS : 4 nodes 1 leaves 20480 minterms
T-d HS : 26 nodes 1 leaves 4453 minterms
T-d SI : 28 nodes
T-d GI : 28 nodes 1 leaves 1381 minterms
T-d HI : 1 nodes 1 leaves 32768 minterms
T-d SD : 33 nodes
T-d GD : 22 nodes 1 leaves 4560 minterms
T-d HD : 12 nodes 1 leaves 10688 minterms
T-d SQ : 36 nodes
T-d GQ : 23 nodes 1 leaves 17608 minterms
T-d HQ : 24 nodes 1 leaves 16541 minterms
TEST-DECOMP:: G131 (12 variables)
T-d    : 17 nodes 1 leaves 306 minterms
T-d SS : 17 nodes
T-d GS : 2 nodes 1 leaves 2048 minterms
T-d HS : 16 nodes 1 leaves 612 minterms
T-d SI : 17 nodes
T-d GI : 2 nodes 1 leaves 2048 minterms
T-d HI : 16 nodes 1 leaves 612 minterms
T-d SD : 18 nodes
T-d GD : 6 nodes 1 leaves 1280 minterms
T-d HD : 14 nodes 1 leaves 912 minterms
T-d SQ : 18 nodes
T-d GQ : 15 nodes 1 leaves 2098 minterms
T-d HQ : 5 nodes 1 leaves 2304 minterms
TEST-DECOMP:: G132 (9 variables)
T-d    : 10 nodes 1 leaves 71 minterms
T-d SS : 10 nodes
T-d GS : 3 nodes 1 leaves 128 minterms
T-d HS : 8 nodes 1 leaves 284 minterms
T-d SI : 10 nodes
T-d GI : 3 nodes 1 leaves 128 minterms
T-d HI : 8 nodes 1 leaves 284 minterms
T-d SD : 10 nodes
T-d GD : 8 nodes 1 leaves 284 minterms
T-d HD : 3 nodes 1 leaves 128 minterms
T-d SQ : 11 nodes
T-d GQ : 10 nodes 1 leaves 263 minterms
T-d HQ : 4 nodes 1 leaves 320 minterms
G91: 73 nodes 4.72237e+21 minterms
G94: 73 nodes 4.72237e+21 minterms
G107: 72 nodes 1.18059e+21 minterms
G83: 72 nodes 1.18059e+21 minterms
G84: 72 nodes 1.18059e+21 minterms
G85: 72 nodes 1.18059e+21 minterms
G100BF: 75 nodes 8.26414e+21 minterms
G98BF: 81 nodes 8.26414e+21 minterms
G96BF: 137 nodes 8.26414e+21 minterms
G92: 73 nodes 5.90296e+20 minterms
G87BF: 115 nodes 7.74763e+21 minterms
G89BF: 83 nodes 7.74763e+21 minterms
G101BF: 97 nodes 9.02046e+21 minterms
G106BF: 104 nodes 8.13501e+21 minterms
G97BF: 132 nodes 9.02046e+21 minterms
G104BF: 141 nodes 8.13501e+21 minterms
G88BF: 123 nodes 6.57626e+21 minterms
G99BF: 152 nodes 8.72762e+21 minterms
G105BF: 150 nodes 8.06353e+21 minterms
G86BF: 230 nodes 6.30792e+21 minterms
G95BF: 240 nodes 8.66053e+21 minterms
G103BF: 236 nodes 8.05179e+21 minterms
G90: 286 nodes 2.3211e+21 minterms
G380: 203 nodes 2.78589e+21 minterms
G262: 134 nodes 3.98046e+20 minterms
G394: 118 nodes 2.7624e+21 minterms
G250: 78 nodes 1.30972e+21 minterms
G122: 78 nodes 8.4855e+20 minterms
G133: 142 nodes 3.0783e+21 minterms
G138: 143 nodes 7.44211e+21 minterms
G139: 125 nodes 2.78546e+21 minterms
G140: 126 nodes 7.29569e+21 minterms
G141: 260 nodes 3.14539e+21 minterms
G142: 244 nodes 7.47565e+21 minterms
G125: 304 nodes 2.08921e+21 minterms
G126: 272 nodes 1.97936e+21 minterms
G127: 290 nodes 2.06572e+21 minterms
G128: 271 nodes 2.0237e+21 minterms
G129: 180 nodes 2.39375e+20 minterms
G130: 134 nodes 3.98046e+20 minterms
G131: 106 nodes 7.05588e+20 minterms
G132: 78 nodes 1.30972e+21 minterms
G91: 1 nodes 1 minterms
G94: 1 nodes 1 minterms
G107: 3 nodes 1 minterms
G83: 3 nodes 1 minterms
G84: 3 nodes 1 minterms
G85: 3 nodes 1 minterms
G100BF: 3 nodes 3 minterms
G98BF: 3 nodes 3 minterms
G96BF: 3 nodes 3 minterms
G92: 4 nodes 1 minterms
G87BF: 7 nodes 4 minterms
G89BF: 7 nodes 4 minterms
G101BF: 9 nodes 6 minterms
G106BF: 9 nodes 6 minterms
G97BF: 9 nodes 6 minterms
G104BF: 9 nodes 6 minterms
G88BF: 11 nodes 7 minterms
G99BF: 13 nodes 9 minterms
G105BF: 13 nodes 9 minterms
G86BF: 43 nodes 57 minterms
G95BF: 45 nodes 59 minterms
G103BF: 36 nodes 59 minterms
G90: 52 nodes 35 minterms
G380: 30 nodes 14 minterms
G262: 41 nodes 25 minterms
G394: 14 nodes 9 minterms
G250: 9 nodes 4 minterms
G122: 10 nodes 4 minterms
G133: 28 nodes 18 minterms
G138: 17 nodes 13 minterms
G139: 17 nodes 8 minterms
G140: 10 nodes 6 minterms
G141: 80 nodes 75 minterms
G142: 34 nodes 20 minterms
G125: 97 nodes 110 minterms
G126: 68 nodes 63 minterms
G127: 84 nodes 105 minterms
G128: 74 nodes 63 minterms
G129: 61 nodes 55 minterms
G130: 41 nodes 25 minterms
G131: 20 nodes 8 minterms
G132: 9 nodes 4 minterms
**** CUDD modifiable parameters ****
Hard limit for cache size: 2796202
Cache hit threshold for resizing: 30%
Garbage collection enabled: yes
Limit for fast unique table growth: 1677721
Maximum number of variables sifted per reordering: 1000
Maximum number of variable swaps per reordering: 2000000
Maximum growth while sifting a variable: 1.2
Dynamic reordering of BDDs enabled: yes
Default BDD reordering method: 14
Dynamic reordering of ZDDs enabled: yes
Default ZDD reordering method: 4
Realignment of ZDDs to BDDs enabled: yes
Realignment of BDDs to ZDDs enabled: no
Dead nodes counted in triggering reordering: no
Group checking criterion: 7
Recombination threshold: 0
Symmetry violation threshold: 10
Arc violation threshold: 10
GA population size: 0
Number of crossovers for GA: 0
Next reordering threshold: 5060
**** CUDD non-modifiable parameters ****
Memory in use: 5184016
Peak number of nodes: 16352
Peak number of live nodes: 4984
Number of BDD variables: 73
Number of ZDD variables: 146
Number of cache entries: 65536
Number of cache look-ups: 101733
Number of cache hits: 38960
Number of cache insertions: 64741
Number of cache collisions: 10858
Number of cache deletions: 39991
Cache used slots = 21.20% (expected 21.36%)
Soft limit for cache size: 225280
Number of buckets in unique table: 56320
Used buckets in unique table: 6.72% (expected 6.75%)
Number of BDD and ADD nodes: 4289
Number of ZDD nodes: 1185
Number of dead BDD and ADD nodes: 3545
Number of dead ZDD nodes: 1039
Total number of nodes allocated: 38977
Total number of nodes reclaimed: 10527
Garbage collections so far: 6
Time for garbage collection: 0.00 sec
Reorderings so far: 5
Time for reordering: 0.12 sec
Final size: 688
total time = 0.15 sec
Runtime Statistics
------------------
Machine name: ubuntuBDD
User time      0.1 seconds
System time    0.0 seconds

Average resident text size       =     0K
Average resident data+stack size =     0K
Maximum resident size            =  7080K

Virtual memory limit             = unlimited (unlimited)
Major page faults = 0
Minor page faults = 1684
Swaps = 0
Input blocks = 8
Output blocks = 88
Context switch (voluntary) = 1
Context switch (involuntary) = 0
