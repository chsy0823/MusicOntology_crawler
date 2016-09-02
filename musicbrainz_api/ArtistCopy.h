//
// Created by Elenore on 2016. 9. 2..
//

#ifndef MUSICBRAINZ_API_ARTISTCOPY_H
#define MUSICBRAINZ_API_ARTISTCOPY_H

#pragma once

#include <iostream>
#include "musicbrainz5/ReleaseGroup.h"
#include "musicbrainz5/Release.h"
#include "musicbrainz5/Recording.h"
#include "ArtistCopy.h"
#include <map>
#include <list>
#include <vector>

class ArtistCopy {

public:
    std::string id;
    std::string gid;
    std::string name;
    std::string sort_name;

    std::string begin_date_year;
    std::string begin_date_month;
    std::string begin_date_day;

    std::string end_date_year;
    std::string end_date_month;
    std::string end_date_day;

    std::string type;
    std::string area;
    std::string gender;

    std::string comment;
    std::string edits_pending;
    std::string last_updated;
    std::string ended;
    std::string begin_area;
    std::string end_area;

    std::list<MusicBrainz5::CReleaseGroup*> totalGroupList;
    std::map<std::string, std::vector<MusicBrainz5::CRecording>> totalReleaseInGroup;

};


#endif //MUSICBRAINZ_API_ARTISTCOPY_H
