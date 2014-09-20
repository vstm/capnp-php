#include <limits>
#include <iostream>

#include "dynamic-value-converter.h"
#include "dynamic-struct-reader.h"
#include "dynamic-list-reader.h"
#include "dynamic-struct-builder.h"
#include "dynamic-list-builder.h"

namespace capnp_php {
    template<typename T>
    Php::Value convertBaseFromCapnp(T value) {
        switch(value.getType()) {
            case capnp::DynamicValue::BOOL:
                return Php::Value(value.template as<bool>());

            case capnp::DynamicValue::INT:
                return Php::Value(value.template as<int64_t>());

            case capnp::DynamicValue::UINT:
            {
                uint64_t val = value.template as<uint64_t>();
                if(val <= std::numeric_limits<int64_t>::max()) {
                    return Php::Value((int64_t)val);
                } else {
                    return Php::Value(std::to_string(val));
                }
            }

            case capnp::DynamicValue::FLOAT:
                return Php::Value(value.template as<double>());

            case capnp::DynamicValue::TEXT:
            {
                auto text = value.template as<capnp::Text>();
                return Php::Value(text.begin(), text.size());
            }

            case capnp::DynamicValue::DATA:
            {
                auto data = value.template as<capnp::Text>();
                return Php::Value(data.begin(), data.size());
            }

            case capnp::DynamicValue::ENUM:
            {
                Php::Value enumText;
                auto enumerant_maybe = value.template as<capnp::DynamicEnum>()
                    .getEnumerant();

                KJ_IF_MAYBE(enumerant, enumerant_maybe) {
                    auto name = enumerant->getProto().getName();
                    enumText = Php::Value(name.begin(), name.size());
                }

                return enumText;
            }

            case capnp::DynamicValue::VOID:
                return Php::Value();

            case capnp::DynamicValue::UNKNOWN:
            default:
                return Php::Value();
        }
    }

    Php::Value DynamicValueConverter::convertFromCapnp(
        capnp::DynamicValue::Reader value, Php::Value parent) {
        //Php::out << "convertFromCapnp (Reader)" << std::endl;

        switch(value.getType()) {
            case capnp::DynamicValue::STRUCT:
                return Php::Object("\\CAPNP\\DynamicStructReader",
                    new DynamicStructReader(value.as<capnp::DynamicStruct>(),
                        parent));

            case capnp::DynamicValue::LIST:
                return Php::Object("\\CAPNP\\DynamicListReader",
                    new DynamicListReader(value.as<capnp::DynamicList>(),
                        parent));

            case capnp::DynamicValue::ANY_POINTER:
                return Php::Value();

            default:
                return convertBaseFromCapnp(value);
        }
    }

    Php::Value DynamicValueConverter::convertFromCapnp(capnp::DynamicValue::Builder value, Php::Value parent) {
        //Php::out << "convertFromCapnp (Builder)" << ", type=" << value.getType() << std::endl;
        switch(value.getType()) {
            case capnp::DynamicValue::STRUCT:
                //Php::out << "return new struct builder" << std::endl;
                return Php::Object("\\CAPNP\\DynamicStructBuilder",
                    new DynamicStructBuilder(value.as<capnp::DynamicStruct>(),
                        parent));

            case capnp::DynamicValue::LIST:
                return Php::Object("\\CAPNP\\DynamicListBuilder",
                    new DynamicListBuilder(value.as<capnp::DynamicList>(),
                        parent));

            case capnp::DynamicValue::ANY_POINTER:
                return Php::Value();

            default:
                return convertBaseFromCapnp(value);
        }
    }

    Php::Value DynamicValueConverter::convertTextToPhpString(capnp::Text::Reader text)
    {
        return Php::Value(text.begin(), text.size());
    }
    
    capnp::DynamicValue::Reader DynamicValueConverter::convertFromPhp(const Php::Value & value) {
        switch(value.type()) {
            case Php::Type::Null:
                return capnp::VOID;

            case Php::Type::Numeric:
                return capnp::DynamicValue::Reader(value.numericValue());

            case Php::Type::Float:
                return capnp::DynamicValue::Reader(value.floatValue());

            case Php::Type::Bool:
                return capnp::DynamicValue::Reader(value.boolValue());

            case Php::Type::String:
                return capnp::Text::Reader(value.stringValue().c_str(), value.stringValue().size());

            case Php::Type::Array:
            {
            }

            case Php::Type::Object:
            {
            }

            case Php::Type::Resource:
            case Php::Type::Constant:
            case Php::Type::ConstantArray:
            case Php::Type::Callable:
            default:
            return capnp::VOID;
        }
    }

    void DynamicValueConverter::convertToCapnp(capnp::DynamicList::Builder& builder, capnp::uint field, const Php::Value& value) {
        auto capnpValue = convertFromPhp(value);
        builder.set(field, capnpValue);
    }

    void DynamicValueConverter::convertToCapnp(capnp::DynamicStruct::Builder& builder, capnp::StructSchema::Field field, const Php::Value& value) {
        auto capnpValue = convertFromPhp(value);
        builder.set(field, capnpValue);
    }
}
