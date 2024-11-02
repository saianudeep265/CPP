#include <iostream>
#include <fstream>
#include <string>

// Contains Serialization and Deserialization for both binary and ASII format

class StringClass
{
public:
	StringClass() : age(0) { }

	StringClass(std::string str_, int age_) : str(std::move(str_)), age(age_) { }

	void display() const
	{
		std::cout << "Name: " << str << " Age: " << age << std::endl;
	}

	void Serialize(const std::string& filename) const
	{
		std::ofstream file(filename, std::ios::binary);
		if (file.is_open())
		{
			size_t length = str.length();
			file.write(reinterpret_cast<const char*>(&length), sizeof(length));
			file.write(str.c_str(), length);
			file.write(reinterpret_cast<const char*>(&age), sizeof(age));
			file.close();
			std::cout << "Successfully serialized the StringClass!!" << std::endl;
		}
		else
			std::cout << "Failed to serialize the StringClass!!" << std::endl;
	}

	void Deserialize(const std::string& filename)
	{
		std::ifstream file(filename, std::ios::binary);
		if (file.is_open())
		{
			size_t length;
			file.read(reinterpret_cast<char*>(&length), sizeof(length));
			str.resize(length);
			file.read(reinterpret_cast<char*>(&str[0]), length);
			file.read(reinterpret_cast<char*>(&age), sizeof(age));
			file.close();
			std::cout << "Successfully deserialized the StringClass!!" << std::endl;
		}
		else
			std::cout << "Failed to deserialize the StringClass!!" << std::endl;
	}

	void SerializeToASCIIFormat(const std::string& filename) const
	{
		std::ofstream file(filename);
		if (file.is_open())
		{
			file << str << ' ' << age;
			file.close();
			std::cout << "Successfully serialized the StringClass!!" << std::endl;
		}
		else
			std::cout << "Failed to serialize the StringClass!!" << std::endl;
	}

	static StringClass DeserializeFromASCIIFormat(const std::string& filename)
	{
		StringClass obj;
		std::ifstream file(filename);
		if (file.is_open())
		{
			file >> obj.str;

			file >> obj.age;

			file.close();
			std::cout << "Successfully deserialized the StringClass!!" << std::endl;
		}
		else
			std::cout << "Failed to deserialize the StringClass!!" << std::endl;
		return obj;
	}

private:
	std::string str;
	int age;
};

int main()
{
	StringClass test = { "Anudeep", 25 };
	test.display();

	test.Serialize("test.bin");

	StringClass test1;
	test1.Deserialize("test.bin");
	test1.display();

	test.SerializeToASCIIFormat("testascii.txt");

	auto test2 = StringClass::DeserializeFromASCIIFormat("testascii.txt");
	test2.display();

	return 0;
}