import FWCore.ParameterSet.Config as cms

process = cms.Process("RA4SynchronizationProc")

process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(


      "file:/home/veszpv/CMSSW_2_2_9/data/LM0/patLayer1_1.root",
#       "file:/home/veszpv/CMSSW_2_2_9/data/LM0/patLayer1_2.root",
#       "file:/home/veszpv/CMSSW_2_2_9/data/LM0/patLayer1_3.root",
#       "file:/home/veszpv/CMSSW_2_2_9/data/LM0/patLayer1_4.root"


    )
)

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(100)
)

#SimpleMemoryCheck = cms.Service("SimpleMemoryCheck",
#                                ignoreTotal = cms.untracked.int32(1)
#)

process.RA4SynchronizationMod = cms.EDFilter(
    "RA4Synchronization",

    patJetConfig = cms.PSet(
        name = cms.string("pjet"),
        storeNJets = cms.uint32(4),
        jetTag = cms.InputTag("allLayer1JetsSC5"),
        selectionType = cms.string("RefAna4JetMetMuon"),
        correction = cms.vstring("RAW", "NONE"),
        ## correction:
        # "RAW"
        # "OFF"
        # "REL"
        # "ABS"
        # "EMF"
        # "HAD"
        # "UE"
        # "PART"
        # "ERROR"
        ## flavour:
        # "GLU"
        # "UDS"
        # "C"
        # "B"
        # "NONE"
        sortBy = cms.string("pt")
    ),
    patMetConfig = cms.PSet(
        name = cms.string("pmet"),
        metTag = cms.InputTag("allLayer1METsSC5"),
        selectionType = cms.string("RefAna4JetMetMuon"),
        corrections = cms.vstring("uncorrMAXN"),
        storeList = cms.vstring("uncorrMAXN", "uncorrALL")
 ## index 0
        #uncorrALL = 0, //! uncorrect to bare bones
        #uncorrJES,     //! uncorrect for JES only
        #uncorrMUON,    //! uncorrect for MUON only
        #uncorrMAXN     //"none"
    ),
    patElectronConfig = cms.PSet(
        name = cms.string("pele"),
        storeNElectrons = cms.int32(1),
        electronTag = cms.InputTag("allLayer1Electrons"),
        selectionType = cms.string("RefAna4JetMetMuon")
    ),
    patMuonConfig = cms.PSet(  
        name = cms.string("pmuon"),
        storeNMuons = cms.int32(1),
        muonTag = cms.InputTag("allLayer1Muons"),
        selectionType = cms.string("RefAna4JetMetMuon")
    ),
     EventConfig = cms.PSet(
        eventNumber = cms.double(202686.0),
        eventCrossSec = cms.double(110.0),
        luminosity = cms.double(100.0),
#         #w=0.05427
        procIdx = cms.int32(0),    # genEventProcID invalid: <0
#                                    # LM0: 0
#                                    # LM1: 1
#                                    # LM2: 2
#                                    # LM3: 3
#                                    # LM4: 4
#                                    # LM5: 5
#                                    # LM6: 6
#                                    # LM7: 7
#                                    # LM8: 8
#                                    # LM9: 9
#                                    # LM10: 10
#                                    # LM11: 11
#                                    # W+Jet: 20
#                                    # TTbar+Jet: 30
#                                    # Z+Jet: 40
#                                    # QCD: 50
#        # RefAna4JetMetMuon:
#        # https://twiki.cern.ch/twiki/bin/view/CMS/SusyRA4SingleMuonProjectTable
#        # RefAna4JetMetElectron:
#        # https://twiki.cern.ch/twiki/bin/view/CMS/SusyRA4SingleElectronProjectTable   
     ),
    
    TriggerConfig = cms.PSet(
        name = cms.string("trigger"),
        triggerTag = cms.InputTag("TriggerResults","","HLT"),
        storeList = cms.vstring("HLT_Ele15_LW_L1R","brr"),
        selectionType = cms.string("RefAna4JetMetMuon") 
    )
    
)

process.p = cms.Path(
    process.RA4SynchronizationMod
)

