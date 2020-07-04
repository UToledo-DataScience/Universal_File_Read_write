/*
 * file_writer.h
 *
 *  Created on: Mar 19, 2020
 *      Author: jzmac
 */

#ifndef CPPS_FILEREADING_FILEWRITING_FILE_WRITER_H_
#define CPPS_FILEREADING_FILEWRITING_FILE_WRITER_H_
#include <fstream>
void initialize_writer(std::string path);
void wd(double d);
void wf(float f);

void wb(bool b);
void wc(char c);
void wuc(unsigned char uc);
void ws(short s);
void wus(unsigned short us);
void wi(int i);
void wui(unsigned int ui);

void wstr(std::string s);

void free_writer();

#endif /* CPPS_FILEREADING_FILEWRITING_FILE_WRITER_H_ */
