/* 
 * PID.hpp - The C++ head file of PID controller
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
#ifndef _PID_H_
#define _PID_H_

#define _use_incremental_PID_ //使用增量式PID

template<typename T>
class PID
{

private:
/************ 内部参数 *************/
    T K_p = 0;  //比例增益
    T K_i = 0;  //积分增益
    T K_d = 0;  //微分增益

    T target_ = 0;   //输出目标值
    T error_Pre = 0;    //上一次误差

#ifdef _use_incremental_PID_
    T error_PPre = 0;   //上上次误差
    T output_pre = 0;   //上次输出值
#else
    T error_integral = 0;   //误差积分值
#endif

    T max_ = 65536;  //PID输出最大值
    T min_ = 0;  //PID输出最小值

public:
/*********** 模块接口 ***********/
    typedef PID * PIDptr;   //模块指针

    /* 概要：默认构造函数
     * 入参：无
    */
    PID();
    
    /* 概要：带参构造函数
     * 入参：
     *      P: 比例系数
     *      I：积分系数
     *      D：微分系数
    */
    PID(T P,T I,T D,T outMax,T outMin);
    
    /* 概要：默认析构函数
     * 入参：无
    */
    ~PID();

    /* 概要：改变PID实例参数
     * 入参：
     *      P: 比例系数
     *      I：积分系数
     *      D：微分系数
     * 回参：参数设置成功或失败
    */
    bool PID_setParam(T P,T I,T D);
    
    /* 概要：改变PID实例参数
     * 入参：
     *      P: 比例系数
     *      I：积分系数
     *      D：微分系数
     * 回参：参数设置成功或失败
    */
    bool PID_setTarget(T target);

    /* 概要：求取PID实例输出值
     * 入参：
     *      status：测量目标输出值
     * 回参：控制器输出值
    */
    T PID_update(T status);
    
    /* 概要：获取P参数
     * 入参：无
     * 回参：P参数
     */
    T PID_getKp()
    {
        return K_p;
    }
    
    /* 概要：获取P参数
     * 入参：无
     * 回参：P参数
     */
    T PID_getKi()
    {
        return K_i;
    }
    
    /* 概要：获取P参数
     * 入参：无
     * 回参：P参数
     */
    T PID_getKd()
    {
        return K_d;
    }
    
};

#endif
