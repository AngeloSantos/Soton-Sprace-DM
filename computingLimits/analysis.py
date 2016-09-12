### To run this script use:    python ../../../theta-auto.py  analysis.py

model = build_model_from_rootfile(['EXO-16-013_data_2p3.root',
                                   'EXO-16-013_background_2p3.root',
                                   'Marc_Delphes_jetPtScale_Mh160_histos_13TeV_MET200.root'])

# signal cross section (fb)
#xSec = 0.24281 # Mh1 = 40 GeV
#xSec = 0.22092 # Mh1 = 45 GeV
#xSec = 0.19255 # Mh1 = 50 GeV
#xSec = 0.15431 # Mh1 = 55 GeV
#xSec = 0.12249 # Mh1 = 58 GeV
xSec = 0.093206 # Mh1 = 60 GeV
#xSec = 0.072845 # Mh1 = 61 GeV
#xSec = 0.042620 # Mh1 = 62 GeV

Lumi      = 2.3    # luminosity (1/fb)
genEvents = 100000 # number of generated events

#print model
model.set_signal_processes('Mh1*')
model.scale_predictions(xSec*Lumi*genEvents,procname="Mh160",obsname="CMS_EXO_16_013")

expected, observed = asymptotic_cls_limits(model)
print expected, observed

report.write_html('htmlout')
