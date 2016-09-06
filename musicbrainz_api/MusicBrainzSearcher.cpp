//
// Created by Elenore on 2016. 8. 30..
//

#include "MusicBrainzSearcher.h"


MusicBrainzSearcher::MusicBrainzSearcher(void) {

}
MusicBrainzSearcher::~MusicBrainzSearcher(void) {

}

void MusicBrainzSearcher::searchReleaseGroup(MusicBrainz5::CQuery::tParamMap Params, MusicBrainz5::CQuery& Query, int index) {

    ArtistCopy artist = this->artistList.at(index);

    std::vector<MusicBrainz5::CReleaseGroup*> totalGroupList;
    std::map<std::string, std::vector<MusicBrainz5::CRecording>> totalReleaseInGroup;

    int offset = 0;

    std::cout << "Start read group" <<std::endl;

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

                        MusicBrainz5::CQuery Query2("queryexample-1.0");

                        MusicBrainz5::CQuery::tParamMap Params2;
                        Params2["query"]="reid:"+release->ID();
                        Params2["limit"]=std::to_string(MAX);
                        std::vector<MusicBrainz5::CRecording> rel = searchRecording(Params2,Query2);
                        totalReleaseInGroup[group->ID()] = rel;

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

    artist.totalGroupList = totalGroupList;
    artist.totalReleaseInGroup = totalReleaseInGroup;

    this->artistList[index] = artist;

    std::cout << "end group count " << totalGroupList.size()<< std::endl;

}

std::vector<MusicBrainz5::CRecording> MusicBrainzSearcher::searchRecording(MusicBrainz5::CQuery::tParamMap Params, MusicBrainz5::CQuery& Query) {

    std::vector<MusicBrainz5::CRecording> totalRecordList;
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
                std::cout << "\t\t----track title: " << record->Title() << " ID: " << record->ID() << std::endl;
            }
        }
        if(currentMetaCount < MAX) {
            break;
        }
        offset+=MAX;
    }

    std::cout << "----------end record " <<std::endl;

    return totalRecordList;

}
void MusicBrainzSearcher::DoSearch(const std::string Entity, const std::string Search, int index) {

    MusicBrainz5::CQuery Query("queryexample-1.0");

    MusicBrainz5::CQuery::tParamMap Params;
    Params["query"]=Search;
    Params["limit"]=std::to_string(MAX);

    try {

        if(!Entity.compare("release-group")) {
            searchReleaseGroup(Params,Query, index);
            std::cout << "Finished"<<std::endl;
        }
        else {
            //searchRecording(Params,Query);
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

void MusicBrainzSearcher::startSearchWithArtistList(std::vector<ArtistCopy> artistList) {

    this->artistList = artistList;
    struct timespec tim, tim2;
    tim.tv_sec = 1;
    tim.tv_nsec = 0;

    for(int i = 0; i<artistList.size(); i++) {
        ArtistCopy artist = artistList.at(i);

        std::cout << "########## Star search "<< artist.name << "##########" << std::endl;
        this->DoSearch("release-group","arid:"+artist.gid, i);
        std::cout << "########## End search "<< artist.name << "##########" << std::endl;
        nanosleep(&tim, &tim2);
    }

    XMLMaker xmlMaker;
    xmlMaker.generateXML(this->artistList);
}
