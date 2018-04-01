#include "simulation/Elements.h"
//#TPT-Directive ElementClass Element_NCTD PT_NCTD 215
Element_NCTD::Element_NCTD()
{
	Identifier = "DEFAULT_PT_NCTD";
	Name = "NCTD";
	FullName = "Nucleotide";
	Colour = PIXPACK(0xD4C890);
	MenuVisible = 1;
	MenuSection = SC_BIOLOGY;
	Enabled = 1;

	Advection = 0.7f;
	AirDrag = 0.02f * CFDS;
	AirLoss = 0.96f;
	Loss = 0.80f;
	Collision = 0.0f;
	Gravity = 0.1f;
	Diffusion = 0.00f;
	HotAir = 0.000f	* CFDS;
	Falldown = 1;

	Flammable = 0;
	Explosive = 0;
	Meltable = 0;
	Hardness = 30;

	Weight = 15;

	Temperature = R_TEMP + 0.0f + 273.15f;
	HeatConduct = 70;
	Description = "Nucleotide, the basic building block of DNA. (Doesn't do anything yet)";

	Properties = TYPE_PART;

	LowPressure = IPL;
	LowPressureTransition = NT;
	HighPressure = IPH;
	HighPressureTransition = NT;
	LowTemperature = ITL;
	LowTemperatureTransition = NT;
	HighTemperature = ITH;
	HighTemperatureTransition = NT;

	Update = NULL;
}

Element_NCTD::~Element_NCTD() {}
