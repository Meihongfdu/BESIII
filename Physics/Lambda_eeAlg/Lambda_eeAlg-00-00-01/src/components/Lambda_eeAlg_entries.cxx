#include "GaudiKernel/DeclareFactoryEntries.h"
#include "Lambda_eeAlg/Lambda_ee.h"

DECLARE_ALGORITHM_FACTORY( Lambda_ee )

DECLARE_FACTORY_ENTRIES( Lambda_eeAlg ) {
  DECLARE_ALGORITHM(Lambda_ee);
}

