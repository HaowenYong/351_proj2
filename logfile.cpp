#include <stdio.h>
#include <iostream>
#include <fstream>
#include <thread>
#include <pthread.h>
#include <mutex>

using namespace std;

mutex mtx;

void writenumbers(string);
void writeletters(string);

int main()
{
/*
	fstream file;
	file.open("test_log.log", ios::out);
	if(!file)
	{
		cout<<"failed to create a log file"<<endl;
		return 0;
	}
	cout<<"file created successfully"<<endl;
*/
	string filename = "hyong.log";
	ofstream file(filename.c_str());

	thread first(writenumbers, filename);
	thread second(writeletters, filename);

	file<<"Thread A (ID "<<first.get_id()<<") created"<<endl;
	file<<"Thread B (ID "<<second.get_id()<<") created"<<endl;

	first.join();
	second.join();

	file<<"Thread A (ID "<<first.get_id()<<") terminated"<<endl;
	file<<"Thread B (ID "<<second.get_id()<<") terminated"<<endl;

	return 0;
}

void writenumbers(string name)
{
	fstream file(name);
	mtx.lock();
	for(int i=0; i<10; i++)
	{	for(int j=1; j<27; j++)
		{	file<<j;
			file<<" ";
		}
		file<<"\n";
	}
	mtx.unlock();
}

void writeletters(string name)
{
	fstream file(name);
	mtx.lock();
	for(int i=0; i<10; i++)
	{	for(int j=65; j<91; j++)
		{	char temp = j;
			file<<temp;
			file<<" ";
		}
		file<<"\n";
	}
	mtx.unlock();
}