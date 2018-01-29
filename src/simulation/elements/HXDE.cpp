#include "simulation/Elements.h"
//#TPT-Directive ElementClass Element_HXDE PT_HXDE 191
Element_HXDE::Element_HXDE()
{
	Identifier = "DEFAULT_PT_HXDE";
	Name = "OH-";
	FullName = "Hydroxide Ion";
	Colour = PIXPACK(0xF9F0FF);
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
	Description = "The hydroxide ion. Also represents the hydroxyl functional group, useful in organic compounds.";

	Properties = TYPE_GAS;

	LowPressure = IPL;
	LowPressureTransition = NT;
	HighPressure = IPH;
	HighPressureTransition = NT;
	LowTemperature = ITL;
	LowTemperatureTransition = NT;
	HighTemperature = ITH;
	HighTemperatureTransition = NT;

	Update = &Element_HXDE::update;
}

Element_HXDE::~Element_HXDE() {}

//#TPT-Directive ElementHeader Element_HXDE static int update(UPDATE_FUNC_ARGS)
int Element_HXDE::update(UPDATE_FUNC_ARGS)
{
	int r, rx, ry;
	for (rx = -1; rx < 2; rx++)
		for (ry = -1; ry < 2; ry++)
			if (BOUNDS_CHECK)
			{
				r = pmap[y + ry][x + rx];
				if (!r || (r & 0xFF) == PT_HXDE)
					r = sim->photons[y + ry][x + rx];
				if (!r)
					continue;

				if ((r & 0xFF) == PT_H2) {
					sim->part_change_type(i, x, y, PT_WTRV);
					sim->kill_part(ID(r));
				}

				if ((r & 0xFF) == PT_GAS || (r & 0xFF) == PT_DESL || (r & 0xFF) == PT_MWAX || (r & 0xFF) == PT_WAX || (r & 0xFF) == PT_PRFN || (r & 0xFF) == PT_OIL) {
					sim->part_change_type(ID(r), x + rx, y + ry, PT_ALCL);
					sim->kill_part(i);
				}
			}
	return 0;
}