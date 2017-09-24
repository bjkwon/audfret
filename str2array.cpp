#pragma once

#include <string>
#include <vector>
using namespace std;
#include "audfret.h"
#include "audstr.h"

AUDFRET_EXP void ReplaceStr(string &str, const string& from, const string& to) {
    size_t start_pos = 0;
    while((start_pos = str.find(from, start_pos)) != std::string::npos) {
        str.replace(start_pos, from.length(), to);
        start_pos += to.length(); // Handles case where 'to' is a substring of 'from'
    }
}

AUDFRET_EXP size_t str2vect(vector<string> &_out, const char* input, const char *delim)
{ // Bug found--If delim contains repeating character(s), it goes into an infinite loop. Avoid that. 8/4/2017
	size_t pos;
	string str(input);
	string delim2(delim); 
	vector<string> out;
	int nitems = countDeliminators(input, delim);
	out.reserve(nitems);
	delim2 = delim2.front();
	for (unsigned int k=1; k<strlen(delim); k++) 
		while( (pos=str.find(delim[k]))!=string::npos)
			str.replace(pos,1,delim2);

	while( (pos=str.find(delim[0]))!=string::npos)
	{
		if (pos==0) pos++;
		else		out.push_back(str.substr(0,pos));
		str.erase(0,pos);
	}
	if (str.length()>0) out.push_back(str);
	_out = out;
	return out.size();
}

AUDFRET_EXP string consoldateStr(vector<string> &input, char delim)
{
	string out;
	for (size_t k=0; k<input.size(); k++)
	{
		out += input[k];
		out += delim;
	}
	return out;
}

AUDFRET_EXP char* recoverNULL(int *dummy, char *dest, const char *src)
{ return NULL; }
AUDFRET_EXP char* recoverNULL(float *dummy, char *dest, const char *src)
{ return NULL; }
AUDFRET_EXP char* recoverNULL(double *dummy, char *dest, const char *src)
{ return NULL; }

AUDFRET_EXP char * copyItem(char * out, char * in)
{
	return strcpy(out,in);
}

AUDFRET_EXP int copyItem(int out, char * in)
{
	int res = sscanf(in, "%d", &out);
	if (res==EOF || res==0) return 0;
	return out;
}

AUDFRET_EXP double copyItem(double out, char * in)
{
	int res = sscanf(in, "%lf", &out);
	if (res==EOF || res==0) return 0;
	return out;
}

AUDFRET_EXP int str2intarray(int* out, int maxSize_x, const char * str, const char *deliminators)
{
	return str2array(out, maxSize_x, str, deliminators);
}

AUDFRET_EXP int str2strarray(char** out, int maxSize_x, const char * str, const char *deliminators)
{
	return str2array(out, maxSize_x, str, deliminators);
}

AUDFRET_EXP int str2doublearray(double* out, int maxSize_x, const char * str, const char *deliminators)
{
	return str2array(out, maxSize_x, str, deliminators);
}

AUDFRET_EXP void splitevenindices(vector<int> &out, int nTotals, int nGroups)
{
	int nItems = nTotals / nGroups;
	int chunkwithnItems = nGroups * nItems;
	int leftover = nTotals - chunkwithnItems;
	out.clear();
	out.assign(nGroups, nItems);

	if (leftover>0)
	{
		int *holder = new int[nGroups];
		double split = (double)leftover / (double)nGroups;
		for (int i=0; i<nGroups; i++)	holder[i] = (int)(split*(double)i+.5);
		for (int i=1; i<nGroups; i++)	holder[i-1] = holder[i]-holder[i-1];
		int sum(0);
		for (int i=0; i<nGroups-1; i++) sum += holder[i];
		holder[nGroups-1] = leftover - sum;
		int k(0);
		for (vector<int>::iterator it=out.begin(); it!=out.end(); it++, k++)
			*it += holder[k];
		delete[] holder;
	}
}

AUDFRET_EXP int sformat(string& out, size_t nLengthMax, const char* format, ...) 
{
	// Obsolete as of 5/2/2017 bjkwon
	char *buffer = new char[nLengthMax];
	va_list vl;
	va_start(vl, format);
	int res = vsnprintf(buffer, nLengthMax, format, vl);
	buffer[nLengthMax-1] =0;
	out = string(buffer);
	delete[] buffer;
	va_end(vl);
	return res;
}


AUDFRET_EXP int sformat(string& out, const char* format, ...) 
{
	size_t bufsize(4096);
	bufsize += strlen(format);
	const char *tp;
	va_list args;
	va_start(args, format);
	char *buffer = new char[bufsize];
	int res = vsnprintf(buffer, bufsize, format, args);
	va_end(args);
	if (res>=bufsize) 
	{
		delete[] buffer;
		bufsize = res+1;
		buffer = new char[bufsize];
		va_start(args, format);
		res = vsnprintf(buffer, bufsize, format, args);
		va_end(args);
	}
	out = string(buffer);
	delete[] buffer;
	return res; // This includes the null character
}
