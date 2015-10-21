/*\
 *
 * File: form.hpp
 * Language: C++
 *
 * Author: culb ( nightfrog )
 *
 * Methods to form the values returned from the CPUID instruction
 *
\*/

#ifndef __FORM__
#define __FORM__

#include <string>
#include <cctype> /* isspace */
#include <sstream> /* stringstream */
#include <stdint.h>




/* Push the values in a register to a string */
static
void
reg_to_string(uint32_t reg, std::stringstream & str)
{
	for(int32_t i = 0; i <= 3; i++)
		str << ((char*)&reg)[i];
}


/* Reduce multiple whitespaces to a single whitepace */
static
std::string
whitespace_reduce(std::string str)
{
	uint32_t index;
	while ((index = str.find("  ")) != std::string::npos)
		str.erase(index, 1);
	return str;
}


/* Remove leading whitespace */
static
std::string
trim_l(std::string str)
{
	while (std::isspace(*str.begin()))
		str.erase(str.begin());
	return str;
}

#endif /* __FORM__ */
