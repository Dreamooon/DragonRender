//
// Created by Dreamoon on 2023/3/20.
//

#ifndef DRAGON_COMMON_H
#define DRAGON_COMMON_H

#pragma once

#include<Eigen/Eigen>
#include<limits>
#include<string>
#include<memory>
#include<vector>
#include<map>

using std::string;
using std::shared_ptr;
using std::map;
using std::vector;
using std::make_shared;

typedef unsigned int uint;



constexpr float kEpsilon = 1e-5f;
constexpr float kFInf = std::numeric_limits<float>::infinity();

const float kPi = acos(-1.f);
const float kTowPi = 2.f * kPi;
const float kInvPi = 1.f / kPi;
const float kInvTowPi = 1.f / (2.f * kPi);
const float kInvFourPi = 1.f / (4.f * kPi);

inline float Clamp(float value, float min, float max) {
    if (value < min)
        return min;
    else if (value > max)
        return max;
    else return value;
}


inline float Fresnel(float cosThetaI, float extIOR, float intIOR) {
    float etaI = extIOR, etaT = intIOR;

    if (extIOR == intIOR)
        return 0.0f;
    if (cosThetaI < 0.0f) {
        std::swap(etaI, etaT);
        cosThetaI = -cosThetaI;
    }
    float eta = etaI / etaT,
            sinThetaTSqr = eta * eta * (1 - cosThetaI * cosThetaI);

    if (sinThetaTSqr > 1.0f)
        return 1.0f;

    float cosThetaT = std::sqrt(1.0f - sinThetaTSqr);

    float Rs = (etaI * cosThetaI - etaT * cosThetaT)
               / (etaI * cosThetaI + etaT * cosThetaT);
    float Rp = (etaT * cosThetaI - etaI * cosThetaT)
               / (etaT * cosThetaI + etaI * cosThetaT);

    return (Rs * Rs + Rp * Rp) / 2.0f;
}

#endif //DRAGON_COMMON_H
