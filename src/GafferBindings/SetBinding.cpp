//////////////////////////////////////////////////////////////////////////
//  
//  Copyright (c) 2011, John Haddon. All rights reserved.
//  Copyright (c) 2011-2013, Image Engine Design Inc. All rights reserved.
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

#include "boost/python.hpp"
#include "boost/python/slice.hpp"

#include "IECorePython/RunTimeTypedBinding.h"

#include "Gaffer/Set.h"

#include "GafferBindings/SignalBinding.h"
#include "GafferBindings/CatchingSlotCaller.h"

using namespace Gaffer;

namespace GafferBindings
{

static IECore::RunTimeTypedPtr getItem( Set &s, long index )
{
	long size = s.size();

	if( index < 0 )
	{
		index += size;
	}

	if( index >= size || index < 0 )
	{
		PyErr_SetString( PyExc_IndexError, "Index out of range" );
		boost::python::throw_error_already_set();
	}

	return s.member( index );
}

static boost::python::list getSlice( Set &s, boost::python::slice sl )
{
	Py_ssize_t start, stop, step, length;
	if( PySlice_GetIndicesEx( (PySliceObject *)sl.ptr(), s.size(), &start, &stop, &step, &length ) )
	{
		boost::python::throw_error_already_set();
	}
	
	boost::python::list result;
	for( Py_ssize_t i = start; i < stop; i++ )
	{
		result.append( Set::MemberPtr( s.member( i ) ) );
	}
	return result;
}

struct MemberSignalSlotCaller
{
	
	boost::signals::detail::unusable operator()( boost::python::object slot, SetPtr s, Set::MemberPtr m )
	{
		try
		{
			slot( s, m );
		}
		catch( const boost::python::error_already_set &e )
		{
			PyErr_PrintEx( 0 ); // clears the error status
		}
		return boost::signals::detail::unusable();
	}


};

void bindSet()
{
	
	boost::python::scope s = IECorePython::RunTimeTypedClass<Set>()
		.def( "contains", &Set::contains )
		.def( "size", &Set::size )
		.def( "__contains__", &Set::contains )
		.def( "__len__", &Set::size )
		// boost python overload resolution will try the functions in the reverse
		// order to which they were def'd. so getItem is bound last as that's the
		// one that needs the best performance - there's a small but measurable speed
		// hit to indexing if the getSlice binding is tried and rejected before finding the
		// getItem binding.
		.def( "__getitem__", &getSlice )
		.def( "__getitem__", &getItem )
		.def( "memberAddedSignal", &Set::memberAddedSignal, boost::python::return_internal_reference<1>() )
		.def( "memberRemovedSignal", &Set::memberRemovedSignal, boost::python::return_internal_reference<1>() )
	;	

	SignalBinder<Set::MemberSignal, DefaultSignalCaller<Set::MemberSignal>, MemberSignalSlotCaller>::bind( "MemberSignal" );
	
}

} // namespace GafferBindings
