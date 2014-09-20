#include "dynamic-list-builder.h"
#include "dynamic-value-converter.h"
namespace capnp_php {

    DynamicListBuilder::DynamicListBuilder(capnp::DynamicList::Builder builder,
            Php::Object messageBuilder) 
        : Php::Base(),
          messageBuilder(messageBuilder),
          builder(builder)
    {
    }

    Php::Value DynamicListBuilder::getByIndex(int64_t index) {
        return DynamicValueConverter::convertFromCapnp(builder[index], this);
    }

    long DynamicListBuilder::count() {
        return static_cast<long>(builder.size());
    }

    bool DynamicListBuilder::offsetExists(const Php::Value &key) {
        int64_t index = key;

        return index < static_cast<int64_t>(builder.size());
    }

    Php::Value DynamicListBuilder::offsetGet(const Php::Value &key) {
        return getByIndex(key);
    }

    void DynamicListBuilder::offsetSet(const Php::Value &key, const Php::Value &value) {
        int64_t index = key;
        DynamicValueConverter::convertToCapnp(builder, index, value);
    }

    void DynamicListBuilder::offsetUnset(const Php::Value &key) {
        //throw Php::NotImplemented();
    }

    Php::Iterator *DynamicListBuilder::getIterator() {
        throw Php::Exception("getIterator not implemented");
        return nullptr;
    }

}
