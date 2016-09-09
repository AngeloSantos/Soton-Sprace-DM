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

massPoint = 0 ### Number of mass points

### Choose cross sections accordingly
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

### These efficiencies come from  signalEfficiencies/getSignalEfficiencies.py
### The most up (down) line correspond to the first (last) cross section above
### The most left (right) value corresponds to the lowest (highest) bin in MET distribution
effSig = [
    (0.06635, 0.03482, 0.01933, 0.01137, 0.00696, 0.00424, 0.00263, 0.00159, 0.00103, 0.00057, 0.00044, 0.00025, 0.00018, 0.00014, 0.00006),
    (0.06638, 0.03349, 0.01829, 0.0104, 0.0062, 0.00379, 0.00245, 0.00145, 0.00094, 0.00058, 0.00041, 0.00025, 0.00016, 0.00011, 0.00003),
    (0.06683, 0.03532, 0.01983, 0.01126, 0.00675, 0.00388, 0.00251, 0.00169, 0.00101, 0.00061, 0.00043, 0.00028, 0.00016, 5e-05, 0.00001),
    (0.06653, 0.03499, 0.01916, 0.0113, 0.00653, 0.00405, 0.00275, 0.0019, 0.00127, 0.00087, 0.00056, 0.00039, 0.00022, 8e-05, 0.00004),
    (0.06515, 0.03463, 0.01972, 0.01172, 0.00723, 0.0044, 0.00251, 0.0017, 0.00116, 0.00067, 0.00043, 0.00028, 0.00014, 8e-05, 0.00001),
    (0.06642, 0.03456, 0.019, 0.01104, 0.00681, 0.0042, 0.00277, 0.00172, 0.00112, 0.00065, 0.00043, 0.00023, 0.00013, 8e-05, 0.00005),
    (0.06656, 0.03442, 0.01864, 0.01085, 0.00625, 0.00378, 0.00237, 0.0015, 0.00098, 0.00065, 0.0004, 0.00023, 0.00014, 8e-05, 0.00002),
    (0.06688, 0.03454, 0.01964, 0.01153, 0.0069, 0.00415, 0.00261, 0.00177, 0.00109, 0.00078, 0.0006, 0.00042, 0.00023, 0.00016, 0.00006),
    ]

### Expected limits
### These cross sections come from computingLimitsWithTheta.py
### (Mass, Exp,    -2 sd,  +2 sd,  -1 sd,  +1 sd)
exp = [
    (250,  16.835, 9.0508,  31.54, 12.083, 23.552),
    (300,   21.75, 11.633, 41.086, 15.563, 30.552),
    (350,  22.784,  12.18, 43.068, 16.298, 32.015),
    (400,  22.561, 12.039, 42.773, 16.122, 31.746),
    (450,  22.613, 12.023, 43.139, 16.122, 31.914),
    (500,  22.971, 12.206, 43.886, 16.372, 32.438),
    (550,  23.859, 12.712, 45.391, 17.031, 33.623),
    (600,  23.837, 12.684, 45.478, 17.002, 33.633),
    (650,  23.685, 12.587, 45.363, 16.881, 33.477),
    (700,  26.732, 13.989, 52.555, 18.879, 38.251),
    (750,  27.088, 14.182, 53.297, 19.135, 38.764),
    (800,  34.219, 17.578,  69.45, 23.894, 49.701),
    (850,  37.246, 18.901, 77.263, 25.814, 54.653),
    (900,  38.005, 19.084, 80.518, 26.168, 56.303),
    (950,  61.924, 29.673, 140.71, 41.473,  94.98),
    ]

### Observed limits
### These cross sections come from computingLimitsWithTheta.py
### (Mass, Obs)
obs = [
    (250,  12.562),
    (300,  28.584),
    (350,  32.902),
    (400,  27.839),
    (450,  20.326),
    (500,  21.807),
    (550,  18.857),
    (600,  19.378),
    (650,  18.976),
    (700,   19.54),
    (750,  19.939),
    (800,  23.101),
    (850,  27.294),
    (900,  26.234),
    (950,  62.492),
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

