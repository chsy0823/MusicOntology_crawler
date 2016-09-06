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

        madeCollection.put("foaf:made.<xmlattr>.rdf:parseType", "Collection");

        for(int j=0;j<artist.totalGroupList.size();j++) {

            ptree release;
            MusicBrainz5::CReleaseGroup *releaseGroup = artist.totalGroupList.at(j);
            std::vector<MusicBrainz5::CRecording> recording = artist.totalReleaseInGroup[releaseGroup->ID()];

            release.put("dc:title", releaseGroup->Title());

            ptree records;

            for(int k=0;k<recording.size();k++) {

            }
            
            release.put("mo:records.<xmlattr>.rdf:parseType","Collection");

            madeCollection.add_child("mo:Release",release);
        }

        pt.add_child("rdf:RDF.mo:MusicArtist", musicArtist);


        std::cout << "## " << artist.name << "release-group count :" << artist.totalReleaseInGroup.size() << std::endl;


    }
}