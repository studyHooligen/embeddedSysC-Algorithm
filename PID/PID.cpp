/* 
 * PID.cpp - The C++ source file of PID controller
 * NOTE: This file is based on C++11
 *
 * Copyright (c) 2020-, FOSH Project
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author            Notes           mail
 * 2020-06-14     StudyHooligen     first version   2373180028@qq.com
 */
#include "PID/PID.hpp"

template<typename T>
PID<T>::PID(T P,T I,T D,T outMax,T outMin)
    :K_p(P),K_i(I),K_d(D),
    max_(outMax),min_(outMin){
}

template<typename T>
bool PID<T>::PID_setTarget(T target){
    target_ = target;
    return true;
}

template<typename T>
bool PID<T>::PID_setParam(T P,T I,T D){
    this->K_p = P;
    this->K_i = I;
    this->K_d = D;
    return true;
}

template<typename T>
bool PID<T>::PID_setThreshold(T outMin,T outMax){
    max_ = outMax;
    min_ = outMin;
    return true;
}

template<typename T>
T PID<T>::PID_updateDelta(T status){
    T errNow = target_ - status;  //目前误差值

    T delta =   //输出增量
        K_p * (errNow - error_Pre) +    //比例P
        K_i * errNow +                  //积分I
        K_d * (errNow - 2*error_Pre + error_PPre);  //微分D

    if(delta>max_) delta = max_;  //输出限幅
    else if(delta<min_) delta = min_;

    error_PPre = error_Pre; //误差记忆
    error_Pre = errNow;

    return delta;  //返回结果
}

#ifdef PID_use_integral

template<typename T>
T PID<T>::PID_updateStatus(T status){

    output_pre += this->PID_updateDelta(status);
    
    if(output_pre>max_) output_pre = max_;  //输出限幅
    else if(output_pre<min_) output_pre = min_;

    return output_pre;
}

#endif
