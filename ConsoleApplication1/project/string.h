#pragma once

class String
{
public:
	// Constructors
	String();
	String(const char* newText);
	String(const String& other);
	String& operator=(const String& other);
	~String();
	
	String& operator+=(const char* other);
	void removeLastChars(const unsigned int numberOfChars);

	bool operator==(const char* other) const;
	bool operator==(const String& other) const;
	const char* getLastChars(const unsigned int numberOfChars) const;
	const unsigned int countSpaces() const;
	String* breakDown() const;

	const char* getText() const;
	const unsigned int convertStrToNumber() const;

private:
	void copy(const String& other);
	void destroy();

private:
	unsigned int textMemory;
	char* text;
};

