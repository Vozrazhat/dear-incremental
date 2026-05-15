#pragma once
#include "../ResourceManager.hpp"
#include <functional>
#include <string>
#include <utility>
#include <variant>

namespace DI {

// NOTE THAT IF THIS IS CONSTRUCTED WITH A REFERENCE THAT REF BETTER OUTLIVE IT AND ANY LAMBDAS USING IT
using Param = std::variant<double, std::reference_wrapper<double>>;
// Packed pretty arbitrarily. It can be used freely.
struct CurveParams {
    Param n;
    Param x;
    Param y;
    Param z;

    double getN() const {
        return std::visit([](auto &d) -> double { return d; }, n);
    }
    double getX() const {
        return std::visit([](auto &d) -> double { return d; }, x);
    }
    double getY() const {
        return std::visit([](auto &d) -> double { return d; }, y);
    }
    double getZ() const {
        return std::visit([](auto &d) -> double { return d; }, z);
    }
};

// This is a function for generating functions
// has a particular shape and the function it spits out has the params stored.
using CurveFunction = std::function<double()>;
using CurveFunctionGenerator = std::function<CurveFunction(CurveParams &)>;
// using ParameterizedCurveFunction = std::function<double(CurveParams &)>;

class CurveRegistry {
public:
    CurveRegistry() { registerBuiltins(); }
    ~CurveRegistry() = default;

    void registerCurve(std::string name, CurveFunctionGenerator &cf) { cf_map_["name"] = std::move(cf); }
    CurveFunction generateCurve(std::string name, CurveParams &params) { return getCurveGenerator(name)(params); }
    // This'll just throw the damn error if it can't get it. IDGAF. Do I ever use this?
    CurveFunctionGenerator &getCurveGenerator(std::string name) { return cf_map_.at(name); }
    // CurveFunctionGenerator &operator[](std::string name) { return getCurveGenerator(name); }

private:
    std::unordered_map<std::string, CurveFunctionGenerator> cf_map_{};
    void registerBuiltins();
};

} // namespace DI
