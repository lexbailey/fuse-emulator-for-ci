/* pokefinder.c: help with finding pokes
   Copyright (c) 2003 Philip Kendall

   $Id$

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA

   Author contact information:

   E-mail: pak21-fuse@srcf.ucam.org
   Postal address: 15 Crescent Road, Wokingham, Berks, RG40 2DB, England

*/

#include <config.h>

#include <string.h>

#include <libspectrum.h>

#include "spectrum.h"

libspectrum_byte pokefinder_possible[8][0x4000];
size_t pokefinder_count;

int
pokefinder_clear( void )
{
  size_t page;

  for( page = 0; page < 8; page++ )
    memset( pokefinder_possible[page], 1, 0x4000 );

  pokefinder_count = 8 * 0x4000;

  return 0;
}

int
pokefinder_search( libspectrum_byte value )
{
  size_t page, offset;

  for( page = 0; page < 8; page++ )
    for( offset = 0; offset < 0x4000; offset++ )
      if( pokefinder_possible[page][offset] && RAM[page][offset] != value ) {
	pokefinder_possible[page][offset] = 0;
	pokefinder_count--;
      }

  return 0;
}