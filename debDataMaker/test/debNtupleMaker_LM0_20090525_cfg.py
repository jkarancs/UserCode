import FWCore.ParameterSet.Config as cms

process = cms.Process("debNtupleMakerProc")
#process.load("FWCore.MessageService.MessageLogger_cfi")
##process.load("SimGeneral.HepPDTESSource.pythiapdt_cfi")

process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(
##    "file:/afs/cern.ch/user/a/akapusi/scratch0/Lm0_1.root"
##    "/SUSY_LM0-sftsht/susy-SUSY_LM0_228_SUSYPAT_V5_v1-01fcb16777fedba722b5ef4d05407ac6/USER"
    "rfio:/castor/cern.ch/user/a/akapusi/PAT/V5f/patLayer1__SUSY_LM0-sftsht__Summer08_IDEAL_V11_v1__GEN-SIM-RECO__byV5f_1.root",
    "rfio:/castor/cern.ch/user/a/akapusi/PAT/V5f/patLayer1__SUSY_LM0-sftsht__Summer08_IDEAL_V11_v1__GEN-SIM-RECO__byV5f_2.root",
    "rfio:/castor/cern.ch/user/a/akapusi/PAT/V5f/patLayer1__SUSY_LM0-sftsht__Summer08_IDEAL_V11_v1__GEN-SIM-RECO__byV5f_3.root",
    "rfio:/castor/cern.ch/user/a/akapusi/PAT/V5f/patLayer1__SUSY_LM0-sftsht__Summer08_IDEAL_V11_v1__GEN-SIM-RECO__byV5f_4.root",
    "rfio:/castor/cern.ch/user/a/akapusi/PAT/V5f/patLayer1__SUSY_LM0-sftsht__Summer08_IDEAL_V11_v1__GEN-SIM-RECO__byV5f_5.root",
    "rfio:/castor/cern.ch/user/a/akapusi/PAT/V5f/patLayer1__SUSY_LM0-sftsht__Summer08_IDEAL_V11_v1__GEN-SIM-RECO__byV5f_6.root"
    )
)

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(10)
)

process.TFileService = cms.Service("TFileService",
    fileName = cms.string('LM0_20090525.root')
)


process.debNtupleMakerMod = cms.EDFilter(
    "debNtupleMaker",
##    genPartTag = cms.InputTag("genParticles"),
##    genJetTag = cms.InputTag("sisCone5GenJets"),
##    caloJetTag = cms.InputTag("sisCone5CaloJets"),
##    numOfCaloJets = cms.int32(6),
##    correctionType = 
##    genMetTag = cms.InputTag("genMet"),
##    caloMetTag = cms.InputTag("met")


    patJetConfig = cms.PSet(
        storeNJets = cms.int32(4),
        jetTag = cms.InputTag("allLayer1Jets"),
        selectionType = cms.string("RA4mu"),
        correction = cms.vstring("HAD", "UDS"),
        sortBy = cms.string("pt")
    ),
    patMetConfig = cms.PSet(
        metTag = cms.InputTag("allLayer1METs"),
        selectionType = cms.string("RA4mu"),
        corrections = cms.vstring("uncorrALL", "uncorrMAXN") ## index 0
    ),
    patElectronConfig = cms.PSet(
        storeNElectrons = cms.int32(4),
        electronTag = cms.InputTag("allLayer1Electrons"),
        selectionType = cms.string("RefAna4JetMetMuon")
    ),
    patMuonConfig = cms.PSet(
        storeNMuons = cms.int32(4),
        muonTag = cms.InputTag("allLayer1Muons"),
        selectionType = cms.string("RefAna4JetMetMuon")
    ),
    EventConfig = cms.PSet(
        eventWeight = cms.double(0.05427),
        #100.0/(202686.0/110.0)
        procIdx = cms.int32(0),    # genEventProcID invalid: <0
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
                                   # W+Jet: 10
                                   # TTbar+Jet: 20
                                   # Z+Jet: 30
                                   # QCD: 40
        selectionType = cms.string("RefAna4JetMetMuon")
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
    ),

    drPatJetPatMetConfig = cms.PSet(
        patJetIndices = cms.vuint32(0, 1, 2, 3),
        ## Met indices follow the order of the requested corrections given
        ## in patMetConfig, conversion is done in the constructor of
        ## debNtupleMakerMod or one could just manually conver them by passing
        ## a vuint32() here listing the corresponding indices starting from 0
        caloMetCorrections = cms.vstring("uncorrMAXN")
    ),

    drPatJetConfig = cms.PSet(
        patJetIndices = cms.vuint32(0, 1, 2, 3)
    )
)

process.p = cms.Path(
    process.debNtupleMakerMod
)

