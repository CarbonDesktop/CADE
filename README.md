<!--
@Author: Marius Messerschmidt <marius>
@Date:   08-10-2016 20:10:88
@Email:  marius.messerschmidt@googlemail.com
@Last modified by:   marius
@Last modified time: 08-10-2016 20:10:25
@License: MIT
-->


### Builds
| Branch  | Build |
|---------|-------|
| `master`| [![Build Status](https://travis-ci.org/CarbonDesktop/CADE.svg?branch=master)](https://travis-ci.org/CarbonDesktop/CADE)

 > Our current Development happens on the master branch, this will change as soon as we
 > have a (stable or unstable) release.

------------------------------------------

# Carbon Desktop

The Carbon Desktop (short CADE) is a simple Desktop Environment written
in C and GTK3 that aims to combine classic and modern desktop concepts
into a simple interface. Besides the design concepts, it should follow
two important rules:

#### Performance

The Desktop Environment is running all the time, so it should not
waste any resources. It should have more or less the same footprint as
Xfce4 or LXDE.

#### Customisation

We want to enable our users to change everything to how they like it.
This means that we are working on a rock-solid plugin system, theme
support and a generaly customisatizable user interface

## Screenshots

> Soon!

## Usage

As this is in very early stages, there is no deployment system right
now. If you still want to try it out, you can simply download the source
and run the following commands:

```bash
$ ./autogen.sh            # Generate the build system
$ ./configure             # Configurate your build
$ make                    # Build the executeables
```

right now, this will build one single lonley file. You can run it by
calling:

`./src/apps/shell/cade-shell`

## Installation

> see above

A real guide will be there as soon as we have something to install :+1:

## License

The whole project is licensed under the MIT-license, for more
information, look at the LICENSE file.

## Related

This is the core suite containing everything that is *required* for CADE
to work. There will be other repos in future like `CADE-extra` (for Tools
like editor/viewer/calculator) and `CADE-data` (for themes/plugins and so on)!
