//eth32nix Shaders 
// Credits: *nixCoders Team 2008
//git commit -am "my commit msg", git format-patch -1

//keramic cham 
keramicChams
{
	cull none
	deformVertexes wave 1 sin 3 0 0 0
	noPicmip
	surfaceparm trans
	{
		map textures/sfx/construction.tga
		blendFunc GL_SRC_ALPHA GL_ONE 
		rgbGen entity
		tcGen environment 
		tcMod scroll 0.025 -0.07625 
	} 

}
outChams
{
  deformVertexes wave 100 sin 3 0 0 0.1
 	{
        map menu/art/fx_white.tga
        rgbGen entity
        blendfunc GL_ONE GL_ONE
 	}
}

/*outChams
{
	deformVertexes wave 1 sin 5 0 0 0
	{
		map textures/sfx/construction.tga
		blendFunc GL_ONE GL_ONE 
		rgbGen entity

		tcGen environment 
		tcMod scroll 0.025 -0.07625 
	} 

}*/
crystalChams
{
	cull none
	deformVertexes wave 1 sin -0.5 0 0 1
	noPicmip
	surfaceparm trans
	{
		map textures/sfx/construction.tga
		blendFunc GL_SRC_ALPHA GL_ONE 
		rgbGen entity
		tcGen environment 
		tcMod scroll 0.025 -0.07625 
	} 

}
// simple glow chams from old eth
glowChams
{
		deformVertexes wave 64 sawtooth 3 0 0 0 
		{
			map menu/art/fx_white.tga
			rgbGen entity
                depthWrite
			blendFunc GL_ONE GL_ONE 
		}
	}

// flame shader with nice effect
flameChams
{
q3map_surfacelight 1800

deformVertexes wave sawtooth 0 1 1 100
        
{
		animMap 10 gfx/effects/r.tga
		blendFunc GL_ONE GL_ONE
		depthWrite
		rgbGen entity
 		tcGen environment
                tcmod rotate 20
                tcmod scroll 1 .1
	}
	{
		animMap 10 gfx/effects/r.tga
		blendFunc GL_ONE GL_ONE
		depthWrite
		rgbGen entity
 		tcGen environment
                tcmod rotate 20
                tcmod scroll 1 .1
	}
	{
		map gfx/effects/quad.tga
		depthWrite
		blendFunc GL_ONE GL_ONE
 		tcGen environment
                tcmod rotate 20
                tcmod scroll 2 .1
		rgbGen entity
	}
}

//solid shader
solidAChams
{
deformVertexes wave 100 sin 1.5 0 0 0
	{
		map *white
		rgbGen entity
	}
}

//solid shader test
solidBChams
{
q3map_surfacelight 1800

deformVertexes wave 100 sin 3 0 0 0
 surfaceparm trans
cull none
	surfaceparm pointlight
	surfaceparm alphashadow
	{
	
		map gfx/effects/r.tga
		blendfunc GL_ONE GL_ONE
                  depthWrite
		rgbgen entity
 		tcGen environment
                tcmod rotate 10
                tcmod scroll 0 .1
	}
}

//simle old quad shader
quadAChams
{
q3map_surfacelight 1800

deformVertexes wave 100 sin 3 0 0 0
        
	{
		map gfx/effects/quad.tga
                depthWrite
  		tcGen environment
		tcmod rotate 4
		tcmod scroll 0.5 .1
 		rgbgen entity
		blendfunc GL_ONE GL_ONE
	}
}

//new type of quad shader :P
quadBChams
{
q3map_surfacelight 1800

deformVertexes wave 100 sin 3 0 0 0
        
{
		map gfx/effects/quad.tga
                depthWrite
  		tcGen environment
		tcmod rotate 4
		tcmod scroll 0.5 .1
 		rgbgen entity
		blendfunc GL_ONE GL_ONE
}
	{
		map gfx/effects/quad.tga
                depthWrite
		blendfunc GL_ONE GL_ONE
		tcGen environment
		tcmod rotate 8
		tcmod scroll 0.5 .1
  		rgbgen entity
}
	{

		map gfx/effects/quad.tga
		tcGen environment
		rgbgen entity
		tcmod rotate 16
		tcmod scroll 0.8 .1
		blendfunc GL_ONE GL_ONE
	}
}


