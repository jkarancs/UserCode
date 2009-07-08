import FWCore.ParameterSet.Config as cms

process = cms.Process("RA4SynchronizationProc")

process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(
#    "/WJets-madgraph/susy-SUSY_WJets-madgraph_229_SUSYPAT_V5_v2-00a24c1fa2b61c755cc684c50e9bc48c/USER"
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_99.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_98.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_979.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_978.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_977.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_976.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_975.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_974.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_973.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_972.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_971.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_970.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_97.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_969.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_968.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_967.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_966.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_965.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_964.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_963.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_962.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_961.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_960.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_96.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_959.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_958.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_957.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_956.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_955.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_954.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_953.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_952.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_951.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_950.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_95.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_949.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_948.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_947.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_946.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_945.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_944.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_943.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_942.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_941.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_940.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_94.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_939.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_938.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_937.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_936.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_935.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_934.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_933.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_932.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_931.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_930.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_93.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_929.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_928.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_927.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_926.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_925.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_924.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_923.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_922.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_921.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_920.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_92.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_919.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_918.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_917.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_916.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_915.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_914.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_913.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_912.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_911.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_910.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_91.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_909.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_908.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_907.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_906.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_905.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_904.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_903.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_902.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_901.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_900.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_90.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_9.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_899.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_898.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_897.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_896.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_895.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_894.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_893.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_892.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_891.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_890.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_89.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_889.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_888.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_887.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_886.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_885.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_884.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_883.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_882.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_881.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_880.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_88.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_879.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_878.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_877.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_876.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_875.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_874.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_873.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_872.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_871.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_870.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_87.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_869.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_868.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_867.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_866.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_865.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_864.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_863.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_862.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_861.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_860.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_86.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_859.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_858.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_857.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_856.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_855.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_854.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_853.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_852.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_851.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_850.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_85.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_849.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_848.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_847.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_846.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_845.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_844.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_843.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_842.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_841.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_840.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_84.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_839.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_838.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_837.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_836.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_835.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_834.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_833.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_832.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_831.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_830.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_83.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_829.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_828.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_827.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_826.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_825.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_824.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_823.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_822.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_821.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_820.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_82.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_819.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_818.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_817.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_816.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_815.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_814.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_813.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_812.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_811.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_810.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_81.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_809.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_808.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_807.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_806.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_805.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_804.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_803.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_802.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_801.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_800.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_80.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_8.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_799.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_798.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_797.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_796.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_795.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_794.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_793.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_792.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_791.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_790.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_79.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_789.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_788.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_787.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_786.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_785.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_784.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_783.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_782.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_781.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_780.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_78.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_779.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_778.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_777.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_776.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_775.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_774.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_773.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_772.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_771.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_770.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_77.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_769.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_768.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_767.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_766.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_765.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_764.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_763.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_762.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_761.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_760.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_76.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_759.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_758.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_757.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_756.root",
        "/store/group/user/susy/walten/WJets-madgraph/SUSY_WJets-madgraph_229_SUSYPAT_V5_v2/00a24c1fa2b61c755cc684c50e9bc48c/patLayer1_755.root"
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

