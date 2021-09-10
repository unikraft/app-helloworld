# Unikraft "hello world" Application

This application prints a basic "Hello World!" message.

To configure, build and run the application you need to have [kraft](https://github.com/unikraft/kraft) installed.

To be able to run it, configure the application to run on the desired platform and architecture:
```
$ kraft configure -p PLATFORM -m ARCH
```

Build the application:
```
$ kraft build
```

And, finally, run the application:
```
$ kraft run
Hello World!
```

If you want to have more control you can also configure, build and run the application manually.

To configure it with the desired features:
```
$ make menuconfig
```

Build the application:
```
$ make
```

Run the application:
- If you built the application for `kvm`:
```
sudo qemu-system-x86_64 -kernel "build/app-helloworld_kvm-x86_64" \
                        -enable-kvm \
                        -nographic
```

- If you built the application for `linuxu`:
```
./build/app-helloworld_linuxu-x86_64
```

For more information about `kraft` type ```kraft -h``` or read the
[documentation](http://docs.unikraft.org).
