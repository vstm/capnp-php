#include <iostream>
#include "dynamic-struct-builder.h"
#include "dynamic-value-converter.h"

namespace capnp_php {
    DynamicStructBuilder::DynamicStructBuilder(
        capnp::DynamicStruct::Builder builder,
        Php::Object messageBuilder) 
        : Php::Base(),
          messageBuilder(messageBuilder),
          builder(builder)
    {
    }

    DynamicStructBuilder::~DynamicStructBuilder() {
        //Php::out << "DynamicStructBuilder::~DynamicStructBuilder()" << std::endl;
    }

    Php::Value DynamicStructBuilder::__get(const Php::Value& name) {
        auto schema = builder.getSchema();

        //Php::out << " DynamicStructBuilder::__get" << std::endl;
        KJ_IF_MAYBE(field, schema.findFieldByName(name.stringValue())) {
            return DynamicValueConverter::convertFromCapnp(
                builder.get(*field), this);
        }

        return Php::Base::__get(name);
    }

    void DynamicStructBuilder::__set(const Php::Value& name,
            const Php::Value& value) {
        auto schema = builder.getSchema();
        //Php::out << " DynamicStructBuilder::__set" << std::endl;

        KJ_IF_MAYBE(field, schema.findFieldByName(name.stringValue())) {
            DynamicValueConverter::convertToCapnp(builder, *field, value);
            //builder.set(*field)
        }

        // TODO: throw exception (no such field)
        Php::Base::__set(name, value);
    }

    Php::Value DynamicStructBuilder::init(Php::Parameters& parameters) {
        std::string name = parameters[0];

        if(parameters.size() > 1) {
            capnp::uint size = parameters[1].numericValue();
            return DynamicValueConverter::convertFromCapnp(builder.init(name, size), this);
        } else {
            return DynamicValueConverter::convertFromCapnp(builder.init(name), this);
        }
    }

    Php::Value DynamicStructBuilder::which() {
        Php::Value result;

        auto schema_maybe = builder.which();

        KJ_IF_MAYBE(schema, schema_maybe) {
            auto name = schema->getProto().getName();

            result = Php::Value(name.begin(), name.size());
        }

        return result;
    }
}
