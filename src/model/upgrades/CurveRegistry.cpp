#include "CurveRegistry.hpp"

namespace DI::CurveRegistry {

// void CurveRegistry::registerBuiltins() {

const std::unordered_map<std::string, CurveFunctionGenerator> &registry() {

    // static map that's constructed only once by that lambda
    static const std::unordered_map<std::string, CurveFunctionGenerator> reg = [] {
        // construct all the builtin functions here
        std::unordered_map<std::string, CurveFunctionGenerator> builtins{};

        builtins["linear"] = [](CurveParams &p) -> CurveFunction {
            CurveParams captured = p;
            return [captured] { return captured.getX() + captured.getN() * captured.getY(); };
        };

        return builtins;
    }();

    return reg;
};

//     CurveFunctionGenerator linear = [](CurveParams &p) -> CurveFunction {
//         CurveParams captured = p;
//         return [captured]() { return captured.getX() + captured.getN() * captured.getY(); };
//     };
//     registerCurve("linear", linear);
// }
} // namespace DI::CurveRegistry