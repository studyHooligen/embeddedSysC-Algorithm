/* 
 * huffmanCode.hpp - The C++ head file of 哈夫曼树
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
#ifndef _HuffmanCode_H_

#define _HuffmanCode_H_
#include<vector>
#include<string>

namespace huffman{

typedef struct huffmanTree
{
    int weight; //节点权重
    char data;   //节点数据
    struct huffmanTree* Parent; //父节点
    struct huffmanTree * Ln,* Rn;   //左右子节点

}huffmanTree,*huffmanTreePtr;

typedef struct huffmanCodeSet
{
    char data;  //编码源字符
    std::string huffmanCode;    //编码密码
    struct huffmanCodeSet* next;    //下一个节点

}huffmanCodeSet,* huffmanCodeSetPtr;

typedef struct huffmanInitNode {
    char data;  //字符数据
    int weight; //权重
}huffmanInitNode,* huffmanInitNodePtr;
    
/* 初始化（建立）哈夫曼树
 * 参数1：编码集元素个数
 * 参数2：编码集头指针
 * 参数3：生成的哈夫曼树存储文件位置
 * 输出： 生成于内存中的哈夫曼树根节点
 */
huffmanTreePtr HuffmanInit(int setSize, huffmanInitNodePtr setPtr, std::string location);

/* 哈夫曼编码密码本生成
 * 参数1：哈夫曼树
 * 输出： 哈夫曼密码本
 */
huffmanCodeSetPtr HuffmanCodeSetInit(huffmanTreePtr sourceTree);

/* 哈夫曼编码
 * 参数1：哈夫曼编码密码本
 * 参数2：待编码文件内容
 * 参数3：编码后文件内容
 * 输出： 编码成功（true）或失败（false）
 */
bool HuffmanEncoding(huffmanCodeSetPtr codeSet,
    std::string sourceContent, std::string& finishContent);


/* 哈夫曼解码
 * 参数1：哈夫曼树头
 * 参数2：待解码文件位置
 * 参数3：解码后文件存储位置
 * 输出： 编码成功（true）或失败（false）
 */
bool HuffmanDecoding(huffmanTreePtr sourceTree,
    std::string sourceContent, std::string& finishContent);

/* 哈夫曼编码打印
 * 参数1：编码后文件内容
 * 参数2：存储文件路径
 * 输出： 无
 */
void codeTxtPrint(std::string sourceContent,std::string saveLocation);

/* 哈夫曼树打印
 * 参数1：哈夫曼树头
 * 输出： 无
 */
void HuffmanTreePrint(huffmanTreePtr sourceTree);

//namespace end
}

#endif