/* 
 * hashTable.hpp - The C++ head file of 哈希树
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
#pragma once
#include<string>
#include<vector>
#include<ctime>

namespace hash {
	//采用除留余数法构造哈希表
	//冲突解决方案为：伪随机探测再散列法
	
	typedef struct hashTable
	{
		std::vector<std::string> data;	//哈希表中存储的数据

		int hashMod;	//哈希函数除数
		std::vector<int> hashRN;	//哈希函数冲突时使用的随机数序列
	}hashTable,* hashTablePtr;

	/*	函数功能：产生哈希表
	*	参数1：建立的查找数据
	*	参数2：数据量
	*	参数3：用户给定的哈希除数摸
	*	返回值：建立好的哈希存储表指针
	*/
	hashTablePtr hashCreate(std::vector<std::string> inputData, int size,int hashMod);

	/*	函数功能：在指定哈希表中查找数据
	*	参数1：建立好的哈希表指针
	*	参数2：查找的数据
	*	参数3：查找的数据结果存储地址
	*	返回值：查找结果成功（Bool：true）或者失败（false）
	*/
	bool hashSearch(const hashTablePtr sourceTable, const std::string targetID, std::string* resault);


	/**********************开始函数定义*******************************/
	hashTablePtr hashCreate(std::vector<std::string> inputData, int size, int hashMod) {
		//建立哈希表（动态内存）
		hashTablePtr hashT = new hashTable;
		hashT->hashMod = hashMod;
		hashT->data.resize(size*2);	//最坏情况下，两倍内存空间

		srand(time(0)); //随机数发生器初始化

		for (int i = 0,key = 0,H_key; i < size; i++) {
			key = inputData[i].front() + inputData[i].back();	//提取关键字

			H_key = key % hashMod;	//哈希函数
			
			if ((hashT->data)[H_key].empty()) {	//不冲突
				(hashT->data)[H_key] = inputData[i];	//存入数据
				//std::cout << "insert(no conflict) :" << inputData[i] //调试用
				//	<< " to " << H_key << std::endl;
			}
			else {
				int j = 0;
				while (j < hashT->hashRN.size() && hashT->hashRN[j]) {
					H_key = (key + hashT->hashRN[j]) % hashMod;	//哈希冲突函数
					if ((hashT->data)[H_key].empty()) {	//不冲突
						(hashT->data)[H_key] = inputData[i];	//存入数据
						//std::cout << "insert(conflict) :" << inputData[i]	//调试用
						//	<< " to " << H_key << " with random: " 
						//	<< hashT->hashRN[j] << std::endl;
						j = -1;	//退出循环标志位
						break;
					}
					else {
						//发生冲突
						j++;
						continue;
					}
				}
				if (j == -1) continue;
				else {
					while (1)
					{
						int RN = rand();	//生成随机数

						H_key = (key + RN) % hashMod;	//哈希冲突函数
						
						if ((hashT->data)[H_key].empty()) {	//不冲突
							(hashT->data)[H_key] = inputData[i];	//存入数据
							hashT->hashRN.push_back(RN);	//该有效随机数存入随机数表
							//std::cout << "insert(conflict) :" << inputData[i]	//调试用
							//	<< " to " << H_key << " with random(create): " 
							//	<< RN << std::endl;
							break;
						}
						//如果冲突，则重新生成随机数，直到找到有效随机数为止
					}
				}
			}
		}
		return hashT;
	}

	bool hashSearch(const hashTablePtr sourceTable, const std::string targetID, std::string* resault) {
		int key = targetID.front() + targetID.back();	//提取关键值
		int H_key = key % sourceTable->hashMod;	//哈希函数
		if (sourceTable->data[H_key] == targetID) {
			*resault = sourceTable->data[H_key];	//结果返回
			return true;	//成功查找
		}
		else {
			for (auto i : sourceTable->hashRN) {
				H_key = (key + i) % sourceTable->hashMod;	//哈希冲突函数
				if (sourceTable->data[H_key] == targetID) {
					*resault = sourceTable->data[H_key];	//结果返回
					return true;	//查找成功
				}
			}
			return false;	//查找失败
		}
	}
}
