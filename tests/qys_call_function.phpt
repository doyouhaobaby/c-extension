--TEST--
Check for qys presence
--SKIPIF--
<?php if (!extension_loaded("qys")) print "skip"; ?>
--FILE--
<?php 
// http://www.bo56.com/php7%E6%89%A9%E5%B1%95%E5%BC%80%E5%8F%91%E4%B9%8B%E5%AD%97%E7%AC%A6%E4%B8%B2%E5%A4%84%E7%90%86/
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
 
// http://www.bo56.com/php7%E6%89%A9%E5%B1%95%E5%BC%80%E5%8F%91%E4%B9%8B%E5%87%BD%E6%95%B0%E8%B0%83%E7%94%A8/
class demo {
    public function get_site_name ($prefix) {
        return $prefix."信海龙的博客\n";
    }
}
function get_site_url ($prefix) {
    return $prefix."www.bo56.com\n";
}
 
// function call_function ($obj, $fun, $param) {
//     if ($obj == null) {
//         $result = $fun($param);
//     } else {
//         $result = $obj->$fun($param);
//     }
//     return $result;
// }


$demo = new demo();
echo qys_call_function($demo, "get_site_name", "site name:");
echo qys_call_function(null, "get_site_url", "site url:");

?>
--EXPECT--
qys extension is available
