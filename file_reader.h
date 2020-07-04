/*
 * file_reader.h
 *
 *  Created on: Mar 19, 2020
 *      Author: jzmac
 */

#ifndef CPPS_FILEREADING_FILE_READER_H_
#define CPPS_FILEREADING_FILE_READER_H_

#include<fstream>
namespace read{
std::ifstream* initialize_reader(std::string path, bool textfile);

double rd(std::ifstream* f);
float rf(std::ifstream* f);
bool rb(std::ifstream* f);

char rc(std::ifstream* f);
unsigned char ruc(std::ifstream* f);
short rs(std::ifstream* f);
unsigned short rus(std::ifstream* f);
int ri(std::ifstream* f);
unsigned int rui(std::ifstream* f);

std::string rstr(std::ifstream* f);
std::string rFile(std::ifstream* f);

void free_reader(std::ifstream* f);

static std::string s = "";
};

#endif /* CPPS_FILEREADING_FILE_READER_H_ */
