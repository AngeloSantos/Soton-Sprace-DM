# Soton-Sprace-DM
Phenomenological studies between Southampton and SPRACE in i2HDM

## Contents

1. `inputMetHistos/` (contains macro files to prepare the input histograms)
  1. plotDataBackgMetDistribution.cpp (print data and background MET distributions)
  2. prepareHistosOneBinAnalys.py (prepare histograms for one bin analisys)
  3. prepareHistosShapeBinAnalys.py (prepare histograms for shape analisys)
2. `signalEfficiencies/` (contains macro file to compute signal effiencies)
  * getSignalEfficiencies.py (compute signal efficiencies)
3. `computingLimits/` (contains macro files to compute limits and plot them)
  1. computingLimitsWithTheta.py (compute limits using Theta code)
  2. analysis.py (simple script to compute limits using Theta)
  3. limitsForPlotting.py (prepare limits to be plotted)
  4. computingLimitsWithTheta.py (plot limits)


## Installing theta code using CMSSW

Following instructions from [Theta web page](http://www-ekp.physik.uni-karlsruhe.de/~ott/theta/theta-auto/installation.html)

* Preparing CMSSW workarea

```
cmsrel CMSSW_8_0_19_patch1
cd CMSSW_8_0_19_patch1/src/
cmsenv
```

* Downloading theta

`svn co https://ekptrac.physik.uni-karlsruhe.de/public/theta/tags/testing theta`

* Compiling theta

```
cd theta/
make
```

## Computing limits with Theta

Prepare a working area inside `theta/` directory:

```
cd utils2/examples/counting/
mkdir TestingTheta
cd TestingTheta/
```

Copy `computingLimits/analysis.py` to `TestingTheta/` and run

```
python ../../../theta-auto.py  analysis.py
```
