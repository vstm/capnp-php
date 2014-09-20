#include <phpcpp.h>
#include "schema-parser.h"
#include "parsed-schema.h"
#include "flat-array-message-reader.h"
#include "struct-schema.h"
#include "dynamic-struct-reader.h"
#include "dynamic-list-reader.h"
#include "dynamic-struct-builder.h"
#include "dynamic-list-builder.h"
#include "malloc-message-builder.h"

/**
 *  tell the compiler that the get_module is a pure C function
 */
extern "C" {
    
    /**
     *  Function that is called by PHP right after the PHP process
     *  has started, and that returns an address of an internal PHP
     *  strucure with all the details and features of your extension
     *
     *  @return void*   a pointer to an address that is understood by PHP
     */
    PHPCPP_EXPORT void *get_module() 
    {
        // static(!) Php::Extension object that should stay in memory
        // for the entire duration of the process (that's why it's static)
        static Php::Extension extension("capnp-php", "1.0");
        
        // @todo    add your own functions, classes, namespaces to the extension
        Php::Namespace extNamespace("CAPNP");

        Php::Class<capnp_php::SchemaParser> schemaParser("SchemaParser");

        schemaParser.method("parseDiskFile", &capnp_php::SchemaParser::parseDiskFile, {
            Php::ByVal("displayName", Php::Type::String, true),
            Php::ByVal("fileName", Php::Type::String, true), 
            Php::ByVal("importPaths", Php::Type::Array, false) 
        });


        Php::Class<capnp_php::ParsedSchema> parsedSchema("ParsedSchema");

        parsedSchema.method("getProto", &capnp_php::ParsedSchema::getProto);
        parsedSchema.method("getNested", &capnp_php::ParsedSchema::getNested, {
            Php::ByVal("name", Php::Type::String, true)
        });
        parsedSchema.method("asStruct", &capnp_php::ParsedSchema::asStruct);

        Php::Class<capnp_php::FlatArrayMessageReader> flatArrayMessageReader("FlatArrayMessageReader");

        flatArrayMessageReader.method("__construct", &capnp_php::FlatArrayMessageReader::__construct, {
            Php::ByVal("data", Php::Type::String, true), 
        });

        flatArrayMessageReader.method("getRoot", &capnp_php::FlatArrayMessageReader::getRoot, {
            Php::ByVal("data", "\\CAPNP\\StructSchema", true), 
        });


        Php::Class<capnp_php::StructSchema> structSchema("StructSchema");
        structSchema.method("getFieldNames", &capnp_php::StructSchema::getFieldNames);


        Php::Class<capnp_php::DynamicStructReader> dynamicStructReader("DynamicStructReader");
        dynamicStructReader.method("which", &capnp_php::DynamicStructReader::which);

        Php::Class<capnp_php::DynamicListReader> dynamicListReader("DynamicListReader");

        Php::Class<capnp_php::DynamicStructBuilder> dynamicStructBuilder("DynamicStructBuilder");
        dynamicStructBuilder.method("init", &capnp_php::DynamicStructBuilder::init);
        dynamicStructBuilder.method("which", &capnp_php::DynamicStructBuilder::which);

        Php::Class<capnp_php::DynamicListBuilder> dynamicListBuilder("DynamicListBuilder");

        Php::Interface messageBuilder("MessageBuilder");
        messageBuilder.method("initRoot", {
            Php::ByVal("schema", "\\CAPNP\\StructSchema", true)
        });
        messageBuilder.method("toFlatArray");

        Php::Class<capnp_php::MallocMessageBuilder> mallocMessageBuilder("MallocMessageBuilder");
        mallocMessageBuilder.implements(messageBuilder);
        mallocMessageBuilder.method("initRoot", &capnp_php::MallocMessageBuilder::initRoot, {
            Php::ByVal("schema", "\\CAPNP\\StructSchema", true)
        });
        mallocMessageBuilder.method("toFlatArray", &capnp_php::MallocMessageBuilder::toFlatArray);
            

        extNamespace.add(std::move(schemaParser));
        extNamespace.add(std::move(parsedSchema));
        extNamespace.add(std::move(flatArrayMessageReader));
        extNamespace.add(std::move(structSchema));
        extNamespace.add(std::move(dynamicStructReader));
        extNamespace.add(std::move(dynamicListReader));
        extNamespace.add(std::move(dynamicStructBuilder));
        extNamespace.add(std::move(dynamicListBuilder));
        extNamespace.add(std::move(messageBuilder));
        extNamespace.add(std::move(mallocMessageBuilder));

        extension.add(std::move(extNamespace));
        
        // return the extension
        return extension;
    }
}
