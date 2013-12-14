Friday Night Hack!
==================

A client/server chat program
----------------------------

Built over zero-MQ. Obviously this is not "safe" C. But it is C! And it does work!

Currently the server ports are hardcoded to 5556 and 5558.

Dependencies
------------

 - GCC + GNU make
 - ZeroMQ (>= 4.0.0)

You can test the dependencies by running `make version` and executing the `version` binary. Should see:

```
% make version && ./version
ZeroMQ v4.0.3
```

Or similar.


Authors
-------

 - Andy C.
 - ...


License
-------

Distributed under the MIT License. Copyright &copy; Andy Chiang, 2013.