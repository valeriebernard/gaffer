##########################################################################
#  
#  Copyright (c) 2011, Image Engine Design Inc. All rights reserved.
#  
#  Redistribution and use in source and binary forms, with or without
#  modification, are permitted provided that the following conditions are
#  met:
#  
#      * Redistributions of source code must retain the above
#        copyright notice, this list of conditions and the following
#        disclaimer.
#  
#      * Redistributions in binary form must reproduce the above
#        copyright notice, this list of conditions and the following
#        disclaimer in the documentation and/or other materials provided with
#        the distribution.
#  
#      * Neither the name of John Haddon nor the names of
#        any other contributors to this software may be used to endorse or
#        promote products derived from this software without specific prior
#        written permission.
#  
#  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS
#  IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
#  THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
#  PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
#  CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
#  EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
#  PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
#  PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
#  LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
#  NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
#  SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
#  
##########################################################################

import unittest

import Gaffer
import GafferUI

class StandardNodeGadgetTest( unittest.TestCase ) :

	def testContents( self ) :
	
		n = Gaffer.Node()
		
		g = GafferUI.StandardNodeGadget( n )
		
		self.failUnless( isinstance( g.getContents(), GafferUI.NameGadget ) )
		self.assertEqual( g.getContents().getText(), n.getName() )
		
		t = GafferUI.TextGadget( "I'll choose my own label thanks" )
		g.setContents( t )
		
		self.failUnless( g.getContents().isSame( t ) )
	
	def testSubClassing( self ) :
	
		class MyNodeGadget( GafferUI.StandardNodeGadget ) :
		
			def __init__( self, node ) :
			
				GafferUI.StandardNodeGadget.__init__( self, node, deferNoduleCreation = True )
				
				self.addNodules()
				
			def acceptsNodule( self, plug ) :
			
				return isinstance( plug, Gaffer.IntPlug )
				
		n = Gaffer.Node()
		n.addChild( Gaffer.IntPlug( "i" ) )
		n.addChild( Gaffer.FloatPlug( "f" ) )
		
		g = MyNodeGadget( n )
		
		self.failUnless( g.nodule( n["i"] ) is not None )
		self.failUnless( g.nodule( n["f"] ) is None )
	
	def testBadSubclassingRaises( self ) :
	
		class MyBrokenNodeGadget( GafferUI.StandardNodeGadget ) :
			
			def __init__( self, node ) :
			
				# oops! not passing deferNoduleCreation = True
				GafferUI.StandardNodeGadget.__init__( self, node )
				
				self.addNodules()
				
		self.assertRaises( RuntimeError, MyBrokenNodeGadget, Gaffer.Node() )
		
if __name__ == "__main__":
	unittest.main()
	
