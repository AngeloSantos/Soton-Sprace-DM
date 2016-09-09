# Soton-Sprace-DM
Phenomenological studies between Southampton and SPRACE in i2HDM

## Contents of this 

## Installing theta code using CMSSW following instructions from [Theta web page](http://www-ekp.physik.uni-karlsruhe.de/~ott/theta/theta-auto/installation.html)

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

