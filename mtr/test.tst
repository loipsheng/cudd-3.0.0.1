# TestMtr Version #0.6, Release date 2/6/12
# mtr/testmtr -p 2 ./mtr/test.groups
N=0x5584dadc42b0 C=0x5584dadc4370 Y=0x0        E=0x0        P=0x0        F=0 L=0 S=0
N=0x5584dadc4370 C=0x0        Y=0x5584dadc43b0 E=0x0        P=0x5584dadc42b0 F=3 L=0 S=0
N=0x5584dadc43b0 C=0x0        Y=0x5584dadc42f0 E=0x5584dadc4370 P=0x5584dadc42b0 F=4 L=0 S=0
N=0x5584dadc42f0 C=0x0        Y=0x5584dadc4330 E=0x5584dadc43b0 P=0x5584dadc42b0 F=1 L=0 S=0
N=0x5584dadc4330 C=0x0        Y=0x0        E=0x5584dadc42f0 P=0x5584dadc42b0 F=2 L=0 S=0
#------------------------
N=0x5584dadc42b0 C=0x0        Y=0x0        E=0x0        P=0x0        F=0 L=0 S=12
#  (0,11)

N=0x5584dadc42b0 C=0x5584dadc4370 Y=0x0        E=0x0        P=0x0        F=0 L=0 S=12
N=0x5584dadc4370 C=0x0        Y=0x5584dadc43b0 E=0x0        P=0x5584dadc42b0 F=0 L=0 S=6
N=0x5584dadc43b0 C=0x0        Y=0x0        E=0x5584dadc4370 P=0x5584dadc42b0 F=0 L=6 S=6
#  (0(0,5)(6,11)11)

N=0x5584dadc42b0 C=0x5584dadc4430 Y=0x0        E=0x0        P=0x0        F=0 L=0 S=12
N=0x5584dadc4430 C=0x5584dadc4370 Y=0x0        E=0x0        P=0x5584dadc42b0 F=4 L=0 S=12
N=0x5584dadc4370 C=0x5584dadc42f0 Y=0x5584dadc43b0 E=0x0        P=0x5584dadc4430 F=0 L=0 S=6
N=0x5584dadc42f0 C=0x0        Y=0x5584dadc4330 E=0x0        P=0x5584dadc4370 F=0 L=0 S=2
N=0x5584dadc4330 C=0x0        Y=0x5584dadc43f0 E=0x5584dadc42f0 P=0x5584dadc4370 F=0 L=2 S=2
N=0x5584dadc43f0 C=0x0        Y=0x0        E=0x5584dadc4330 P=0x5584dadc4370 F=0 L=4 S=2
N=0x5584dadc43b0 C=0x0        Y=0x0        E=0x5584dadc4370 P=0x5584dadc4430 F=0 L=6 S=6
#  (0(0(0(0,1)(2,3)(4,5)5)(6,11)11|F)11)

#  (0(0(0,1)(2,3)(4,5)5)(6,11)11|F)
N=0x5584dadc42b0 C=0x5584dadc4430 Y=0x0        E=0x0        P=0x0        F=0 L=0 S=12
N=0x5584dadc4430 C=0x5584dadc42f0 Y=0x0        E=0x0        P=0x5584dadc42b0 F=4 L=0 S=12
N=0x5584dadc42f0 C=0x0        Y=0x5584dadc4330 E=0x0        P=0x5584dadc4430 F=0 L=0 S=2
N=0x5584dadc4330 C=0x0        Y=0x5584dadc43f0 E=0x5584dadc42f0 P=0x5584dadc4430 F=0 L=2 S=2
N=0x5584dadc43f0 C=0x0        Y=0x5584dadc43b0 E=0x5584dadc4330 P=0x5584dadc4430 F=0 L=4 S=2
N=0x5584dadc43b0 C=0x0        Y=0x0        E=0x5584dadc43f0 P=0x5584dadc4430 F=0 L=6 S=6
#  (0(0(0,1)(2,3)(4,5)(6,11)11|F)11)

N=0x5584dadc42b0 C=0x5584dadc4430 Y=0x0        E=0x0        P=0x0        F=0 L=0 S=12
N=0x5584dadc4430 C=0x5584dadc42f0 Y=0x0        E=0x0        P=0x5584dadc42b0 F=4 L=0 S=12
N=0x5584dadc42f0 C=0x0        Y=0x5584dadc4330 E=0x0        P=0x5584dadc4430 F=0 L=0 S=2
N=0x5584dadc4330 C=0x0        Y=0x5584dadc43b0 E=0x5584dadc42f0 P=0x5584dadc4430 F=0 L=2 S=2
N=0x5584dadc43b0 C=0x0        Y=0x5584dadc43f0 E=0x5584dadc4330 P=0x5584dadc4430 F=0 L=4 S=6
N=0x5584dadc43f0 C=0x0        Y=0x0        E=0x5584dadc43b0 P=0x5584dadc4430 F=0 L=10 S=2
#  (0(0(0,1)(2,3)(4,9)(10,11)11|F)11)
#------------------------
N=0x5584dadc42b0 C=0x0        Y=0x0        E=0x0        P=0x0        F=0 L=0 S=4
#  (0,3)

N=0x5584dadc42b0 C=0x5584dadc4430 Y=0x0        E=0x0        P=0x0        F=0 L=0 S=4
N=0x5584dadc4430 C=0x0        Y=0x5584dadc42f0 E=0x0        P=0x5584dadc42b0 F=4 L=0 S=2
N=0x5584dadc42f0 C=0x0        Y=0x0        E=0x5584dadc4430 P=0x5584dadc42b0 F=4 L=2 S=2
#  (0(0,1|F)(2,3|F)3)

#------------------------
N=0x5584dadc42b0 C=0x5584dadc4430 Y=0x0        E=0x0        P=0x0        F=0 L=0 S=12
N=0x5584dadc4430 C=0x5584dadc4330 Y=0x5584dadc42f0 E=0x0        P=0x5584dadc42b0 F=0 L=0 S=6
N=0x5584dadc4330 C=0x0        Y=0x5584dadc43b0 E=0x0        P=0x5584dadc4430 F=0 L=0 S=2
N=0x5584dadc43b0 C=0x0        Y=0x5584dadc43f0 E=0x5584dadc4330 P=0x5584dadc4430 F=0 L=2 S=2
N=0x5584dadc43f0 C=0x0        Y=0x0        E=0x5584dadc43b0 P=0x5584dadc4430 F=0 L=4 S=2
N=0x5584dadc42f0 C=0x0        Y=0x0        E=0x5584dadc4430 P=0x5584dadc42b0 F=4 L=6 S=6
#  (0(0(0,1)(2,3)(4,5)5)(6,11|F)11)

