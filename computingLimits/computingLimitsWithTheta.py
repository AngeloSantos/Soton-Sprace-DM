from ROOT import *
import os
import subprocess
import string
import stat
import shutil
import sys

minMET  = 250  ### Lower x in MET distribution
maxMET  = 1000 ### High x in MET distribution
stepMET = 50   ### Size of histogram bin

### Choose (h1 mass, cross section)
xSec = [
#    (40, 0.073899),
#    (41, 0.072681),
#    (42, 0.071266),
#    (43, 0.070021),
#    (44, 0.068574),
#    (45, 0.067103),
#    (46, 0.065719),
#    (47, 0.064175),
#    (48, 0.062273),
#    (49, 0.06049),
#    (50, 0.058593),
#    (51, 0.056552),
#    (52, 0.054462),
#    (53, 0.052094),
#    (54, 0.049695),
#    (55, 0.04703),
#    (56, 0.04403),
#    (57, 0.040899),
#    (58, 0.037309),
#    (59, 0.033193),
    (60, 0.028262),
#    (61, 0.022176),
#    (62, 0.012981),
    ]


#######################################################################################
### This function creates a script to be run into Theta code and compute limits
#######################################################################################
def createScript( mass, xs, MET ):

    print "--->\t Mh1:", mass, ",   xSec:", xs

    output = open( "analysis.py", "w" )

    output.write("model = build_model_from_rootfile(['EXO-12-048_data5MET_" + str(MET) + "_1000.root',\n")
    output.write("                                   'alternate_background5MET_" + str(MET) + "_1000.root',\n")
    output.write("                                   'Marc_Delphes_jetPtScale_Mh1" + str(mass) + "_histos_8TeV_MET_" + str(MET) + "_1000.root'])\n")
    output.write("\n")
    output.write("#print model\n")
    output.write("\n")
    output.write("model.set_signal_processes('Mh1*')\n")
    output.write("model.scale_predictions("+ str(xs * 19710 / 100000) +",procname=\"Mh1"+ str(mass) +"\",obsname=\"CMS_EXO_12_048\")\n")
    output.write("\n")
    output.write("expected, observed = asymptotic_cls_limits(model)\n")
    output.write("print expected, observed\n")
    output.write("\n")
    output.write("report.write_html('htmlout')\n")

    output.close()


#######################################################################################
# This function enable to run bash commands via Python and read its results pop up
# on screen in real time.
#######################################################################################
def bash_via_python(command_line):
    p2 = subprocess.Popen(command_line, shell=True, stderr=subprocess.PIPE)
    while True:
        out = p2.stderr.read(1)
        if out == '' and p2.poll() != None:
            break
        if out != '':
            sys.stdout.write(out)
            sys.stdout.flush()


#######################################################################################
### Main function: it calls the theta script and compute limits
#######################################################################################
def main ():

    nBins = (maxMET - minMET) / stepMET
    for i in range(0, nBins):

        MET = minMET + (i * stepMET)
        print "\n ========[[", MET, "< MET <", maxMET, "]]========"

        for j in range(0, len(xSec)):
            createScript(xSec[j][0], xSec[j][1], MET)
            bash_via_python( "python  ../../../theta-auto.py  analysis.py" )

    ### Type the commands bellow to 
    print "\n\t For odd  line,  use: -------->>> grep \"140\" LogFile.log | sed -n 1~2p"
    print "\n\t For even lines, use: -------->>> grep \"140\" LogFile.log | sed -n 2~2p"

#######################################################################################
# Here we call the main funtion
#######################################################################################
main()
