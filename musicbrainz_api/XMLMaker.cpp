//
// Created by Elenore on 2016. 9. 2..
//

#include "XMLMaker.h"
#include "json/json.h"
#include <iostream>

XMLMaker::XMLMaker() {

}

XMLMaker::~XMLMaker() {

}

void XMLMaker::connectMongo() {

    auto uri = mongocxx::uri("mongodb://127.0.0.1:27017");
    this->mongoClient =  mongocxx::client{uri};

}
void XMLMaker::disconnectMongo() {

}

void XMLMaker::generateXML(std::vector<ArtistCopy> artistList) {

    std::ofstream file("/Users/Elenore/Documents/out2.xml");
    ptree pt;

    pt.put("rdf:RDF.<xmlattr>.xmlns:rdf","http://www.w3.org/1999/02/22-rdf-syntax-ns#");
    pt.put("rdf:RDF.<xmlattr>.xmlns:rdfs","http://www.w3.org/2000/01/rdf-schema#");
    pt.put("rdf:RDF.<xmlattr>.xmlns:owl","http://www.w3.org/2002/07/owl#");
    pt.put("rdf:RDF.<xmlattr>.xmlns:dc","http://purl.org/dc/elements/1.1/");
    pt.put("rdf:RDF.<xmlattr>.xmlns:base","http://www.eswc2006.org/technologies/ontology");

    for(int i = 0; i<artistList.size(); i++) {

        ptree musicArtist;
        ptree madeCollection;

        ArtistCopy artist = artistList.at(i);

        musicArtist.put("<xmlattr>.rdf:about","&users;"+artist.name);
        musicArtist.put("foaf:name", artist.name);
        musicArtist.put("rdfs:label", artist.sort_name);

        madeCollection.put("<xmlattr>.rdf:parseType", "Collection");

        for(int j=0;j<artist.totalGroupList.size();j++) {

            ptree release;
            MusicBrainz5::CReleaseGroup releaseGroup = artist.totalGroupList.at(j);

            std::vector<MusicBrainz5::CRecording> recordingList = artist.totalReleaseInGroup[releaseGroup.ID()];

            release.put("dc:title", releaseGroup.Title());
            release.put("<xmlattr>.rdf:ID","musicbrainz_"+releaseGroup.ID());
            ptree records;
            records.put("<xmlattr>.rdf:parseType","Collection");

            for(int k=0;k<recordingList.size();k++) {

                MusicBrainz5::CRecording recording = recordingList.at(k);

                ptree Record;
                ptree track;
                ptree Track;

                Track.put("<xmlattr>.rdf:ID","musicbrainz_"+recording.ID());
                Track.put("dc:title",recording.Title());
                track.add_child("mo:Track",Track);
                Record.add_child("mo:track",track);
                records.add_child("mo:Record",Record);
            }

            release.add_child("mo:records",records);
            madeCollection.add_child("mo:Release",release);
        }

        musicArtist.add_child("foaf:made",madeCollection);

        pt.add_child("rdf:RDF.mo:MusicArtist", musicArtist);


        std::cout << "## " << artist.name << " release-group count :" << artist.totalReleaseInGroup.size() << std::endl;

    }

    //write_xml(file,pt,xml_writer_settings<std::string>('\t',1));
    file.close();
}

void XMLMaker::generateJSON(ArtistCopy artist) {

    Json::Value root;

    root["id"] = artist.id;
    root["gid"] = artist.gid;
    root["name"] = artist.name;
    root["sort_name"] = artist.sort_name;
    root["begin_date_year"] = artist.begin_date_year;
    root["begin_date_month"] = artist.begin_date_month;
    root["begin_date_day"] = artist.begin_date_day;
    root["type"] = artist.type;
    root["area"] = artist.area;
    root["gender"] = artist.gender;
    root["comment"] = artist.comment;
    root["edits_pending"] = artist.edits_pending;
    root["last_updated"] = artist.last_updated;
    root["ended"] = artist.ended;
    root["begin_area"] = artist.begin_area;
    root["end_area"] = artist.end_area;

    Json::Value tagList;

    for(int i=0;i<artist.tagList.size();i++) {
        Json::Value tagValue;
        MusicBrainz5::CTag tag = artist.tagList.at(i);

        tagValue["name"] = tag.Name();
        tagList.append(tagValue);
    }

    root["tag_list"] = tagList;

    Json::Value totalGroupList;

    for(int j=0;j<artist.totalGroupList.size();j++) {

        Json::Value releaseGroupValue;
        MusicBrainz5::CReleaseGroup releaseGroup = artist.totalGroupList.at(j);

        releaseGroupValue["id"] = releaseGroup.ID();
        releaseGroupValue["title"] = releaseGroup.Title();
        releaseGroupValue["primaryType"] = releaseGroup.PrimaryType();
        releaseGroupValue["disambiguation"] = releaseGroup.Disambiguation();
        releaseGroupValue["firstReleaseDate"] = releaseGroup.FirstReleaseDate();

        Json::Value releaseListValue;
        MusicBrainz5::CReleaseList *releaseList = releaseGroup.ReleaseList();

        for (int k =0; k<releaseList->Count(); k++) {

            Json::Value releaseValue;
            MusicBrainz5::CRelease *release = static_cast<MusicBrainz5::CRelease*>(releaseList->Item(k));

            if(release != NULL) {

                releaseValue["id"] = release->ID();
                releaseValue["title"] = release->Title();
                releaseValue["status"] = release->Status();
                releaseValue["quality"] = release->Quality();
                releaseValue["Packaging"] = release->Packaging();
                releaseValue["disambiguation"] = release->Disambiguation();
                releaseValue["date"] = release->Date();
                releaseValue["country"] = release->Country();
                releaseValue["barcode"] = release->Barcode();
                releaseValue["asin"] = release->ASIN();

                releaseListValue.append(releaseValue);
            }
        }

        Json::Value recordingListValue;
        std::vector<MusicBrainz5::CRecording> recordingList = artist.totalReleaseInGroup[releaseGroup.ID()];

        for(int k=0;k<recordingList.size();k++) {

            Json::Value recordingValue;
            MusicBrainz5::CRecording recording = recordingList.at(k);

            recordingValue["id"] = recording.ID();
            recordingValue["title"] = recording.Title();
            recordingValue["length"] = recording.Length();
            recordingValue["disambiguation"] = recording.Disambiguation();

            recordingListValue.append(recordingValue);
        }

        releaseGroupValue["recordingList"] = recordingListValue;
        releaseGroupValue["releaseList"] = releaseListValue;
        root["totalGroupList"].append(releaseGroupValue);
    }

    Json::StyledWriter writer;
    std::string outputStr = writer.write(root);

    //std::cout << outputStr.c_str() << std::endl;
    //bool result = writeToFile("/Users/elenore/Documents/test.json", outputStr.c_str(), outputStr.length());
    //std::cout << "## " << artist.name << " release-group count :" << artist.totalReleaseInGroup.size() << std::endl;

    bsoncxx::document::value details = bsoncxx::from_json(outputStr);

    auto db = this->mongoClient["musicbrainz"];
    auto res = db["musicbrainz"].insert_one(std::move(details));
}

void XMLMaker::saveToMongo(std::string jsonStr) {

}

bool XMLMaker::writeToFile(const char* filename, const char* buffer, int len) {
    FILE* r = fopen(filename, "wb");

    if(r == NULL) {
        return false;
    }

    size_t file = fwrite(buffer, 1, len, r);
    fclose(r);

    return true;

}
