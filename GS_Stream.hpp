#ifndef _GSSTREAMBASE_HPP_GUARD
#define _GSSTREAMBASE_HPP_GUARD

#include <vector>
#include <exception>

class GS_ComponentBase;
class BbVector{};

class GS_StreamBase
{
private:
	GS_ComponentBase* source;
	GS_ComponentBase* destination;
};

class GS_MassStream : public GS_StreamBase
{
private:
	double streamProperties[9];
	BbVector concentrations;

public:
	// Properties for public access
	// Temperature
	__declspec(property( put = SetT, get = GetT )) double Temperature;

	double GetT() const
	{
		return streamProperties[0];
	}

	void SetT(double val)
	{
		if (val < 0.)
		{
			throw std::exception("Cannot set a Temperature lower than absolute 0!");
		}
		else
		{
			streamProperties[0] = val;
		}
	}

	// Pressure
	__declspec(property( put = SetP, get = GetP )) double Pressure;

	double GetP() const
	{
		return streamProperties[1];
	}

	void SetP(double val)
	{
		if (val < 0.)
		{
			throw std::exception("Cannot set a negative Pressure!");
		}
		else
		{
			streamProperties[1] = val;
		}
	}

	// Mass Flow
	__declspec(property( put = SetMF, get = GetMF )) double MassFlow;
	
	double GetMF() const
	{
		return streamProperties[2];
	}

	void SetMF(double val)
	{
		if (val < 0.)
		{
			throw std::exception("Cannot set a negative mass flow!");
		}
		else
		{
			streamProperties[2] = val;
		}
	}

	// Mass Volume
	__declspec(property( put = SetV, get = GetV )) double MassSpecificVolume;
	
	double GetV() const
	{
		return streamProperties[3];
	}

	void SetV(double val)
	{
		if (val < 0.)
		{
			throw std::exception("Cannot set a negative mass volume!");
		}
		else
		{
			streamProperties[3] = val;
		}
	}

	// Molar enthalpy
	__declspec(property( put = SetH, get = GetH )) double MolarEnthalpy;
	
	double GetH() const
	{
		return streamProperties[4];
	}

	void SetH(double val)
	{
		if (val < 0.)
		{
			throw std::exception("Cannot set a negative molar enthalpy!");
		}
		else
		{
			streamProperties[4] = val;
		}
	}

	// Molar entropy
	__declspec(property( put = SetS, get = GetS )) double MolarEntropy;
	
	double GetS() const
	{
		return streamProperties[5];
	}

	void SetS(double val)
	{
		if (val < 0.)
		{
			throw std::exception("Cannot set a negative molar entropy!");
		}
		else
		{
			streamProperties[5] = val;
		}
	}

	// Molar mass - READONLY
	__declspec(property( get = GetMW )) double MolarMass;
	
	double GetH() const
	{
		return streamProperties[6];
	}

	// Concentration of species in the stream
	__declspec(property( put = SetX, get = GetX )) BbVector Concentrations;
	
	BbVector GetX() const
	{
		return concentrations;
	}

	void SetX(const BbVector& val)
	{
		concentrations = val;
	}

public:
	double get_cp();
};

#endif