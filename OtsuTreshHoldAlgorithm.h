#include "ITreshHoldAlgorithm.h"

class OtsuTreshHoldAlgorithm : public IThreshHoldAlgorithm
{
public:
    OtsuTreshHoldAlgorithm();

    int FindTreshHold(const IBrightImage& image) override;
};
