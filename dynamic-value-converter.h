#ifndef CAPNP_PHP_DYNAMIC_VALUE_CONVERTER_H
#define CAPNP_PHP_DYNAMIC_VALUE_CONVERTER_H

#include <phpcpp.h>
#include <capnp/dynamic.h>

namespace capnp_php {
    class DynamicValueConverter {
        public:
            static capnp::DynamicValue::Reader convertFromPhp(const Php::Value & value);

            static void convertToCapnp(capnp::DynamicList::Builder& builder, capnp::uint field, const Php::Value& value);
            static void convertToCapnp(capnp::DynamicStruct::Builder& builder, capnp::StructSchema::Field field, const Php::Value& value);

            static Php::Value convertFromCapnp(capnp::DynamicValue::Reader value, Php::Value parent);
            static Php::Value convertFromCapnp(capnp::DynamicValue::Builder value, Php::Value parent);

            static Php::Value convertTextToPhpString(capnp::Text::Reader text);
    };
}

#endif /* CAPNP_PHP_DYNAMIC_VALUE_CONVERTER_H */
