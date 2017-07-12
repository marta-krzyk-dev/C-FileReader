#include "stdafx.h"
#include "FileReader.h"


FileReader::FileReader(string filepath) : filePath(filepath)
{
	stream.open(filePath, ios::app);

	if (stream.fail())
		throw exception("Failed to open the file.");
}

FileReader::~FileReader()
{
	stream.close();
}


string FileReader::ReadWord()
{
	if (stream)
	{
		stream.getline(buffer, BUFFER_SIZE);
		line = buffer;
		size_t index = line.find_first_of(" \n\t\r\v\f\0");
		line = line.substr(index); //remove white-spaces at the end of the line
		return line;
	}

	return "";
}

string FileReader::ReadLine()
{
	//go to the end of current line if it only contains whitespaces
	bool only_whitespace = true;
	line = "";

	while (stream && only_whitespace)
	{
		std::getline(stream, line); //read line until it is not empty

		for each (char c in line)
		{
			if (false == iswspace(c))
			{
				only_whitespace = false;
				return line;
			}
		}
	}

	return line;
}

string FileReader::ReadLine2()
{
	if (stream)
	{
		stream.getline(buffer, BUFFER_SIZE);
		line = buffer;
		return line;

		size_t index = line.find_first_of('\0');
		line = line.substr(index); //remove white-spaces at the end of the line
		return line;
	}
}

string FileReader::ReadDigitString()
{
	char c;
	line = "";
	bool reading_number = false;

	while (stream)
	{
		stream.get(c);

		if (isdigit(c) || c == ',' || c == '.')
		{
			reading_number = true;
			line += c;
		}
		else
			if (reading_number) //reached end of number
				break;
	}

	return line;
}

bool FileReader::IsEnd()
{
	return stream.eof();
}
