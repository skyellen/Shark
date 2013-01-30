/**
*
* \brief Two-dimensional, real-valued Himmelblau function.
*
*  Multi-modal benchmark function.
*  
* <BR><HR>
* This file is part of Shark. This library is free software;
* you can redistribute it and/or modify it under the terms of the
* GNU General Public License as published by the Free Software
* Foundation; either version 3, or (at your option) any later version.
*
* This library is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this library; if not, see <http://www.gnu.org/licenses/>.
*  
*/
#ifndef SHARK_OBJECTIVEFUNCTIONS_BENCHMARK_HIMMELBLAU_H
#define SHARK_OBJECTIVEFUNCTIONS_BENCHMARK_HIMMELBLAU_H

#include <shark/ObjectiveFunctions/AbstractObjectiveFunction.h>
#include <shark/Core/SearchSpaces/VectorSpace.h>
#include <shark/Rng/GlobalRng.h>

namespace shark {
	/** 
	* \brief Multi-modal two-dimensional continuous Himmelblau benchmark function.
	*
	* Implements Himmelblau's real-valued, multi-modal benchmark function. The
	* function is limited to two dimensions. Please see:
	*   http://en.wikipedia.org/wiki/Himmelblau%27s_function
	* for further information.
	*/
	struct Himmelblau : public AbstractObjectiveFunction< VectorSpace<double>,double > {
		typedef AbstractObjectiveFunction<VectorSpace<double>,double> super;

		/**
		* \brief Constructs an instance of the function. Ignores the supplied dimension.
		*/
		Himmelblau( unsigned int dimension = 2 ) {
			m_numberOfVariables = 2;

			m_features|=CAN_PROPOSE_STARTING_POINT;

			m_name = "Himmelblau";
		}

		void configure( const PropertyTree & node ) {
			(void) node;
		}

		void proposeStartingPoint( super::SearchPointType & x ) const {
			x.resize( 2 );

			for( unsigned int i = 0; i < x.size(); i++ ) {
				x( i ) = Rng::uni( -3, 3 );
			}
		}

		/**
		* \brief Evaluates the function for the supplied search point.
		* \throws shark::Exception if the size of p does not equal 2.
		*/
		double eval( const super::SearchPointType & p ) const {

			if( p.size() != 2 )
				throw SHARKEXCEPTION( "Himmelblau::eval: Dimension of input needs to equal 2." );

			m_evaluationCounter++;

			return( 
				boost::math::pow<2>( boost::math::pow< 2 >( p( 0 ) ) + p( 1 ) - 11 ) +
				boost::math::pow<2>( p( 0 ) + boost::math::pow< 2 >( p( 1 ) ) - 7 )
			);
		}

		/**
		* \brief Accesses the dimension of the search space, fixed to 2.
		*/
		std::size_t numberOfVariables() const {
			return( 2 );
		}
	};

	/**
	* \brief Makes Himmelblau's function known to the factory.
	*/
	ANNOUNCE_SINGLE_OBJECTIVE_FUNCTION( Himmelblau, shark::soo::RealValuedObjectiveFunctionFactory );
}

#endif
