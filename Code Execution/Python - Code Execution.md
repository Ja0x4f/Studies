# Python RCE

### Description

In this example, we are dealing with a Python application.
Like in the Ruby example, we can see that injecting a double-quote gives us an error.

First, let's see how we can properly close the double-quote.

We can inject a + (properly encoded) and another double-quote to get a response without error (`%22%2B%22` - `"+"`).

Now, we need to make sure it's a Python application. For this, we can use:
```python3
hacker"%2bstr("test")%2b"
```
The fact that both `str()` and True are available give us a pretty good chance that Python is used. For the rest of the challenge, we will put our payload inside the call to `str()`.

Now, we want to get to code execution. We can try to use `os.system('id')` for example.

We can see a 0 coming back in the response. This shows that the command was executed successfully. If you try an invalid command like hacker, you will get 32512 meaning that the process returned 127 (since the command is not found).

It may also be valuable to get the value returned by the command. To do this, you can use: `os.popen('[CMD]').read()` instead of `os.system('[CMD]')`.

Payload utilizado:
user1"%2bstr(os.popen("ls").read())%2b"

But, if we try to use `os.system('id')` for example and we get an error message, this is likely due to the fact that the os module (that we need to access system) is not loaded. We can use the following syntax to load and run the system function:

`__import__('os').system(...)`

Finally, by replacing our initial call to id with the score command.

### Base64 encoding

The previous example allowed / in the path, since the following Flask route was used:

`@app.route('/hello/')`
This challenge prevents us from using / in the path, since the following route is used:

`@app.route('/hello/user')`
This is obviously something you can only guess by trial and error. We can go back to the previous payload using ls and it will work. However, we can't run `/bin/bash` (since we need a /).

To bypass this issue, we can use base64 encoding.

We will send a base64 encoded command to the server (to avoid the / in the path), and tell the server to decode it using the function b64decode.

The call to b64decode will be done by the server as part of our payload. However, unfortunately the base64 module is not loaded, so we will need to use the __import__ trick to load base64.

Finally, the command to score will need to be base64-encoded before being sent to the server (so the payload can decode it).

Payload:
```python
__import__('os').popen(__import__('base64').b64decode('Y2F0IC9ldGMvcGFzc3dk')).read()
```