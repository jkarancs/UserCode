import FWCore.ParameterSet.Config as cms

process = cms.Process("RA4SynchronizationProc")

process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(
#    "/WJets-madgraph/susy-SUSY_WJets-madgraph_229_SUSYPAT_V5_v2-00a24c1fa2b61c755cc684c50e9bc48c/USER"
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_754.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_753.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_752.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_751.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_750.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_75.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_749.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_748.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_747.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_746.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_745.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_744.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_743.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_742.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_741.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_740.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_74.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_739.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_738.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_737.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_736.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_735.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_734.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_733.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_732.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_731.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_730.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_73.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_729.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_728.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_727.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_726.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_725.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_724.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_723.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_722.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_721.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_720.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_72.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_719.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_718.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_717.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_716.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_715.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_714.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_713.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_712.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_711.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_710.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_71.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_709.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_708.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_707.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_706.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_705.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_704.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_703.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_702.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_701.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_700.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_70.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_7.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_699.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_698.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_697.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_696.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_695.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_694.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_693.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_692.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_691.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_690.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_69.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_689.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_688.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_687.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_686.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_685.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_684.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_683.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_682.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_681.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_680.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_68.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_679.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_678.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_677.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_676.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_675.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_674.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_673.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_672.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_671.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_670.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_67.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_669.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_668.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_667.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_666.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_665.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_664.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_663.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_662.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_661.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_660.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_66.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_659.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_658.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_657.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_656.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_655.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_654.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_653.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_652.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_651.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_650.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_65.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_649.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_648.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_647.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_646.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_645.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_644.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_643.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_642.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_641.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_640.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_64.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_639.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_638.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_637.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_636.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_635.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_634.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_633.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_632.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_631.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_630.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_63.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_629.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_628.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_627.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_626.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_625.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_624.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_623.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_622.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_621.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_620.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_62.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_619.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_618.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_617.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_616.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_615.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_614.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_613.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_612.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_611.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_610.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_61.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_609.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_608.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_607.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_606.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_605.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_604.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_603.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_602.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_601.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_600.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_60.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_6.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_599.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_598.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_597.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_596.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_595.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_594.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_593.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_592.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_591.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_590.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_59.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_589.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_588.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_587.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_586.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_585.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_584.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_583.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_582.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_581.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_580.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_58.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_579.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_578.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_577.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_576.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_575.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_574.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_573.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_572.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_571.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_570.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_57.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_569.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_568.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_567.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_566.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_565.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_564.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_563.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_562.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_561.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_560.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_56.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_559.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_558.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_557.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_556.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_555.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_554.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_553.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_552.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_551.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_550.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_55.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_549.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_548.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_547.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_546.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_545.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_544.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_543.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_542.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_541.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_540.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_54.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_539.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_538.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_537.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_536.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_535.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_534.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_533.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_532.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_531.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_530.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_53.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_529.root"
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

