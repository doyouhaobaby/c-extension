--TEST--
Check for qys presence
--SKIPIF--
<?php if (!extension_loaded("qys")) print "skip"; ?>
--FILE--
<?php 
// http://www.bo56.com/php7%E6%89%A9%E5%B1%95%E5%BC%80%E5%8F%91%E4%B9%8B%E5%B8%B8%E9%87%8F%E5%AE%9A%E4%B9%89/
echo "qys extension is available";
/*
	you can add regression tests for your extension here

  the output of your test code has to be equal to the
  text in the --EXPECT-- section below for the tests
  to pass, differences between the output and the
  expected text are interpreted as failure

	see php7/README.TESTING for further information on
  writing regression tests
*/
echo PHP_EOL;

// function str_concat($prefix, $string) {
//     $len = strlen($prefix);
//     $substr = substr($string, 0, $len);
//     if ($substr != $prefix) {
//         return $prefix." ".$string;
//     } else {
//         return $string;
//     }   
// }
 
// define("__ARR__", array('2', 'site'=>"www.bo56.com"));  
// define("__SITE__", "www.bo56.com", true);
// define("say\__SITE__", "bo56.com");
var_dump(__ARR__);
var_dump(__site__);
var_dump(say\__SITE__);

?>
--EXPECT--
qys extension is available
