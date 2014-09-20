#ifndef CAPNP_PHP_DYNAMIC_STRUCT_BUILDER_H
#define CAPNP_PHP_DYNAMIC_STRUCT_BUILDER_H

#include <phpcpp.h>
#include <capnp/dynamic.h>

namespace capnp_php {
    class DynamicStructBuilder : public Php::Base {
        private:
            Php::Object messageBuilder;
            capnp::DynamicStruct::Builder builder;

        public:
            DynamicStructBuilder(capnp::DynamicStruct::Builder builder,
                Php::Object messageBuilder);
            ~DynamicStructBuilder();

            Php::Value __get(const Php::Value& name);
            void __set(const Php::Value& name, const Php::Value& value);

            Php::Value init(Php::Parameters& parameter);
            Php::Value which();
    };
}

#endif /* CAPNP_PHP_DYNAMIC_STRUCT_BUILDER_H */
