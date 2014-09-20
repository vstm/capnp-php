--TEST--
SchemaParser::parseDiskFile throws exceptions if an invalid filename is supplied
--FILE--
<?php

use CAPNP\SchemaParser;

$wd = __DIR__ . DIRECTORY_SEPARATOR;
$schemaParser = new SchemaParser();
try
{
    $schema = $schemaParser->parseDiskFile("AddressBook", $wd . "non-existing-file.capnp", array());
    var_dump($schema);
} catch(Exception $e) {
    echo "Exception caught: ", $e->getMessage(), PHP_EOL;
}

--EXPECTF--
Exception caught: open(path.cStr(), O_RDONLY): No such file or directory; path = %s%etests%enon-existing-file.capnp
