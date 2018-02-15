#include "simulation/Elements.h"
//#TPT-Directive ElementClass Element_CYAN PT_CYAN 199
Element_CYAN::Element_CYAN()
{
	Identifier = "DEFAULT_PT_CYAN";
	Name = "CYAN";
	FullName = "Cyanide";
	Colour = PIXPACK(0x03a4f9);
	MenuVisible = 1;
	MenuSection = SC_ORGANIC;
	Enabled = 1;

	Advection = 0.6f;
	AirDrag = 0.01f * CFDS;
	AirLoss = 0.98f;
	Loss = 0.95f;
	Collision = 0.0f;
	Gravity = 0.1f;
	Diffusion = 0.00f;
	HotAir = 0.000f	* CFDS;
	Falldown = 2;

	Flammable = 0;
	Explosive = 0;
	Meltable = 0;
	Hardness = 20;

	Weight = 30;

	Temperature = R_TEMP + 0.0f + 273.15f;
	HeatConduct = 251;
	Description = "Cyanide, the deadly poison.";

	Properties = TYPE_LIQUID | PROP_DEADLY;

	LowPressure = IPL;
	LowPressureTransition = NT;
	HighPressure = IPH;
	HighPressureTransition = NT;
	LowTemperature = ITL;
	LowTemperatureTransition = NT;
	HighTemperature = ITH;
	HighTemperatureTransition = NT;

	Update = &Element_CYAN::update;
}

Element_CYAN::~Element_CYAN() {}

//#TPT-Directive ElementHeader Element_CYAN static int update(UPDATE_FUNC_ARGS)
int Element_CYAN::update(UPDATE_FUNC_ARGS)
{
	int r, rx, ry;
	for (rx = -1; rx < 2; rx++)
		for (ry = -1; ry < 2; ry++)
			if (BOUNDS_CHECK)
			{
				r = pmap[y + ry][x + rx];
				if (!r || TYP(r) == PT_CYAN)
					r = sim->photons[y + ry][x + rx];
				if (!r)
					continue;
			}
	return 0;
}