//
// Created by Elenore on 2016. 8. 30..
//

#ifndef MUSICBRAINZ_API_MUSICBRAINZSEARCHER_H
#define MUSICBRAINZ_API_MUSICBRAINZSEARCHER_H


#include <sstream>
#include <list>

#include "musicbrainz5/Query.h"
#include "musicbrainz5/HTTPFetch.h"
#include "musicbrainz5/ReleaseGroup.h"
#include "musicbrainz5/Release.h"
#include "musicbrainz5/Recording.h"
//
//namespace MusicBrainz5 {
//    class CQuery;
//    class CArtist;
//}

class MusicBrainzSearcher {

private :

    std::list<MusicBrainz5::CArtist*> artistList;
    const int MAX = 50;
    void searchRecording(MusicBrainz5::CQuery::tParamMap Params, MusicBrainz5::CQuery& Query);
    void searchReleaseGroup(MusicBrainz5::CQuery::tParamMap Params, MusicBrainz5::CQuery& Query);

public :

    MusicBrainzSearcher();
    ~MusicBrainzSearcher();

    void DoSearch(const std::string Entity, const std::string Search);
    void setFileList(std::list<MusicBrainz5::CArtist*> artistList);
};

//64482	f4a31f0a-51dd-4fa7-986d-3095c40c5ed9	Evanescence	Evanescence	1995	\N	\N	\N	\N	\N	2	222	\N		0	2014-04-28 10:00:31.635889+00	f	5255	\N


#endif //MUSICBRAINZ_API_MUSICBRAINZSEARCHER_H
