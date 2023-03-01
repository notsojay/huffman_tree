/***********************************************************************
** Date: 		5/19/22
** Project :	huffman_file_stream.cpp
** Programers:	Jiahao Liang, Jianwen QI
** File:		huffman_file_stream.cpp
** Purpose:		
** Notes:		
***********************************************************************/

#include "huffman_file_stream.h"

HuffmanFileStream::HuffmanFileStream(){}

HuffmanFileStream::~HuffmanFileStream(){}

void
HuffmanFileStream::openInFile()
{
	std::string fileName = getUserLineInput<std::string>("Enter the file-path to read: ");
	inFile.open(fileName.c_str(), std::ios::in);
	if(!inFile.is_open())
	{
		std::cout << "ERROR: INVALID FILE" << std::endl;
		clearInstream();
		openInFile();
	}
}

void
HuffmanFileStream::openOutFile()
{
	std::string fileName = getUserLineInput<std::string>("Enter the file-path to write: ");
	outFile.open(fileName.c_str(), std::ios::out);
	if(!outFile.is_open())
		throw std::invalid_argument("ERROR: Could not open the file.");
}

void
HuffmanFileStream::closeInFile()
{
	inFile.close();
}

void
HuffmanFileStream::closeOutFile()
{
	outFile.close();
}

void
HuffmanFileStream::readDataFromFile()
{
	char buffer[BUFFER_SIZE];
	while(inFile.getline(buffer, BUFFER_SIZE))
	{
		std::stringstream sstr(buffer);
		std::string text;
		getline(sstr, text);
		std::cout << text << '\n';
		paragraph.push_back(text);
	}
}

void
HuffmanFileStream::writeDataToFile(const std::vector<std::string>& codes)
{
	for(auto &i : codes)
		outFile << i << "\n";
}


std::vector<std::string>
HuffmanFileStream::getParagraph() const
{
	return paragraph;
}

void
HuffmanFileStream::clearInstream()
{
	std::cin.clear();
	std::cin.ignore(INT_MAX, '\n');
}