#include "simulation/Elements.h"
//#TPT-Directive ElementClass Element_GAS PT_GAS 10
Element_GAS::Element_GAS()
{
	Identifier = "DEFAULT_PT_GAS";
	Name = "HCBN";
	FullName = "Hydrocarbon Gas";
	Colour = PIXPACK(0xE0FF20);
	MenuVisible = 1;
	MenuSection = SC_ORGANIC;
	Enabled = 1;

	Advection = 1.0f;
	AirDrag = 0.01f * CFDS;
	AirLoss = 0.99f;
	Loss = 0.30f;
	Collision = -0.1f;
	Gravity = 0.0f;
	Diffusion = 0.75f;
	HotAir = 0.001f	* CFDS;
	Falldown = 0;

	Flammable = 600;
	Explosive = 0;
	Meltable = 0;
	Hardness = 1;

	Weight = 1;

	Temperature = R_TEMP + 2.0f + 273.15f;
	HeatConduct = 42;
	Description = "Hydrocarbon gas. Diffuses quickly and is flammable.";

	Properties = TYPE_GAS | PROP_NEUTPASS;

	LowPressure = IPL;
	LowPressureTransition = NT;
	HighPressure = IPH;
	HighPressureTransition = NT;
	LowTemperature = ITL;
	LowTemperatureTransition = NT;
	HighTemperature = ITH;
	HighTemperatureTransition = NT;

	Update = &Element_GAS::update;
}

//#TPT-Directive ElementHeader Element_GAS static int update(UPDATE_FUNC_ARGS)
int Element_GAS::update(UPDATE_FUNC_ARGS) {
	//life=num carbons
	//tmp=num hydrogens
	//tmp2=location of double/triple bond if alkene/alkyne (tmp<2*life+2)

	//Condensation
	int t = parts[i].temp - sim->pv[y / CELL][x / CELL];	//Pressure affects state transitions
	if ((parts[i].life == 1 && t <= (-180 + 273.15)) || (parts[i].life == 2 && t <= (-100 + 273.15)) || (parts[i].life == 3 && t <= -50 + 273.15) || (parts[i].life >= 4 && t <= (4 * sqrt(500 * (parts[i].life - 4))) + 273.15))
		if (parts[i].life < 8)//Low carbon condensation
			sim->part_change_type(i, x, y, PT_MWAX);
		else if (parts[i].life >= 8 && parts[i].life < 20) //Medium carbon condensation
			sim->part_change_type(i, x, y, PT_DESL);
		else //High carbon condensation
			sim->part_change_type(i, x, y, PT_OIL);

	//Update
	int r, rx, ry;
	for (rx = -1; rx < 2; rx++)
		for (ry = -1; ry < 2; ry++)
			if (BOUNDS_CHECK)
			{
				r = pmap[y + ry][x + rx];
				if (!r || (r & 0xFF) == PT_GAS)
					r = sim->photons[y + ry][x + rx];
				if (!r)
					continue;
				if (parts[i].temp >= -100 * log(parts[i].life) + 400 + 273.15f || (r & 0xFF) == PT_FIRE || (r & 0xFF) == PT_PLSM || (r & 0xFF) == PT_LAVA) {
					for (int yy = -3; yy <= 3; yy++)
						for (int xx = -3; xx <= 3; xx++)
							if (xx*xx + yy * yy <= 9) {
								sim->create_part(-1, x + xx, y + yy, PT_FIRE);
								sim->pv[y / CELL][x / CELL] = parts[i].life > 45 ? 5 : 100.0f - parts[i].life;
							}
					if (rand() % 61 > parts[i].life)sim->part_change_type(i, x, y, rand() % 10 < 3 ? PT_CO2 : PT_SMKE);
				}
			}
	return 0;
}

Element_GAS::~Element_GAS() {}
