#include "string.h"
#include <iostream>
#include <cmath>
#include <cstring>
#pragma warning(disable : 4996)

String::String()
	: String("") {}

String::String(const char* newText)
	: textMemory(strlen(newText) + 1)
{
	this->text = new char[this->textMemory];
	strcpy_s(this->text, this->textMemory, newText);
}

String::String(const String& other)
{
	this->copy(other);
}

String& String::operator=(const String& other)
{
	if (this != &other) {
		this->destroy();
		this->copy(other);
	}
	return *this;
}

String::~String()
{
	this->destroy();
}

/// <summary>
/// Concatinates a string and a const char*.
/// </summary>
/// <param name="const char* text"></param>
/// <returns></returns>
String& String::operator+=(const char* other)
{
	char* newStr = new char[this->textMemory + strlen(other) + 1];
	strcpy_s(newStr, this->textMemory + strlen(other) + 1, this->text);
	strcat(newStr, other);
	String result(newStr);
	*this = result;
	return *this;
}

/// <summary>
/// Removes given number of char from the end of a string.
/// </summary>
/// <param name="number of chars to be removed"></param>
void String::removeLastChars(const unsigned int numberOfChars)
{
	if (this->textMemory <= numberOfChars) {
		throw "text memory is smaller or equal to number of chars for removal";
	}
	this->textMemory -= numberOfChars;

	char* holdChars = new char[this->textMemory];
	for (std::size_t i = 0; i < this->textMemory - 1; ++i)
	{
		holdChars[i] = this->text[i];
	}
	holdChars[this->textMemory - 1] = '\0';

	delete[] this->text;
	this->text = new char[this->textMemory];
	strcpy_s(this->text, this->textMemory, holdChars);
}

/// <summary>
/// Compares a string and a const char* are they the same.
/// </summary>
/// <param name="const char* text"></param>
/// <returns></returns>
bool String::operator==(const char* other) const
{
	return strcmp(this->text, other) == false;
}

/// <summary>
/// Compares two string are they the same.
/// </summary>
/// <param name="other string"></param>
/// <returns></returns>
bool String::operator==(const String& other) const
{
	return strcmp(this->text, other.text) == false;
}

/// <summary>
/// Returns given number of char at the end of string.
/// </summary>
/// <param name="number of chars"></param>
/// <returns></returns>
const char* String::getLastChars(const unsigned int numberOfChars) const
{
	if (this->textMemory <= numberOfChars) {
		throw "Error";
	}
	char* result = new char[numberOfChars + 1];
	std::size_t j = 0;
	for (std::size_t i = this->textMemory - numberOfChars - 1; i < this->textMemory; ++i)
	{
		result[j] = this->text[i];
		j++;
	}
	return result;
}

/// <summary>
/// Returns the count of spaces in a string.
/// </summary>
/// <returns></returns>
const unsigned int String::countSpaces() const
{
	unsigned int result = 0;
	for (std::size_t i = 0; this->text[i] != '\0' && i < this->textMemory; ++i)
	{
		if (this->text[i] == ' ') {
			result++;
		}
	}
	return result;
}

/// <summary>
/// Where the spaces are the string gets broken in individual string.
/// </summary>
/// <returns></returns>
String* String::breakDown() const
{
	const unsigned int resultSize = this->countSpaces() + 1;
	String* result = new String[resultSize];
	std::size_t j = 0;
	for (std::size_t i = 0; i < resultSize; ++i)
	{
		char word[100];
		std::size_t k = 0;
		for (j; this->text[j] != ' ' && this->text[j] != '\0' && j < this->textMemory; ++j)
		{
			word[k] = this->text[j];
			k++;
		}
		word[k] = '\0';
		j++;
		result[i] = word;
	}
	return result;
}

const char* String::getText() const
{
	return this->text;
}

/// <summary>
/// Converts a string to a number.
/// </summary>
/// <returns></returns>
const unsigned int String::convertStrToNumber() const
{
	unsigned int number = pow(10, this->textMemory - 2);
	unsigned int result = 0;
	for (std::size_t i = 0; this->text[i] != '\0' && i < this->textMemory; ++i)
	{
		if (this->text[i] == '0') {
			result += 0 * number;
		}
		else if (this->text[i] == '1') {
			result += 1 * number;
		}
		else if (this->text[i] == '2') {
			result += 2 * number;
		}
		else if (this->text[i] == '3') {
			result += 3 * number;
		}
		else if (this->text[i] == '4') {
			result += 4 * number;
		}
		else if (this->text[i] == '5') {
			result += 5 * number;
		}
		else if (this->text[i] == '6') {
			result += 6 * number;
		}
		else if (this->text[i] == '7') {
			result += 7 * number;
		}
		else if (this->text[i] == '8') {
			result += 8 * number;
		}
		else if (this->text[i] == '9') {
			result += 9 * number;
		}
		else {
			throw "string can't be converted to number";
		}
		number /= 10;
	}
	return result;
}

/// <summary>
/// Copies an other string.
/// </summary>
/// <param name="other string"></param>
void String::copy(const String& other)
{
	this->textMemory = other.textMemory;
	this->text = new char[this->textMemory];
	strcpy_s(this->text, this->textMemory, other.text);
}

/// <summary>
/// Frees the heap memory.
/// </summary>
void String::destroy()
{
	delete[] this->text;
}
 