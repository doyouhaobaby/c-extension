--TEST--
Check for qys presence
--SKIPIF--
<?php if (!extension_loaded("qys")) print "skip"; ?>
--FILE--
<?php 
http://www.bo56.com/php7%E6%89%A9%E5%B1%95%E5%BC%80%E5%8F%91%E4%B9%8B%E6%95%B0%E7%BB%84%E5%A4%84%E7%90%86/
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

// function qys_array_concat ($arr, $prefix) {
//     foreach($arr as $key => $val) {
//         if (isset($prefix[$key]) 
//                 && is_string($val) 
//                 && is_string($prefix[$key])) {
//             $arr[$key] = $prefix[$key].$val;
//         }   
//     }   
//     return $arr;
// }
 
$arr = array(
    0 => '0',
    1 => '123',
    'a' => 'abc',
);  
$prefix = array(
    1 => '456',
    'a' => 'def',
);  
var_dump(qys_array_concat($arr, $prefix));

?>
--EXPECT--
qys extension is available
