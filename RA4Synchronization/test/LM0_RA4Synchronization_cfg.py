import FWCore.ParameterSet.Config as cms

process = cms.Process("RA4SynchronizationProc")

process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(
##    "/SUSY_LM0-sftsht/susy-SUSY_LM0_228_SUSYPAT_V5_v1-01fcb16777fedba722b5ef4d05407ac6/USER"
# "/store/group/user/susy/fronga/SUSY_LM0-sftsht/SUSY_LM0_229_SUSYPAT_V5_v1/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_9.root",
# "/store/group/user/susy/fronga/SUSY_LM0-sftsht/SUSY_LM0_229_SUSYPAT_V5_v1/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_8.root",
# "/store/group/user/susy/fronga/SUSY_LM0-sftsht/SUSY_LM0_229_SUSYPAT_V5_v1/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_7.root",
# "/store/group/user/susy/fronga/SUSY_LM0-sftsht/SUSY_LM0_229_SUSYPAT_V5_v1/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_6.root",
# "/store/group/user/susy/fronga/SUSY_LM0-sftsht/SUSY_LM0_229_SUSYPAT_V5_v1/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_5.root",
# "/store/group/user/susy/fronga/SUSY_LM0-sftsht/SUSY_LM0_229_SUSYPAT_V5_v1/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_41.root",
# "/store/group/user/susy/fronga/SUSY_LM0-sftsht/SUSY_LM0_229_SUSYPAT_V5_v1/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_40.root",
# "/store/group/user/susy/fronga/SUSY_LM0-sftsht/SUSY_LM0_229_SUSYPAT_V5_v1/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_4.root",
# "/store/group/user/susy/fronga/SUSY_LM0-sftsht/SUSY_LM0_229_SUSYPAT_V5_v1/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_39.root",
# "/store/group/user/susy/fronga/SUSY_LM0-sftsht/SUSY_LM0_229_SUSYPAT_V5_v1/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_38.root",
# "/store/group/user/susy/fronga/SUSY_LM0-sftsht/SUSY_LM0_229_SUSYPAT_V5_v1/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_37.root",
# "/store/group/user/susy/fronga/SUSY_LM0-sftsht/SUSY_LM0_229_SUSYPAT_V5_v1/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_36.root",
# "/store/group/user/susy/fronga/SUSY_LM0-sftsht/SUSY_LM0_229_SUSYPAT_V5_v1/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_35.root",
# "/store/group/user/susy/fronga/SUSY_LM0-sftsht/SUSY_LM0_229_SUSYPAT_V5_v1/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_34.root",
# "/store/group/user/susy/fronga/SUSY_LM0-sftsht/SUSY_LM0_229_SUSYPAT_V5_v1/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_33.root",
# "/store/group/user/susy/fronga/SUSY_LM0-sftsht/SUSY_LM0_229_SUSYPAT_V5_v1/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_32.root",
# "/store/group/user/susy/fronga/SUSY_LM0-sftsht/SUSY_LM0_229_SUSYPAT_V5_v1/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_31.root",
# "/store/group/user/susy/fronga/SUSY_LM0-sftsht/SUSY_LM0_229_SUSYPAT_V5_v1/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_30.root",
# "/store/group/user/susy/fronga/SUSY_LM0-sftsht/SUSY_LM0_229_SUSYPAT_V5_v1/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_3.root",
# "/store/group/user/susy/fronga/SUSY_LM0-sftsht/SUSY_LM0_229_SUSYPAT_V5_v1/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_29.root",
# "/store/group/user/susy/fronga/SUSY_LM0-sftsht/SUSY_LM0_229_SUSYPAT_V5_v1/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_28.root",
# "/store/group/user/susy/fronga/SUSY_LM0-sftsht/SUSY_LM0_229_SUSYPAT_V5_v1/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_27.root",
# "/store/group/user/susy/fronga/SUSY_LM0-sftsht/SUSY_LM0_229_SUSYPAT_V5_v1/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_26.root",
# "/store/group/user/susy/fronga/SUSY_LM0-sftsht/SUSY_LM0_229_SUSYPAT_V5_v1/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_25.root",
# "/store/group/user/susy/fronga/SUSY_LM0-sftsht/SUSY_LM0_229_SUSYPAT_V5_v1/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_24.root",
# "/store/group/user/susy/fronga/SUSY_LM0-sftsht/SUSY_LM0_229_SUSYPAT_V5_v1/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_23.root",
# "/store/group/user/susy/fronga/SUSY_LM0-sftsht/SUSY_LM0_229_SUSYPAT_V5_v1/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_22.root",
# "/store/group/user/susy/fronga/SUSY_LM0-sftsht/SUSY_LM0_229_SUSYPAT_V5_v1/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_21.root",
# "/store/group/user/susy/fronga/SUSY_LM0-sftsht/SUSY_LM0_229_SUSYPAT_V5_v1/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_20.root",
# "/store/group/user/susy/fronga/SUSY_LM0-sftsht/SUSY_LM0_229_SUSYPAT_V5_v1/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_2.root",
# "/store/group/user/susy/fronga/SUSY_LM0-sftsht/SUSY_LM0_229_SUSYPAT_V5_v1/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_19.root",
# "/store/group/user/susy/fronga/SUSY_LM0-sftsht/SUSY_LM0_229_SUSYPAT_V5_v1/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_18.root",
# "/store/group/user/susy/fronga/SUSY_LM0-sftsht/SUSY_LM0_229_SUSYPAT_V5_v1/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_17.root",
# "/store/group/user/susy/fronga/SUSY_LM0-sftsht/SUSY_LM0_229_SUSYPAT_V5_v1/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_16.root",
# "/store/group/user/susy/fronga/SUSY_LM0-sftsht/SUSY_LM0_229_SUSYPAT_V5_v1/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_15.root",
# "/store/group/user/susy/fronga/SUSY_LM0-sftsht/SUSY_LM0_229_SUSYPAT_V5_v1/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_14.root",
# "/store/group/user/susy/fronga/SUSY_LM0-sftsht/SUSY_LM0_229_SUSYPAT_V5_v1/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_13.root",
# "/store/group/user/susy/fronga/SUSY_LM0-sftsht/SUSY_LM0_229_SUSYPAT_V5_v1/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_12.root",
# "/store/group/user/susy/fronga/SUSY_LM0-sftsht/SUSY_LM0_229_SUSYPAT_V5_v1/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_11.root",
# "/store/group/user/susy/fronga/SUSY_LM0-sftsht/SUSY_LM0_229_SUSYPAT_V5_v1/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_10.root",
#"/store/group/user/susy/fronga/SUSY_LM0-sftsht/SUSY_LM0_229_SUSYPAT_V5_v1/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_1.root"

#"/store/mc/Summer08/SUSY_LM0-sftsht/GEN-SIM-RECO/IDEAL_V11_v1/0009/FE53DD4E-2FF0-DD11-B7FB-001A645D07C8.root"

#      "file:/home/veszpv/CMSSW_2_2_9/data/LM1/patLayer1_1.root",
#      "file:/home/veszpv/CMSSW_2_2_9/data/LM1/patLayer1_2.root",
#      "file:/home/veszpv/CMSSW_2_2_9/data/LM1/patLayer1_3.root",
#      "file:/home/veszpv/CMSSW_2_2_9/data/LM1/patLayer1_4.root",
#      "file:/home/veszpv/CMSSW_2_2_9/data/LM1/patLayer1_5.root",
#      "file:/home/veszpv/CMSSW_2_2_9/data/LM1/patLayer1_6.root",
#      "file:/home/veszpv/CMSSW_2_2_9/data/LM1/patLayer1_7.root",
#      "file:/home/veszpv/CMSSW_2_2_9/data/LM1/patLayer1_8.root",
#      "file:/home/veszpv/CMSSW_2_2_9/data/LM1/patLayer1_9.root",
#      "file:/home/veszpv/CMSSW_2_2_9/data/LM1/patLayer1_10.root",
#      "file:/home/veszpv/CMSSW_2_2_9/data/LM1/patLayer1_11.root",
#      "file:/home/veszpv/CMSSW_2_2_9/data/LM1/patLayer1_12.root",
#      "file:/home/veszpv/CMSSW_2_2_9/data/LM1/patLayer1_13.root",
#      "file:/home/veszpv/CMSSW_2_2_9/data/LM1/patLayer1_14.root",
#      "file:/home/veszpv/CMSSW_2_2_9/data/LM1/patLayer1_15.root",
#      "file:/home/veszpv/CMSSW_2_2_9/data/LM1/patLayer1_16.root",
#      "file:/home/veszpv/CMSSW_2_2_9/data/LM1/patLayer1_17.root",
#      "file:/home/veszpv/CMSSW_2_2_9/data/LM1/patLayer1_18.root",
#      "file:/home/veszpv/CMSSW_2_2_9/data/LM1/patLayer1_19.root",
#      "file:/home/veszpv/CMSSW_2_2_9/data/LM1/patLayer1_20.root",
#      "file:/home/veszpv/CMSSW_2_2_9/data/LM1/patLayer1_21.root",
#     "file:/home/veszpv/CMSSW_2_2_9/data/LM1/patLayer1_22.root"

      "file:/home/veszpv/CMSSW_2_2_9/data/LM0/patLayer1_1.root",
      "file:/home/veszpv/CMSSW_2_2_9/data/LM0/patLayer1_2.root",
      "file:/home/veszpv/CMSSW_2_2_9/data/LM0/patLayer1_3.root",
      "file:/home/veszpv/CMSSW_2_2_9/data/LM0/patLayer1_4.root"

### Patified data by Anita Kapusi:
### Change the tags to these: ...Tag = cms.InputTag("allLayer1...s"),
#    "rfio:/castor/cern.ch/user/a/akapusi/PAT/V5f/patLayer1__SUSY_LM0-sftsht__Summer08_IDEAL_V11_v1__GEN-SIM-RECO__byV5f_1.root",
#    "rfio:/castor/cern.ch/user/a/akapusi/PAT/V5f/patLayer1__SUSY_LM0-sftsht__Summer08_IDEAL_V11_v1__GEN-SIM-RECO__byV5f_2.root",
#    "rfio:/castor/cern.ch/user/a/akapusi/PAT/V5f/patLayer1__SUSY_LM0-sftsht__Summer08_IDEAL_V11_v1__GEN-SIM-RECO__byV5f_3.root",
#    "rfio:/castor/cern.ch/user/a/akapusi/PAT/V5f/patLayer1__SUSY_LM0-sftsht__Summer08_IDEAL_V11_v1__GEN-SIM-RECO__byV5f_4.root",
#    "rfio:/castor/cern.ch/user/a/akapusi/PAT/V5f/patLayer1__SUSY_LM0-sftsht__Summer08_IDEAL_V11_v1__GEN-SIM-RECO__byV5f_5.root",
#    "rfio:/castor/cern.ch/user/a/akapusi/PAT/V5f/patLayer1__SUSY_LM0-sftsht__Summer08_IDEAL_V11_v1__GEN-SIM-RECO__byV5f_6.root"
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
         selectionType = cms.vstring(
                         "RefAna4JetMetMuon",
                         "RefAna4JetMetElectron"
         )
#        # RefAna4JetMetMuon:
#        # https://twiki.cern.ch/twiki/bin/view/CMS/SusyRA4SingleMuonProjectTable
#        # RefAna4JetMetElectron:
#        # https://twiki.cern.ch/twiki/bin/view/CMS/SusyRA4SingleElectronProjectTable   
     ),
    
    TriggerConfig = cms.PSet(
        name = cms.string("trigger"),
        triggerResults = cms.InputTag("TriggerResults","","HLT"),
        pathNames = cms.vstring(
        'HLT_Ele15_LW_L1R'
    )
    )
    
)

process.p = cms.Path(
    process.RA4SynchronizationMod
)

