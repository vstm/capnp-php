--TEST--
SchemaParser::parseDiskFile throws exceptions if an invalid (but existing)
capnp file is supplied.
--FILE--
<?php

use CAPNP\SchemaParser;

$wd = __DIR__ . DIRECTORY_SEPARATOR;
$schemaParser = new SchemaParser();
try
{
    $schema = $schemaParser->parseDiskFile("AddressBook", $wd . "invalid.capnp", array());
    var_dump($schema);
} catch(Exception $e) {
    echo "Exception caught: ", $e->getMessage(), PHP_EOL;
}

--EXPECTF--
Exception caught: Parse error.
