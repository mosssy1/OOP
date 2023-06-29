#pragma once
#include "CSolidBody.h"
#include <vector>

class CCompound final : public CBody
{
public:
	CCompound();
	double GetVolume() const;
	double GetMass() const;
	double GetDensity() const ;
	size_t GetSize() const;
	std::string GetType() const override;
	bool AddChild(std::shared_ptr<CBody> child);
	~CCompound();

private:
	void AddParent(CCompound* parent);
	void AppendProperties(std::ostringstream& output) const override;
	CCompound* m_parent;
	std::vector<std::shared_ptr<CBody>> m_children;
};