import FWCore.ParameterSet.Config as cms

process = cms.Process("debNtupleMakerProc")
#process.load("FWCore.MessageService.MessageLogger_cfi")
##process.load("SimGeneral.HepPDTESSource.pythiapdt_cfi")

process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(

   "file:/home/veszpv/CMSSW_2_2_9/data/patLayer1__SUSY_LM0-sftsht__Summer08_IDEAL_V11_v1__GEN-SIM-RECO__byV5f_1.root"
  ##  "file:/home/veszpv/CMSSW_2_2_3/data/LM1-F441C2B4-1ACC-DD11-9C41-00E08178C06F.root"

        
##    "file:/home/veszpv/CMSSW_2_2_3/data/LM1/00211808-75CE-DD11-A5C6-0013D3DE2633.root",
##    "file:/home/veszpv/CMSSW_2_2_3/data/LM1/007339CA-F0CC-DD11-AD95-00E08178C107.root",
##    "file:/home/veszpv/CMSSW_2_2_3/data/LM1/0263F495-71CE-DD11-A8CC-00E08179181F.root",
##    "file:/home/veszpv/CMSSW_2_2_3/data/LM1/04209804-F7CC-DD11-94EC-00E08178C093.root",
##    "file:/home/veszpv/CMSSW_2_2_3/data/LM1/065E8461-50CC-DD11-B4F1-00E081791733.root",
##    "file:/home/veszpv/CMSSW_2_2_3/data/LM1/18D3F67E-F1CD-DD11-8CD8-00E08178C10B.root",
##    "file:/home/veszpv/CMSSW_2_2_3/data/LM1/1AD569CA-EECC-DD11-810A-00E081791865.root",
##    "file:/home/veszpv/CMSSW_2_2_3/data/LM1/1AF358E6-CECD-DD11-9470-00E08178C065.root",
##    "file:/home/veszpv/CMSSW_2_2_3/data/LM1/1EBB0741-F0CC-DD11-8BA2-00E081791747.root",
##    "file:/home/veszpv/CMSSW_2_2_3/data/LM1/24354D52-EBCD-DD11-B855-00E0817918A5.root",
##    "file:/home/veszpv/CMSSW_2_2_3/data/LM1/288FB099-F7CC-DD11-BB1C-00151715C5D4.root",
##    "file:/home/veszpv/CMSSW_2_2_3/data/LM1/2ED9688B-CFCD-DD11-8B53-00E08178C17B.root",
##    "file:/home/veszpv/CMSSW_2_2_3/data/LM1/3450FE2F-51CC-DD11-BE55-003048670ADA.root",
##    "file:/home/veszpv/CMSSW_2_2_3/data/LM1/34B4E4D7-3BCC-DD11-9724-00E081791795.root",
##    "file:/home/veszpv/CMSSW_2_2_3/data/LM1/40FB7D27-E5CD-DD11-AD49-00304832672C.root",
##    "file:/home/veszpv/CMSSW_2_2_3/data/LM1/483C995C-B5CD-DD11-9AEF-00304832672A.root",
##    "file:/home/veszpv/CMSSW_2_2_3/data/LM1/58A735E2-F0CC-DD11-BB49-00E0817917E1.root",
##    "file:/home/veszpv/CMSSW_2_2_3/data/LM1/628FC9F0-CECD-DD11-96C3-00E0817918BB.root",
##    "file:/home/veszpv/CMSSW_2_2_3/data/LM1/6EE42A8F-C3CD-DD11-B988-001A64789DD0.root",
##    "file:/home/veszpv/CMSSW_2_2_3/data/LM1/72E9CD2E-67CF-DD11-B8CF-00E08178C0F9.root",
##    "file:/home/veszpv/CMSSW_2_2_3/data/LM1/7C42C282-F0CC-DD11-99F4-00E0817917FB.root",
##    "file:/home/veszpv/CMSSW_2_2_3/data/LM1/7CEEDD41-EBCD-DD11-8300-001A64789508.root",
##    "file:/home/veszpv/CMSSW_2_2_3/data/LM1/866EEF02-D6CC-DD11-A51D-00E081791853.root",
##    "file:/home/veszpv/CMSSW_2_2_3/data/LM1/8812264E-B2CD-DD11-9ADB-001A64789D28.root",
##    "file:/home/veszpv/CMSSW_2_2_3/data/LM1/8E2880A8-A5CD-DD11-83F8-00E08178C181.root",
##    "file:/home/veszpv/CMSSW_2_2_3/data/LM1/909C4DA0-F7CC-DD11-8BE3-00E08178C179.root",
##    "file:/home/veszpv/CMSSW_2_2_3/data/LM1/A20BD48D-EDCD-DD11-8360-00E08178C189.root",
##    "file:/home/veszpv/CMSSW_2_2_3/data/LM1/AC677B21-CFCD-DD11-ABE7-00E08178C097.root",
##    "file:/home/veszpv/CMSSW_2_2_3/data/LM1/B4CD17BF-F0CC-DD11-8CA3-00E08178C117.root",
##    "file:/home/veszpv/CMSSW_2_2_3/data/LM1/B806F61F-31CF-DD11-BFCA-003048635C78.root",
##    "file:/home/veszpv/CMSSW_2_2_3/data/LM1/C21E8290-C3CD-DD11-8CF2-00E08178C0B1.root",
##    "file:/home/veszpv/CMSSW_2_2_3/data/LM1/C6D92D53-EBCD-DD11-8603-003048635E40.root",
##    "file:/home/veszpv/CMSSW_2_2_3/data/LM1/C8DB0D90-EDCD-DD11-B64D-00E08178C07B.root",
##    "file:/home/veszpv/CMSSW_2_2_3/data/LM1/CA48DBD8-F0CC-DD11-B576-003048670B64.root",
##    "file:/home/veszpv/CMSSW_2_2_3/data/LM1/DA9AA256-70CE-DD11-BC6C-0015170AE780.root",
##    "file:/home/veszpv/CMSSW_2_2_3/data/LM1/DC296707-74CE-DD11-B467-003048673E9C.root",
##    "file:/home/veszpv/CMSSW_2_2_3/data/LM1/EC9C2983-6CCE-DD11-9594-003048670B4A.root",
##    "file:/home/veszpv/CMSSW_2_2_3/data/LM1/F049A07C-F1CD-DD11-B2FF-00E08179189F.root",
##    "file:/home/veszpv/CMSSW_2_2_3/data/LM1/F0EC3E19-95CE-DD11-A7C2-003048674048.root",
##    "file:/home/veszpv/CMSSW_2_2_3/data/LM1/F441C2B4-1ACC-DD11-9C41-00E08178C06F.root",
##    "file:/home/veszpv/CMSSW_2_2_3/data/LM1/F456C245-EBCD-DD11-A67C-00E081791805.root",
##    "file:/home/veszpv/CMSSW_2_2_3/data/LM1/F6483E9A-80CE-DD11-A954-00E0817917EB.root",
##    "file:/home/veszpv/CMSSW_2_2_3/data/LM1/F68C1DF2-F1CD-DD11-9854-00E08178C0B9.root",
##    "file:/home/veszpv/CMSSW_2_2_3/data/LM1/F6E9B8E3-CFCE-DD11-A538-00E081791867.root",
##    "file:/home/veszpv/CMSSW_2_2_3/data/LM1/FA1842F3-3DCC-DD11-ACB3-00E08178C08C.root"
    )
)

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(10)
)

process.TFileService = cms.Service("TFileService",
    fileName = cms.string('debNtupleMaker.root')
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

    genJetConfig = cms.PSet(
        storeNJets = cms.int32(1),
        jetTag = cms.InputTag("sisCone5GenJets"),
        selectionType = cms.string("NONE"),
        correction = cms.vstring("HAD", "UDS"),
        sortBy = cms.string("et")
    ),

    patJetConfig = cms.PSet(
        storeNJets = cms.int32(4),
        jetTag = cms.InputTag("allLayer1Jets"),
        selectionType = cms.string("NONE"),
        correction = cms.vstring("HAD", "UDS"),
        sortBy = cms.string("et")
    ),
   
    patMetConfig = cms.PSet(
        metTag = cms.InputTag("allLayer1METs"),
        selectionType = cms.string("NONE"),
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

