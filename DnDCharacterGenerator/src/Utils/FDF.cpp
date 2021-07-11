#include "FDF.h"

#include <string>

FDF::FDF(const std::string& filepath, const std::string& target)
{
	m_File.open(filepath, std::fstream::out);

	if (m_File.is_open())
	{
		m_File << "%FDF-1.2\n";
		m_File << "1 0 obj\n";
		m_File << "<<\n/FDF\n<<\n";
		m_File << "/F(" << target << ")\n";
		m_File << "/Fields\n[";
	}
}

FDF::~FDF()
{
	if (m_File.is_open())
	{
		m_File << "\n]\n>>\n>>\n";
		m_File << "endobj\ntrailer\n";
		m_File << "<</Root 1 0 R>>\n";
		m_File << "%%EOF\n";
		m_File.close();
	}
}

void FDF::WriteTextField(const std::string& field, const std::string& value)
{
	if (m_File.is_open())
		m_File << "\n<< /T (" << field << ") /V (" << value <<  ") >>";
}

void FDF::WriteCheckbox(const std::string& field, bool checked)
{
	if (m_File.is_open())
	{
		if (checked)
			m_File << "\n<< /T (" << field << ") /V /Yes >>";
		else
			m_File << "\n<< /T (" << field << ") /V /Off >>";
	}
}
