#include "simulation/Elements.h"
//#TPT-Directive ElementClass Element_HDZN PT_HDZN 203
Element_HDZN::Element_HDZN()
{
	Identifier = "DEFAULT_PT_HDZN";
	Name = "HDZN";
	FullName = "Hydrazine";
	Colour = PIXPACK(0x9999af);
	MenuVisible = 1;
	MenuSection = SC_EXPLOSIVE;
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

	Flammable = 100;
	Explosive = 0;
	Meltable = 0;
	Hardness = 20;

	Weight = 35;

	Temperature = R_TEMP - 2.0f + 273.15f;
	HeatConduct = 29;
	Description = "Hydrazine rocket fuel.";

	Properties = TYPE_LIQUID;

	LowPressure = IPL;
	LowPressureTransition = NT;
	HighPressure = IPH;
	HighPressureTransition = NT;
	LowTemperature = ITL;
	LowTemperatureTransition = NT;
	HighTemperature = ITH;
	HighTemperatureTransition = NT;

	Update = &Element_HDZN::update;
}

//#TPT-Directive ElementHeader Element_HDZN static int update(UPDATE_FUNC_ARGS)
int Element_HDZN::update(UPDATE_FUNC_ARGS)
{
	bool hasHNO3 = false;
	int r, rx, ry;
	for (rx = -1; rx < 2; rx++)
		for (ry = -1; ry < 2; ry++)
			if (BOUNDS_CHECK)
			{
				r = pmap[y + ry][x + rx];
				if (!r || TYP(r) == PT_HDZN)
					r = sim->photons[y + ry][x + rx];
				if (!r)
					continue;
				if (TYP(r) == PT_HNO3)
					hasHNO3 = true;
			}
	if (hasHNO3&&parts[i].temp >= 400.0f) {
		sim->pv[y / CELL][x / CELL] += 10.0f;
		sim->part_change_type(ID(r), x + rx, y + ry, PT_O2);
		sim->part_change_type(i, x, y, PT_FIRE);
	}
	return 0;
}

Element_HDZN::~Element_HDZN() {}
