#ifndef _GSSTREAMBASE_HPP_GUARD
#define _GSSTREAMBASE_HPP_GUARD

#include "BbVector.hpp"
#include "GS_Globals.hpp"
#include "GS_Species.hpp"

namespace BetterGS
{
	class GS_ComponentBase;

	class GS_StreamBase
	{
	private:
		GS_ComponentBase* source = nullptr;
		GS_ComponentBase* destination = nullptr;
	};

	class GS_Stream : public GS_StreamBase
	{
	private:
		unsigned int id = -1;
		std::array<double, 9> streamProperties;
		BbMath::BbVector conc;
		std::map<GS_Species, double> species;

	public:
		GS_Stream() = default;
		explicit GS_Stream(std::istream& is) { read(is); }

		void read(std::istream& is);

	public:
		// Properties for public access
		// Temperature
		double T() const
		{
			return streamProperties[0];
		}

		void setT(double val)
		{
			if (val < 0.)
				throw std::range_error("Cannot set a Temperature lower than absolute 0!!\n");
			else
				streamProperties[0] = val;
		}

		// Pressure
		double P() const
		{
			return streamProperties[1];
		}

		void setP(double val)
		{
			if (val < 0.)
				throw std::range_error("Cannot set a negative Pressure!!\n");
			else
				streamProperties[1] = val;
		}

		// Mass volume
		double MassVolume() const
		{
			return streamProperties[2];
		}

		void setMassVolume(double val)
		{
			if (val < 0.)
				throw std::range_error("Cannot set a negative mass volume!!\n");
			else
				streamProperties[2] = val;
		}

		// Mass enthalpy
		double MassH() const
		{
			return streamProperties[3];
		}

		void setMassH(double val)
		{
			//		if (val < 0.)
			//			throw std::range_error("Cannot set a negative mass enthalpy!");
			//		else
			streamProperties[3] = val;
		}

		// Mass entropy
		double MassS() const
		{
			return streamProperties[4];
		}

		void setMassS(double val)
		{
			//		if (val < 0.)
			//			throw std::range_error("Cannot set a negative mass entropy!");
			//		else
			streamProperties[4] = val;
		}

		// Mass flowrate
		double MassFlow() const
		{
			return streamProperties[5];
		}

		void setMassFlow(double val)
		{
			if (val < 0.)
				throw std::range_error("Cannot set a negative mass flow!!\n");
			else
				streamProperties[5] = val;
		}

		// Molar mass - READONLY
		double AverageMW() const
		{
			return streamProperties[6];
		}

		// Concentration of species in the stream
		BbMath::BbVector Concentrations() const
		{
			return conc;
		}

		void setConcentrations(const BbMath::BbVector& val)
		{
			conc = val;
		}

		void setConcentrations(BbMath::BbVector&& val)
		{
			conc = val;
		}

	public:
		double get_cp();
	};
}

#endif
