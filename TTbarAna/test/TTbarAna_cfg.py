import FWCore.ParameterSet.Config as cms

process = cms.Process("TTbarAnaProc")
#process.load("FWCore.MessageService.MessageLogger_cfi")
##process.load("SimGeneral.HepPDTESSource.pythiapdt_cfi")

process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(
    "file:/home/veszpv/CMSSW_2_2_9/data/TTbar/patLayer1_100.root",
    "file:/home/veszpv/CMSSW_2_2_9/data/TTbar/patLayer1_101.root",
    "file:/home/veszpv/CMSSW_2_2_9/data/TTbar/patLayer1_102.root",
    "file:/home/veszpv/CMSSW_2_2_9/data/TTbar/patLayer1_103.root",
    "file:/home/veszpv/CMSSW_2_2_9/data/TTbar/patLayer1_104.root",
    "file:/home/veszpv/CMSSW_2_2_9/data/TTbar/patLayer1_105.root",
    "file:/home/veszpv/CMSSW_2_2_9/data/TTbar/patLayer1_106.root",
    "file:/home/veszpv/CMSSW_2_2_9/data/TTbar/patLayer1_107.root",
    "file:/home/veszpv/CMSSW_2_2_9/data/TTbar/patLayer1_108.root",
    "file:/home/veszpv/CMSSW_2_2_9/data/TTbar/patLayer1_109.root",
    "file:/home/veszpv/CMSSW_2_2_9/data/TTbar/patLayer1_10.root",
    "file:/home/veszpv/CMSSW_2_2_9/data/TTbar/patLayer1_110.root",
    "file:/home/veszpv/CMSSW_2_2_9/data/TTbar/patLayer1_111.root",
    "file:/home/veszpv/CMSSW_2_2_9/data/TTbar/patLayer1_112.root",
    "file:/home/veszpv/CMSSW_2_2_9/data/TTbar/patLayer1_113.root",
##    "file:/home/veszpv/CMSSW_2_2_9/data/TTbar/patLayer1_114.root",
##    "file:/home/veszpv/CMSSW_2_2_9/data/TTbar/patLayer1_115.root",
##    "file:/home/veszpv/CMSSW_2_2_9/data/TTbar/patLayer1_116.root",
##    "file:/home/veszpv/CMSSW_2_2_9/data/TTbar/patLayer1_117.root",
##    "file:/home/veszpv/CMSSW_2_2_9/data/TTbar/patLayer1_118.root",
##    "file:/home/veszpv/CMSSW_2_2_9/data/TTbar/patLayer1_119.root",
##    "file:/home/veszpv/CMSSW_2_2_9/data/TTbar/patLayer1_11.root",
##    "file:/home/veszpv/CMSSW_2_2_9/data/TTbar/patLayer1_120.root",
##    "file:/home/veszpv/CMSSW_2_2_9/data/TTbar/patLayer1_121.root",
##    "file:/home/veszpv/CMSSW_2_2_9/data/TTbar/patLayer1_122.root",
##    "file:/home/veszpv/CMSSW_2_2_9/data/TTbar/patLayer1_123.root",
##    "file:/home/veszpv/CMSSW_2_2_9/data/TTbar/patLayer1_124.root",
##    "file:/home/veszpv/CMSSW_2_2_9/data/TTbar/patLayer1_125.root",
##    "file:/home/veszpv/CMSSW_2_2_9/data/TTbar/patLayer1_126.root",
##    "file:/home/veszpv/CMSSW_2_2_9/data/TTbar/patLayer1_127.root",
##    "file:/home/veszpv/CMSSW_2_2_9/data/TTbar/patLayer1_128.root",
##    "file:/home/veszpv/CMSSW_2_2_9/data/TTbar/patLayer1_129.root",
##    "file:/home/veszpv/CMSSW_2_2_9/data/TTbar/patLayer1_12.root",
##    "file:/home/veszpv/CMSSW_2_2_9/data/TTbar/patLayer1_130.root",
##    "file:/home/veszpv/CMSSW_2_2_9/data/TTbar/patLayer1_131.root",
##    "file:/home/veszpv/CMSSW_2_2_9/data/TTbar/patLayer1_132.root",
##    "file:/home/veszpv/CMSSW_2_2_9/data/TTbar/patLayer1_133.root",
##    "file:/home/veszpv/CMSSW_2_2_9/data/TTbar/patLayer1_134.root",
##    "file:/home/veszpv/CMSSW_2_2_9/data/TTbar/patLayer1_135.root",
##    "file:/home/veszpv/CMSSW_2_2_9/data/TTbar/patLayer1_136.root",
##    "file:/home/veszpv/CMSSW_2_2_9/data/TTbar/patLayer1_137.root",
##    "file:/home/veszpv/CMSSW_2_2_9/data/TTbar/patLayer1_138.root",
##    "file:/home/veszpv/CMSSW_2_2_9/data/TTbar/patLayer1_139.root",
##    "file:/home/veszpv/CMSSW_2_2_9/data/TTbar/patLayer1_13.root",
##    "file:/home/veszpv/CMSSW_2_2_9/data/TTbar/patLayer1_140.root",
##    "file:/home/veszpv/CMSSW_2_2_9/data/TTbar/patLayer1_141.root",
##    "file:/home/veszpv/CMSSW_2_2_9/data/TTbar/patLayer1_142.root",
##    "file:/home/veszpv/CMSSW_2_2_9/data/TTbar/patLayer1_143.root",
##    "file:/home/veszpv/CMSSW_2_2_9/data/TTbar/patLayer1_144.root",
##    "file:/home/veszpv/CMSSW_2_2_9/data/TTbar/patLayer1_145.root",
##    "file:/home/veszpv/CMSSW_2_2_9/data/TTbar/patLayer1_146.root",
##    "file:/home/veszpv/CMSSW_2_2_9/data/TTbar/patLayer1_147.root",
##    "file:/home/veszpv/CMSSW_2_2_9/data/TTbar/patLayer1_148.root",
##    "file:/home/veszpv/CMSSW_2_2_9/data/TTbar/patLayer1_149.root",
##    "file:/home/veszpv/CMSSW_2_2_9/data/TTbar/patLayer1_14.root",
##    "file:/home/veszpv/CMSSW_2_2_9/data/TTbar/patLayer1_150.root",
##    "file:/home/veszpv/CMSSW_2_2_9/data/TTbar/patLayer1_151.root",
##    "file:/home/veszpv/CMSSW_2_2_9/data/TTbar/patLayer1_152.root",
##    "file:/home/veszpv/CMSSW_2_2_9/data/TTbar/patLayer1_153.root",
##    "file:/home/veszpv/CMSSW_2_2_9/data/TTbar/patLayer1_154.root",
##    "file:/home/veszpv/CMSSW_2_2_9/data/TTbar/patLayer1_155.root",
##    "file:/home/veszpv/CMSSW_2_2_9/data/TTbar/patLayer1_156.root",
##    "file:/home/veszpv/CMSSW_2_2_9/data/TTbar/patLayer1_157.root",
##    "file:/home/veszpv/CMSSW_2_2_9/data/TTbar/patLayer1_158.root",
##    "file:/home/veszpv/CMSSW_2_2_9/data/TTbar/patLayer1_159.root",
##    "file:/home/veszpv/CMSSW_2_2_9/data/TTbar/patLayer1_15.root",
##    "file:/home/veszpv/CMSSW_2_2_9/data/TTbar/patLayer1_160.root",
##    "file:/home/veszpv/CMSSW_2_2_9/data/TTbar/patLayer1_161.root",
##    "file:/home/veszpv/CMSSW_2_2_9/data/TTbar/patLayer1_162.root",
##    "file:/home/veszpv/CMSSW_2_2_9/data/TTbar/patLayer1_163.root",
##    "file:/home/veszpv/CMSSW_2_2_9/data/TTbar/patLayer1_164.root",
##    "file:/home/veszpv/CMSSW_2_2_9/data/TTbar/patLayer1_165.root",
##    "file:/home/veszpv/CMSSW_2_2_9/data/TTbar/patLayer1_166.root",
##    "file:/home/veszpv/CMSSW_2_2_9/data/TTbar/patLayer1_167.root",
##    "file:/home/veszpv/CMSSW_2_2_9/data/TTbar/patLayer1_168.root",
##    "file:/home/veszpv/CMSSW_2_2_9/data/TTbar/patLayer1_169.root",
##    "file:/home/veszpv/CMSSW_2_2_9/data/TTbar/patLayer1_16.root",
##    "file:/home/veszpv/CMSSW_2_2_9/data/TTbar/patLayer1_170.root",
##    "file:/home/veszpv/CMSSW_2_2_9/data/TTbar/patLayer1_171.root",
##    "file:/home/veszpv/CMSSW_2_2_9/data/TTbar/patLayer1_172.root",
##    "file:/home/veszpv/CMSSW_2_2_9/data/TTbar/patLayer1_173.root",
##    "file:/home/veszpv/CMSSW_2_2_9/data/TTbar/patLayer1_174.root",
##    "file:/home/veszpv/CMSSW_2_2_9/data/TTbar/patLayer1_175.root",
##    "file:/home/veszpv/CMSSW_2_2_9/data/TTbar/patLayer1_176.root",
##    "file:/home/veszpv/CMSSW_2_2_9/data/TTbar/patLayer1_177.root",
##    "file:/home/veszpv/CMSSW_2_2_9/data/TTbar/patLayer1_178.root",
##    "file:/home/veszpv/CMSSW_2_2_9/data/TTbar/patLayer1_179.root",
##    "file:/home/veszpv/CMSSW_2_2_9/data/TTbar/patLayer1_17.root",
##    "file:/home/veszpv/CMSSW_2_2_9/data/TTbar/patLayer1_180.root",
##    "file:/home/veszpv/CMSSW_2_2_9/data/TTbar/patLayer1_181.root",
##    "file:/home/veszpv/CMSSW_2_2_9/data/TTbar/patLayer1_182.root",
##    "file:/home/veszpv/CMSSW_2_2_9/data/TTbar/patLayer1_183.root",
##    "file:/home/veszpv/CMSSW_2_2_9/data/TTbar/patLayer1_184.root",
##    "file:/home/veszpv/CMSSW_2_2_9/data/TTbar/patLayer1_185.root",
##    "file:/home/veszpv/CMSSW_2_2_9/data/TTbar/patLayer1_186.root",
##    "file:/home/veszpv/CMSSW_2_2_9/data/TTbar/patLayer1_187.root",
##    "file:/home/veszpv/CMSSW_2_2_9/data/TTbar/patLayer1_188.root",
##    "file:/home/veszpv/CMSSW_2_2_9/data/TTbar/patLayer1_189.root",
##    "file:/home/veszpv/CMSSW_2_2_9/data/TTbar/patLayer1_18.root",
##    "file:/home/veszpv/CMSSW_2_2_9/data/TTbar/patLayer1_190.root",
##    "file:/home/veszpv/CMSSW_2_2_9/data/TTbar/patLayer1_191.root",
##    "file:/home/veszpv/CMSSW_2_2_9/data/TTbar/patLayer1_19.root",
##    "file:/home/veszpv/CMSSW_2_2_9/data/TTbar/patLayer1_1.root",
##    "file:/home/veszpv/CMSSW_2_2_9/data/TTbar/patLayer1_20.root",
##    "file:/home/veszpv/CMSSW_2_2_9/data/TTbar/patLayer1_21.root",
##    "file:/home/veszpv/CMSSW_2_2_9/data/TTbar/patLayer1_22.root",
##    "file:/home/veszpv/CMSSW_2_2_9/data/TTbar/patLayer1_23.root",
##    "file:/home/veszpv/CMSSW_2_2_9/data/TTbar/patLayer1_24.root",
##    "file:/home/veszpv/CMSSW_2_2_9/data/TTbar/patLayer1_25.root",
##    "file:/home/veszpv/CMSSW_2_2_9/data/TTbar/patLayer1_26.root",
##    "file:/home/veszpv/CMSSW_2_2_9/data/TTbar/patLayer1_27.root",
##    "file:/home/veszpv/CMSSW_2_2_9/data/TTbar/patLayer1_28.root",
##    "file:/home/veszpv/CMSSW_2_2_9/data/TTbar/patLayer1_29.root",
##    "file:/home/veszpv/CMSSW_2_2_9/data/TTbar/patLayer1_2.root",
##    "file:/home/veszpv/CMSSW_2_2_9/data/TTbar/patLayer1_30.root",
##    "file:/home/veszpv/CMSSW_2_2_9/data/TTbar/patLayer1_31.root",
##    "file:/home/veszpv/CMSSW_2_2_9/data/TTbar/patLayer1_32.root",
##    "file:/home/veszpv/CMSSW_2_2_9/data/TTbar/patLayer1_33.root",
##    "file:/home/veszpv/CMSSW_2_2_9/data/TTbar/patLayer1_34.root",
##    "file:/home/veszpv/CMSSW_2_2_9/data/TTbar/patLayer1_35.root",
##    "file:/home/veszpv/CMSSW_2_2_9/data/TTbar/patLayer1_36.root",
##    "file:/home/veszpv/CMSSW_2_2_9/data/TTbar/patLayer1_37.root",
##    "file:/home/veszpv/CMSSW_2_2_9/data/TTbar/patLayer1_38.root",
##    "file:/home/veszpv/CMSSW_2_2_9/data/TTbar/patLayer1_39.root",
##    "file:/home/veszpv/CMSSW_2_2_9/data/TTbar/patLayer1_3.root",
##    "file:/home/veszpv/CMSSW_2_2_9/data/TTbar/patLayer1_40.root",
##    "file:/home/veszpv/CMSSW_2_2_9/data/TTbar/patLayer1_41.root",
##    "file:/home/veszpv/CMSSW_2_2_9/data/TTbar/patLayer1_42.root",
##    "file:/home/veszpv/CMSSW_2_2_9/data/TTbar/patLayer1_43.root",
##    "file:/home/veszpv/CMSSW_2_2_9/data/TTbar/patLayer1_44.root",
##    "file:/home/veszpv/CMSSW_2_2_9/data/TTbar/patLayer1_45.root",
##    "file:/home/veszpv/CMSSW_2_2_9/data/TTbar/patLayer1_46.root",
##    "file:/home/veszpv/CMSSW_2_2_9/data/TTbar/patLayer1_47.root",
##    "file:/home/veszpv/CMSSW_2_2_9/data/TTbar/patLayer1_48.root",
##    "file:/home/veszpv/CMSSW_2_2_9/data/TTbar/patLayer1_49.root",
##    "file:/home/veszpv/CMSSW_2_2_9/data/TTbar/patLayer1_4.root",
##    "file:/home/veszpv/CMSSW_2_2_9/data/TTbar/patLayer1_50.root",
##    "file:/home/veszpv/CMSSW_2_2_9/data/TTbar/patLayer1_51.root",
##    "file:/home/veszpv/CMSSW_2_2_9/data/TTbar/patLayer1_52.root",
##    "file:/home/veszpv/CMSSW_2_2_9/data/TTbar/patLayer1_53.root",
##    "file:/home/veszpv/CMSSW_2_2_9/data/TTbar/patLayer1_54.root",
##    "file:/home/veszpv/CMSSW_2_2_9/data/TTbar/patLayer1_55.root",
##    "file:/home/veszpv/CMSSW_2_2_9/data/TTbar/patLayer1_56.root",
##    "file:/home/veszpv/CMSSW_2_2_9/data/TTbar/patLayer1_57.root",
##    "file:/home/veszpv/CMSSW_2_2_9/data/TTbar/patLayer1_58.root",
##    "file:/home/veszpv/CMSSW_2_2_9/data/TTbar/patLayer1_59.root",
##    "file:/home/veszpv/CMSSW_2_2_9/data/TTbar/patLayer1_5.root",
##    "file:/home/veszpv/CMSSW_2_2_9/data/TTbar/patLayer1_60.root",
##    "file:/home/veszpv/CMSSW_2_2_9/data/TTbar/patLayer1_61.root",
##    "file:/home/veszpv/CMSSW_2_2_9/data/TTbar/patLayer1_62.root",
##    "file:/home/veszpv/CMSSW_2_2_9/data/TTbar/patLayer1_63.root",
##    "file:/home/veszpv/CMSSW_2_2_9/data/TTbar/patLayer1_64.root",
##    "file:/home/veszpv/CMSSW_2_2_9/data/TTbar/patLayer1_65.root",
##    "file:/home/veszpv/CMSSW_2_2_9/data/TTbar/patLayer1_66.root",
##    "file:/home/veszpv/CMSSW_2_2_9/data/TTbar/patLayer1_67.root",
##    "file:/home/veszpv/CMSSW_2_2_9/data/TTbar/patLayer1_68.root",
##    "file:/home/veszpv/CMSSW_2_2_9/data/TTbar/patLayer1_69.root",
##    "file:/home/veszpv/CMSSW_2_2_9/data/TTbar/patLayer1_6.root",
##    "file:/home/veszpv/CMSSW_2_2_9/data/TTbar/patLayer1_70.root",
##    "file:/home/veszpv/CMSSW_2_2_9/data/TTbar/patLayer1_71.root",
##    "file:/home/veszpv/CMSSW_2_2_9/data/TTbar/patLayer1_72.root",
##    "file:/home/veszpv/CMSSW_2_2_9/data/TTbar/patLayer1_73.root",
##    "file:/home/veszpv/CMSSW_2_2_9/data/TTbar/patLayer1_74.root",
##    "file:/home/veszpv/CMSSW_2_2_9/data/TTbar/patLayer1_75.root",
##    "file:/home/veszpv/CMSSW_2_2_9/data/TTbar/patLayer1_76.root",
##    "file:/home/veszpv/CMSSW_2_2_9/data/TTbar/patLayer1_77.root",
##    "file:/home/veszpv/CMSSW_2_2_9/data/TTbar/patLayer1_78.root",
##    "file:/home/veszpv/CMSSW_2_2_9/data/TTbar/patLayer1_79.root",
##    "file:/home/veszpv/CMSSW_2_2_9/data/TTbar/patLayer1_7.root",
##    "file:/home/veszpv/CMSSW_2_2_9/data/TTbar/patLayer1_80.root",
##    "file:/home/veszpv/CMSSW_2_2_9/data/TTbar/patLayer1_81.root",
##    "file:/home/veszpv/CMSSW_2_2_9/data/TTbar/patLayer1_82.root",
##    "file:/home/veszpv/CMSSW_2_2_9/data/TTbar/patLayer1_83.root",
##    "file:/home/veszpv/CMSSW_2_2_9/data/TTbar/patLayer1_84.root",
##    "file:/home/veszpv/CMSSW_2_2_9/data/TTbar/patLayer1_85.root",
##    "file:/home/veszpv/CMSSW_2_2_9/data/TTbar/patLayer1_86.root",
##    "file:/home/veszpv/CMSSW_2_2_9/data/TTbar/patLayer1_87.root",
##    "file:/home/veszpv/CMSSW_2_2_9/data/TTbar/patLayer1_88.root",
##    "file:/home/veszpv/CMSSW_2_2_9/data/TTbar/patLayer1_89.root",
##    "file:/home/veszpv/CMSSW_2_2_9/data/TTbar/patLayer1_8.root",
##    "file:/home/veszpv/CMSSW_2_2_9/data/TTbar/patLayer1_90.root",
##    "file:/home/veszpv/CMSSW_2_2_9/data/TTbar/patLayer1_91.root",
##    "file:/home/veszpv/CMSSW_2_2_9/data/TTbar/patLayer1_92.root",
##    "file:/home/veszpv/CMSSW_2_2_9/data/TTbar/patLayer1_93.root",
##    "file:/home/veszpv/CMSSW_2_2_9/data/TTbar/patLayer1_94.root",
##    "file:/home/veszpv/CMSSW_2_2_9/data/TTbar/patLayer1_95.root",
##    "file:/home/veszpv/CMSSW_2_2_9/data/TTbar/patLayer1_96.root",
##    "file:/home/veszpv/CMSSW_2_2_9/data/TTbar/patLayer1_97.root",
##    "file:/home/veszpv/CMSSW_2_2_9/data/TTbar/patLayer1_98.root",
##    "file:/home/veszpv/CMSSW_2_2_9/data/TTbar/patLayer1_99.root",
##    "file:/home/veszpv/CMSSW_2_2_9/data/TTbar/patLayer1_9.root"    
    )
)

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(-1)
)

