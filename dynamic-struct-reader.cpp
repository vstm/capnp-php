#include <iostream>

#include "dynamic-struct-reader.h"
#include "dynamic-value-converter.h"

namespace capnp_php {
    DynamicStructReader::DynamicStructReader(capnp::DynamicStruct::Reader reader,
        Php::Object messageReader)
        : Php::Base(),
          messageReader(messageReader),
          reader(reader)
    {
    }

    Php::Value DynamicStructReader::__get(const Php::Value& name) {
        auto schema = reader.getSchema();
        //Php::out << "DynamicStructReader = " << (void*)this 
            //<< ", schema=" << (void*)&schema 
            //<< ", name=" << name << std::endl;
        KJ_IF_MAYBE(field, schema.findFieldByName(name.stringValue())) {
            //Php::out << "field=" << (void*)&(*field) << ", name=" << name.stringValue()  << std::endl;
            return DynamicValueConverter::convertFromCapnp(
                reader.get(*field), this);
        }

        return Php::Base::__get(name);
    }

    Php::Value DynamicStructReader::which() {
        Php::Value result;

        auto schema_maybe = reader.which();

        KJ_IF_MAYBE(schema, schema_maybe) {
            auto name = schema->getProto().getName();

            result = Php::Value(name.begin(), name.size());
        }

        return result;
    }
}
