#ifndef STRING_H
#define STRING_H

class String {
private:
	char* Mas = nullptr;

	void CreateString(const char* str, int Length) {
		this->Length = Length;
		this->Mas = new char[Length + 1];

		for (int i = 0; i < Length; i++) {
			Mas[i] = str[i];
		}
		Mas[Length] = '\0';
	}

public:
	int Length = 0;

	// Constructors
	String() {}

	String(const char* str) noexcept
	{
		this->CreateString(str, strlen(str));
	}

	// Copy constructor
	String(const String& ref_String) noexcept
	{
		this->CreateString(ref_String.Mas, strlen(ref_String.Mas));
	}

	// Destructor
	~String() {
		if (this->Mas != nullptr)
			delete[] this->Mas;
	}

	friend String operator+(String& str1, const String& str2);
	friend String operator+(String& str1, const char& chr);
	friend std::istream& operator>> (std::istream& in, String& str);

	void Print() {
		for (int i = 0; i < this->Length; i++) {
			std::cout << this->Mas[i];
		}
		std::cout << "\n";
	}

	void Clear() {
		if (Mas == nullptr) return;

		delete[] this->Mas;
		this->Mas = nullptr;
		this->Length = 0;
	}

	String operator+(const char* str) {
		int ScndPartLength = strlen(str);

		char* newString = new char[this->Length + ScndPartLength + 1];

		for (int i = 0; i < this->Length; i++) {
			newString[i] = this->Mas[i];
		}
		for (int i = 0; i < ScndPartLength; i++) {
			newString[this->Length + i] = str[i];
		}
		newString[this->Length + ScndPartLength] = '\0';

		this->Clear();
		this->CreateString(newString, strlen(newString));
		delete[] newString;

		return *this;
	}

	char& operator[] (const int index) {
		try {
			if (this->Mas == nullptr || index < 0 || index >= Length)
				throw "Index out of range";
		}
		catch (const char* e) // ���������� ���������� ���� const char*
		{
			std::cerr << "[STRING] Error: " << e << '\n';
			exit(-1);
		}

		return Mas[index];
	}

	const char& operator[] (int index) const {
		try {
			if (this->Mas == nullptr || index < 0 || index >= Length)
				throw "Index out of range";
		}
		catch (const char* e) // ���������� ���������� ���� const char*
		{
			std::cerr << "[STRING] Error: " << e << '\n';
			exit(-1);
		}

		return Mas[index];
	}

	// Assignment operator
	String& operator= (const String& ref_String)
	{
		this->CreateString(ref_String.Mas, strlen(ref_String.Mas));

		return *this;
	}

	String operator=(const char* str) {
		this->Clear();
		this->CreateString(str, strlen(str));

		return *this;
	}

	// Move operator
	String& operator=(String&& str) noexcept {
		this->Clear();
		this->Mas = str.Mas;
		this->Length = str.Length;
		
		str.Mas = nullptr;
		str.Length = 0;

		return *this;
	}
};

String operator+(String& str1, const String& str2) {
	int ScndPartLength = str2.Length;

	char* newString = new char[str1.Length + ScndPartLength + 1];

	for (int i = 0; i < str1.Length; i++) {
		newString[i] = str1[i];
	}
	for (int i = 0; i < ScndPartLength; i++) {
		newString[str1.Length + i] = str2.Mas[i];
	}
	newString[str1.Length + ScndPartLength] = '\0';


	str1.Clear();
	str1.CreateString(newString, strlen(newString));
	delete[] newString;

	return str1;
}

String operator+(String& str1, const char& chr) {
	char* newString = new char[str1.Length + 2];

	for (int i = 0; i < str1.Length; i++) {
		newString[i] = str1[i];
	}
	newString[str1.Length] = chr;
	newString[str1.Length+1] = '\0';


	str1.Clear();
	str1.CreateString(newString, strlen(newString));
	delete[] newString;

	return str1;
}

std::ostream& operator<< (std::ostream& out, const String& str) {

	for (int i = 0; i < str.Length; i++) {
		out << str[i];
	}
	return out;
}

#endif