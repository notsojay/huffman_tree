/***********************************************************************
** Date: 		5/18/22
** Project :	huffman_tree.cpp
** Programers:	Jiahao Liang, Jianwen QI
** File:		huffman_tree.cpp
** Purpose:		
** Notes:		
***********************************************************************/

#include "huffman_tree.h"


HuffmanTree::HuffmanTree():
						root(nullptr),
						huffmanCode(std::make_unique<std::unordered_map<char, std::string>>())
{
	
}

HuffmanTree::~HuffmanTree()
{
	if(root != nullptr)
		clear();
	if(huffmanCode != nullptr)
		huffmanCode = nullptr;
}

void
HuffmanTree::buildTree(const std::string& text)
{
	if(text.empty()) return;
	if(root != nullptr) clear();
	std::unordered_map<char, int> map;
	std::priority_queue<HuffmanNode*, std::vector<HuffmanNode*>, CompareHuffmanNode> forest;
	for(auto &i : text)
		++map[i];
	for(auto &i : map)
		forest.push(new HuffmanNode(i.first, i.second));
	while(forest.size() > 1)
	{
		HuffmanNode* leftNode(forest.top());
		forest.pop();
		HuffmanNode* rightNode(forest.top());
		forest.pop();
		forest.push(new HuffmanNode(leftNode->freq+rightNode->freq, leftNode, rightNode));
	}
	root = forest.top();
	forest.pop();
	enCode(root, "");

}

void
HuffmanTree::buildTreeFromFile()
{
	if(root != nullptr) clear();
	std::unordered_map<char, int> map;
	std::priority_queue<HuffmanNode*, std::vector<HuffmanNode*>, CompareHuffmanNode> forest;
	file.openInFile();
	file.readDataFromFile();
	file.closeInFile();
	for(auto &i : file.getParagraph())
	{
		for(auto &j : i)
		{
			++map[j];
		}
	}
	for(auto &i : map)
		forest.push(new HuffmanNode(i.first, i.second));
	while(forest.size() > 1)
	{
		HuffmanNode* leftNode(forest.top());
		forest.pop();
		HuffmanNode* rightNode(forest.top());
		forest.pop();
		forest.push(new HuffmanNode(leftNode->freq+rightNode->freq, leftNode, rightNode));
	}
	root = forest.top();
	forest.pop();
	enCode(root, "");
}

void 
HuffmanTree::writeCodeToFile()
{
	std::vector<std::string> code;
	file.openOutFile();
	for(auto &i : file.getParagraph())
		code.push_back(getCode(i));
	file.writeDataToFile(code);
	file.closeOutFile();
}

void
HuffmanTree::enCode(HuffmanNode* current, std::string code)
{
	if(current == nullptr) return;
	enCode(current->left, code + "0");
	enCode(current->right, code + "1");
	if(isLeafNode(current))
		huffmanCode->insert({current->val, code});
}

std::string
HuffmanTree::getCode(const std::string& text) const
{
	std::string code = "";
	if(text.empty() || root == nullptr)
		return code;
	for(auto &i : text)
	{
		auto itor = huffmanCode->find(i);
		if(itor != huffmanCode->end())
			code += itor->second + " ";
		else
			return "";
	}
	return code;
}

std::string
HuffmanTree::deCode(const std::string& code)
{
	std::string text = "";
	HuffmanNode* current = root;
	if(code.empty() || root == nullptr)
		return code;
	for(auto &i : code)
	{
		if(isLeafNode(current))
		{
			text += current->val;
			current = root;
			continue;
		}
		current = (i == '1' ? current->right : current = current->left);
	}
	return text;
}

void
HuffmanTree::printSingleCharacterCode() const
{
	for(auto &i : *huffmanCode)
	{
		if(i.first == ' ')
			std::cout << "space" << " = " << i.second << "\n";
		else 
			std::cout << i.first << " = " << i.second << "\n";
	}
}

HuffmanFileStream&
HuffmanTree::getFileStream()
{
	return file;
}

void
HuffmanTree::clear()
{
	if(root != nullptr)
		clear(root);
	if(huffmanCode != nullptr)
	{
		huffmanCode.reset();
		huffmanCode = std::make_unique<std::unordered_map<char, std::string>>();
	}
}

void
HuffmanTree::clear(HuffmanNode*& current)
{
	if(current != nullptr)
	{
		clear(current->left);
		clear(current->right);
		delete current;
		current = nullptr;
	}
}

bool
HuffmanTree::isLeafNode(HuffmanNode* current)
{
	if(current->left == nullptr && current->right == nullptr && current->val != '\0')
		return true;
	return false;
}