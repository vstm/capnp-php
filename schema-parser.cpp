#include <kj/exception.h>

#include "schema-parser.h"
#include "parsed-schema.h"

namespace capnp_php {
        SchemaParser::SchemaParser() 
            : Php::Base(),
              parser(new capnp::SchemaParser())
        {
        }

        SchemaParser::~SchemaParser() {
            delete parser;
        }

        Php::Value SchemaParser::parseDiskFile(Php::Parameters &params) {
            std::string display_name = params[0];
            std::string disk_path = params[1];
            kj::ArrayPtr<::kj::StringPtr> importpaths;

            if(params.size() > 2) {
                Php::Array paths = params[2];
            }

            try {
                auto schema = parser->parseDiskFile(display_name, disk_path, importpaths);
                return Php::Object("\\CAPNP\\ParsedSchema",
                    new ParsedSchema(schema, this));
            } catch(const kj::Exception& ex) {
                throw Php::Exception(ex.getDescription());
            }

            return Php::Value();
        }
}
