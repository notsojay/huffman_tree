/***********************************************************************
** Date: 		5/18/22
** Project :	huffman_tree.h
** Programers:	Jiahao Liang, Jianwen QI
** File:		huffman_tree.h
** Purpose:		The class huffman_tree.h, which implement the huffman_tree.h ADT
** Notes:		
***********************************************************************/

#pragma once
#ifndef _HUFFMAN_TREE_H_
#define _HUFFMAN_TREE_H_

#include <iostream>
#include <utility>
#include <memory>
#include <queue>
#include <string>
#include <vector>
#include <unordered_map>

#include "huffman_file_stream.h"
#include "huffman_file_stream.cpp"

class HuffmanTree;
class CompareHuffmanNode;

class HuffmanNode
{
public:
	friend class HuffmanTree;
	friend class CompareHuffmanNode;
public:
	HuffmanNode(const int& weight, HuffmanNode* const left = nullptr, HuffmanNode* const right = nullptr):
				val('\0'),
				freq(weight),
				left(left),
				right(right)
	{}
	HuffmanNode(const char& val = char(), const int& weight = int(), HuffmanNode* const left = nullptr, HuffmanNode* const right = nullptr):
				val(val),
				freq(weight),
				left(left), 
				right(right)
	{}
private:
	char val;
	int freq;
	HuffmanNode* left;
	HuffmanNode* right;
};

class CompareHuffmanNode
{
public:
	bool operator()(const HuffmanNode* const &node1, const HuffmanNode* const &node2) const
	{
		return node1->freq > node2->freq;
	}
	bool operator()(const HuffmanNode &node1, const HuffmanNode &node2) const
	{
		return node1.freq > node2.freq;
	}
};

class HuffmanTree
{
public:
	HuffmanTree();
	~HuffmanTree();
	void buildTree(const std::string&);
	void buildTreeFromFile();
	void writeCodeToFile();
	void printSingleCharacterCode() const;
	std::string deCode(const std::string&);
	std::string getCode(const std::string&) const;
	HuffmanFileStream& getFileStream();
	void clear();
protected:
	void enCode(HuffmanNode*, std::string);
	bool isLeafNode(HuffmanNode*);
	void clear(HuffmanNode*&);
private:
	HuffmanNode* root;
	std::unique_ptr<std::unordered_map<char, std::string>> huffmanCode;
	HuffmanFileStream file;
};


#endif