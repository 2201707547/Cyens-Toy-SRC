#include "simulation/Elements.h"
//#TPT-Directive ElementClass Element_SDUM PT_SDUM 187
Element_SDUM::Element_SDUM()
{
	Identifier = "DEFAULT_PT_SDUM";
	Name = "SDUM";
	FullName = "Sodium";
	Colour = PIXPACK(0xdddddd);
	MenuVisible = 1;
	MenuSection = SC_POWDERS;
	Enabled = 1;

	Advection = 0.4f;
	AirDrag = 0.04f * CFDS;
	AirLoss = 0.94f;
	Loss = 0.95f;
	Collision = -0.1f;
	Gravity = 0.3f;
	Diffusion = 0.00f;
	HotAir = 0.000f	* CFDS;
	Falldown = 1;

	Flammable = 100;
	Explosive = 0;
	Meltable = 5;
	Hardness = 1;

	Weight = 75;

	Temperature = R_TEMP + 0.0f + 273.15f;
	HeatConduct = 110;
	Description = "Sodium, like a weak powder form of RBDM.";

	Properties = TYPE_PART;

	LowPressure = IPL;
	LowPressureTransition = NT;
	HighPressure = IPH;
	HighPressureTransition = NT;
	LowTemperature = ITL;
	LowTemperatureTransition = NT;
	HighTemperature = ITH;
	HighTemperatureTransition = NT;

	Update = &Element_SDUM::update;
}

Element_SDUM::~Element_SDUM() {}

//#TPT-Directive ElementHeader Element_SDUM static int update(UPDATE_FUNC_ARGS)
int Element_SDUM::update(UPDATE_FUNC_ARGS)
{
	int r, rx, ry;
	for (rx = -1; rx < 2; rx++)
		for (ry = -1; ry < 2; ry++)
			if (BOUNDS_CHECK)
			{
				r = pmap[y + ry][x + rx];
				if (!r || (r & 0xFF) == PT_SDUM)
					r = sim->photons[y + ry][x + rx];
				if (!r)
					continue;
				if ((r & 0xFF) == PT_CAUS) {
					sim->part_change_type(i, x, y, PT_SALT);
					sim->kill_part(ID(r));
					sim->pv[y / CELL][x / CELL] += 5;
					sim->hv[y / CELL][x / CELL] += 15;
				}
			}
	return 0;
}