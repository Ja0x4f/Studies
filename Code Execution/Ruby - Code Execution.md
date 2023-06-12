### eval()

In this example, we are dealing with a Ruby application, which you will be able to quickly tell by injecting a double quote in the username parameter.

Since the application is in development mode, we get a lot of details on the error. The following line is especially interesting:

```ruby
@message = eval "\"Hello "+params['username']+"\""
```

We can see that we are injecting in a call to eval.

Always remember: eval is *evil*.

Here, we will need to do the following:

A double-quote " to break out of the string.
 - Add a + sign for string concatenation (don't forget to URL-encode it)
 - Add a call to the command ([COMMAND]) we want to run using \`[COMMAND]\`.
 - Add another + sign for string concatenation.
 - Another double-quote " to close the one that was already there.
 - Once we put everything together, we should be able to run the score command.

Payload example:
```ruby
"+`uname -a`+"
```

 ---

