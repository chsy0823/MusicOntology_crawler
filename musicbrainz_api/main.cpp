/* --------------------------------------------------------------------------

   libmusicbrainz5 - Client library to access MusicBrainz

   Copyright (C) 2012 Andrew Hawkins

   This file is part of libmusicbrainz5.

   This library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   libmusicbrainz5 is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this library.  If not, see <http://www.gnu.org/licenses/>.

     $Id$

----------------------------------------------------------------------------*/



/* For further information, see the web service search documentation:
 *
 * http://wiki.musicbrainz.org/Text_Search_Syntax
 */

#include "MusicBrainzSearcher.h"
#include "FIleHandler.h"

int main(int argc, const char *argv[])
{
    //Search for all releases by Kate Bush
    MusicBrainzSearcher searcher;
    FIleHandler fileHandler;

    fileHandler.readFileFromPath("/Users/elenore/Documents/Develop/MusicOntology_crawler/musicbrainz_api/artist_test");

    std::vector<ArtistCopy> artistList = fileHandler.getArtistList();

    searcher.startSearchWithArtistList(artistList);

    //DoSearch("recording","reid:977f28ed-837b-4caa-836e-1a17b6808980");

    //Search for all releases with 'sensual' in the title

    //DoSearch("release","release:sensual");

    //Search for all artists with 'john' in the name

    //DoSearch("artist","artist:john");
}
