/***********************************************************************
** Date: 		5/19/22
** Project :	text_driver.cpp
** Programers:	Jiahao Liang, Jianwen QI
** File:		text_driver.cpp
** Purpose:		
** Notes:		
***********************************************************************/

#include <iostream>
#include <string>
#include "huffman_tree.h"

void testByString();
void testByFile();
template<typename T> inline T getUserLineInput(const std::string &prompt);

int main(int argc, char *argv[]) 
{
	testByString();
	std::cout << "\n\n";
	testByFile();
	return 0;
}

void
testByString()
{
	HuffmanTree tree;
	std::cout << "*********************| Test by a string |*********************\n";
	std::string text = getUserLineInput<std::string>("Input a string: "), code;
	tree.buildTree(text);
	code = tree.getCode(text);
	std::cout << "\nSingle-character code: \n";
	tree.printSingleCharacterCode();
	std::cout << "\nstring to code: " << code << "\ncode to string: " << tree.deCode(code) << "\n";
}

void
testByFile()
{
	HuffmanTree tree;
	std::cout << "*********************| Test by a file |*********************\n";
	tree.buildTreeFromFile();
	std::cout << "Single-character code: \n";
	tree.printSingleCharacterCode();
	for(auto &i : tree.getFileStream().getParagraph())
	{
		std::string code = tree.getCode(i);
		std::cout << "\nstring to code: " << code << "\ncode to string: " << tree.deCode(code) << "\n";
	}
	std::cout << "\n";
	tree.writeCodeToFile();
}

template<typename T>
inline
T
getUserLineInput(const std::string &prompt)
{
	T input;
	std::cout << prompt;
	getline(std::cin, input);
	return input;
}