testChams
{
	q3map_surfacelight 1200
	deformVertexes wave 100 sin 0 0 0 0
		{
		map gfx/effects/test.tga
  		tcGen environment
		tcmod rotate 2
		tcmod scroll 2.3 0.4
 		rgbgen entity
		blendfunc GL_ONE GL_ONE
	}
}

plasticChams
{
		deformVertexes wave 100 sin 0 0 0 0
		{
			map menu/art/fx_white.tga
			rgbGen entity
			blendfunc GL_ONE GL_ONE
		}
}


plasmaChams
{
      tessSize 64
        deformVertexes wave 194 sin 0 1.2 0 .4
        deformVertexes normal .5 .1
        surfaceparm nomarks
        cull none
        {
		map gfx/effects/plasma.tga
		blendfunc GL_ONE GL_ONE
		rgbGen entity
		tcGen environment
                tcmod rotate 30
		//tcMod turb 0 0.2 0 .2
                tcmod scroll 1 .1
	}
}

// quad C shader

quadCChams
{
	q3map_surfacelight 1800
       deformVertexes wave 100 sin 3 0 0 0
	{
		map gfx/effects/x.jpg
		alphaFunc GE128
                depthWrite
		
 		blendFunc GL_SRC_ALPHA GL_ONE_MINUS_DST_ALPHA
			
			tcGen environment
			tcmod rotate 15
			tcmod scroll 1 .1
}
	{
			map gfx/effects/quad.tga
		alphaFunc GE128
                depthWrite
			blendFunc GL_ONE GL_ONE
			tcGen environment
			tcmod rotate 15
			tcmod scroll 1 .1
			rgbGen entity


	}
}
// quad D

quadDChams
{
q3map_surfacelight 1800

deformVertexes wave 100 sin 3 0 0 0
        
{
		map gfx/effects/quad.tga
		alphaFunc GE128
                depthWrite
  		tcGen environment
		tcmod rotate 8
		tcmod scroll 0.5 .1
 		rgbgen entity
 		blendFunc GL_SRC_ALPHA GL_ONE_MINUS_DST_ALPHA

}
	{
		 map gfx/effects/quad.tga
		alphaFunc GE128
                depthWrite
 		blendFunc GL_ONE GL_ONE
		tcGen environment
		tcmod rotate 18
		tcmod scroll 0.5 .1
// 		rgbgen entity
}
	{
		map gfx/effects/q.jpg
		alphaFunc GE128
                depthWrite
		tcGen environment
		rgbgen entity
		tcmod rotate 16
		tcmod scroll 0.5 .1
 		blendfunc GL_ONE GL_ONE
	}
}

matrixChams
{
	q3map_surfacelight 1800
       deformVertexes wave 100 sin 3 0 0 0.1
	{
		map gfx/effects/matrix.tga
		blendFunc GL_SRC_ALPHA GL_ONE 
		alphaFunc GE128
                depthWrite
		
			rgbgen entity
			
			tcGen environment
			tcmod rotate 4
			tcmod scroll 0.3 .1
}
	{
			map gfx/effects/q.jpg
			blendFunc GL_ONE GL_ONE
			tcGen environment
			tcmod rotate 1
			tcmod scroll 0.1 .1
			rgbGen entity


	}
}

