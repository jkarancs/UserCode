import FWCore.ParameterSet.Config as cms

process = cms.Process("RA4SynchronizationProc")

process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(
#    "/WJets-madgraph/susy-SUSY_WJets-madgraph_229_SUSYPAT_V5_v2-00a24c1fa2b61c755cc684c50e9bc48c/USER"
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_301.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_300.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_30.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_3.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_299.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_298.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_297.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_296.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_295.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_294.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_293.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_292.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_291.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_290.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_29.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_289.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_288.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_287.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_286.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_285.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_284.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_283.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_282.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_281.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_280.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_28.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_279.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_278.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_277.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_276.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_275.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_274.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_273.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_272.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_271.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_270.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_27.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_269.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_268.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_267.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_266.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_265.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_264.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_263.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_262.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_261.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_260.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_26.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_259.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_258.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_257.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_256.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_255.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_254.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_253.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_252.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_251.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_250.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_25.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_249.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_248.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_247.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_246.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_245.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_244.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_243.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_242.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_241.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_240.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_24.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_239.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_238.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_237.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_236.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_235.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_234.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_233.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_232.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_231.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_230.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_23.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_229.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_228.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_227.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_226.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_225.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_224.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_223.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_222.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_221.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_220.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_22.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_219.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_218.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_217.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_216.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_215.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_214.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_213.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_212.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_211.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_210.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_21.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_209.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_208.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_207.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_206.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_205.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_204.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_203.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_202.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_201.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_200.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_20.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_2.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_199.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_198.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_197.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_196.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_195.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_194.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_193.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_192.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_191.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_190.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_19.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_189.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_188.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_187.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_186.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_185.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_184.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_183.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_182.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_181.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_180.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_18.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_179.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_178.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_177.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_176.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_175.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_174.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_173.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_172.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_171.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_170.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_17.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_169.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_168.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_167.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_166.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_165.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_164.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_163.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_162.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_161.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_160.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_16.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_159.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_158.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_157.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_156.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_155.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_154.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_153.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_152.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_151.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_150.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_15.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_149.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_148.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_147.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_146.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_145.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_144.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_143.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_142.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_141.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_140.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_14.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_139.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_138.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_137.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_136.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_135.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_134.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_133.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_132.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_131.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_130.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_13.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_129.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_128.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_127.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_126.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_125.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_124.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_123.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_122.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_121.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_120.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_12.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_119.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_118.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_117.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_116.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_115.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_114.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_113.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_112.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_111.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_110.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_11.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_109.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_108.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_107.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_106.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_105.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_104.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_103.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_102.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_101.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_100.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_10.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_1.root"
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
        eventNumber = cms.double(9745661.0),
        eventCrossSec = cms.double(40000),
        luminosity = cms.double(100.0),
        #w=0.410439
        procIdx = cms.int32(20),   # genEventProcID invalid: <0
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

