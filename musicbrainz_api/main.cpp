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

#include <iostream>
#include <sstream>
#include <list>

#include "musicbrainz5/Query.h"
#include "musicbrainz5/HTTPFetch.h"
#include "musicbrainz5/ReleaseGroup.h"
#include "musicbrainz5/Release.h"
#include "musicbrainz5/Recording.h"

/* For further information, see the web service search documentation:
 *
 * http://wiki.musicbrainz.org/Text_Search_Syntax
 */

void DoSearch(const std::string Entity, const std::string Search);

const int MAX = 50;

void searchReleaseGroup(MusicBrainz5::CQuery::tParamMap Params, MusicBrainz5::CQuery& Query) {

    std::list<MusicBrainz5::CReleaseGroup*> totalGroupList;
    int offset = 0;

    while(true) {

        int currentMetaCount = 0;

        Params["offset"]=std::to_string(offset);
        MusicBrainz5::CMetadata Metadata=Query.Query("release-group","","",Params);

        MusicBrainz5::CReleaseGroupList *groupList = Metadata.ReleaseGroupList();

        std::cout << "Release Group size: " << groupList->Count() << std::endl;

        for(int i =0; i < groupList->Count(); i++) {

            MusicBrainz5::CReleaseGroup *group = static_cast<MusicBrainz5::CReleaseGroup*>(groupList->Item(i));

            if(group != NULL) {
                currentMetaCount++;
                totalGroupList.push_back(group);
                std::cout << "Release Group title: " << group->Title() << " ID: " << group->ID() << std::endl;

                MusicBrainz5::CReleaseList *releaseList = group->ReleaseList();
                for(int j =0; j< releaseList->Count(); j++) {

                    MusicBrainz5::CRelease *release = static_cast<MusicBrainz5::CRelease*>(releaseList->Item(j));
                    if(releaseList != NULL) {
                        std::cout << "\t--Release title: " << release->Title() << " ID: " << release->ID() << std::endl;

                        DoSearch("recording","reid:"+release->ID());
                        break;
                    }
                }
            }
        }

        if(currentMetaCount < MAX) {
            break;
        }
        offset+=MAX;
    }

    std::cout << "end group count " << totalGroupList.size()<< std::endl;

}

void searchRecording(MusicBrainz5::CQuery::tParamMap Params, MusicBrainz5::CQuery& Query) {

    std::list<MusicBrainz5::CRecording> totalRecordList;
    int offset = 0;

    std::cout << "----------start record " <<std::endl;

    while(true) {

        int currentMetaCount = 0;

        Params["offset"]=std::to_string(offset);
        MusicBrainz5::CMetadata Metadata=Query.Query("recording","","",Params);

        MusicBrainz5::CRecordingList *recordingList = Metadata.RecordingList();
        std::cout << "recordingList list size: " << recordingList->Count() << std::endl;

        for(int i =0; i < recordingList->Count(); i++) {

            MusicBrainz5::CRecording *record = static_cast<MusicBrainz5::CRecording*>(recordingList->Item(i));

            if(record != NULL) {
                currentMetaCount++;
                totalRecordList.push_back(*record);
                std::cout << "\t----track title: " << record->Title() << " ID: " << record->ID() << std::endl;
            }
        }
        if(currentMetaCount < MAX) {
            break;
        }
        offset+=MAX;
    }

    std::cout << "----------end record " <<std::endl;

}
void DoSearch(const std::string Entity, const std::string Search)
{

    MusicBrainz5::CQuery Query("queryexample-1.0");

    MusicBrainz5::CQuery::tParamMap Params;
    Params["query"]=Search;
    Params["limit"]=std::to_string(MAX);

    try
    {

        if(!Entity.compare("release-group")) {
            searchReleaseGroup(Params,Query);
            std::cout << "Finished"<<std::endl;
        }
        else {
            searchRecording(Params,Query);
        }

        //std::cout << "Release Group size: " << Metadata.ReleaseGroupList()->size() << std::endl;

    }
    catch (MusicBrainz5::CConnectionError& Error)
    {
        std::cout << "Connection Exception: '" << Error.what() << "'" << std::endl;
        std::cout << "LastResult: " << Query.LastResult() << std::endl;
        std::cout << "LastHTTPCode: " << Query.LastHTTPCode() << std::endl;
        std::cout << "LastErrorMessage: " << Query.LastErrorMessage() << std::endl;
    }

    catch (MusicBrainz5::CTimeoutError& Error)
    {
        std::cout << "Timeout Exception: '" << Error.what() << "'" << std::endl;
        std::cout << "LastResult: " << Query.LastResult() << std::endl;
        std::cout << "LastHTTPCode: " << Query.LastHTTPCode() << std::endl;
        std::cout << "LastErrorMessage: " << Query.LastErrorMessage() << std::endl;
    }

    catch (MusicBrainz5::CAuthenticationError& Error)
    {
        std::cout << "Authentication Exception: '" << Error.what() << "'" << std::endl;
        std::cout << "LastResult: " << Query.LastResult() << std::endl;
        std::cout << "LastHTTPCode: " << Query.LastHTTPCode() << std::endl;
        std::cout << "LastErrorMessage: " << Query.LastErrorMessage() << std::endl;
    }

    catch (MusicBrainz5::CFetchError& Error)
    {
        std::cout << "Fetch Exception: '" << Error.what() << "'" << std::endl;
        std::cout << "LastResult: " << Query.LastResult() << std::endl;
        std::cout << "LastHTTPCode: " << Query.LastHTTPCode() << std::endl;
        std::cout << "LastErrorMessage: " << Query.LastErrorMessage() << std::endl;
    }

    catch (MusicBrainz5::CRequestError& Error)
    {
        std::cout << "Request Exception: '" << Error.what() << "'" << std::endl;
        std::cout << "LastResult: " << Query.LastResult() << std::endl;
        std::cout << "LastHTTPCode: " << Query.LastHTTPCode() << std::endl;
        std::cout << "LastErrorMessage: " << Query.LastErrorMessage() << std::endl;
    }

    catch (MusicBrainz5::CResourceNotFoundError& Error)
    {
        std::cout << "ResourceNotFound Exception: '" << Error.what() << "'" << std::endl;
        std::cout << "LastResult: " << Query.LastResult() << std::endl;
        std::cout << "LastHTTPCode: " << Query.LastHTTPCode() << std::endl;
        std::cout << "LastErrorMessage: " << Query.LastErrorMessage() << std::endl;
    }
}

int main(int argc, const char *argv[])
{

    //Search for all releases by Kate Bush

    DoSearch("release-group","artist:Evanescence");
    //DoSearch("recording","reid:977f28ed-837b-4caa-836e-1a17b6808980");

    //Search for all releases with 'sensual' in the title

    //DoSearch("release","release:sensual");

    //Search for all artists with 'john' in the name

    //DoSearch("artist","artist:john");
}
