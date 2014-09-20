#include "struct-schema.h"
#include "dynamic-value-converter.h"

namespace capnp_php {
    StructSchema::StructSchema(capnp::StructSchema schema, Php::Object parent)
        : Php::Base(),
          parent(parent),
          schema(schema)
    {
    }

    capnp::StructSchema& StructSchema::getSchema() {
        return schema;
    }

    Php::Value StructSchema::getFieldNames() {
        Php::Value result;

        auto fields = schema.getFields();

        for(capnp::uint i = 0; i < fields.size(); ++i) {
            result.set(i, DynamicValueConverter::convertTextToPhpString(fields[i].getProto().getName()));
        }

        return result;
    }
}
