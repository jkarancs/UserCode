import FWCore.ParameterSet.Config as cms

process = cms.Process("RA4MuonStudyProc")
#process.load("FWCore.MessageService.MessageLogger_cfi")
##process.load("SimGeneral.HepPDTESSource.pythiapdt_cfi")

process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(

	
     "file:/home/veszpv/CMSSW_2_2_9/data/LM1/patLayer1_1.root",
     #"file:/home/veszpv/CMSSW_2_2_9/data/LM1/patLayer1_2.root",
     #"file:/home/veszpv/CMSSW_2_2_9/data/LM1/patLayer1_3.root",
     #"file:/home/veszpv/CMSSW_2_2_9/data/LM1/patLayer1_4.root",
     #"file:/home/veszpv/CMSSW_2_2_9/data/LM1/patLayer1_5.root",
     #"file:/home/veszpv/CMSSW_2_2_9/data/LM1/patLayer1_6.root",
     #"file:/home/veszpv/CMSSW_2_2_9/data/LM1/patLayer1_7.root",
     #"file:/home/veszpv/CMSSW_2_2_9/data/LM1/patLayer1_8.root",
     #"file:/home/veszpv/CMSSW_2_2_9/data/LM1/patLayer1_9.root",
     #"file:/home/veszpv/CMSSW_2_2_9/data/LM1/patLayer1_10.root",
     #"file:/home/veszpv/CMSSW_2_2_9/data/LM1/patLayer1_11.root",
     #"file:/home/veszpv/CMSSW_2_2_9/data/LM1/patLayer1_12.root",
     #"file:/home/veszpv/CMSSW_2_2_9/data/LM1/patLayer1_13.root",
     #"file:/home/veszpv/CMSSW_2_2_9/data/LM1/patLayer1_14.root",
     #"file:/home/veszpv/CMSSW_2_2_9/data/LM1/patLayer1_15.root",
     #"file:/home/veszpv/CMSSW_2_2_9/data/LM1/patLayer1_16.root",
     #"file:/home/veszpv/CMSSW_2_2_9/data/LM1/patLayer1_17.root",
     #"file:/home/veszpv/CMSSW_2_2_9/data/LM1/patLayer1_18.root",
     #"file:/home/veszpv/CMSSW_2_2_9/data/LM1/patLayer1_19.root",
     #"file:/home/veszpv/CMSSW_2_2_9/data/LM1/patLayer1_20.root",
     #"file:/home/veszpv/CMSSW_2_2_9/data/LM1/patLayer1_21.root",
     #"file:/home/veszpv/CMSSW_2_2_9/data/LM1/patLayer1_22.root"
     # "file:/home/veszpv/CMSSW_2_2_3/data/LM1-F441C2B4-1ACC-DD11-9C41-00E08178C06F.root"
	  
       
    )
)

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(20)
)

process.TFileService = cms.Service("TFileService",
    fileName = cms.string('RA4muon.root')
)
#SimpleMemoryCheck = cms.Service("SimpleMemoryCheck",
#                                ignoreTotal = cms.untracked.int32(1)
#)

process.RA4MuonStudyMod = cms.EDFilter(
    "RA4MuonStudy",

    patMuonConfig = cms.PSet(
        name = cms.string("pmuon"),
        storeNMuons = cms.int32(1),
        muonTag = cms.InputTag("allLayer1Muons"),
        selectionType = cms.string("RefAna4JetMetMuon")
    ),

    
    promptMuonConfig = cms.PSet(
        mcProcessTag = cms.InputTag("genParticles","","HLT"),
        name = cms.string('promptmuon'), 
        processTree  = cms.vstring(
          '~chi1+(1000024,-1000024),mu(13,-13)'       
	
        ),
        storeList = cms.vstring("~chi1+", "mu")
    ),
      
    mcMuonConfig = cms.PSet(
        mcParticleTag = cms.InputTag("genParticles","","HLT"),
        name = cms.string('mcmuon'),  
  
        mcParticlePdgId = cms.vint32(13,-13),
        mcParticleStatus = cms.int32(1), 
        storeNParticles = cms.int32(4),
        selectionType = cms.string("Origin"),
        sortBy = cms.string("pt")
    )
    
)

process.p = cms.Path(
    process.RA4MuonStudyMod
)

