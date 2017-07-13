# C-FileReader
A class that enables to read almost any type of data from a text file.

## Problem
How to retrieve a data of specific type from a text file without having to manually navigate inside file stream?

## Solution
Use template function.

The easiest and most convinient solution is to read a variable using >> operand. The type/class must implement >> operand function. If operation success, it returns the stream object (*this). If the operation fails, it throws an exception. By default >> reads in data till it encounters a white-space. To read in the whole line, I created a specialized template Read2<string>(). 

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

## Solution 2
Another solution is to read a line from text file, then determine the typeid using typeid(T) function. Only then we can and then convert text data into desired type. The type is known at compile type, because we have to put it in angle brackets when calling the Read function. See code below.

main () {
...
unsigned short us = fr.Read<unsigned short>();
...
}

class FileReader
{
...
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
  }

If the conversion fails, the function prints exception onto screen.

To handle non-numeric types like char, string, bool, I had to create specialized templates.

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

		throw "Bool not found";
	}
