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
mkdir .unikraft
git clone https://github.com/unikraft/unikraft .unikraft/unikraft
UK_DEFCONFIG=$(pwd)/.config.helloworld_qemu-x86_64 make defconfig
make -j(nproc)
/usr/bin/qemu-system-x86_64 -kernel build/helloworld_qemu-x86_64 -nographic
```

This will configure, build and run the `helloworld` application, resulting in a `Hello world!` message being printed, along with the Unikraft banner.

The same can be done for `AArch64`, by running the commands below:

```console
make properclean
UK_DEFCONFIG=$(pwd)/.config.helloworld_qemu-arm64 make defconfig
make -j(nproc)
/usr/bin/qemu-system-aarch64 -kernel build/helloworld_qemu-arm64 -nographic -machine virt -cpu cortex-a57
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
     .config.helloworld_qemu-arm64  .config.helloworld_qemu-x86_64  kraft.yaml  Makefile  Makefile.uk  README.md  run-qemu-aarch64.sh*  run-qemu-x86_64.sh* [...]
     ```

  1. While inside the `helloworld/` directory, create the `.unikraft/` directory:

     ```console
     mkdir .unikraft
     ```

     Enter the `.unikraft/` directory:

     ```console
     cd .unikraft/
     ```

  1. While inside the `.unikraft` directory, clone the [`unikraft` repository](https://github.com/unikraft/unikraft):

     ```console
     git clone https://github.com/unikraft/unikraft unikraft
     ```

  1. Get back to the application directory:

     ```console
     cd ../
     ```

     Use the `tree` command to inspect the contents of the `.unikraft/` directory.
     It should print something like this:

     ```console
     tree -F -L 2 .unikraft/
     ```

     You should see the following layout:

     ```text
     .unikraft/
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

### Configure

Configuring, building and running a Unikraft application depends on our choice of platform and architecture.
Currently, supported platforms are QEMU (KVM), Xen and linuxu.
QEMU (KVM) is known to be working, so we focus on that.

Supported architectures are x86_64 and AArch64.

Use the corresponding the configuration files (`config-...`), according to your choice of platform and architecture.

#### QEMU x86_64

Use the `.config.helloworld_qemu-x86_64` configuration file together with `make defconfig` to create the configuration file:

```console
UK_DEFCONFIG=$(pwd)/.config.helloworld_qemu-x86_64 make defconfig
```

This results in the creation of the `.config` file:

```console
ls .config
.config
```

The `.config` file will be used in the build step.

#### QEMU AArch64

Use the `.config.helloworld_qemu-arm64` configuration file together with `make defconfig` to create the configuration file:

```console
UK_DEFCONFIG=$(pwd)/.config.helloworld_qemu-arm64 make defconfig
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
make[1]: Leaving directory '/media/stefan/projects/unikraft/scripts/workdir/apps/app-helloworld/.unikraft/unikraft'
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
make[1]: Leaving directory '/media/stefan/projects/unikraft/scripts/workdir/apps/app-helloworld/.unikraft/unikraft'
```

Similarly to x86_64, at the end of the build command, the `helloworld_qemu-arm64` unikernel image is generated.
This image is to be used in the run step.

### Run

Run the resulting image using `qemu-system`.

#### QEMU x86_64

To run the QEMU x86_64 build, use `qemu-system-x86_64`:

```console
/usr/bin/qemu-system-x86_64 -kernel build/helloworld_qemu-x86_64 -nographic
```

You will be met by the Unikraft banner, along with the `Hello, world!` message:

```text
qemu-system-x86_64: warning: TCG doesn't support requested feature: CPUID.01H:ECX.vmx [bit 5]
1: Set IPv4 address 172.44.0.2 mask 255.255.255.0 gw 172.44.0.1
en1: Added
en1: Interface is up
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

To run the AArch64 build, use `run-qemu-aarch64.sh`:

```console
/usr/bin/qemu-system-aarch64 -kernel build/helloworld_qemu-arm64 -nographic -machine virt -cpu cortex-a57
```

Same as running on x86_64, the application will start:

```
1: Set IPv4 address 172.44.0.2 mask 255.255.255.0 gw 172.44.0.1
en1: Added
en1: Interface is up
Powered by
o.   .o       _ _               __ _
Oo   Oo  ___ (_) | __ __  __ _ ' _) :_
oO   oO ' _ `| | |/ /  _)' _` | |_|  _)
oOo oOO| | | | |   (| | | (_) |  _) :_
 OoOoO ._, ._:_:_,\_._,  .__,_:_, \___)
                  Atlas 0.13.1~5eb820bd
Hello world!
```
