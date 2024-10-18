# ZT Framework.

The ZT framework for C++ is the ZKA Web Services's Official SDK.
</br>
It can be used to develop:

- Desktop Apps in Mac OS/Windows.
- Backend Apps in ZKA OS/Linux/Windows.
- ZKA OS based apps for your IoT, Embedded Solutions.
- Mobile apps (via NDK on Android or a Bridge header for Obj-C/Swift)
  - Please note that ARM64 is also supported because of ARM64 releases of ZKA and macOS.

## Installing/Building:

Start by cloning the repo:

```
git clone git@bitbucket.org:mahrouss/priv-dll.git
```

</br>

Use __btb__ to build the frameworks.

</br>
BTB is ZKA's own build system, desinged to parse JSON objects to build a file.
</br>
Use BTB as in the following:

```
btb FoundationKit.json # For instance.
```

You can now use the DLL/SO/DYLIB for your project.

###### Copyright ZKA Web Services Co, all rights reserved.
