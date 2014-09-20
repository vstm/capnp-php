#include "parsed-schema.h"
#include "schema-node-reader.h"
#include "struct-schema.h"


namespace capnp_php {
    ParsedSchema::ParsedSchema(const ::capnp::ParsedSchema & schema,
                               Php::Value schemaParser)
        : schemaParser(schemaParser), schema(schema) {
    }

    Php::Value ParsedSchema::getProto() {
        return Php::Object("\\CAPNP\\SchemaNodeReader", new SchemaNodeReader(schema.getProto(), this));
    }

    Php::Value ParsedSchema::getNested(Php::Parameters& params) {
        auto nestedSchema = schema.getNested(params[0].stringValue());
        return Php::Object("\\CAPNP\\ParsedSchema", new ParsedSchema(nestedSchema, this));
    }

    Php::Value ParsedSchema::asStruct() {
        return Php::Object("\\CAPNP\\StructSchema", new StructSchema(schema.asStruct(), this));
    }
}
