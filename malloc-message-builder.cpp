#include <capnp/serialize.h>

#include "malloc-message-builder.h"
#include "struct-schema.h"
#include "dynamic-struct-builder.h"

namespace capnp_php {

    MallocMessageBuilder::MallocMessageBuilder()
        : Php::Base(),
          builder(new capnp::MallocMessageBuilder()) {
    }

    MallocMessageBuilder::~MallocMessageBuilder() {
        delete builder;
    }

    Php::Value MallocMessageBuilder::initRoot(Php::Parameters& params) {
        auto schema = params[0].implementation<StructSchema>()->getSchema();
        auto structBuilder = builder->initRoot<capnp::DynamicStruct>(schema);

        return Php::Object("\\CAPNP\\DynamicStructBuilder",
            new DynamicStructBuilder(structBuilder, this));
    }

    Php::Value MallocMessageBuilder::toFlatArray() {
        auto array = capnp::messageToFlatArray(*builder);
        return Php::Value((char*)array.begin(), sizeof(capnp::word) * array.size());
    }
}
