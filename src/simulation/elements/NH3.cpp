#include "simulation/Elements.h"
//#TPT-Directive ElementClass Element_NH3 PT_NH3 190
Element_NH3::Element_NH3()
{
	Identifier = "DEFAULT_PT_NH3";
	Name = "NH3";
	FullName = "Ammonia";
	Colour = PIXPACK(0xCACCBE);
	MenuVisible = 1;
	MenuSection = SC_ORGANIC;
	Enabled = 1;

	Advection = 2.0f;
	AirDrag = 0.00f * CFDS;
	AirLoss = 0.99f;
	Loss = 0.30f;
	Collision = -0.10f;
	Gravity = 0.00f;
	Diffusion = 3.00f;
	HotAir = 0.000f	* CFDS;
	Falldown = 0;

	Flammable = 0;
	Explosive = 0;
	Meltable = 0;
	Hardness = 0;

	Weight = 1;

	Temperature = R_TEMP + 0.0f + 273.15f;
	HeatConduct = 251;
	Description = "Ammonia, useful organic compound.";

	Properties = TYPE_GAS;

	LowPressure = IPL;
	LowPressureTransition = NT;
	HighPressure = IPH;
	HighPressureTransition = NT;
	LowTemperature = ITL;
	LowTemperatureTransition = NT;
	HighTemperature = ITH;
	HighTemperatureTransition = NT;

	Update = &Element_NH3::update;
}

Element_NH3::~Element_NH3() {}

//#TPT-Directive ElementHeader Element_NH3 static int update(UPDATE_FUNC_ARGS)
int Element_NH3::update(UPDATE_FUNC_ARGS)
{
	int r, rx, ry;
	for (rx = -1; rx < 2; rx++)
		for (ry = -1; ry < 2; ry++)
			if (BOUNDS_CHECK)
			{
				r = pmap[y + ry][x + rx];
				if (!r || TYP(r) == PT_NH3)
					r = sim->photons[y + ry][x + rx];
				if (!r)
					continue;
				
				//Future reactions to be implemented here
			}
	return 0;
}