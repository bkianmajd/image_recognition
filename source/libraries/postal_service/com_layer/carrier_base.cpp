#include "libraries/postal_service/com_layer/carrier_base.h"

#include <cstdint>
#include "libraries/postal_service/com_layer/com_defs.h"

namespace com_layer {

CarrierBase::CarrierBase() {
    connect(this, SIGNAL(ReadySend()), this, SLOT(OnReadySend()));
}

}  // namespace com_laer

#endif  // COM_LAYER_ICARIER_H_
