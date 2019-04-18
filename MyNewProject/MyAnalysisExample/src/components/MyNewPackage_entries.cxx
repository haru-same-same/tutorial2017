#include "GaudiKernel/DeclareFactoryEntries.h"
#include "MyAnalysisExample/MyAnalysisAlg.h"

DECLARE_ALGORITHM_FACTORY(MyAnalysisAlg)

DECLARE_FACTORY_ENTRIES(MyAnalysisExample) {
  DECLARE_ALGORITHM(MyAnalysisAlg)
}
