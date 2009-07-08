import FWCore.ParameterSet.Config as cms

process = cms.Process("RA4SynchronizationProc")

process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(
#    "/WJets-madgraph/susy-SUSY_WJets-madgraph_229_SUSYPAT_V5_v2-00a24c1fa2b61c755cc684c50e9bc48c/USER"
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_528.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_527.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_526.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_525.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_524.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_523.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_522.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_521.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_520.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_52.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_519.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_518.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_517.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_516.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_515.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_514.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_513.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_512.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_511.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_510.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_51.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_509.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_508.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_507.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_506.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_505.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_504.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_503.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_502.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_501.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_500.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_50.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_5.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_499.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_498.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_497.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_496.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_495.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_494.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_493.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_492.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_491.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_490.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_49.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_489.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_488.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_487.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_486.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_485.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_484.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_483.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_482.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_481.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_480.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_48.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_479.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_478.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_477.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_476.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_475.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_474.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_473.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_472.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_471.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_470.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_47.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_469.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_468.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_467.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_466.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_465.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_464.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_463.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_462.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_461.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_460.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_46.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_459.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_458.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_457.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_456.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_455.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_454.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_453.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_452.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_451.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_450.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_45.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_449.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_448.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_447.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_446.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_445.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_444.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_443.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_442.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_441.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_440.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_44.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_439.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_438.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_437.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_436.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_435.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_434.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_433.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_432.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_431.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_430.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_43.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_429.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_428.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_427.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_426.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_425.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_424.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_423.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_422.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_421.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_420.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_42.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_419.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_418.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_417.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_416.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_415.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_414.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_413.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_412.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_411.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_410.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_41.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_409.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_408.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_407.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_406.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_405.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_404.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_403.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_402.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_401.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_400.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_40.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_4.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_399.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_398.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_397.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_396.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_395.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_394.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_393.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_392.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_391.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_390.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_39.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_389.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_388.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_387.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_386.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_385.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_384.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_383.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_382.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_381.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_380.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_38.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_379.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_378.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_377.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_376.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_375.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_374.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_373.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_372.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_371.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_370.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_37.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_369.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_368.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_367.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_366.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_365.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_364.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_363.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_362.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_361.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_360.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_36.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_359.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_358.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_357.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_356.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_355.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_354.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_353.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_352.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_351.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_350.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_35.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_349.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_348.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_347.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_346.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_345.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_344.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_343.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_342.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_341.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_340.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_34.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_339.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_338.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_337.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_336.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_335.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_334.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_333.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_332.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_331.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_330.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_33.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_329.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_328.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_327.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_326.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_325.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_324.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_323.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_322.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_321.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_320.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_32.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_319.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_318.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_317.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_316.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_315.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_314.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_313.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_312.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_311.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_310.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_31.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_309.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_308.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_307.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_306.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_305.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_304.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_303.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_302.root"
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

