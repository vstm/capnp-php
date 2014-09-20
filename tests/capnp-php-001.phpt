--TEST--
Is the capnp-php extension correctly loaded?
--FILE--
<?php

use CAPNP\SchemaParser;

$wd = __DIR__ . DIRECTORY_SEPARATOR;
$schemaParser = new SchemaParser();
$schema = $schemaParser->parseDiskFile("AddressBook", $wd . "addressbook.capnp", array());

var_dump($schema);
--EXPECT--
object(CAPNP\ParsedSchema)#2 (0) {
}
