//////////////////////////////////////////////////////////////////////////
//  
//  Copyright (c) 2012, Image Engine Design Inc. All rights reserved.
//  
//  Redistribution and use in source and binary forms, with or without
//  modification, are permitted provided that the following conditions are
//  met:
//  
//      * Redistributions of source code must retain the above
//        copyright notice, this list of conditions and the following
//        disclaimer.
//  
//      * Redistributions in binary form must reproduce the above
//        copyright notice, this list of conditions and the following
//        disclaimer in the documentation and/or other materials provided with
//        the distribution.
//  
//      * Neither the name of John Haddon nor the names of
//        any other contributors to this software may be used to endorse or
//        promote products derived from this software without specific prior
//        written permission.
//  
//  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS
//  IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
//  THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
//  PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
//  CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
//  EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
//  PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
//  PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
//  LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
//  NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
//  SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//  
//////////////////////////////////////////////////////////////////////////

#ifndef GAFFER_DATETIMEPARAMETERHANDLER_H
#define GAFFER_DATETIMEPARAMETERHANDLER_H

#include "IECore/DateTimeParameter.h"

#include "Gaffer/ParameterHandler.h"
#include "Gaffer/TypedPlug.h"

namespace Gaffer
{

class DateTimeParameterHandler : public ParameterHandler
{

	public :

		IE_CORE_DECLAREMEMBERPTR( DateTimeParameterHandler );

		DateTimeParameterHandler( IECore::DateTimeParameterPtr parameter );
		virtual ~DateTimeParameterHandler();
				
		virtual IECore::ParameterPtr parameter();
		virtual IECore::ConstParameterPtr parameter() const;
		virtual void restore( GraphComponent *plugParent );
		virtual Gaffer::PlugPtr setupPlug( GraphComponent *plugParent, Plug::Direction direction=Plug::In );
		virtual Gaffer::PlugPtr plug();
		virtual Gaffer::ConstPlugPtr plug() const;
		virtual void setParameterValue();
		virtual void setPlugValue();
				
	private :

		IECore::DateTimeParameterPtr m_parameter;
		StringPlugPtr m_plug;
	
		static ParameterHandlerDescription<DateTimeParameterHandler, IECore::DateTimeParameter> g_description;

};

} // namespace Gaffer

#endif // GAFFER_DATETIMEPARAMETERHANDLER_H
