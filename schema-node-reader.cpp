#include "schema-node-reader.h"

namespace capnp_php {
    SchemaNodeReader::SchemaNodeReader(capnp::schema::Node::Reader reader,
                            Php::Value parsedSchema)
        : Php::Base(),
          parsedSchema(parsedSchema),
          reader(reader)
    {
    }

    Php::Object SchemaNodeReader::getNestedNodes()
    {
    }

    Php::Value SchemaNodeReader::isStruct() {
        return reader.isStruct();
    }

    Php::Value SchemaNodeReader::isEnum() {
        return reader.isEnum();
    }
}
