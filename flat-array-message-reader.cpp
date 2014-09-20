#include <capnp/dynamic.h>

#include "flat-array-message-reader.h"
#include "dynamic-struct-reader.h"
#include "struct-schema.h"

namespace capnp_php {

    FlatArrayMessageReader::FlatArrayMessageReader()
        : Php::Base(),
          message(),
          reader(nullptr)
    {
    }

    FlatArrayMessageReader::~FlatArrayMessageReader() {
        delete reader;
    }

    void FlatArrayMessageReader::__construct(Php::Parameters& params) {
        if(reader != nullptr) {
            throw Php::Exception("__construct called more than once!");
        }

        message = params[0].stringValue();

        kj::ArrayPtr<const capnp::word> buff(
            (const capnp::word*)message.c_str(),
            message.size() / sizeof(capnp::word)
        );

        try {
            reader = new ::capnp::FlatArrayMessageReader(buff);
        } catch(kj::Exception ex) {
            // TODO: raise ex
        }
    }

    Php::Value FlatArrayMessageReader::getRoot(Php::Parameters& params) {
        if(reader == nullptr) {
            throw Php::Exception("this is not a valid object");
        }

        StructSchema * schema = params[0].implementation<StructSchema>();

        if(schema == nullptr) {
            throw Php::Exception("invalid parameter, expected StructSchema");
        }

        auto structReader = reader->
            getRoot<capnp::DynamicStruct>(schema->getSchema());

        return Php::Object("\\CAPNP\\DynamicStructReader", new DynamicStructReader(structReader, this));
    }
}

