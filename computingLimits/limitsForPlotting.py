import os
import subprocess
import string
import stat
import shutil
import sys
"""
xSec = [
    0.073899,
    0.070021,
    0.064175,
    0.056552,
    0.04703,
    0.033193,
    0.012981,
    ]
"""

massPoint = 5

xSec = [
    0.073899,
#    0.072681,
#    0.071266,
#    0.070021,
#    0.068574,
    0.067103,
#    0.065719,
#    0.064175,
#    0.062273,
#    0.06049,
    0.058593,
#    0.056552,
#    0.054462,
#    0.052094,
#    0.049695,
    0.04703,
#    0.04403,
#    0.040899,
    0.037309,
#    0.033193,
    0.028262,
    0.022176,
    0.012981,
    ]

CrossSection = xSec[massPoint]

effSig = [
    (0.06635, 0.03482, 0.01933, 0.01137, 0.00696, 0.00424, 0.00263, 0.00159, 0.00103, 0.00057, 0.00044, 0.00025, 0.00018, 0.00014, 6e-05),
    (0.06638, 0.03349, 0.01829, 0.0104, 0.0062, 0.00379, 0.00245, 0.00145, 0.00094, 0.00058, 0.00041, 0.00025, 0.00016, 0.00011, 3e-05),
    (0.06683, 0.03532, 0.01983, 0.01126, 0.00675, 0.00388, 0.00251, 0.00169, 0.00101, 0.00061, 0.00043, 0.00028, 0.00016, 5e-05, 1e-05),
    (0.06653, 0.03499, 0.01916, 0.0113, 0.00653, 0.00405, 0.00275, 0.0019, 0.00127, 0.00087, 0.00056, 0.00039, 0.00022, 8e-05, 4e-05),
    (0.06515, 0.03463, 0.01972, 0.01172, 0.00723, 0.0044, 0.00251, 0.0017, 0.00116, 0.00067, 0.00043, 0.00028, 0.00014, 8e-05, 1e-05),
    (0.06642, 0.03456, 0.019, 0.01104, 0.00681, 0.0042, 0.00277, 0.00172, 0.00112, 0.00065, 0.00043, 0.00023, 0.00013, 8e-05, 5e-05),
    (0.06656, 0.03442, 0.01864, 0.01085, 0.00625, 0.00378, 0.00237, 0.0015, 0.00098, 0.00065, 0.0004, 0.00023, 0.00014, 8e-05, 2e-05),
    (0.06688, 0.03454, 0.01964, 0.01153, 0.0069, 0.00415, 0.00261, 0.00177, 0.00109, 0.00078, 0.0006, 0.00042, 0.00023, 0.00016, 6e-05),
    ]

exp = [
    (250,  45.08, 24.276, 84.243, 32.388,  62.99),
    (300, 56.001, 30.097, 104.95, 40.187, 78.363),
    (350, 57.732, 31.043, 108.09, 41.441, 80.749),
    (400, 58.787, 31.539, 110.47, 42.142, 82.369),
    (450, 58.407, 31.265,  110.2, 41.813, 81.989),
    (500, 59.503, 31.839, 112.37, 42.587,  83.56),
    (550, 64.051, 34.366, 120.38, 45.916, 89.743),
    (600, 67.822,  36.33,  127.8, 48.575, 95.148),
    (650, 67.418, 36.091, 127.27, 48.264, 94.652),
    (700, 73.546,  39, 141.14, 52.359, 104.06),
    (750, 77.888, 40.993, 151.65, 55.195, 110.93),
    (800, 100.11, 51.497, 202.28, 69.971, 145.13),
    (850, 125.12, 62.512, 264.78, 85.949, 185.51),
    (900, 153.16, 74.221, 338.66, 103.34,  232.1),
    (950, 183.06,  85.95, 425.71, 121.2, 284.31),
    ]

obs = [
    (250, 53.809),
    (300, 89.693),
    (350, 99.403),
    (400, 82.238),
    (450, 63.919),
    (500, 65.739),
    (550, 45.365),
    (600, 56.523),
    (650, 55.686),
    (700,  54.06),
    (750, 60.318),
    (800, 75.184),
    (850, 94.567),
    (900,  96.79),
    (950, 152.23),
    ]

print "double x[] = {",
for i in range(0, len(obs)):
    if i+1 == len(obs):
        print obs[i][0] + 25,
    else:
        print obs[i][0] + 25,",",
print "};"

print "double xErr[] = {",
for i in range(0, len(obs)):
    if i+1 == len(obs):
        print 25,
    else:
        print 25,",",
print "};"

print "double yErr[] = {",
for i in range(0, len(obs)):
    if i+1 == len(obs):
        print 0.0,
    else:
        print 0.0,",",
print "};"

print "double yExp[] = {",
for i in range(0, len(obs)):
    if i+1 == len(obs):
        print exp[i][1]*CrossSection*effSig[massPoint][i],
    else:
        print exp[i][1]*CrossSection*effSig[massPoint][i],",",
print "};"

print "double yObs[] = {",
for i in range(0, len(obs)):
    if i+1 == len(obs):
        print obs[i][1]*CrossSection*effSig[massPoint][i],
    else:
        print obs[i][1]*CrossSection*effSig[massPoint][i],",",
print "};"

print "double yLow2[] = {",
for i in range(0, len(obs)):
    if i+1 == len(obs):
        print abs(exp[i][2] - exp[i][1])*CrossSection*effSig[massPoint][i],
    else:
        print abs(exp[i][2] - exp[i][1])*CrossSection*effSig[massPoint][i],",",
print "};"

print "double yLow1[] = {",
for i in range(0, len(obs)):
    if i+1 == len(obs):
        print abs(exp[i][4] - exp[i][1])*CrossSection*effSig[massPoint][i],
    else:
        print abs(exp[i][4] - exp[i][1])*CrossSection*effSig[massPoint][i],",",
print "};"

print "double yHigh1[] = {",
for i in range(0, len(obs)):
    if i+1 == len(obs):
        print abs(exp[i][5] - exp[i][1])*CrossSection*effSig[massPoint][i],
    else:
        print abs(exp[i][5] - exp[i][1])*CrossSection*effSig[massPoint][i],",",
print "};"

print "double yHigh2[] = {",
for i in range(0, len(obs)):
    if i+1 == len(obs):
        print abs(exp[i][3] - exp[i][1])*CrossSection*effSig[massPoint][i],
    else:
        print abs(exp[i][3] - exp[i][1])*CrossSection*effSig[massPoint][i],",",
print "};"


print "double ySignal[] = {",
for i in range(0, len(obs)):
    if i+1 == len(obs):
        print CrossSection*effSig[massPoint][i],
    else:
        print CrossSection*effSig[massPoint][i],",",
print "};"

