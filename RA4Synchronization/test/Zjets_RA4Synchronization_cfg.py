import FWCore.ParameterSet.Config as cms

process = cms.Process("RA4SynchronizationProc")

process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(
#    "ZJets-madgraph/susy-SUSY_ZJets-madgraph_229_SUSYPAT_V5_v2-00a24c1fa2b61c755cc684c50e9bc48c/USER"
        "/store/group/user/susy/walten/ZJets-madgraph/SUSY_ZJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_99.root",
        "/store/group/user/susy/walten/ZJets-madgraph/SUSY_ZJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_98.root",
        "/store/group/user/susy/walten/ZJets-madgraph/SUSY_ZJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_97.root",
        "/store/group/user/susy/walten/ZJets-madgraph/SUSY_ZJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_96.root",
        "/store/group/user/susy/walten/ZJets-madgraph/SUSY_ZJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_95.root",
        "/store/group/user/susy/walten/ZJets-madgraph/SUSY_ZJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_94.root",
        "/store/group/user/susy/walten/ZJets-madgraph/SUSY_ZJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_93.root",
        "/store/group/user/susy/walten/ZJets-madgraph/SUSY_ZJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_92.root",
        "/store/group/user/susy/walten/ZJets-madgraph/SUSY_ZJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_91.root",
        "/store/group/user/susy/walten/ZJets-madgraph/SUSY_ZJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_90.root",
        "/store/group/user/susy/walten/ZJets-madgraph/SUSY_ZJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_9.root",
        "/store/group/user/susy/walten/ZJets-madgraph/SUSY_ZJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_89.root",
        "/store/group/user/susy/walten/ZJets-madgraph/SUSY_ZJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_88.root",
        "/store/group/user/susy/walten/ZJets-madgraph/SUSY_ZJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_87.root",
        "/store/group/user/susy/walten/ZJets-madgraph/SUSY_ZJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_86.root",
        "/store/group/user/susy/walten/ZJets-madgraph/SUSY_ZJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_85.root",
        "/store/group/user/susy/walten/ZJets-madgraph/SUSY_ZJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_84.root",
        "/store/group/user/susy/walten/ZJets-madgraph/SUSY_ZJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_83.root",
        "/store/group/user/susy/walten/ZJets-madgraph/SUSY_ZJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_82.root",
        "/store/group/user/susy/walten/ZJets-madgraph/SUSY_ZJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_81.root",
        "/store/group/user/susy/walten/ZJets-madgraph/SUSY_ZJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_80.root",
        "/store/group/user/susy/walten/ZJets-madgraph/SUSY_ZJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_8.root",
        "/store/group/user/susy/walten/ZJets-madgraph/SUSY_ZJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_79.root",
        "/store/group/user/susy/walten/ZJets-madgraph/SUSY_ZJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_78.root",
        "/store/group/user/susy/walten/ZJets-madgraph/SUSY_ZJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_77.root",
        "/store/group/user/susy/walten/ZJets-madgraph/SUSY_ZJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_76.root",
        "/store/group/user/susy/walten/ZJets-madgraph/SUSY_ZJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_75.root",
        "/store/group/user/susy/walten/ZJets-madgraph/SUSY_ZJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_74.root",
        "/store/group/user/susy/walten/ZJets-madgraph/SUSY_ZJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_73.root",
        "/store/group/user/susy/walten/ZJets-madgraph/SUSY_ZJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_72.root",
        "/store/group/user/susy/walten/ZJets-madgraph/SUSY_ZJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_71.root",
        "/store/group/user/susy/walten/ZJets-madgraph/SUSY_ZJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_70.root",
        "/store/group/user/susy/walten/ZJets-madgraph/SUSY_ZJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_7.root",
        "/store/group/user/susy/walten/ZJets-madgraph/SUSY_ZJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_69.root",
        "/store/group/user/susy/walten/ZJets-madgraph/SUSY_ZJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_68.root",
        "/store/group/user/susy/walten/ZJets-madgraph/SUSY_ZJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_67.root",
        "/store/group/user/susy/walten/ZJets-madgraph/SUSY_ZJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_66.root",
        "/store/group/user/susy/walten/ZJets-madgraph/SUSY_ZJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_65.root",
        "/store/group/user/susy/walten/ZJets-madgraph/SUSY_ZJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_64.root",
        "/store/group/user/susy/walten/ZJets-madgraph/SUSY_ZJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_63.root",
        "/store/group/user/susy/walten/ZJets-madgraph/SUSY_ZJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_62.root",
        "/store/group/user/susy/walten/ZJets-madgraph/SUSY_ZJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_61.root",
        "/store/group/user/susy/walten/ZJets-madgraph/SUSY_ZJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_60.root",
        "/store/group/user/susy/walten/ZJets-madgraph/SUSY_ZJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_6.root",
        "/store/group/user/susy/walten/ZJets-madgraph/SUSY_ZJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_59.root",
        "/store/group/user/susy/walten/ZJets-madgraph/SUSY_ZJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_58.root",
        "/store/group/user/susy/walten/ZJets-madgraph/SUSY_ZJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_57.root",
        "/store/group/user/susy/walten/ZJets-madgraph/SUSY_ZJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_56.root",
        "/store/group/user/susy/walten/ZJets-madgraph/SUSY_ZJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_55.root",
        "/store/group/user/susy/walten/ZJets-madgraph/SUSY_ZJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_54.root",
        "/store/group/user/susy/walten/ZJets-madgraph/SUSY_ZJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_53.root",
        "/store/group/user/susy/walten/ZJets-madgraph/SUSY_ZJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_52.root",
        "/store/group/user/susy/walten/ZJets-madgraph/SUSY_ZJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_51.root",
        "/store/group/user/susy/walten/ZJets-madgraph/SUSY_ZJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_50.root",
        "/store/group/user/susy/walten/ZJets-madgraph/SUSY_ZJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_5.root",
        "/store/group/user/susy/walten/ZJets-madgraph/SUSY_ZJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_49.root",
        "/store/group/user/susy/walten/ZJets-madgraph/SUSY_ZJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_48.root",
        "/store/group/user/susy/walten/ZJets-madgraph/SUSY_ZJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_47.root",
        "/store/group/user/susy/walten/ZJets-madgraph/SUSY_ZJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_46.root",
        "/store/group/user/susy/walten/ZJets-madgraph/SUSY_ZJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_45.root",
        "/store/group/user/susy/walten/ZJets-madgraph/SUSY_ZJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_44.root",
        "/store/group/user/susy/walten/ZJets-madgraph/SUSY_ZJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_43.root",
        "/store/group/user/susy/walten/ZJets-madgraph/SUSY_ZJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_42.root",
        "/store/group/user/susy/walten/ZJets-madgraph/SUSY_ZJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_41.root",
        "/store/group/user/susy/walten/ZJets-madgraph/SUSY_ZJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_40.root",
        "/store/group/user/susy/walten/ZJets-madgraph/SUSY_ZJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_4.root",
        "/store/group/user/susy/walten/ZJets-madgraph/SUSY_ZJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_39.root",
        "/store/group/user/susy/walten/ZJets-madgraph/SUSY_ZJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_38.root",
        "/store/group/user/susy/walten/ZJets-madgraph/SUSY_ZJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_37.root",
        "/store/group/user/susy/walten/ZJets-madgraph/SUSY_ZJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_36.root",
        "/store/group/user/susy/walten/ZJets-madgraph/SUSY_ZJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_35.root",
        "/store/group/user/susy/walten/ZJets-madgraph/SUSY_ZJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_34.root",
        "/store/group/user/susy/walten/ZJets-madgraph/SUSY_ZJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_33.root",
        "/store/group/user/susy/walten/ZJets-madgraph/SUSY_ZJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_32.root",
        "/store/group/user/susy/walten/ZJets-madgraph/SUSY_ZJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_31.root",
        "/store/group/user/susy/walten/ZJets-madgraph/SUSY_ZJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_30.root",
        "/store/group/user/susy/walten/ZJets-madgraph/SUSY_ZJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_3.root",
        "/store/group/user/susy/walten/ZJets-madgraph/SUSY_ZJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_29.root",
        "/store/group/user/susy/walten/ZJets-madgraph/SUSY_ZJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_28.root",
        "/store/group/user/susy/walten/ZJets-madgraph/SUSY_ZJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_27.root",
        "/store/group/user/susy/walten/ZJets-madgraph/SUSY_ZJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_26.root",
        "/store/group/user/susy/walten/ZJets-madgraph/SUSY_ZJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_254.root",
        "/store/group/user/susy/walten/ZJets-madgraph/SUSY_ZJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_253.root",
        "/store/group/user/susy/walten/ZJets-madgraph/SUSY_ZJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_252.root",
        "/store/group/user/susy/walten/ZJets-madgraph/SUSY_ZJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_251.root",
        "/store/group/user/susy/walten/ZJets-madgraph/SUSY_ZJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_250.root",
        "/store/group/user/susy/walten/ZJets-madgraph/SUSY_ZJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_25.root",
        "/store/group/user/susy/walten/ZJets-madgraph/SUSY_ZJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_249.root",
        "/store/group/user/susy/walten/ZJets-madgraph/SUSY_ZJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_248.root",
        "/store/group/user/susy/walten/ZJets-madgraph/SUSY_ZJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_247.root",
        "/store/group/user/susy/walten/ZJets-madgraph/SUSY_ZJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_246.root",
        "/store/group/user/susy/walten/ZJets-madgraph/SUSY_ZJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_245.root",
        "/store/group/user/susy/walten/ZJets-madgraph/SUSY_ZJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_244.root",
        "/store/group/user/susy/walten/ZJets-madgraph/SUSY_ZJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_243.root",
        "/store/group/user/susy/walten/ZJets-madgraph/SUSY_ZJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_242.root",
        "/store/group/user/susy/walten/ZJets-madgraph/SUSY_ZJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_241.root",
        "/store/group/user/susy/walten/ZJets-madgraph/SUSY_ZJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_240.root",
        "/store/group/user/susy/walten/ZJets-madgraph/SUSY_ZJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_24.root",
        "/store/group/user/susy/walten/ZJets-madgraph/SUSY_ZJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_239.root",
        "/store/group/user/susy/walten/ZJets-madgraph/SUSY_ZJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_238.root",
        "/store/group/user/susy/walten/ZJets-madgraph/SUSY_ZJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_237.root",
        "/store/group/user/susy/walten/ZJets-madgraph/SUSY_ZJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_236.root",
        "/store/group/user/susy/walten/ZJets-madgraph/SUSY_ZJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_235.root",
        "/store/group/user/susy/walten/ZJets-madgraph/SUSY_ZJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_234.root",
        "/store/group/user/susy/walten/ZJets-madgraph/SUSY_ZJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_233.root",
        "/store/group/user/susy/walten/ZJets-madgraph/SUSY_ZJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_232.root",
        "/store/group/user/susy/walten/ZJets-madgraph/SUSY_ZJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_231.root",
        "/store/group/user/susy/walten/ZJets-madgraph/SUSY_ZJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_230.root",
        "/store/group/user/susy/walten/ZJets-madgraph/SUSY_ZJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_23.root",
        "/store/group/user/susy/walten/ZJets-madgraph/SUSY_ZJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_229.root",
        "/store/group/user/susy/walten/ZJets-madgraph/SUSY_ZJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_228.root",
        "/store/group/user/susy/walten/ZJets-madgraph/SUSY_ZJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_227.root",
        "/store/group/user/susy/walten/ZJets-madgraph/SUSY_ZJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_226.root",
        "/store/group/user/susy/walten/ZJets-madgraph/SUSY_ZJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_225.root",
        "/store/group/user/susy/walten/ZJets-madgraph/SUSY_ZJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_224.root",
        "/store/group/user/susy/walten/ZJets-madgraph/SUSY_ZJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_223.root",
        "/store/group/user/susy/walten/ZJets-madgraph/SUSY_ZJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_222.root",
        "/store/group/user/susy/walten/ZJets-madgraph/SUSY_ZJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_221.root",
        "/store/group/user/susy/walten/ZJets-madgraph/SUSY_ZJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_220.root",
        "/store/group/user/susy/walten/ZJets-madgraph/SUSY_ZJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_22.root",
        "/store/group/user/susy/walten/ZJets-madgraph/SUSY_ZJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_219.root",
        "/store/group/user/susy/walten/ZJets-madgraph/SUSY_ZJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_218.root",
        "/store/group/user/susy/walten/ZJets-madgraph/SUSY_ZJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_217.root",
        "/store/group/user/susy/walten/ZJets-madgraph/SUSY_ZJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_216.root",
        "/store/group/user/susy/walten/ZJets-madgraph/SUSY_ZJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_215.root",
        "/store/group/user/susy/walten/ZJets-madgraph/SUSY_ZJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_214.root",
        "/store/group/user/susy/walten/ZJets-madgraph/SUSY_ZJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_213.root",
        "/store/group/user/susy/walten/ZJets-madgraph/SUSY_ZJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_212.root",
        "/store/group/user/susy/walten/ZJets-madgraph/SUSY_ZJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_211.root",
        "/store/group/user/susy/walten/ZJets-madgraph/SUSY_ZJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_210.root",
        "/store/group/user/susy/walten/ZJets-madgraph/SUSY_ZJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_21.root",
        "/store/group/user/susy/walten/ZJets-madgraph/SUSY_ZJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_209.root",
        "/store/group/user/susy/walten/ZJets-madgraph/SUSY_ZJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_208.root",
        "/store/group/user/susy/walten/ZJets-madgraph/SUSY_ZJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_207.root",
        "/store/group/user/susy/walten/ZJets-madgraph/SUSY_ZJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_206.root",
        "/store/group/user/susy/walten/ZJets-madgraph/SUSY_ZJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_205.root",
        "/store/group/user/susy/walten/ZJets-madgraph/SUSY_ZJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_204.root",
        "/store/group/user/susy/walten/ZJets-madgraph/SUSY_ZJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_203.root",
        "/store/group/user/susy/walten/ZJets-madgraph/SUSY_ZJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_202.root",
        "/store/group/user/susy/walten/ZJets-madgraph/SUSY_ZJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_201.root",
        "/store/group/user/susy/walten/ZJets-madgraph/SUSY_ZJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_200.root",
        "/store/group/user/susy/walten/ZJets-madgraph/SUSY_ZJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_20.root",
        "/store/group/user/susy/walten/ZJets-madgraph/SUSY_ZJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_2.root",
        "/store/group/user/susy/walten/ZJets-madgraph/SUSY_ZJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_199.root",
        "/store/group/user/susy/walten/ZJets-madgraph/SUSY_ZJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_198.root",
        "/store/group/user/susy/walten/ZJets-madgraph/SUSY_ZJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_197.root",
        "/store/group/user/susy/walten/ZJets-madgraph/SUSY_ZJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_196.root",
        "/store/group/user/susy/walten/ZJets-madgraph/SUSY_ZJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_195.root",
        "/store/group/user/susy/walten/ZJets-madgraph/SUSY_ZJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_194.root",
        "/store/group/user/susy/walten/ZJets-madgraph/SUSY_ZJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_193.root",
        "/store/group/user/susy/walten/ZJets-madgraph/SUSY_ZJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_192.root",
        "/store/group/user/susy/walten/ZJets-madgraph/SUSY_ZJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_191.root",
        "/store/group/user/susy/walten/ZJets-madgraph/SUSY_ZJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_190.root",
        "/store/group/user/susy/walten/ZJets-madgraph/SUSY_ZJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_19.root",
        "/store/group/user/susy/walten/ZJets-madgraph/SUSY_ZJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_189.root",
        "/store/group/user/susy/walten/ZJets-madgraph/SUSY_ZJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_188.root",
        "/store/group/user/susy/walten/ZJets-madgraph/SUSY_ZJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_187.root",
        "/store/group/user/susy/walten/ZJets-madgraph/SUSY_ZJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_186.root",
        "/store/group/user/susy/walten/ZJets-madgraph/SUSY_ZJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_185.root",
        "/store/group/user/susy/walten/ZJets-madgraph/SUSY_ZJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_184.root",
        "/store/group/user/susy/walten/ZJets-madgraph/SUSY_ZJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_183.root",
        "/store/group/user/susy/walten/ZJets-madgraph/SUSY_ZJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_182.root",
        "/store/group/user/susy/walten/ZJets-madgraph/SUSY_ZJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_181.root",
        "/store/group/user/susy/walten/ZJets-madgraph/SUSY_ZJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_180.root",
        "/store/group/user/susy/walten/ZJets-madgraph/SUSY_ZJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_18.root",
        "/store/group/user/susy/walten/ZJets-madgraph/SUSY_ZJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_179.root",
        "/store/group/user/susy/walten/ZJets-madgraph/SUSY_ZJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_178.root",
        "/store/group/user/susy/walten/ZJets-madgraph/SUSY_ZJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_177.root",
        "/store/group/user/susy/walten/ZJets-madgraph/SUSY_ZJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_176.root",
        "/store/group/user/susy/walten/ZJets-madgraph/SUSY_ZJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_175.root",
        "/store/group/user/susy/walten/ZJets-madgraph/SUSY_ZJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_174.root",
        "/store/group/user/susy/walten/ZJets-madgraph/SUSY_ZJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_173.root",
        "/store/group/user/susy/walten/ZJets-madgraph/SUSY_ZJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_172.root",
        "/store/group/user/susy/walten/ZJets-madgraph/SUSY_ZJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_171.root",
        "/store/group/user/susy/walten/ZJets-madgraph/SUSY_ZJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_170.root",
        "/store/group/user/susy/walten/ZJets-madgraph/SUSY_ZJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_17.root",
        "/store/group/user/susy/walten/ZJets-madgraph/SUSY_ZJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_169.root",
        "/store/group/user/susy/walten/ZJets-madgraph/SUSY_ZJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_168.root",
        "/store/group/user/susy/walten/ZJets-madgraph/SUSY_ZJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_167.root",
        "/store/group/user/susy/walten/ZJets-madgraph/SUSY_ZJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_166.root",
        "/store/group/user/susy/walten/ZJets-madgraph/SUSY_ZJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_165.root",
        "/store/group/user/susy/walten/ZJets-madgraph/SUSY_ZJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_164.root",
        "/store/group/user/susy/walten/ZJets-madgraph/SUSY_ZJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_163.root",
        "/store/group/user/susy/walten/ZJets-madgraph/SUSY_ZJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_162.root",
        "/store/group/user/susy/walten/ZJets-madgraph/SUSY_ZJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_161.root",
        "/store/group/user/susy/walten/ZJets-madgraph/SUSY_ZJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_160.root",
        "/store/group/user/susy/walten/ZJets-madgraph/SUSY_ZJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_16.root",
        "/store/group/user/susy/walten/ZJets-madgraph/SUSY_ZJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_159.root",
        "/store/group/user/susy/walten/ZJets-madgraph/SUSY_ZJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_158.root",
        "/store/group/user/susy/walten/ZJets-madgraph/SUSY_ZJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_157.root",
        "/store/group/user/susy/walten/ZJets-madgraph/SUSY_ZJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_156.root",
        "/store/group/user/susy/walten/ZJets-madgraph/SUSY_ZJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_155.root",
        "/store/group/user/susy/walten/ZJets-madgraph/SUSY_ZJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_154.root",
        "/store/group/user/susy/walten/ZJets-madgraph/SUSY_ZJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_153.root",
        "/store/group/user/susy/walten/ZJets-madgraph/SUSY_ZJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_152.root",
        "/store/group/user/susy/walten/ZJets-madgraph/SUSY_ZJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_151.root",
        "/store/group/user/susy/walten/ZJets-madgraph/SUSY_ZJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_150.root",
        "/store/group/user/susy/walten/ZJets-madgraph/SUSY_ZJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_15.root",
        "/store/group/user/susy/walten/ZJets-madgraph/SUSY_ZJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_149.root",
        "/store/group/user/susy/walten/ZJets-madgraph/SUSY_ZJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_148.root",
        "/store/group/user/susy/walten/ZJets-madgraph/SUSY_ZJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_147.root",
        "/store/group/user/susy/walten/ZJets-madgraph/SUSY_ZJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_146.root",
        "/store/group/user/susy/walten/ZJets-madgraph/SUSY_ZJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_145.root",
        "/store/group/user/susy/walten/ZJets-madgraph/SUSY_ZJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_144.root",
        "/store/group/user/susy/walten/ZJets-madgraph/SUSY_ZJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_143.root",
        "/store/group/user/susy/walten/ZJets-madgraph/SUSY_ZJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_142.root",
        "/store/group/user/susy/walten/ZJets-madgraph/SUSY_ZJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_141.root",
        "/store/group/user/susy/walten/ZJets-madgraph/SUSY_ZJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_140.root",
        "/store/group/user/susy/walten/ZJets-madgraph/SUSY_ZJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_14.root",
        "/store/group/user/susy/walten/ZJets-madgraph/SUSY_ZJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_139.root",
        "/store/group/user/susy/walten/ZJets-madgraph/SUSY_ZJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_138.root",
        "/store/group/user/susy/walten/ZJets-madgraph/SUSY_ZJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_137.root",
        "/store/group/user/susy/walten/ZJets-madgraph/SUSY_ZJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_136.root",
        "/store/group/user/susy/walten/ZJets-madgraph/SUSY_ZJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_135.root",
        "/store/group/user/susy/walten/ZJets-madgraph/SUSY_ZJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_134.root",
        "/store/group/user/susy/walten/ZJets-madgraph/SUSY_ZJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_133.root",
        "/store/group/user/susy/walten/ZJets-madgraph/SUSY_ZJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_132.root",
        "/store/group/user/susy/walten/ZJets-madgraph/SUSY_ZJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_131.root",
        "/store/group/user/susy/walten/ZJets-madgraph/SUSY_ZJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_130.root",
        "/store/group/user/susy/walten/ZJets-madgraph/SUSY_ZJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_13.root",
        "/store/group/user/susy/walten/ZJets-madgraph/SUSY_ZJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_129.root",
        "/store/group/user/susy/walten/ZJets-madgraph/SUSY_ZJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_128.root",
        "/store/group/user/susy/walten/ZJets-madgraph/SUSY_ZJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_127.root",
        "/store/group/user/susy/walten/ZJets-madgraph/SUSY_ZJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_126.root",
        "/store/group/user/susy/walten/ZJets-madgraph/SUSY_ZJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_125.root",
        "/store/group/user/susy/walten/ZJets-madgraph/SUSY_ZJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_124.root",
        "/store/group/user/susy/walten/ZJets-madgraph/SUSY_ZJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_123.root",
        "/store/group/user/susy/walten/ZJets-madgraph/SUSY_ZJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_122.root",
        "/store/group/user/susy/walten/ZJets-madgraph/SUSY_ZJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_121.root",
        "/store/group/user/susy/walten/ZJets-madgraph/SUSY_ZJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_120.root",
        "/store/group/user/susy/walten/ZJets-madgraph/SUSY_ZJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_12.root",
        "/store/group/user/susy/walten/ZJets-madgraph/SUSY_ZJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_119.root",
        "/store/group/user/susy/walten/ZJets-madgraph/SUSY_ZJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_118.root",
        "/store/group/user/susy/walten/ZJets-madgraph/SUSY_ZJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_117.root",
        "/store/group/user/susy/walten/ZJets-madgraph/SUSY_ZJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_116.root",
        "/store/group/user/susy/walten/ZJets-madgraph/SUSY_ZJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_115.root",
        "/store/group/user/susy/walten/ZJets-madgraph/SUSY_ZJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_114.root",
        "/store/group/user/susy/walten/ZJets-madgraph/SUSY_ZJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_113.root",
        "/store/group/user/susy/walten/ZJets-madgraph/SUSY_ZJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_112.root",
        "/store/group/user/susy/walten/ZJets-madgraph/SUSY_ZJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_111.root",
        "/store/group/user/susy/walten/ZJets-madgraph/SUSY_ZJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_110.root",
        "/store/group/user/susy/walten/ZJets-madgraph/SUSY_ZJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_11.root",
        "/store/group/user/susy/walten/ZJets-madgraph/SUSY_ZJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_109.root",
        "/store/group/user/susy/walten/ZJets-madgraph/SUSY_ZJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_108.root",
        "/store/group/user/susy/walten/ZJets-madgraph/SUSY_ZJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_107.root",
        "/store/group/user/susy/walten/ZJets-madgraph/SUSY_ZJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_106.root",
        "/store/group/user/susy/walten/ZJets-madgraph/SUSY_ZJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_105.root",
        "/store/group/user/susy/walten/ZJets-madgraph/SUSY_ZJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_104.root",
        "/store/group/user/susy/walten/ZJets-madgraph/SUSY_ZJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_103.root",
        "/store/group/user/susy/walten/ZJets-madgraph/SUSY_ZJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_102.root",
        "/store/group/user/susy/walten/ZJets-madgraph/SUSY_ZJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_101.root",
        "/store/group/user/susy/walten/ZJets-madgraph/SUSY_ZJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_100.root",
        "/store/group/user/susy/walten/ZJets-madgraph/SUSY_ZJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_10.root",
        "/store/group/user/susy/walten/ZJets-madgraph/SUSY_ZJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_1.root"
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
        eventNumber = cms.double(1262816.0),
        eventCrossSec = cms.double(3700.0),
        luminosity = cms.double(100.0),
        #w=0.29299597
        procIdx = cms.int32(40),   # genEventProcID invalid: <0
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