process.TFileService = cms.Service("TFileService",
    fileName = cms.string('TTbarAna.root')
)


process.TTbarAnaMod = cms.EDFilter(
    "TTbarAna",

    patJetConfig = cms.PSet(
        name = cms.string("pjet"),
        storeNJets = cms.uint32(8),
        jetTag = cms.InputTag("allLayer1JetsIC5"), ## try iterative cone
        selectionType = cms.string("TopJetSelection"),
        correction = cms.vstring("HAD", "UDS"),
        sortBy = cms.string("et")
    ),
   
    genJetConfig = cms.PSet(
        name = cms.string("gjet"),
        storeNJets = cms.uint32(6),
        jetTag = cms.InputTag("sisCone5GenJets"),
        selectionType = cms.string("TopGenJetSelection"),
        correction = cms.vstring("HAD", "UDS"),
        sortBy = cms.string("et"),
   ),

##   patMetConfig = cms.PSet(
##        name = cms.string("pmet"),
##        metTag = cms.InputTag("allLayer1METsSC5"),
##        corrections = cms.vstring("uncorrALL", "uncorrMAXN"), ## index
##        storeList = cms.vstring("uncorrALL", "uncorrMAXN")
##    ),

##    patElectronConfig = cms.PSet(
##        name = cms.string("pele"),
##        storeNElectrons = cms.int32(2),
##        electronTag = cms.InputTag("allLayer1Electrons"),
##        selectionType = cms.string("StandardElectronSelection")
##    ),
    
##    patMuonConfig = cms.PSet(
##        name = cms.string("pmuon"),
##        storeNMuons = cms.int32(2),
##        muonTag = cms.InputTag("allLayer1Muons"),
##        selectionType = cms.string("StandardMuonSelection")
##    ),
    
    ttbarConfig = cms.PSet(
        name = cms.string("ttbarHH"),
        storeNCandidates = cms.uint32(4),
        jetIndices = cms.vuint32(0, 1, 2, 3, 4, 5, 6, 7)
    ),

##    hadronicTopDecay = cms.PSet(
##         genParticles = cms.InputTag("genParticles","","HLT"),
##         processTree  = cms.vstring(
##              't(6,-6) -> W, b',
##              'W(24,-24) -> q, qbar',
##              'q(1,2,3,4,5)',
##              'qbar(-1,-2,-3,-4,-5)',
##              'b(5,-5)'
##        ),
##        matchParticles = cms.vuint32(2, 3, 4), ## q, qbar, b
##    )

    mcTtbarHH1ProcessConfig = cms.PSet(
        name = cms.string("mcttbar1"),
        mcProcessTag = cms.InputTag("genParticles","","HLT"),
        processTree  = cms.vstring(
        't(6,-6),W(24,-24),b(5,-5)',
        'W(24,-24),q(1,2,3,4),qbar(-1,-2,-3,-4)'
       )
    ),

    mcTtbarHH2ProcessConfig = cms.PSet(
        name = cms.string("mcttbar2"),
        mcProcessTag = cms.InputTag("genParticles","","HLT"),
        processTree  = cms.vstring(
        't(6,-6),W(24,-24),b(5,-5)',
        'W(24,-24),q(1,2,3,4),qbar(-1,-2,-3,-4)'
       )
    ),

##    drMcTop1PatJetConfig = cms.PSet(
##        name = cms.string("dr_t1_pjet"),
##        storePatJetIndices = cms.vuint32(0, 1, 2, 3, 4, 5, 6, 7),
##        storeMcTopIndices = cms.vstring("b","q","qbar")
##    ),

##    drMcTop2PatJetConfig = cms.PSet(
##        name = cms.string("dr_t2_pjet"),
##        storePatJetIndices = cms.vuint32(0, 1, 2, 3, 4, 5, 6, 7),
##        storeMcTopIndices = cms.vstring("b","q","qbar")
##    ),

    matchTtbarQuarksJets = cms.PSet(
        ## two DeltaR will compute angles between mcTtbarHH{1,2} and Pat Jets
        ## the following 4 parameters are needed only to save DeltaR on ntuples
        ## for later cross-check of the DR values
        nameDr1 = cms.string("dr_t1_pjet"),
        nameDr2 = cms.string("dr_t2_pjet"),
        storeDrMatchQuarks = cms.vstring("b","q","qbar"),
        storeDrPatJetIndices = cms.vuint32(0, 1, 2, 3, 4, 5, 6, 7),
        ## jets matched to quarks will be collected in an MContainer and saved
        nameJets = cms.string("qjet"),
        matchQuarks = cms.vstring("q", "qbar", "b"),
        storeMatchedJets = cms.vstring("b1","q1","qbar1","b2","q2","qbar2")
    )

)

process.p = cms.Path(
    process.TTbarAnaMod
)

