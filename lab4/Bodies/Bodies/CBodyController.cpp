#include "CBodyController.h"

constexpr double gravity = 9.80, densityOfWater = 1000.00;

CBodyController::CBodyController(std::istream& input, std::ostream& output, std::vector<std::shared_ptr<CBody>>& bodies)
	: m_input(input)
	, m_output(output)
	, m_bodies(bodies)
{
}

Result CBodyController::Interpret()
{
	m_output << "�������:\n"
			 << "1 - �������� ����\n"
			 << "2 - ����� ���� � ���������� ������\n"
			 << "3 - ����� ���� ������� ����� ����� ����� ������ � ����\n"
			 << "4 - ������� ���������� ��� ���� �����\n"
			 << "5 - ����� �� ���������\n";
	int command;
	ResultValidation resultValidation = ValidationValue();
	if (resultValidation.status == Status::ERROR_)
	{
		return { Status::ERROR_, "������, ����� ������� �� ����������" };
	}
	else
	{
		command = resultValidation.value;
	}
	Result result;
	result = ExecuteCommand(command);
	return result;
}

Result CBodyController::ExecuteCommand(int command)
{
	Result result;
	switch (command)
	{
	case 1:
		return AddBody();
	case 2:
		return FindBodyWithMaxMass();
	case 3:
		return FindBodyWithMinWeightInWater();
	case 4:
		return PrintAllBodies();
	case 5:
		return { Status::EXIT };
	default:
		return { Status::ERROR_, "������, ����� ������� �� ����������" };
	}
}

double CBodyController::ReadValue() const
{
	double value;
	while (!(m_input >> value))
	{
		m_input.clear();
		m_input.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		m_output << "������, ������� �����: ";
	}
	return value;
}

std::shared_ptr<CSphere> CBodyController::CreateSphere()
{
	m_output << "������� ������ ����� � ���������\n";
	double radius = ReadValue();
	double density = ReadValue();
	std::shared_ptr<CSphere> sphere = std::make_shared<CSphere>(radius, density);
	return sphere;
}

std::shared_ptr<CParallelepiped> CBodyController::CreateParallelepiped()
{
	m_output << "������� ������, �����, ������ � ��������� ���������������\n";
	double width = ReadValue();
	double depth = ReadValue();
	double height = ReadValue();
	double density = ReadValue();
	std::shared_ptr<CParallelepiped> parallelepiped = std::make_shared<CParallelepiped>(density, height, width, depth);
	return parallelepiped;
}

std::shared_ptr<CCone> CBodyController::CreateCone()
{
	m_output << "������� ������� ������, ������ � ��������� ������\n";
	double baseRadius = ReadValue();
	double height = ReadValue();
	double density = ReadValue();
	std::shared_ptr<CCone> cone = std::make_shared<CCone>(baseRadius, height, density);
	return cone;
}

std::shared_ptr<CCylinder> CBodyController::CreateCylinder()
{
	m_output << "������� ������� ������, ������ � ��������� ��������\n";
	double baseRadius = ReadValue();
	double height = ReadValue();
	double density = ReadValue();
	std::shared_ptr<CCylinder> cylinder = std::make_shared<CCylinder>(baseRadius, height, density);
	return cylinder;
}

Result CBodyController::AddBody()
{
	m_output << "\n������� ��� ���� \n1 - �����\n2 - ��������������\n3 - �����\n4 - �������\n5 - �������� ��������� ����\n6 - ����� � ������� ����\n";
	if (m_input.eof())
	{
		return { Status::EXIT };
	}
	int typeFigure;
	ResultValidation resultValidation = ValidationValue();
	if (resultValidation.status == Status::ERROR_)
	{
		return { Status::ERROR_, "������, ����� ������� �� ����������" };
	}
	else
	{
		typeFigure = resultValidation.value;
	}
	switch (typeFigure)
	{
	case 1: {
		m_bodies.push_back(CreateSphere());
		break;
	}
	case 2: {
		m_bodies.push_back(CreateParallelepiped());
		break;
	}
	case 3: {
		m_bodies.push_back(CreateCone());
		break;
	}
	case 4: {
		m_bodies.push_back(CreateCylinder());
		break;
	}
	case 5: {
		std::shared_ptr<CCompound> compound = std::make_shared<CCompound>();
		AddCompound(compound);
		if (compound->GetSize() > 0)
		{
			m_bodies.push_back(compound);
		}
		break;
	}
	case 6:
		return { Status::UP };
	default:
		return { Status::ERROR_, "������, ����� ������� �� ����������" };
	}
	return { Status::OK };
}

