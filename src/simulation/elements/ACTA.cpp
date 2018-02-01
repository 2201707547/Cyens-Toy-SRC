#include "simulation/Elements.h"
//#TPT-Directive ElementClass Element_ACTA PT_ACTA 194
Element_ACTA::Element_ACTA()
{
	Identifier = "DEFAULT_PT_ACTA";
	Name = "ACTA";
	FullName = "Acetic Acid";
	Colour = PIXPACK(0xE9F0D3);
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

	Weight = 35;

	Temperature = R_TEMP + 0.0f + 273.15f;
	HeatConduct = 251;
	Description = "Acetic acid, mix with water to make vinegar.";

	Properties = TYPE_LIQUID;

	LowPressure = IPL;
	LowPressureTransition = NT;
	HighPressure = IPH;
	HighPressureTransition = NT;
	LowTemperature = ITL;
	LowTemperatureTransition = NT;
	HighTemperature = ITH;
	HighTemperatureTransition = NT;

	Update = &Element_ACTA::update;
}

Element_ACTA::~Element_ACTA() {}

//#TPT-Directive ElementHeader Element_ACTA static int update(UPDATE_FUNC_ARGS)
int Element_ACTA::update(UPDATE_FUNC_ARGS)
{
	int w = 0;
	int r, rx, ry;
	for (rx = -1; rx < 2; rx++)
		for (ry = -1; ry < 2; ry++)
			if (BOUNDS_CHECK)
			{
				r = pmap[y + ry][x + rx];
				if (!r || TYP(r) == PT_ACTA)
					r = sim->photons[y + ry][x + rx];
				if (!r)
					continue;
				if (TYP(r) == PT_WATR || TYP(r) == PT_DSTW)w++;
			}
	if (w > 3)sim->part_change_type(i, x, y, PT_VNGR);
	return 0;
}