#pragma once

#include <fstream>

// A class for writing a .fdf file used for filling fields on a .pdf file
class FDF
{
public:
	// Add beginning boilerplate, taking in the filepath to the FDF file and the target PDF to be filled
	FDF(const std::string& filepath, const std::string& target);

	// Add ending boilerplate
	~FDF();

	void WriteTextField(const std::string& field, const std::string& value);
	void WriteCheckbox(const std::string& field, bool checked);

public:
	std::ofstream m_File;
};
