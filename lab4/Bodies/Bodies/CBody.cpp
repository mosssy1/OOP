#include "CBody.h"

CBody::CBody()
{
}

CBody::~CBody()
{
}


std::string CBody::ToString(std::ostringstream& strm) const
{
	strm << GetType() << ":" << std::endl
		 << std::setprecision(10) 
		 << "\tÏëîíòíîñòü = " << GetDensity() << std::endl
		 << "\tÎáú¸ì = " << GetVolume() << std::endl
		 << "\tÌàññà = " << GetMass() << std::endl;
	AppendProperties(strm);
	return strm.str();
}