/***********************************************************************
** Date: 		5/19/22/Users/jay/Desktop/Desktop_Jiahao’s_MacBook_Pro/workspace/Mt.Sac CS/csci230s22_src/project_3/huffman_file_stream.cpp
** Project :	huffman_file_stream.h
** Programers:	Jiahao Liang, Jianwen QI
** File:		huffman_file_stream.h
** Purpose:		The class huffman_file_stream.h, which implement the huffman_file_stream.h ADT
** Notes:		
***********************************************************************/

#pragma once
#ifndef _HUFFMAN_FILE_STREAM_
#define _HUFFMAN_FILE_STREAM_

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

const size_t BUFFER_SIZE = 8192;

class HuffmanFileStream
{
public:
	HuffmanFileStream();
	~HuffmanFileStream();
	void openInFile();
	void openOutFile();
	void closeInFile();
	void closeOutFile();
	void readDataFromFile();
	void writeDataToFile(const std::vector<std::string>&);
	void clearInstream();
	template<typename T> inline T getUserLineInput(const std::string&);
	std::vector<std::string> getParagraph() const;
private:
	std::ifstream inFile;
	std::ofstream outFile;
	std::vector<std::string> paragraph;
};

template<typename T>
inline
T
HuffmanFileStream::getUserLineInput(const std::string &prompt)
{
	T input;
	std::cout << prompt;
	getline(std::cin, input);
	return input;
}

#endif