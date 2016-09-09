# Soton-Sprace-DM
Phenomenological studies between Southampton and SPRACE in i2HDM

## Installing theta code using CMSSW following instructions from [Theta web page](http://www-ekp.physik.uni-karlsruhe.de/~ott/theta/theta-auto/installation.html)

1. Preparing CMSSW workarea

```
cmsrel CMSSW_8_0_19_patch1
cd CMSSW_8_0_19_patch1/src/
cmsenv
```

2. Downloading theta

`svn co https://ekptrac.physik.uni-karlsruhe.de/public/theta/tags/testing theta`

3. Compiling theta

```
cd theta/
make
```

