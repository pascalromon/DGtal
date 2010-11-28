/**
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Lesser General Public License as
 *  published by the Free Software Foundation, either version 3 of the
 *  License, or  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 **/

/**
 * @file dgtalboard-4-colormaps.cpp
 * @ingroup Examples
 * @author Jacques-Olivier Lachaud (\c jacques-olivier.lachaud@univ-savoie.fr )
 * Laboratory of Mathematics (CNRS, UMR 5807), University of Savoie, France
 *
 * @date 2010/11/26
 *
 * An example file named dgtalboard-4-colormaps.
 *
 * This file is part of the DGtal library.
 */

///////////////////////////////////////////////////////////////////////////////
#include <cmath>
#include <iostream>
#include "DGtal/base/Common.h"
#include "DGtal/io/DGtalBoard.h"
#include "DGtal/io/colormaps/GradientColorMap.h"
#include "DGtal/helpers/Shapes.h"
#include "DGtal/helpers/StdDefs.h"
///////////////////////////////////////////////////////////////////////////////

using namespace std;
using namespace DGtal;
using namespace Z2i;

///////////////////////////////////////////////////////////////////////////////

int main( int argc, char** argv )
{
  trace.beginBlock ( "Example dgtalboard-4-colormaps" );

  Point p1( -10, -7 );
  Point p2( 10, 7 );
  Domain domain( p1, p2 );
  Point c1( -5, -1 );
  Point c2( 5, 1 );
  DigitalSet shape_set( domain );
  Shapes<Domain>::addNorm1Ball( shape_set, c1, 5 );
  Shapes<Domain>::addNorm1Ball( shape_set, c2, 5 );
  shape_set.erase( c1 );
  shape_set.erase( c2 );

  // Creating colormap.
  GradientColorMap<int> cmap_grad( 0, 15 );
  cmap_grad.addColor( DGtalBoard::Color( 50, 50, 255 ) );
  cmap_grad.addColor( DGtalBoard::Color( 255, 0, 0 ) );
  cmap_grad.addColor( DGtalBoard::Color( 255, 255, 10 ) );

  // Creating board.
  DGtalBoard board;
  board << SetMode( domain.styleName(), "Paving" )
	<< domain
	<< SetMode( p1.styleName(), "Paving" );
  // This is the name of the style for a Point in mode "Paving".
  string specificStyle =  p1.styleName() + "/Paving";
  for ( DigitalSet::ConstIterator it = shape_set.begin();
	it != shape_set.end();
	++it )
    {
      unsigned int d = (unsigned int) ceil( ( *it - c1 ).norm() );
      // specific color depending on the distance to point c1.
      board << CustomStyle( specificStyle,
			    new CustomColors( DGtalBoard::Color::Black,
					      cmap_grad( d ) ) )
	    << *it;
    }
  board.saveSVG( "dgtalboard-4-colormaps.svg");
  board.saveEPS( "dgtalboard-4-colormaps.eps");

  trace.endBlock();
  return 0;
}
//                                                                           //
///////////////////////////////////////////////////////////////////////////////
