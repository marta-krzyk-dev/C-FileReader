#pragma once
#include "stdafx.h"
#include <string>
#include <cstdio>
#include <iostream>
#include <istream>
#include <fstream>
#include <typeinfo> //typeid()
#include <algorithm> //for_each, transform
#define BUFFER_SIZE 255

using  namespace std;

class FileReader
{
private:
	string filePath;
	ifstream stream;
	char buffer[BUFFER_SIZE];
	string line;				//used for converting buffer into a string

//DECLARATIONS
public:
	FileReader(string);
	~FileReader();

	string ReadWord();
	string ReadLine();
	string ReadLine2();
	string ReadDigitString();
	bool IsEnd();

// DEFINITIONS

	template<typename T>
	T Read2() {

		T object;

		if (stream >> object)
			return object;
		else
			return T();
	}

	template<>
	string Read2<string>() {

		return ReadLine();
	}

	template<typename T>
	T Read() {

		line = ReadDigitString();

		//Convert to return type
		try {
			if (typeid(T) == typeid(short))
				return (short)std::stoi(line);

			if (typeid(T) == typeid(unsigned short))
				return std::stoi(line);

			if (typeid(T) == typeid(int))
				return std::stoi(line);

			if (typeid(T) == typeid(unsigned int))
				return  std::stoul(line);

			if (typeid(T) == typeid(long))
				return  std::stol(line);

			if (typeid(T) == typeid(long long))
				return  std::stoll(line);

			if (typeid(T) == typeid(float))
				return  std::stof(line);

			if (typeid(T) == typeid(double))
				return  std::stod(line);

			if (typeid(T) == typeid(long double))
				return std::stold(line);

			if (typeid(T) == typeid(string))
				return line;
		}
		catch (const std::invalid_argument& ia) {

			std::cerr << "Invalid argument: " << ia.what() << '\n'; //line doesn't contain a number
		}
		catch (const std::out_of_range& or ) {

			std::cerr << "Out of range: " << or.what() << '\n';
		}
		catch (const std::exception& ex)
		{
			std::cerr << "Exception: " << ex.what() << '\n';
		}

		return T(); //return the default value of the type
	}

	template<>
	string Read<string>(void)
	{

		if (std::getline(stream, line))
		{
			return line;
		}

		return string(); //return an empty string if stream is null
	}

	template<>
	char Read<char>() {

		if (stream)
		{
			char c;
			stream >> c;
			return c;
		}
		return char(); //return the default char value if stream is null
	}

	template<>
	bool Read<bool>() {

		line = ReadLine();

		//check if line contains TRUE of FALSE
		std::transform(line.begin(), line.end(), line.begin(), ::toupper);
		if (line.find("TRUE") != string::npos)
			return true;
		if (line.find("FALSE") != string::npos)
			return false;
		
		//check if line contains 1 or 0
		for each (char c in line)
		{
			if (c == '0')
				return false;
			if (c == '1')
				return true;
		}

		return bool();
    //or
    throw "Bool not found";
	}
};




