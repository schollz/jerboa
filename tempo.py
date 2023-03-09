import os
import sys
import numpy as np
from icecream import ic

h={}
h[0]="0"
h[1]="1"
h[2]="2"
h[3]="3"
h[4]="4"
h[5]="5"
h[6]="6"
h[7]="7"
h[8]="8"
h[9]="9"
h[10]="A"
h[11]="B"
h[12]="C"
h[13]="D"
h[14]="E"
h[15]="F"

tempos=list(range(50,220,10));
out=f"#define NUM_TEMPOS {len(tempos)}\n"
out+="byte *tempo_steps[] = {\n"
for bpm_tar in tempos:
    bpm_val = 3
    bpm_set = 150 / (bpm_val / 3)
    bpm_mod = []
    if bpm_tar >= 150:
        bpm_mod.append(3)
    elif bpm_tar <= 56.3:
        bpm_mod.append(9)
    elif bpm_tar <= 64.3:
        bpm_mod.append(7)
    elif bpm_tar <= 75:
        bpm_mod.append(6)
    elif bpm_tar <= 90:
        bpm_mod.append(5)
    elif bpm_tar <= 115:
        bpm_mod.append(5)
    else:
        bpm_mod.append(4)

    bpm_cur = bpm_set
    for i in range(14):
        if np.abs(bpm_cur - bpm_tar) < 0.01:
            bpm_mod.append(0)
            continue
        bpm_cur = bpm_val / np.average(bpm_mod) * bpm_set
        if bpm_cur < bpm_tar:
            if bpm_tar >= 150:
                bpm_mod.append(2)
            elif bpm_tar <= 56.3:
                bpm_mod.append(8)
            elif bpm_tar <= 64.3:
                bpm_mod.append(7)
            elif bpm_tar <= 75:
                bpm_mod.append(6)
            elif bpm_tar <= 90:
                bpm_mod.append(5)
            elif bpm_tar <= 115:
                bpm_mod.append(4)
            else:
                bpm_mod.append(3)
        else:
            if bpm_tar >= 150:
                bpm_mod.append(3)
            elif bpm_tar <= 56.3:
                bpm_mod.append(9)
            elif bpm_tar <= 64.3:
                bpm_mod.append(8)
            elif bpm_tar <= 75:
                bpm_mod.append(7)
            elif bpm_tar <= 90:
                bpm_mod.append(6)
            elif bpm_tar <= 115:
                bpm_mod.append(5)
            else:
                bpm_mod.append(4)
    print(bpm_cur,bpm_mod)
    s =""
    ss = []
    for i,n in enumerate(bpm_mod):
        if i==0:
            s += f"0x{h[(np.array(bpm_mod) > 0).sum()-1]}"
        if i%2==1:
            if n==0:
                break
            s += f"0x{h[n]}"
        else:
            ss.append(s+ f"{h[n]}")
            s= ""
    sjoin = ", ".join(ss)
    out += f"    (byte[]) {{{sjoin}}},\n"

out += "};"
print(out)
