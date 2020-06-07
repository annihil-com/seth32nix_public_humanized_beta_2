// Hitler portrait by Leon
// leonmohpa@yahoo.com
// Do not rip this file or you will R.I.P.

models/players/temperate/axis/soldier/helmet_h
{
	cull none
	{
		map models/players/temperate/axis/soldier/helmet_h.tga
		rgbGen const ( 0 0 0 ) 
		alphaFunc GE128
		depthWrite
	}

	{
		map models/players/temperate/axis/soldier/helmet_h.tga
		blendFunc GL_ONE GL_ONE_MINUS_SRC_ALPHA
		rgbGen lightingdiffuse
		depthFunc equal
	}
}

models/players/temperate/axis/inside_h
{
	cull none
	{
		map models/players/temperate/axis/inside_h.tga
		rgbGen const ( 0 0 0 ) 
		alphaFunc GE128
		depthWrite
	}

	{
		map models/players/temperate/axis/inside_h.tga
		blendFunc GL_ONE GL_ONE_MINUS_SRC_ALPHA
		rgbGen lightingdiffuse
		depthFunc equal
	}
}

models/players/temperate/allied/strap
{
	cull disable
	implicitMap models/players/temperate/allied/inside.tga

}

models/players/multi/acc/backpack/backpack_lieu
{
	cull disable //Rich - Why does this shader have cull disable??
	{
		map models/players/multi/acc/backpack/backpack_lieu.tga
		alphafunc ge128
		rgbGen lightingDiffuse
	}
}

models/players/temperate/axis/ranks/major
{
	polygonoffset
	
	{
		map models/players/temperate/allied/ranks/major.tga
		alphaFunc GE128
		rgbGen lightingDiffuse
	}
}

models/players/temperate/axis/ranks/feldwebel
{
	polygonoffset
	
	{
		map models/players/temperate/allied/ranks/sergeant.tga
		alphaFunc GE128
		rgbGen lightingDiffuse
	}
}

models/players/temperate/axis/ranks/leutnant
{
	polygonoffset
	
	{
		map models/players/temperate/allied/ranks/lieutenant.tga
		alphaFunc GE128
		rgbGen lightingDiffuse
	}
}


models/players/temperate/axis/ranks/gefreiter
{
	polygonoffset
	
	{
		map models/players/temperate/allied/ranks/corporal.tga
		alphaFunc GE128
		rgbGen lightingDiffuse
	}
}



models/players/temperate/axis/ranks/oberst
{
	polygonoffset
	
	{
		map models/players/temperate/allied/ranks/colonel.tga
		alphaFunc GE128
		rgbGen lightingDiffuse
	}
}

models/players/temperate/axis/ranks/hauptmann
{
	polygonoffset	
	
	{
		map models/players/temperate/allied/ranks/captain.tga
		alphaFunc GE128
		rgbGen lightingDiffuse
	}
}



models/players/temperate/axis/ranks/oberschutze
{
	polygonoffset	
	
	{
		map models/players/temperate/allied/ranks/1stclass.tga
		alphaFunc GE128
		rgbGen lightingDiffuse
	}
}



models/players/temperate/allied/ranks/major
{
	polygonoffset
	
	{
		map models/players/temperate/allied/ranks/major.tga
		alphaFunc GE128
		rgbGen lightingDiffuse
	}
}

models/players/temperate/allied/ranks/sergeant
{
	qer_models/players/temperate/allied/ranks/sergeant.tga
	polygonoffset
	
	{
		map models/players/temperate/allied/ranks/sergeant.tga
		alphaFunc GE128
		rgbGen lightingDiffuse
	}
}

models/players/temperate/allied/ranks/lieutenant
{
	polygonoffset
	
	{
		map models/players/temperate/allied/ranks/lieutenant.tga
		alphaFunc GE128
		rgbGen lightingDiffuse
	}
}


models/players/temperate/allied/ranks/corporal
{
	polygonoffset
	
	{
		map models/players/temperate/allied/ranks/corporal.tga
		alphaFunc GE128
		rgbGen lightingDiffuse
	}
}



models/players/temperate/allied/ranks/colonel
{
	polygonoffset
	
	{
		map models/players/temperate/allied/ranks/colonel.tga
		alphaFunc GE128
		rgbGen lightingDiffuse
	}
}


models/players/temperate/allied/ranks/captain
{
	polygonoffset	
	
	{
		map models/players/temperate/allied/ranks/captain.tga
		alphaFunc GE128
		rgbGen lightingDiffuse
	}
}



models/players/temperate/allied/ranks/1stclass
{
	polygonoffset	
	
	{
		map models/players/temperate/allied/ranks/1stclass.tga
		alphaFunc GE128
		rgbGen lightingDiffuse
	}
}

models/players/temperate/axis/engineer/engineer_body
{
	cull none
	implicitMap -
}

models/players/temperate/axis/cvops/body_cvops
{
	cull none
	implicitMap -
}

models/players/temperate/axis/fieldops/body_fieldops
{
	cull none
	implicitMap -
}

models/players/temperate/axis/medic/axis_medic
{
	cull none
	implicitMap -
}

models/players/temperate/axis/soldier/body_soldier
{
	cull none
	implicitMap -
}




models/players/temperate/allied/soldier/body
{
	cull none
	implicitMap -
}

models/players/temperate/allied/medic/body
{
	cull none
	implicitMap -
}

models/players/temperate/allied/engineer/body
{
	cull none
	implicitMap -
}

models/players/temperate/allied/fieldops/body
{
	cull none
	implicitMap -
}

models/players/temperate/allied/cvops/body
{
	cull none
	implicitMap -
}
