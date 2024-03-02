**This repository is no longer maintained.
Please visit the [application catalog](https://github.com/unikraft/catalog/tree/main/examples/helloworld-c).**

# A "Hello, world!" Application on Unikraft

This application starts a Helloworld application with Unikraft.
Follow the instructions below to set up, configure, build and run Helloworld.

To get started immediately, you can use Unikraft's companion command-line companion tool, [`kraft`](https://github.com/unikraft/kraftkit).
Start by running the interactive installer:

```console
curl --proto '=https' --tlsv1.2 -sSf https://get.kraftkit.sh | sudo sh
```

Once installed, clone [this repository](https://github.com/unikraft/app-helloworld) and run `kraft build`:

```console
git clone https://github.com/unikraft/app-helloworld helloworld
cd helloworld/
kraft build
```

This will guide you through an interactive build process where you can select one of the available targets (architecture/platform combinations).
Otherwise, we recommend building for `qemu/x86_64` like so:

```console
kraft build --arch x86_64 --plat qemu
```

Once built, you can instantiate the unikernel via:

```console
kraft run
```

When left without any input flags, you'll be queried for the desired target architecture/platform.

## Work with the Basic Build & Run Toolchain (Advanced)

You can set up, configure, build and run the application from grounds up, without using the companion tool `kraft`.

### Quick Setup (aka TLDR)

For a quick setup, run the commands below.
Note that you still need to install the [requirements](#requirements).

For building and running everything for `x86_64`, follow the steps below:

```console
git clone https://github.com/unikraft/app-helloworld helloworld
cd helloworld/
./scripts/setup.sh
wget https://raw.githubusercontent.com/unikraft/app-testing/staging/scripts/generate.py -O scripts/generate.py
chmod a+x scripts/generate.py
./scripts/generate.py
./scripts/build/make-qemu-x86_64.sh
./scripts/run/qemu-x86_64.sh
```

This will configure, build and run the `helloworld` application, resulting in a `Hello world!` message being printed, along with the Unikraft banner.

The same can be done for `AArch64`, by running the commands below:

```console
git clone https://github.com/unikraft/app-helloworld helloworld
cd helloworld/
./scripts/setup.sh
wget https://raw.githubusercontent.com/unikraft/app-testing/staging/scripts/generate.py -O scripts/generate.py
chmod a+x scripts/generate.py
./scripts/generate.py
./scripts/build/make-qemu-arm64.sh
./scripts/run/qemu-arm64.sh
```

Similar to the `x86_64` build, this will result in a `Hello world!` message being printed.
Information about every step is detailed below.

### Requirements

In order to set up, configure, build and run helloworld on Unikraft, the following packages are required:

* `build-essential` / `base-devel` / `@development-tools` (the meta-package that includes `make`, `gcc` and other development-related packages)
* `sudo`
* `flex`
* `bison`
* `git`
* `wget`
* `uuid-runtime`
* `qemu-system-x86`
* `qemu-system-arm`
* `qemu-kvm`
* `sgabios`
* `gcc-aarch64-linux-gnu`

GCC >= 8 is required to build helloworld on Unikraft.

On Ubuntu/Debian or other `apt`-based distributions, run the following command to install the requirements:

```console
sudo apt install -y --no-install-recommends \
  build-essential \
  sudo \
  gcc-aarch64-linux-gnu \
  libncurses-dev \
  libyaml-dev \
  flex \
  bison \
  git \
  wget \
  uuid-runtime \
  qemu-kvm \
  qemu-system-x86 \
  qemu-system-arm \
  sgabios
```

### Set Up

The following repositories are required for helloworld:

* The application repository (this repository): [`app-helloworld`](https://github.com/unikraft/app-helloworld)
* The Unikraft core repository: [`unikraft`](https://github.com/unikraft/unikraft)

Follow the steps below for the setup:

  1. First clone the [`app-helloworld` repository](https://github.com/unikraft/app-helloworld) in the `helloworld/` directory:

     ```console
     git clone https://github.com/unikraft/app-helloworld helloworld
     ```

     Enter the `helloworld/` directory:

     ```console
     cd helloworld/

     ls -F
     ```

     You will see the contents of the repository:

     ```text
     [...] README.md  defconfigs/  kraft.cloud.yaml  kraft.yaml  main.c  monkey.h  scripts/
     ```

  1. While inside the `helloworld` directory, use the `scripts/setup.sh` to set repositories and required files:

     ```console
     ./scripts/setup.sh
     ```

     Use the `tree` command to inspect the contents of the `workdir/` directory.
     It should print something like this:

     ```console
     tree -F -L 2 workdir/
     ```

     You should see the following layout:

     ```text
     workdir/
     `-- unikraft/
         |-- arch/
         |-- Config.uk
         |-- CONTRIBUTING.md
         |-- COPYING.md
         |-- include/
         |-- lib/
         |-- Makefile
         |-- Makefile.uk
         |-- plat/
         |-- README.md
         |-- support/
         `-- version.mk

     10 directories, 7 files
     ```

## Scripted Building and Running

To make it easier to build, run and test different configurations, the repository provides a set of scripts that do everything required.
These are scripts used for building different configurations of the helloworld application and for running these with all the requirements behind the scenes.

First of all, grab the [`generate.py` script](https://github.com/unikraft/app-testing/blob/staging/scripts/generate.py) and place it in the `scripts/` directory by running:

```console
wget https://raw.githubusercontent.com/unikraft/app-testing/staging/scripts/generate.py -O scripts/generate.py
chmod a+x scripts/generate.py
```

Now, run the `generate.py` script.
You must run it from the root directory of this repository:

```console
./scripts/generate.py
```

The scripts (as shell scripts) are now generated in `scripts/build/` and `scripts/run/`:

```text
scripts/
|-- build/
|   |-- kraft-fc-arm64.sh*
|   |-- kraft-fc-x86_64.sh*
|   |-- kraft-qemu-arm64.sh*
|   |-- kraft-qemu-x86_64.sh*
|   |-- make-fc-arm64.sh*
|   |-- make-fc-x86_64.sh*
|   |-- make-qemu-arm64.sh*
|   `-- make-qemu-x86_64.sh*
|-- generate.py*
|-- run/
|   |-- fc-arm64.json
|   |-- fc-arm64.sh*
|   |-- fc-x86_64.json
|   |-- fc-x86_64.sh*
|   |-- kraft-fc-arm64.sh*
|   |-- kraft-fc-x86_64.sh*
|   |-- kraft-qemu-arm64.sh*
|   |-- kraft-qemu-x86_64.sh*
|   |-- qemu-arm64.sh*
|   `-- qemu-x86_64.sh*
|-- run.yaml
`-- setup.sh*
```

They are shell scripts, so you can use an editor or a text viewer to check their contents:

```console
cat scripts/run/kraft-fc-x86_64.sh
```

Now, invoke each script to build and run the application.
A sample build and run set of commands is:

```console
./scripts/build/kraft-qemu-x86_64.sh
./scripts/run/kraft-qemu-x86_64.sh
```

Another one is:

```console
./scripts/build/make-qemu-arm64.sh
./scripts/run/qemu-arm64.sh
```

## Detailed Steps

### Configure

Configuring, building and running a Unikraft application depends on our choice of platform and architecture.
Currently, supported platforms are QEMU (KVM), Firecraker (KVM), Xen and linuxu.
QEMU (KVM) is known to be working, so we focus on that.

Supported architectures are x86_64 and AArch64.

Use the corresponding the configuration files (`defconfigs/*`), according to your choice of platform and architecture.

#### QEMU x86_64

Use the `defconfigs/qemu-x86_64` configuration file together with `make defconfig` to create the configuration file:

```console
UK_DEFCONFIG=$(pwd)/defconfigs/qemu-x86_64 make defconfig
```

This results in the creation of the `.config` file:

```console
ls .config
.config
```

The `.config` file will be used in the build step.

#### QEMU AArch64

Use the `defconfigs/qemu-arm64` configuration file together with `make defconfig` to create the configuration file:

```console
UK_DEFCONFIG=$(pwd)/defconfigs/qemu-arm64 make defconfig
```

Similar to the x86_64 configuration, this results in the creation of the `.config` file that will be used in the build step.

### Build

Building uses as input the `.config` file from above, and results in a unikernel image as output.
The unikernel output image, together with intermediary build files, are stored in the `build/` directory.

#### Clean Up

Before starting a build on a different platform or architecture, you must clean up the build output.
This may also be required in case of a new configuration.

Cleaning up is done with 3 possible commands:

* `make clean`: cleans all actual build output files (binary files, including the unikernel image)
* `make properclean`: removes the entire `build/` directory
* `make distclean`: removes the entire `build/` directory **and** the `.config` file

Typically, you would use `make properclean` to remove all build artifacts, but keep the configuration file.

#### QEMU x86_64

Building for QEMU x86_64 assumes you did the QEMU x86_64 configuration step above.
Build the Unikraft helloworld image for QEMU AArch64 by using the command below:

```console
make -j $(nproc)
```

You will see a list of all the files generated by the build system:

```text
[...]
  LD      helloworld_qemu-x86_64.dbg
  UKBI    helloworld_qemu-x86_64.dbg.bootinfo
  SCSTRIP helloworld_qemu-x86_64
  GZ      helloworld_qemu-x86_64.gz
make[1]: Leaving directory 'helloworld/workdir/unikraft'
```

At the end of the build command, the `helloworld_qemu-x86_64` unikernel image is generated.
This image is to be used in the run step.

#### QEMU AArch64

If you had configured and build a unikernel image for another platform or architecture (such as x86_64) before, then:

1. Do a cleanup step with `make properclean`.

1. Configure for QEMU AAarch64, as shown above.

1. Follow the instructions below to build for QEMU AArch64.

Building for QEMU AArch64 assumes you did the QEMU AArch64 configuration step above.
Build the Unikraft helloworld image for QEMU AArch64 by using the same command as for x86_64:

```console
make -j $(nproc)
```

Same as in the x86_64 setup, you will see a list of all the files generated by the build system:

```text
[...]
  LD      helloworld_qemu-arm64.dbg
  UKBI    helloworld_qemu-arm64.dbg.bootinfo
  SCSTRIP helloworld_qemu-arm64
  GZ      helloworld_qemu-arm64.gz
make[1]: Leaving directory 'helloworld/workdir/unikraft'
```

Similarly to x86_64, at the end of the build command, the `helloworld_qemu-arm64` unikernel image is generated.
This image is to be used in the run step.

### Run

Run the resulting image using `qemu-system`.

#### QEMU x86_64

To run the QEMU x86_64 build, use:

```console
qemu-system-x86_64 -kernel workdir/build/helloworld_qemu-x86_64 -nographic
```

You will be met by the Unikraft banner, along with the `Hello, world!` message:

```text
qemu-system-x86_64: warning: TCG doesn't support requested feature: CPUID.01H:ECX.vmx [bit 5]
Powered by
o.   .o       _ _               __ _
Oo   Oo  ___ (_) | __ __  __ _ ' _) :_
oO   oO ' _ `| | |/ /  _)' _` | |_|  _)
oOo oOO| | | | |   (| | | (_) |  _) :_
 OoOoO ._, ._:_:_,\_._,  .__,_:_, \___)
                  Atlas 0.13.1~5eb820bd
Hello world!
```

#### QEMU AArch64

To run the AArch64 build, use:

```console
qemu-system-aarch64 -kernel workdir/build/helloworld_qemu-arm64 -nographic -machine virt -cpu cortex-a57
```

Same as running on x86_64, the application will start:

```
Powered by
o.   .o       _ _               __ _
Oo   Oo  ___ (_) | __ __  __ _ ' _) :_
oO   oO ' _ `| | |/ /  _)' _` | |_|  _)
oOo oOO| | | | |   (| | | (_) |  _) :_
 OoOoO ._, ._:_:_,\_._,  .__,_:_, \___)
                  Atlas 0.13.1~5eb820bd
Hello world!
```

### Building and Running with Firecracker

[Firecracker](https://firecracker-microvm.github.io/) is a lightweight VMM (*virtual machine manager*) that can be used as more efficient alternative to QEMU.

Configure and build commands are similar to a QEMU-based build with an initrd-based filesystem:

```console
make distclean
UK_DEFCONFIG=$(pwd)/defconfigs/fc-x86_64 make defconfig
make -j $(nproc)
```

To use Firecraker, you need to download a [Firecracker release](https://github.com/firecracker-microvm/firecracker/releases).
You can use the commands below to make the `firecracker-x86_64` executable from release v1.4.0 available globally in the command line:

```console
cd /tmp
wget https://github.com/firecracker-microvm/firecracker/releases/download/v1.4.0/firecracker-v1.4.0-x86_64.tgz
tar xzf firecracker-v1.4.0-x86_64.tgz
sudo cp release-v1.4.0-x86_64/firecracker-v1.4.0-x86_64 /usr/local/bin/firecracker-x86_64
```

To run a unikernel image, you need to configure a JSON file.
This is the `helloworld-fc-x86_64.json` file.
Pass this file to the `firecracker-x86_64` command to run the Unikernel instance:

```console
rm /tmp/firecracker.socket
firecracker-x86_64 --api-sock /tmp/firecracker.socket --config-file scripts/run/fc-x86_64-helloworld.json
```

Same as running with QEMU, the application will start:

```text
Powered by
o.   .o       _ _               __ _
Oo   Oo  ___ (_) | __ __  __ _ ' _) :_
oO   oO ' _ `| | |/ /  _)' _` | |_|  _)
oOo oOO| | | | |   (| | | (_) |  _) :_
 OoOoO ._, ._:_:_,\_._,  .__,_:_, \___)
                  Atlas 0.13.1~2f2ecc9f
Hello world!
```
