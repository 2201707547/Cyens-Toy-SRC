#include "simulation/Elements.h"
//#TPT-Directive ElementClass Element_CRBN PT_CRBN 189
Element_CRBN::Element_CRBN()
{
	Identifier = "DEFAULT_PT_CRBN";
	Name = "CRBN";
	FullName = "Carbon";
	Colour = PIXPACK(0x6e6e6e);
	MenuVisible = 1;
	MenuSection = SC_ORGANIC;
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

	Flammable = 10;
	Explosive = 0;
	Meltable = 0;
	Hardness = 30;

	Weight = 85;

	Temperature = R_TEMP + 0.0f + 273.15f;
	HeatConduct = 70;
	Description = "Carbon, essential to organic compounds and life.";

	Properties = TYPE_PART;

	LowPressure = IPL;
	LowPressureTransition = NT;
	HighPressure = IPH;
	HighPressureTransition = NT;
	LowTemperature = ITL;
	LowTemperatureTransition = NT;
	HighTemperature = ITH;
	HighTemperatureTransition = NT;

	Update = &Element_CRBN::update;
}

Element_CRBN::~Element_CRBN() {}

//#TPT-Directive ElementHeader Element_CRBN static int update(UPDATE_FUNC_ARGS)
int Element_CRBN::update(UPDATE_FUNC_ARGS)
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

				if ((r & 0xFF) == PT_H2) {
					sim->part_change_type(i, x, y, PT_GAS);
					sim->kill_part(ID(r));
				}

				if ((r & 0xFF) == PT_O2) {
					sim->part_change_type(i, x, y, PT_CO2);
					sim->kill_part(ID(r));
				}

				if (sim->pv[y / CELL][x / CELL] >= 235.0f) {
					sim->part_change_type(i, x, y, PT_BCOL);
					parts[i].life = 110;
					parts[i].tmp = -1;
				}
			}
	return 0;
}