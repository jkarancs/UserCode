import FWCore.ParameterSet.Config as cms

process = cms.Process("debNtupleMakerProc")
#process.load("FWCore.MessageService.MessageLogger_cfi")
##process.load("SimGeneral.HepPDTESSource.pythiapdt_cfi")

process.load("PhysicsTools.PatAlgos.patLayer0_cff")
process.load("PhysicsTools.PatAlgos.patLayer1_cff")

process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(
    "rfio:/castor/cern.ch/user/a/akapusi/LM1_2_2_3/F441C2B4-1ACC-DD11-9C41-00E08178C06F.root"
##    "rfio:/SUSY_LM1-sftsht/Summer08_IDEAL_V9_v1/GEN-SIM-RECO"
##    "file:/home/veszpv/CMSSW_2_2_3/data/LM0_PAT_LAYER1/Lm0_1.root"
##    "rfio:/castor/cern.ch/user/a/akapusi/PAT/V5f/patLayer1__SUSY_LM0-sftsht__Summer08_IDEAL_V11_v1__GEN-SIM-RECO__byV5f_1.root"
##    "file:/home/veszpv/CMSSW_2_2_3/data/LM1-F441C2B4-1ACC-DD11-9C41-00E08178C06F.root"
    )
)

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(100)
)

process.TFileService = cms.Service("TFileService",
    fileName = cms.string('LM1_20090525.root')
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
        jetTag = cms.InputTag("selectedLayer1Jets"),
        selectionType = cms.string("NONE"),
        correction = cms.vstring("HAD", "UDS"),
        sortBy = cms.string("pt")
    ),

    patMetConfig = cms.PSet(
        metTag = cms.InputTag("selectedLayer1METs"),
        selectionType = cms.string("NONE"),
        corrections = cms.vstring("uncorrALL", "uncorrMAXN") ## index 0
    ),

    patElectronConfig = cms.PSet(
        storeNElectrons = cms.int32(4),
        electronTag = cms.InputTag("selectedLayer1Electrons"),
        selectionType = cms.string("RefAna4JetMetMuon")
    ),

    patMuonConfig = cms.PSet(
        storeNMuons = cms.int32(4),
        muonTag = cms.InputTag("selectedLayer1Muons"),
        selectionType = cms.string("RefAna4JetMetMuon")
    ),

    EventConfig = cms.PSet(
        eventNumber = cms.double(104800.0),
        eventCrossSec = cms.double(16.06),
        luminosity = cms.double(100.0),
        #w=0.0153
        procIdx = cms.int32(1),    # genEventProcID invalid: <0
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
    process.patLayer0*
    process.patLayer1*
    process.debNtupleMakerMod
)
