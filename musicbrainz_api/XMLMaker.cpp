//
// Created by Elenore on 2016. 9. 2..
//

#include "XMLMaker.h"


XMLMaker::XMLMaker() {

}

XMLMaker::~XMLMaker() {

}

void XMLMaker::generateXML(std::vector<ArtistCopy> artistList) {

    std::ofstream file("/Users/Elenore/Documents/out.xml");
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

    write_xml(file,pt,xml_writer_settings<std::string>('\t',1));
    file.close();
}

void XMLMaker::generateJSON(ArtistCopy artist) {


    for(int j=0;j<artist.totalGroupList.size();j++) {

        ptree release;
        MusicBrainz5::CReleaseGroup releaseGroup = artist.totalGroupList.at(j);

        std::vector<MusicBrainz5::CRecording> recordingList = artist.totalReleaseInGroup[releaseGroup.ID()];

        for(int k=0;k<recordingList.size();k++) {

            MusicBrainz5::CRecording recording = recordingList.at(k);
        }
    }

        std::cout << "## " << artist.name << " release-group count :" << artist.totalReleaseInGroup.size() << std::endl;
}

void XMLMaker::saveToMongo(std::string jsonStr) {

}