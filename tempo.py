import os
import sys
import numpy as np
from icecream import ic

for bpm_tar in range(50, 220, 10):
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
    for i in range(20):
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
    print(bpm_cur)
