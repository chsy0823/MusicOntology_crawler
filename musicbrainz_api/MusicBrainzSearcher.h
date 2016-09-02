//
// Created by Elenore on 2016. 8. 30..
//

#ifndef MUSICBRAINZ_API_MUSICBRAINZSEARCHER_H
#define MUSICBRAINZ_API_MUSICBRAINZSEARCHER_H

#pragma once

#include <sstream>
#include "musicbrainz5/Query.h"
#include "musicbrainz5/HTTPFetch.h"
#include "XMLMaker.h"

//
//namespace MusicBrainz5 {
//    class CQuery;
//    class CArtist;
//}

class MusicBrainzSearcher {

private :

    std::vector<ArtistCopy> artistList;
    const int MAX = 50;
    std::vector<MusicBrainz5::CRecording> searchRecording(MusicBrainz5::CQuery::tParamMap Params, MusicBrainz5::CQuery& Query);
    void searchReleaseGroup(MusicBrainz5::CQuery::tParamMap Params, MusicBrainz5::CQuery& Query,int index);

public :

    MusicBrainzSearcher();
    ~MusicBrainzSearcher();

    void DoSearch(const std::string Entity, const std::string Search,int index);
    void startSearchWithArtistList(std::vector<ArtistCopy> artistList);
};

//64482	f4a31f0a-51dd-4fa7-986d-3095c40c5ed9	Evanescence	Evanescence	1995	\N	\N	\N	\N	\N	2	222	\N		0	2014-04-28 10:00:31.635889+00	f	5255	\N


#endif //MUSICBRAINZ_API_MUSICBRAINZSEARCHER_H
