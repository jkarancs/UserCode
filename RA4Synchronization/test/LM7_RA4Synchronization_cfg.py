import FWCore.ParameterSet.Config as cms

process = cms.Process("RA4SynchronizationProc")

process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(
#    "/SUSY_LM7-sftsht/auterman-SUSY_LM7_229_SUSYPAT_V5j_v1-00a24c1fa2b61c755cc684c50e9bc48c/USER"
    "/store/user/auterman/SUSY_LM7-sftsht/SUSY_LM7_229_SUSYPAT_V5j_v1/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_9.root",
    "/store/user/auterman/SUSY_LM7-sftsht/SUSY_LM7_229_SUSYPAT_V5j_v1/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_8.root",
    "/store/user/auterman/SUSY_LM7-sftsht/SUSY_LM7_229_SUSYPAT_V5j_v1/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_7.root",
    "/store/user/auterman/SUSY_LM7-sftsht/SUSY_LM7_229_SUSYPAT_V5j_v1/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_6.root",
    "/store/user/auterman/SUSY_LM7-sftsht/SUSY_LM7_229_SUSYPAT_V5j_v1/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_5.root",
    "/store/user/auterman/SUSY_LM7-sftsht/SUSY_LM7_229_SUSYPAT_V5j_v1/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_4.root",
    "/store/user/auterman/SUSY_LM7-sftsht/SUSY_LM7_229_SUSYPAT_V5j_v1/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_3.root",
    "/store/user/auterman/SUSY_LM7-sftsht/SUSY_LM7_229_SUSYPAT_V5j_v1/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_2.root",
    "/store/user/auterman/SUSY_LM7-sftsht/SUSY_LM7_229_SUSYPAT_V5j_v1/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_18.root",
    "/store/user/auterman/SUSY_LM7-sftsht/SUSY_LM7_229_SUSYPAT_V5j_v1/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_17.root",
    "/store/user/auterman/SUSY_LM7-sftsht/SUSY_LM7_229_SUSYPAT_V5j_v1/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_16.root",
    "/store/user/auterman/SUSY_LM7-sftsht/SUSY_LM7_229_SUSYPAT_V5j_v1/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_15.root",
    "/store/user/auterman/SUSY_LM7-sftsht/SUSY_LM7_229_SUSYPAT_V5j_v1/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_14.root",
    "/store/user/auterman/SUSY_LM7-sftsht/SUSY_LM7_229_SUSYPAT_V5j_v1/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_13.root",
    "/store/user/auterman/SUSY_LM7-sftsht/SUSY_LM7_229_SUSYPAT_V5j_v1/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_12.root",
    "/store/user/auterman/SUSY_LM7-sftsht/SUSY_LM7_229_SUSYPAT_V5j_v1/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_11.root",
    "/store/user/auterman/SUSY_LM7-sftsht/SUSY_LM7_229_SUSYPAT_V5j_v1/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_10.root",
    "/store/user/auterman/SUSY_LM7-sftsht/SUSY_LM7_229_SUSYPAT_V5j_v1/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_1.root"
    )
)

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(-1)
)

#SimpleMemoryCheck = cms.Service("SimpleMemoryCheck",
#                                ignoreTotal = cms.untracked.int32(1)
#)

process.RA4SynchronizationMod = cms.EDFilter(
    "RA4Synchronization",

    patJetConfig = cms.PSet(
        storeNJets = cms.int32(4),
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
        metTag = cms.InputTag("allLayer1METsSC5"),
        selectionType = cms.string("RefAna4JetMetMuon"),
        corrections = cms.vstring("uncorrMAXN") ## index 0
        #uncorrALL = 0, //! uncorrect to bare bones
        #uncorrJES,     //! uncorrect for JES only
        #uncorrMUON,    //! uncorrect for MUON only
        #uncorrMAXN     //"none"
    ),
    patElectronConfig = cms.PSet(
        storeNElectrons = cms.int32(1),
        electronTag = cms.InputTag("allLayer1Electrons"),
        selectionType = cms.string("RefAna4JetMetMuon")
    ),
    patMuonConfig = cms.PSet(
        storeNMuons = cms.int32(1),
        muonTag = cms.InputTag("allLayer1Muons"),
        selectionType = cms.string("RefAna4JetMetMuon")
    ),
    EventConfig = cms.PSet(
        eventNumber = cms.double(82400.0),
        eventCrossSec = cms.double(2.9),
        luminosity = cms.double(100.0),
        #w=0.003519
        procIdx = cms.int32(7),    # genEventProcID invalid: <0
                                   # LM0: 0
                                   # LM1: 1
                                   # LM2: 2
                                   # LM3: 3
                                   # LM4: 4
                                   # LM5: 5
                                   # LM6: 6
                                   # LM7: 7
                                   # LM8: 8
                                   # LM9: 9
                                   # LM10: 10
                                   # LM11: 11
                                   # W+Jet: 20
                                   # TTbar+Jet: 30
                                   # Z+Jet: 40
                                   # QCD: 50
        selectionType = cms.vstring(
                        "RefAna4JetMetMuon",
                        "RefAna4JetMetElectron"
        )
       # RefAna4JetMetMuon:
       # https://twiki.cern.ch/twiki/bin/view/CMS/SusyRA4SingleMuonProjectTable
       # RefAna4JetMetElectron:
       # https://twiki.cern.ch/twiki/bin/view/CMS/SusyRA4SingleElectronProjectTable   
    ),
    
    TriggerConfig = cms.PSet(
        triggerResults = cms.InputTag("TriggerResults","","HLT"),
        pathNames = cms.vstring(
        'HLT_Ele15_LW_L1R'
    )
    )
    
)

process.p = cms.Path(
    process.RA4SynchronizationMod
)

