from ROOT import *
import os
import subprocess
import string
import stat
import shutil
import sys

genEvents = 100000
binSize   = 50

inputDir  = "separateBins_Delphes_8TeV_MET250_28Jun2016/originalFiles_28Jun2016/"

inFileNames = [
    "Marc_Delphes_jetPtScale_Mh140_histos_8TeV_MET200.root",
    "Marc_Delphes_jetPtScale_Mh145_histos_8TeV_MET200.root",
    "Marc_Delphes_jetPtScale_Mh150_histos_8TeV_MET200.root",
    "Marc_Delphes_jetPtScale_Mh155_histos_8TeV_MET200.root",
    "Marc_Delphes_jetPtScale_Mh158_histos_8TeV_MET200.root",
    "Marc_Delphes_jetPtScale_Mh160_histos_8TeV_MET200.root",
    "Marc_Delphes_jetPtScale_Mh161_histos_8TeV_MET200.root",
    "Marc_Delphes_jetPtScale_Mh162_histos_8TeV_MET200.root",
    ]

#############################################################################
def getRange(histo):
    return histo.GetBinLowEdge(1), histo.GetBinLowEdge(2)

#############################################################################
def getEfficiencies(histo):

    nBins = histo.GetNbinsX()
    maxX  = histo.GetBinLowEdge(nBins+1)
    eff   = []
    iBin  = 0

    for i in range(1, nBins):
        minX = histo.GetBinLowEdge(i)

        if ((maxX - minX) % binSize) == 0:
            eff.append( histo.Integral(i, nBins) / genEvents )
#            print minX, ",", maxX, "->", histo.Integral(i, nBins), "/", genEvents, "=", eff[iBin]
#            if (i < (nBins-1)):
#                print eff[iBin], ",",
#            else:
#                print eff[iBin],
            iBin += 1
        else:
            continue
    return eff

#############################################################################
def main():

    histo   = []
    listEff = []

    for i in range(0, len(inFileNames)):
        inFile = TFile.Open( inputDir + inFileNames[i], "read")
        listOfKeys = inFile.GetListOfKeys()
        histo.append( inFile.Get(listOfKeys.At(0).GetName()) )
#        mass = (histo[i].GetName()).replace("CMS_EXO_12_048__", "")
#        print "double sigEff[] = {", getEfficiencies(histo[i])
        listEff.append( getEfficiencies(histo[i]) )

        print listEff[i]
        

#############################################################################
main()