thermalChams
{
q3map_surfacelight 400

deformVertexes wave 100 sin 3 0 0 0
        
{
		map gfx/effects/thermal.tga
  		tcGen environment
		tcmod rotate 4
		tcmod scroll 0.5 .1
		rgbgen entity
		blendFunc GL_SRC_ALPHA GL_ONE_MINUS_DST_ALPHA
}
	{
		map gfx/effects/thermal.tga
		blendFunc GL_ONE GL_ONE
		tcGen environment
		tcmod rotate 4
		tcmod scroll 0.5 .1
		rgbgen entity
}
	{
		map gfx/effects/rain.tga
 		tcGen environment
		rgbgen entity
		tcmod rotate 8
		tcmod scroll 0.5 .1
		blendfunc GL_ONE GL_ONE
	}
} 
  
statbar
{
	nomipmaps
	nopicmip
	{
		map gui/common/statbar.tga
		blendfunc GL_SRC_ALPHA GL_ONE_MINUS_SRC_ALPHA
		rgbGen vertex
	}
}

statbar2
{
	nomipmaps
	nopicmip
	{
		map gui/common/statbar2.tga
		blendfunc GL_SRC_ALPHA GL_ONE_MINUS_SRC_ALPHA
		rgbGen vertex
	}
}

wa_play
{
	nomipmaps
	nopicmip
	{
		map gui/common/wa_play.tga
		blendfunc GL_SRC_ALPHA GL_ONE_MINUS_SRC_ALPHA
		rgbGen vertex
	}
}

wa_stop
{
	nomipmaps
	nopicmip
	{
		map gui/common/wa_stop.tga
		blendfunc GL_SRC_ALPHA GL_ONE_MINUS_SRC_ALPHA
		rgbGen vertex
	}
}

wa_pause
{
	nomipmaps
	nopicmip
	{
		map gui/common/wa_pause.tga
		blendfunc GL_SRC_ALPHA GL_ONE_MINUS_SRC_ALPHA
		rgbGen vertex
	}
}

wa_next
{
	nomipmaps
	nopicmip
	{
		map gui/common/wa_next.tga
		blendfunc GL_SRC_ALPHA GL_ONE_MINUS_SRC_ALPHA
		rgbGen vertex
	}
}

wa_prev
{
	nomipmaps
	nopicmip
	{
		map gui/common/wa_prev.tga
		blendfunc GL_SRC_ALPHA GL_ONE_MINUS_SRC_ALPHA
		rgbGen vertex
	}
}

portal_marker
{
	nomipmaps
	nopicmip
	{
		map gui/common/portal_marker.tga
		blendfunc GL_SRC_ALPHA GL_ONE_MINUS_SRC_ALPHA
		rgbGen vertex
	}
}

combtn_left
{
	nomipmaps
	nopicmip
	{
		map gui/common/com_button_left.tga
		blendfunc GL_SRC_ALPHA GL_ONE_MINUS_SRC_ALPHA
		rgbGen vertex
	}
}

combtn_center
{
	nomipmaps
	nopicmip
	{
		map gui/common/com_button_cen.tga
		blendfunc GL_SRC_ALPHA GL_ONE_MINUS_SRC_ALPHA
		rgbGen vertex
	}
}

combtn_right
{
	nomipmaps
	nopicmip
	{
		map gui/common/com_button_right.tga
		blendfunc GL_SRC_ALPHA GL_ONE_MINUS_SRC_ALPHA
		rgbGen vertex
	}
}

comsel_left
{
	nomipmaps
	nopicmip
	{
		map gui/common/com_select_left.tga
		blendfunc GL_SRC_ALPHA GL_ONE_MINUS_SRC_ALPHA
		rgbGen vertex
	}
}

comsel_center
{
	nomipmaps
	nopicmip
	{
		map gui/common/com_select_cen.tga
		blendfunc GL_SRC_ALPHA GL_ONE_MINUS_SRC_ALPHA
		rgbGen vertex
	}
}

comsel_right
{
	nomipmaps
	nopicmip
	{
		map gui/common/com_select_right.tga
		blendfunc GL_SRC_ALPHA GL_ONE_MINUS_SRC_ALPHA
		rgbGen vertex
	}
}
