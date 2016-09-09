//
// Created by Elenore on 2016. 9. 2..
//

#ifndef MUSICBRAINZ_API_XMLMAKER_H
#define MUSICBRAINZ_API_XMLMAKER_H

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include "ArtistCopy.h"

#include <bsoncxx/builder/basic/document.hpp>
#include <bsoncxx/json.hpp>
#include <mongocxx/client.hpp>
#include <mongocxx/instance.hpp>
#include <mongocxx/uri.hpp>

using boost::property_tree::ptree;
using boost::property_tree::write_xml;
using boost::property_tree::xml_writer_settings;

class XMLMaker {
private:
    mongocxx::client mongoClient;

public:
    XMLMaker();
    ~XMLMaker();

    void connectMongo();
    void disconnectMongo();
    void generateXML(std::vector<ArtistCopy> artistList);
    void generateJSON(ArtistCopy artist);
    void saveToMongo(std::string jsonStr);
    bool writeToFile(const char* filename, const char* buffer, int len);
};


#endif //MUSICBRAINZ_API_XMLMAKER_H
