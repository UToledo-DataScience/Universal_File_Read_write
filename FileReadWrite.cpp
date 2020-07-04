// FileReadWrite.cpp : Defines the functions for the static library.
//

//(Copyright) Justin McIntosh

#include "pch.h"
#include "framework.h"

#include <fstream>
#include <utility>

//FILE READING FUNCTIONS
#include "file_reader.h"
const int ETEST = 1; //stored on compile time
bool etest() {
	return ((*(char*)&ETEST) == 0);
}
const bool BIGENDIAN = etest(); //stored on run time

std::ifstream* read::initialize_reader(std::string path, bool textfile) {
	if (textfile) {
		return new std::ifstream(path);
	}
	return new std::ifstream(path, std::ios::binary);
}
//chars and bools being only 1 in length do not depend on byte endian nature
char read::rc(std::ifstream* f) {
	char Cs1[1];
	f->read(Cs1, 1);
	return Cs1[0];
}
unsigned char read::ruc(std::ifstream* f) {
	char Cs1[1];
	f->read(Cs1, 1);
	return (unsigned char)Cs1[0];
}
bool read::rb(std::ifstream* f) {
	char Cs1[1];
	f->read(Cs1, 1);
	return *reinterpret_cast<bool*>(Cs1);
}

//These next data types have to be converted based off of the endian nature of the os running the code
//my os is little endian, keeping that in mind, if the system reading my files is big endian, I have to flip the byte order
double read::rd(std::ifstream* f) {
	char Cs8[8];
	f->read(Cs8, 8);
	if (BIGENDIAN) {
		std::swap(Cs8[0], Cs8[7]); // @suppress("Invalid arguments")
		std::swap(Cs8[1], Cs8[6]); // @suppress("Invalid arguments")
		std::swap(Cs8[2], Cs8[5]); // @suppress("Invalid arguments")
		std::swap(Cs8[3], Cs8[4]); // @suppress("Invalid arguments")
	}
	return *reinterpret_cast<double*>(Cs8);
}

float read::rf(std::ifstream* f) {
	char Cs4[4];
	f->read(Cs4, 4);
	if (BIGENDIAN) {
		std::swap(Cs4[0], Cs4[3]); // @suppress("Invalid arguments")
		std::swap(Cs4[1], Cs4[2]); // @suppress("Invalid arguments")
	}
	return *reinterpret_cast<float*>(Cs4);
}
short read::rs(std::ifstream* f) {
	char Cs2[2];
	f->read(Cs2, 2);
	if (BIGENDIAN) {
		std::swap(Cs2[0], Cs2[1]); // @suppress("Invalid arguments")
	}
	return *reinterpret_cast<short*>(Cs2);
}
unsigned short read::rus(std::ifstream* f) {
	char Cs2[2];
	f->read(Cs2, 2);
	if (BIGENDIAN) {
		std::swap(Cs2[0], Cs2[1]); // @suppress("Invalid arguments")
	}
	return *reinterpret_cast<unsigned short*>(Cs2);
}
#include <iostream>
int read::ri(std::ifstream* f) {
	char Cs4[4];
	f->read(Cs4, 4);
	if (BIGENDIAN) {
		std::swap(Cs4[0], Cs4[3]); // @suppress("Invalid arguments")
		std::swap(Cs4[1], Cs4[2]); // @suppress("Invalid arguments")
	}
	return *reinterpret_cast<int*>(Cs4);
}
unsigned int read::rui(std::ifstream* f) {
	char Cs4[4];
	f->read(Cs4, 4);
	if (BIGENDIAN) {
		std::swap(Cs4[0], Cs4[3]); // @suppress("Invalid arguments")
		std::swap(Cs4[1], Cs4[2]); // @suppress("Invalid arguments")
	}
	return *reinterpret_cast<unsigned int*>(Cs4);
}

std::string read::rstr(std::ifstream* f) {
	//No way to know when the string ends, unless a break character is used
	//Define the break character to be '\n' in this implementation
	s = "";
	char c = rc(f);
	while (c != '\n') { //Break char test
		s += c;
		c = rc(f);
	}
	return s;
}
std::string read::rFile(std::ifstream* f) {
	s = "";
	static char* temp = new char(' ');
	while (f->good()) {
		f->read(temp, 1);
		s += *temp;
	}
	return s;
}
void read::free_reader(std::ifstream* f) {
	f->close();
	delete(f);
}





//FILE WRITING FUNCTIONS AND DECLERATIONS

static std::ofstream WRITE_FILE;

const static char str_escape = 10;
void initialize_writer(std::string path) {
	WRITE_FILE = std::ofstream(path, std::ios::binary);
}


void wd(double d) {
	if (BIGENDIAN) {
		char* c_array = (char*)&d;
		std::swap(c_array[0], c_array[7]); // @suppress("Invalid arguments")
		std::swap(c_array[1], c_array[6]); // @suppress("Invalid arguments")
		std::swap(c_array[2], c_array[5]); // @suppress("Invalid arguments")
		std::swap(c_array[3], c_array[4]); // @suppress("Invalid arguments")
	}
	WRITE_FILE.write((char*)&d, 8);
}
void wf(float ff) {
	if (BIGENDIAN) {
		char* c_array = (char*)&ff;
		std::swap(c_array[0], c_array[3]); // @suppress("Invalid arguments")
		std::swap(c_array[1], c_array[2]); // @suppress("Invalid arguments")
	}
	WRITE_FILE.write((char*)&ff, 4);
}


void wb(bool b) {
	WRITE_FILE.write((char*)&b, 1);
}

void wc(char c) {
	WRITE_FILE.write(&c, 1);
}
void wuc(unsigned char uc) {
	WRITE_FILE.write((char*)&uc, 1);
}


void ws(short s) {
	if (BIGENDIAN) {
		char* c_array = (char*)&s;
		std::swap(c_array[0], c_array[1]); // @suppress("Invalid arguments")
	}
	WRITE_FILE.write((char*)&s, 2);
}
void wus(unsigned short us) {
	if (BIGENDIAN) {
		char* c_array = (char*)&us;
		std::swap(c_array[0], c_array[1]); // @suppress("Invalid arguments")
	}
	WRITE_FILE.write((char*)&us, 2);
}


void wi(int i) {
	if (BIGENDIAN) {
		char* c_array = (char*)&i;
		std::swap(c_array[0], c_array[3]); // @suppress("Invalid arguments")
		std::swap(c_array[1], c_array[2]); // @suppress("Invalid arguments")
	}
	WRITE_FILE.write((char*)&i, 4);
}
void wui(unsigned int ui) {
	if (BIGENDIAN) {
		char* c_array = (char*)&ui;
		std::swap(c_array[0], c_array[3]); // @suppress("Invalid arguments")
		std::swap(c_array[1], c_array[2]); // @suppress("Invalid arguments")
	}
	WRITE_FILE.write((char*)&ui, 4);
}

void wstr(std::string s) {
	WRITE_FILE.write(s.c_str(), s.length());
	WRITE_FILE.write(&str_escape, 1);
}

void free_writer() {
	WRITE_FILE.close();
}




