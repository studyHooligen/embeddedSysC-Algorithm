/* 
 * huffmanCode.cpp - The C++ head file of 哈夫曼树
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
#include "HuffmanCode.hpp"
#include<algorithm>
#include<iostream>
#include<fstream>


namespace huffman {

	 static bool huffmanInitNodeCompare(huffmanInitNode d1, huffmanInitNode d2){
		return d1.weight < d2.weight;
	 }
	
	huffmanTreePtr HuffmanInit(int setSize, huffmanInitNodePtr setPtr, std::string location){
		//�����������ַ�������
		std::sort(setPtr, setPtr + setSize, huffmanInitNodeCompare);
		
		//��ӡ�������������ã�
		std::cout << std::endl << "after sort:" << std::endl;
		for (int i = 0; i < setSize; i++) {
			std::cout << i + 1 << "st.data :" << setPtr[i].data 
				<<". weight:"<<setPtr[i].weight<< std::endl;
		}

		//��ʼ������תΪ���ڵ㣬��ƴ��Ϊ����
		huffmanTreePtr root = new huffmanTree;
		root->data = setPtr[0].data;
		root->weight = setPtr[0].weight;
		root->Parent = root->Ln = root->Rn = nullptr;
		huffmanTreePtr endPtr = root;
		for (int i = 1; i < setSize; i++) {
			endPtr->Parent = new huffmanTree;
			endPtr = endPtr->Parent;
			
			endPtr->data = setPtr[i].data;
			endPtr->weight = setPtr[i].weight;
			endPtr->Parent = endPtr->Rn = endPtr->Ln = nullptr;
		}

		//��ӡ������������������ã�
		std::cout << std::endl << "convert to Tree linkList:" << std::endl;
		for (huffmanTreePtr i = root; i != endPtr; i = i->Parent)
			std::cout << "data:" << i->data << ". weight:" << i->weight << std::endl;
		std::cout << "data:" << endPtr->data << ". weight:" << endPtr->weight << std::endl;
		
		//������δ�����Ľڵ㲢��ʱ
		while (root->Parent) {
			//ȥ����С������Ԫ�غ󣬽ڵ��ַ
			auto nextRoot = root->Parent->Parent;

			//����СȨ�ص������ڵ���ȡ�������γ��½ڵ�
			auto newNode = new huffmanTree;	//�����ڵ�
			newNode->Ln = root;	//��С�ķ�����Ҷ
			newNode->Rn = root->Parent;	///�ڶ�С�ķ�����Ҷ
			newNode->Parent = nextRoot;
			newNode->weight = root->weight + root->Parent->weight;	//Ȩ��Ϊ��Ҷ��
			newNode->data = 0;

			//ת��Ϊ��Ҷ�Ľڵ㣬��ָ���Ϊ�������½ڵ�
			root->Parent->Parent = newNode;
			root->Parent = newNode;

			//���û��δ����ڵ��ˣ�ֱ�ӷ���
			if (!nextRoot) return newNode;

			if (newNode->weight < nextRoot->weight) {
				root = newNode;
				continue;	//�Ѿ�Ĭ��Ϊ�ź�˳��״̬
			}
			else {
				auto insertPtr = nextRoot;//����λ��
				while (insertPtr->Parent && (insertPtr->Parent->weight < newNode->weight) )
				{
					insertPtr = insertPtr->Parent;
				}
				//����ڵ�
				newNode->Parent = insertPtr->Parent;
				insertPtr->Parent = newNode;
				root = nextRoot;
			}

		}
		//������ɣ����ؽڵ�
		return root;
	}


	void HuffmanTreePrint(huffmanTreePtr sourceTree) {

		typedef struct printHuffmanTreeNodeLink
		{	//��ȱ����������������ṹ
			huffmanTreePtr node;	//���ڵ�
			struct printHuffmanTreeNodeLink * next;
		}nodeLink,*nodeLinkPtr;

		typedef struct printHuffmanTreeCountLink
		{	//��ǰ��������ڵ�����������ṹ
			int count;	//����
			struct printHuffmanTreeCountLink* next;
		}countLink,* countLinkPtr;

		//��ʼ��������Ϊ����ͷ
		nodeLinkPtr nodeListHead = new nodeLink;	
		nodeListHead->next = nullptr;
		nodeListHead->node = sourceTree;
		nodeLinkPtr nodeListTail = nodeListHead;

		//��ʼ����ǰ��ӡ�еĽڵ����Ϊ1
		countLinkPtr countList = new countLink;
		countList->count = 1;
		//ѭ����������һ�������ڵ�洢������һ��Ľڵ����
		countList->next = new countLink;
		countList->next->next = countList;
		countList->next->count = 0;

		//ֻҪ��ǰ���ǿ�Ԫ������
		while (countList->count)
		{	
			auto lineCount = countList->count;//��Ҫ��ӡ�Ĳ�ڵ����

			//����ڵ��ӡ
			while (lineCount-- && nodeListHead) {
				//��ӡ�ڵ����ݣ�Ȩ��
				std::cout << "Data: " << nodeListHead->node->data
					<< ",Weight: " << nodeListHead->node->weight
					<< ".  ";

				//����Ҷ��������ڣ������ӡ����β
				if (nodeListHead->node->Ln) {
					nodeListTail->next = new nodeLink;
					nodeListTail = nodeListTail->next;
					nodeListTail->node = nodeListHead->node->Ln;
					nodeListTail->next = nullptr;

					//������һ���ӡ����
					countList->next->count++;
				}

				//����Ҷ��������ڣ������ӡ����β
				if (nodeListHead->node->Rn) {
					nodeListTail->next = new nodeLink;
					nodeListTail = nodeListTail->next;
					nodeListTail->node = nodeListHead->node->Rn;
					nodeListTail->next = nullptr;

					//������һ���ӡ����
					countList->next->count++;
				}

				//ɾ���Ѵ�ӡ�Ĵ�ӡ�����ڵ�
				auto deleteNode = nodeListHead;
				nodeListHead = nodeListHead->next;
				delete deleteNode;
				deleteNode = nullptr;


			}
			std::cout << std::endl;

			//��ǰ��Ԫ�ش�ӡ��
			countList->count = 0;
			countList = countList->next;

		}

		return;
		
	}

	huffmanCodeSetPtr HuffmanCodeSetInit(huffmanTreePtr sourceTree) {

		typedef struct codeSetHuffmanTreeNodeLink
		{	//��ȱ����������������ṹ
			huffmanTreePtr node = nullptr;	//���ڵ�
			std::string code = std::string();	//��ǰΪֹ��������
			struct codeSetHuffmanTreeNodeLink* next = nullptr;
		}csNodeLink, * csNodeLinkPtr;

		//������������
		csNodeLinkPtr codeSetHead = new csNodeLink;
		codeSetHead->code = std::string();	//��ʼ����Ϊ��
		codeSetHead->node = sourceTree;	//Huffman������Ϊ��һ�������ڵ�
		codeSetHead->next = nullptr;	//ָ����
		csNodeLinkPtr codeSetTail = codeSetHead;	//����β

		//���������ָ��
		huffmanCodeSet ResHead;
		huffmanCodeSetPtr resault = &ResHead;
		huffmanCodeSetPtr resTail = resault;

		while (codeSetHead) {	//ֻҪ��û������
			auto L = codeSetHead->node->Ln;
			auto R = codeSetHead->node->Rn;

			if (!R->Ln && !R->Rn) {	//���ӽڵ���Ҷ�ڵ�
				//�������ַ����뱾
				resTail->next = new huffmanCodeSet;
				resTail->next->data = R->data;	//�ַ�
				resTail->next->huffmanCode = codeSetHead->code + '1';	//����
				resTail = resTail->next;	//���뱾����βָ�����
				resTail->next = nullptr;	//ָ�밲ȫ��ʼ��
			}
			else {	//��֦�ڵ�
				//���������������β
				codeSetTail->next = new csNodeLink;
				codeSetTail->next->code = codeSetHead->code + '1';	//����
				codeSetTail->next->node = R;	//�ڵ�
				codeSetTail = codeSetTail->next;	//��������βָ�����
				codeSetTail->next = nullptr;	//ָ�밲ȫ��ʼ��
			}

			//ͬ��������ָ������ͬ����
			if (!L->Ln && !L->Rn) {
				resTail->next = new huffmanCodeSet;
				resTail->next->data = L->data;
				resTail->next->huffmanCode = codeSetHead->code + '0';
				resTail = resTail->next;
				resTail->next = nullptr;
			}
			else {
				codeSetTail->next = new csNodeLink;
				codeSetTail->next->code = codeSetHead->code + '0';
				codeSetTail->next->node = L;
				codeSetTail = codeSetTail->next;
				codeSetTail->next = nullptr;
			}

			//ɾ����ǰ�Ѿ�ʹ����ı�������ͷ�ڵ㣨�ڴ���գ�
			auto deleteNode = codeSetHead;
			codeSetHead = codeSetHead->next;
			delete deleteNode;
		}


		return resault->next;
	}

	bool HuffmanEncoding(huffmanCodeSetPtr codeSet,
		std::string sourceContent, std::string& finishContent) {

		finishContent = std::string();	//����ı���ʼ��

		for (auto data : sourceContent) {
			auto csPtr = codeSet;
			while (csPtr)
			{
				if (csPtr->data == data) {
					finishContent += csPtr->huffmanCode;
					break;
				}
				csPtr = csPtr->next;
			}
			if (!csPtr) return false;
		}

		return true;
	}

	bool HuffmanDecoding(huffmanTreePtr sourceTree,
		std::string sourceContent, std::string& finishContent) {
		auto nowPtr = sourceTree;
		finishContent = std::string();

		for (auto nowChar : sourceContent) {
			if (nowChar == '0') {
				nowPtr = nowPtr->Ln;
			}
			if (nowChar == '1') {
				nowPtr = nowPtr->Rn;
			}

			if (!nowPtr) return false;

			if (!nowPtr->Ln && !nowPtr->Rn) {
				finishContent += nowPtr->data;
				nowPtr = sourceTree;
				continue;
			}
			
		}
		return true;
	}


	void codeTxtPrint(std::string sourceContent, std::string saveLocation) {
		std::fstream saveFile;
		saveFile.open(saveLocation,'w');
		auto lineCount = 0;
		for (auto data : sourceContent) {
			std::cout << data;
			saveFile << data;
			lineCount++;
			if (lineCount == 50) {
				lineCount = 0;
				std::cout << std::endl;
			}
		}
		saveFile.close();
		std::cout << std::endl;
	}

}