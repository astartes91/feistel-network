#include<iostream>
#include<string>
#include<iomanip>
#include<vector>

using namespace std;

void printBytes(vector<string> v_s)
{
	for(int i = 0; i < v_s.size(); i++)
	{
		const char* c = v_s.at(i).c_str();

		int* left = (int*)c;
		int* right = left+1;
	
		cout  << *left << " " << *right << " ";
	}
	cout << endl;
}

int f(int subblock, char key)
{
	return subblock^key;
}

int* decrypt(int *left, int *right, long long* p_key)
{
	int rounds = 8;
	for(int i = rounds - 1; i >= 0; i--)
	{
		int temp = *left ^ f(*right, *(char*)p_key+i);
		if(i != 7)
		{
			*left = *right;
			*right = temp;
		}
		else *right = temp;
		
		//cout << 8-i << "th iteration:" << endl << *left << " " << *right << endl << endl;
	}
	
	return left;
}

int* encrypt(int *left, int *right, long long* p_key)
{
	int rounds = 8;
	for(int i = 0; i < rounds; i++)
	{
		int temp = *right ^ f(*left, *(char*)p_key+i);
		
		if(i != 7)
		{
			*right = *left;
			*left = temp;
		}
		else *right = temp;
		
		//cout << i+1 << "th iteration:" << endl << *left << " " << *right << endl << endl;
	}
	
	return left;
}

int main()
{
	string message;
	vector<string> v_s;
	
	cout << "Please enter message to encrypt:" << endl << endl; 
	getline(cin, message);

	int length = message.length();
	int quotient = length/8;
	if(length%8 != 0) quotient++;
	
	for(int i = 0; i < quotient; i++)
	{
		string new_message = message.substr(0, 8);
		v_s.push_back(new_message);
		
		for(int i = 0; i < 8; i++)
		{
			message.erase(0, 1);
		}
	}
	
	string last_string = v_s.at(v_s.size()-1);
	if(last_string.length() < 8) last_string.resize(8, '0');

	long long key = INT_MAX/0x100 - 0x1000;
	long long* p_key = &key;

	cout << endl << "This message by bytes:" << endl << endl << setbase(16);
	printBytes(v_s);
	
	for(int i = 0; i < v_s.size(); i++)
	{
		const char* c = v_s.at(i).c_str();

		int* left = (int*)c;
		int* right = left+1;

		c = (char*)encrypt(left, right, p_key);
	}

	cout << endl << "Encrypted message by bytes:" << endl << endl;
	printBytes(v_s);

	cout << endl << "Encrypted message:" << endl << endl;
	for(int i = 0; i < v_s.size(); i++)
	{
		const char* c = v_s.at(i).c_str();
		cout  << c;
	}
	cout << endl;

	for(int i = 0; i < v_s.size(); i++)
	{
		const char* c = v_s.at(i).c_str();

		int* left = (int*)c;
		int* right = left+1;

		c = (char*)decrypt(left, right, p_key);
	}

	cout << endl << endl << "Decrypted message by bytes:" << endl << endl;
	printBytes(v_s);

	cout << endl << "Decrypted message:" << endl <<endl;
	for(int i = 0; i < v_s.size(); i++)
	{
		const char* c = v_s.at(i).c_str();
		cout  << c;
	}
	cout << endl << endl;
	
	system("PAUSE");
	return 0;
}