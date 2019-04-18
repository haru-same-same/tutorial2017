#-----------------------------------------------------------------------------
# Athena imports
#-----------------------------------------------------------------------------
from AthenaCommon.Constants import *
from AthenaCommon.AppMgr import theApp
from AthenaCommon.AppMgr import ServiceMgr
import AthenaPoolCnvSvc.ReadAthenaPool
from AthenaCommon.AlgSequence import AlgSequence
job = AlgSequence()

#-----------------------------------------------------------------------------
# Message Service
#-----------------------------------------------------------------------------
# Set output level threshold (2=DEBUG, 3=INFO, 4=WARNING, 5=ERROR, 6=FATAL )
ServiceMgr.MessageSvc.OutputLevel = WARNING
import AthenaServices
AthenaServices.AthenaServicesConf.AthenaEventLoopMgr.OutputLevel = WARNING

#-----------------------------------------------------------------------------
# Input Datasets
#-----------------------------------------------------------------------------
ServiceMgr.EventSelector.InputCollections = [
    '/home/nobe/data2086b/tutorial2017/DxAODs/data17_13TeV.00328374.physics_Main.deriv.DAOD_HIGG2D4.f836_m1824_p3213/DAOD_HIGG2D4.11597487._000001.pool.root.1'
]
theApp.EvtMax = 10 # -1 means all events

#-----------------------------------------------------------------------------
# Algorithms
#-----------------------------------------------------------------------------
from MyAnalysisExample.MyAnalysisExampleConf import *

job += MyAnalysisAlg('MyAnalysisAlg1', OutputLevel = INFO)
job += MyAnalysisAlg('MyAnalysisAlg2', OutputLevel = FATAL)
job += MyAnalysisAlg('MyAnalysisAlg3', OutputLevel = INFO,
    message = "But if you try sometimes, you just might find you get what you need.")

print job
#-----------------------------------------------------------------------------
