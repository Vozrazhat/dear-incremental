#include "CurveRegistry.hpp"

namespace DI {
void CurveRegistry::registerBuiltins() {

    CurveFunctionGenerator linear = [](CurveParams &p) -> CurveFunction {
        CurveParams captured = p;
        return [captured]() { return captured.getX() + captured.getN() * captured.getY(); };
    };
    registerCurve("linear", linear);
}
} // namespace DI