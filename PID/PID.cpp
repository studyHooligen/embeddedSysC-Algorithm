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
bool PID<T>::PID_setParam(T P,T I,T D){
    this->K_p = P;
    this->K_i = I;
    this->K_d = D;
    return true;
}

template<typename T>
bool PID<T>::PID_setTarget(T target){
    target_ = target;
    return true;
}

#ifndef _use_incremental_PID_

template<typename T>
T PID<T>::PID_update(T status){
    T errNow = target_ - status;  //目前误差值

    error_integral += errNow;   //误差积分
    T result = 
        K_p * errNow +              //比例P
        K_i * error_integral +      //积分I
        K_d * (errNow - error_Pre); //微分D

    if(result > max_) result = max_;    //输出限幅
    else if(result < min_) result = min_;
    
    error_Pre = errNow; //误差记忆
    return result;
}

#else _use_incremental_PID_

template<typename T>
T PID<T>::PID_update(T status){
    T errNow = target_ - status;  //目前误差值

    T delta =   //输出增量
        K_p * (errNow - error_Pre) +    //比例P
        K_i * errNow +                  //积分I
        K_d * (errNow - 2*error_Pre + error_PPre);  //微分D
    
    T result = output_pre + delta;  //输出值

    if(result>max_) result = max_;  //输出限幅
    else if(result<min_) result = min_;

    output_pre = result;    //状态存储
    error_PPre = error_Pre; //误差记忆
    error_Pre = errNow;

    return result;  //返回结果
}

#endif

