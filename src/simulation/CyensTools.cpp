#include "CyensTools.h"

void ClampOrganic(Particle *p)
{
	int t = p->type;

	//Update alkanes/enes/ynes to prevent nonsense like C2H16 or C0H4 from forming using the console or prop tool
	if (t == PT_GAS || t == PT_MWAX || t == PT_WAX || t == PT_OIL || t == PT_DESL || t == PT_PRFN) {
		if (p->life <= 1) {	//It's methane or the carbons were set to 0 or less
			p->life = 1;
			p->tmp = 4;
			p->tmp2 = 0;	//There's no double or triple bond in methane
		}
		else if (p->life > 60) {	//If it's too long make it into generic kerosene
			p->life = 60;
			p->tmp = 122;
			p->tmp2 = 0;
		}
		else {	//In the case that it's a proper number of carbons, check the amount of hydrogens to make sure it's good, then check bonds

			//If there are too many or too little hydrogens for the amount of carbons, fix it by randomly generating a proper molecule
			if (p->tmp > 2 * p->life + 2 || p->tmp < 2 * p->life - 2)
				p->tmp = makeAlk(p->life);

			//Get rid of special bonds where they don't belong otherwise check to make sure the bond is in an allowed position
			if (p->tmp == 2 * p->life + 2)
				p->tmp2 = 0;
			else {
				if(p->tmp2>p->life/2)	//These simple hydrocarbons are like palindromes: 1-pentene is the same as 4-pentene, 
										//so always use the lesser number for the bond location
					p->tmp2 = getBondLoc(p->life);
			}
		}
	}
}

//Generates a random hydrocarbon type (alkane/ene/yne) with given number of carbons, returns number of hydrogens
int makeAlk(int c) {
	int alkType = rand() % 3;
	return alkType == 0 ? (2 * c + 2) : alkType == 1 ? (2 * c) : (2 * c - 2);
}

//Gets the bond location randomly for alkenes and alkynes
int getBondLoc(int c) {
	return (rand() % (c / 2)) + 1;
}