from ROOT import *
import os
import subprocess
import string
import stat
import shutil
import sys

### Set the size of histogram bins
binSize = 50

################################################################################
### This function is used to set a proper histo name according bin range
################################################################################
def findString( name ):

#    name = name.replace(".0", "")
    countUnderline = 0
    countDigit     = 0
    nameReversed   = name[::-1]

    for c in nameReversed:
        countDigit += 1

        if c == "_":
            countUnderline += 1
        if countUnderline == 2:
            break
    return name[len(name) - (countDigit) : len(name)]


################################################################################
### This function creates tuples of histograms according bin range
################################################################################
def separateHistoBin( histo ):

    nBins = histo.GetNbinsX()
    minX  = histo.GetBinLowEdge(1)
    maxX  = histo.GetBinLowEdge(nBins+1)

    nNewBins = (maxX - minX) / binSize

    newH = []
    for k in range(0, int(nNewBins)):
        minXX = minX + ( k    * binSize)
        maxXX = minX + ((k+1) * binSize)
#        histoName = histo.GetName() + "_" + str(minXX) + "_" + str(maxXX)
        histoName = histo.GetName() + "_" + str(minXX) + "_" + str(maxX)
        newH.append( TH1F(histoName, histoName, 1, 0, 1) )

        content = 0
        for m in range(1, nBins+1):
#            if (histo.GetBinLowEdge(m) >= minXX) and (histo.GetBinLowEdge(m+1) <= maxXX):
            if (histo.GetBinLowEdge(m) >= minXX) and (histo.GetBinLowEdge(m+1) <= maxX):
                content = content + histo.GetBinContent(m)
            else:
                continue
        newH[k].SetBinContent(1, content)
    return newH

################################################################################
### Main function
################################################################################
def main():

    ### Choose director with input histograms (data, background, signal)
    inDir = "originalFiles_28Jun2016/"
    ### Choose one of the signals
    inFileName = [
        ("EXO-12-048_data5.root"),
        ("alternate_background5.root"),
#        ("Marc_Delphes_jetPtScale_Mh140_histos_8TeV_MET200.root"),
#        ("Marc_Delphes_jetPtScale_Mh145_histos_8TeV_MET200.root"),
#        ("Marc_Delphes_jetPtScale_Mh150_histos_8TeV_MET200.root"),
#        ("Marc_Delphes_jetPtScale_Mh155_histos_8TeV_MET200.root"),
#        ("Marc_Delphes_jetPtScale_Mh158_histos_8TeV_MET200.root"),
        ("Marc_Delphes_jetPtScale_Mh160_histos_8TeV_MET200.root"),
#        ("Marc_Delphes_jetPtScale_Mh161_histos_8TeV_MET200.root"),
#        ("Marc_Delphes_jetPtScale_Mh162_histos_8TeV_MET200.root"),
        ]

    ### !!! DO NOT touch in the lines bellow !!!
    nFiles = len(inFileName)
    newHistos = []
    count = 0
    histo = []

    ### Loop over the list of input files (data, background, signal) and get its histograms
    for i in range(0, nFiles):
        inFile = TFile.Open( inDir + "/" + inFileName[i], "read" )
        nHistos = inFile.GetNkeys()
        listHistos = inFile.GetListOfKeys()

        ### Loop over list of input histograms to create a tuple of one bin histograms.
        ### The number of one bin histograms depends on the bin size.
        for j in range(0, nHistos):
            histo.append( inFile.Get(listHistos.At(j).GetName()) )
            newHistos.append( separateHistoBin( histo[count] ) )
            count += 1

    ### Loop over the list of histogram tuples.
    ### Output files will be created containng the correspondent one bin histograms.
    for i in range(0, len(newHistos[0])):

        print "-----------------------------------------------------------------------------------"
        countRepeated = 0

        for j in range(0, len(newHistos)):
            histoName = ([x[i] for x in newHistos][j]).GetName()
            if ("background" in histoName):
                if (countRepeated == 0):
                    outFileName = inFileName[j - countRepeated]
                    outFileName = outFileName.replace("MET200", "")
                    outFileName = outFileName.replace(".root", "MET"+findString(histoName)+".root")
                    outFileName = outFileName.replace(".0", "")
                    print "\n<< Opening: " + outFileName
                    outFile = TFile.Open(outFileName, "recreate")

                rangeMET = findString(histoName)
                histoBin = [x[i] for x in newHistos][j]
                histoName = histoName.replace( findString(histoName), "" )
                histoBin.SetName( histoName )
                minBin = histo[j].FindBin( float(rangeMET[1 : rangeMET.find(".0")]) )
                maxBin = histo[j].FindBin( float(rangeMET[rangeMET.find(".0")+3 :]) - 1 )
                print histoName + " ---> Integral: " + str(histoBin.Integral()) + " / " + str(histo[j].Integral(minBin, maxBin))
                histoBin.Write()
                countRepeated += 1

                if countRepeated > 2:
                    countRepeated = 2
                    print ">> Closing: " + outFileName
                    outFile.Close()
            else:
                outFileName = inFileName[j - countRepeated]
                outFileName = outFileName.replace("MET200", "")
                outFileName = outFileName.replace(".root", "MET"+findString(histoName)+".root")
                outFileName = outFileName.replace(".0", "")
                print "\n<< Opening: " + outFileName
                outFile = TFile.Open(outFileName, "recreate")

                rangeMET = findString(histoName)
                histoBin = [x[i] for x in newHistos][j]
                histoName = histoName.replace( findString(histoName), "" )
                histoBin.SetName( histoName )
                minBin = histo[j].FindBin( float(rangeMET[1 : rangeMET.find(".0")]) )
                maxBin = histo[j].FindBin( float(rangeMET[rangeMET.find(".0")+3 :]) - 1 )
                print histoName + " ---> Integral: " + str(histoBin.Integral()) + " / " + str(histo[j].Integral(minBin, maxBin))
                histoBin.Write()

                print ">> Closing: " + outFileName
                outFile.Close()
        

################################################################################
main()