Result CBodyController::AddBodyCompound(std::shared_ptr<CCompound>& compound) 
{
	m_output << "\n������� ��� ���� \n1 - �����\n2 - ��������������\n3 - �����\n4 - �������\n5 - �������� ��������� ����\n6 - ��������� �� ������� ����\n";
	if (m_input.eof())
	{
		return { Status::EXIT };
	}
	int typeFigure;
	ResultValidation resultValidation = ValidationValue();
	if (resultValidation.status == Status::ERROR_)
	{
		return { Status::ERROR_, "������, ����� ������� �� ����������" };
	}
	else
	{
		typeFigure = resultValidation.value;
	}
	switch (typeFigure)
	{
	case 1: {
		compound->AddChild(CreateSphere());
		break;
	}
	case 2: {
		compound->AddChild(CreateParallelepiped());
		break;
	}
	case 3: {
		compound->AddChild(CreateCone());
		break;
	}
	case 4: {
		compound->AddChild(CreateCylinder());
		break;
	}
	case 5: {
		std::shared_ptr<CCompound> compounds = std::make_shared<CCompound>();
		AddCompound(compounds);
		if (compounds->GetSize() > 0)
		{
			compound->AddChild(compounds);
		}
		break;
	}
	case 6:
		return { Status::UP };
	default:
		return { Status::ERROR_, "������, ����� ������� �� ����������" };
	}
	return { Status::OK };
}

Result CBodyController::AddCompound(std::shared_ptr<CCompound>& compound)
{
	Result result;
	while ((result = AddBodyCompound(compound)).status != Status::EXIT && (result.status != Status::UP))
	{
		if (result.status == Status::ERROR_)
		{
			m_output << result.errorMessage << std::endl;
		}
	}
	return result;
}

bool CBodyController::IsNumber(const std::string& str) const
{
	std::regex floatRegex("[+-]?([0-9]*[.])?[0-9]+");

	return std::regex_match(str, floatRegex);
}

CBodyController::ResultValidation CBodyController::ValidationValue() const
{
	std::string inputString;
	getline(m_input, inputString);
	int number;
	if (IsNumber(inputString))
	{
		number = stoi(inputString);
		return { Status::OK, number };
	}
	else
	{
		return { Status::ERROR_ };
	}
}

Result CBodyController::FindBodyWithMaxMass() const
{
	if (m_bodies.empty())
	{
		return { Status::ERROR_, "��� ���" };
	}
	double maxMass = -DBL_MAX , currentMass = 0;
	std::shared_ptr<CBody> maxMassBody;
	std::ostringstream strm;
	for (auto& body : m_bodies)
	{
		if ((currentMass = body->GetMass()) > maxMass) 
		{
			maxMass = currentMass;
			maxMassBody = body;
		}
	}
	m_output << maxMassBody->ToString(strm) << std::endl;
	return { Status::OK };
}

Result CBodyController::FindBodyWithMinWeightInWater() const
{
	if (m_bodies.empty())
	{
		return { Status::ERROR_, "��� ���" };
	}
	double minWeight = DBL_MAX, currentWeight = 0;
	std::shared_ptr<CBody> minWeightBody;
	std::ostringstream strm;

	for (auto& body : m_bodies)
	{
		currentWeight = (body->GetDensity() - densityOfWater) * gravity * body->GetVolume();
		if (currentWeight < minWeight)
		{
			minWeight = currentWeight;
			minWeightBody = body;
		}
	}
	m_output << minWeightBody->ToString(strm) << std::endl;
	return { Status::OK };
}

Result CBodyController::PrintAllBodies() const
{
	if (m_bodies.empty())
	{
		return { Status::ERROR_, "��� ���" };
	}
	std::ostringstream strm;
	for (int i = 0; i < m_bodies.size(); i++)
	{
		m_output << m_bodies[i]->ToString(strm) << std::endl;
	}
	return { Status::OK };
}
