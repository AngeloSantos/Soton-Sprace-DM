# Soton-Sprace-DM
Phenomenological studies between Southampton and SPRACE in i2HDM

# To install theta code using CMSSW
# Following instructions from http://www-ekp.physik.uni-karlsruhe.de/~ott/theta/theta-auto/installation.html
1) Prepare CMSSW workarea
cmsrel CMSSW_8_0_19_patch1
cd CMSSW_8_0_19_patch1/src/
cmsenv

2) Download theta
svn co https://ekptrac.physik.uni-karlsruhe.de/public/theta/tags/testing theta

3) Compile theta
cd theta/
make


