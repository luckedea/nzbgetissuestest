# NZBGet installation

This is a short documentation. For more information please
visit NZBGet home page at 
  https://nzbget.com

Contents          
--------
1. About NZBGet
2. Supported OS
3. Prerequisites on POSIX
4. Installation on POSIX
5. Compiling on Windows
6. Configuration
7. Usage
8. Authors
9. Copyright
10. Contact


## 1. About NZBGet

NZBGet is a binary newsgrabber, which downloads files from usenet
based on information given in nzb-files. NZBGet can be used in
standalone and in server/client modes. In standalone mode you 
pass a nzb-file as parameter in command-line, NZBGet downloads
listed files and then exits. 

In server/client mode NZBGet runs as server in background.
Then you use client to send requests to server. The sample requests
are: download nzb-file, list files in queue, etc.

There is also a built-in web-interface. The server has RPC-support
and can be controlled from third party applications too.

Standalone-tool, server and client are all contained in only one 
executable file "nzbget". The mode in which the program works 
depends on command-line parameters passed to the program.

## 2. Supported OS

NZBGet is written in C++ and works on Windows, OS X, Linux and
most POSIX-conform OS'es.

Clients and servers running on different OS'es may communicate with
each other. For example, you can use NZBGet as client on Windows to 
control your NZBGet-server running on Linux.

The download-section of NZBGet web-site provides binary files
for Windows, OS X and Linux. For most POSIX-systems you need to compile
the program yourself. 

If you have downloaded binaries you can just jump to section 
"Configuration".

## 3. Prerequisites on POSIX

NZBGet is developed on a linux-system, but it runs on other
POSIX platforms.

NZBGet absolutely needs the following libraries:

 - libstdc++     (usually part of compiler)
 - [libxml2](https://gitlab.gnome.org/GNOME/libxml2/-/wikis/home)
 - [Boost.JSON](https://www.boost.org/doc/libs/1_84_0/libs/json/doc/html/index.html)
 - [Boost.Optional](https://www.boost.org/doc/libs/1_84_0/libs/optional/doc/html/index.html)

And the following libraries are optional:

  For curses-output-mode (enabled by default):
   - libcurses   (usually part of commercial systems)
     or (better)
   - [libncurses](https://invisible-island.net/ncurses)
    
  For encrypted connections (TLS/SSL):
   - [OpenSSL](https://www.openssl.org)

     or
   - [GnuTLS](https://gnutls.org)

  For gzip support in web-server and web-client (enabled by default):
   - [zlib](https://www.zlib.net/)

  For configuration:
   - [autotools](https://www.gnu.org/software/automake/manual/html_node/Autotools-Introduction.html)
   - [autoconf](https://www.gnu.org/software/autoconf/)

  For managing package dependencies:
   - [pkg-config](https://www.freedesktop.org/wiki/Software/pkg-config/)
  
  For tests:
   - [Boost.Test](https://www.boost.org/doc/libs/1_84_0/libs/test/doc/html/index.html)

All these libraries are included in modern POSIX distributions and
should be available as installable packages. Please note that you also 
need the developer packages for these libraries too, they package names 
have often suffix "dev" or "devel". On other systems you may need to 
download the libraries at the given URLs and compile them (see hints below).

## 4. Installation on POSIX

Installation from the source distribution archive (nzbget-VERSION.tar.gz):

 - untar the nzbget-source via
     tar -zxf nzbget-VERSION.tar.gz

 - change into nzbget-directory via
     cd nzbget-VERSION

 - configure it via

     autoreconf --install

     ./configure

   (maybe you have to tell configure, where to find some libraries.
       ./configure --help is your friend!
    also see "Configure-options" later)

 - in a case you don't have root access or want to install the program
   in your home directory use the configure parameter --prefix, e. g.:

  ./configure --prefix ~/usr

 - compile it via
     make

 - to install system wide become root via:
     su

 - install it via:
     make install

 - install configuration files into <prefix>/etc via:
     make install-conf

   (you can skip this step if you intend to store configuration
    files in a non-standard location)

### Configure-options
---------------------
You may run configure with additional arguments:

  --disable-curses - to make without curses-support. Use this option
    if you can not use curses/ncurses.
    
  --disable-parcheck - to make without parcheck-support. Use this option
    if you have troubles when compiling par2-module.

  --with-tlslib=(OpenSSL, GnuTLS) - to select which TLS/SSL library
    should be used for encrypted server connections.
      
  --disable-tls - to make without TLS/SSL support. Use this option if
    you can not neither OpenSSL nor GnuTLS.

  --disable-gzip - to make without gzip support. Use this option
    if you can not use zlib.
       
  --enable-debug - to build in debug-mode, if you want to see and log
    debug-messages.
    
### Optional package: par-check
-------------------------------
NZBGet can check and repair downloaded files for you. For this purpose
it uses library par2.

For your convenience the source code of libpar2 is integrated into
NZBGet’s source tree and is compiled automatically when you make NZBGet.

In a case errors occur during this process the inclusion of par2-module
can be disabled using configure option "--disable-parcheck":

  ./configure --disable-parcheck

### Optional package: curses
----------------------------
For curses-outputmode you need ncurses or curses on your system.
If you do not have one of them you can download and compile ncurses yourself.
Following configure-parameters may be useful:

  --with-libcurses-includes=/path/to/curses/includes
  --with-libcurses-libraries=/path/to/curses/libraries

If you are not able to use curses or ncurses or do not want them you can
make the program without support for curses using option "--disable-curses":

  ./configure --disable-curses

### Optional package: TLS
-------------------------
To enable encrypted server connections (TLS/SSL) you need to build the program
with TLS/SSL support. NZBGet can use two libraries: OpenSSL or GnuTLS.
Configure-script checks which library is installed and use it. If both are
available it gives the precedence to OpenSSL. You may override that with
the option --with-tlslib=(OpenSSL, GnuTLS). For example to build with GnuTLS:

  ./configure --with-tlslib= GnuTLS
  
Following configure-parameters may be useful:

  --with-libtls-includess=/path/to/gnutls/includes
  --with-libtls-libraries=/path/to/gnutls/libraries

  --with-openssl-includess=/path/to/openssl/includes
  --with-openssl-libraries=/path/to/openssl/libraries

If none of these libraries is available you can make the program without 
TLS/SSL support using option "--disable-tls":

  ./configure --disable-tls
  
## 5. Compiling on Windows

NZBGet is developed using MS Visual Studio 2015 (Community Edition). The project
file is provided.

To compile the program with TLS/SSL support you need either OpenSSL or GnuTLS:
   - [OpenSSL](https://www.openssl.org)

     or
   - [GnuTLS](https://gnutls.org/)

Also required are:
   - [Regex](https://regexlib.com/)
   - [Zlib](https://gnuwin32.sourceforge.net/packages/zlib.htm)
   - [libxml2](https://gitlab.gnome.org/GNOME/libxml2/-/wikis/home)
   - [Boost.JSON](https://www.boost.org/doc/libs/1_84_0/libs/json/doc/html/index.html)
   - [Boost.Optional](https://www.boost.org/doc/libs/1_84_0/libs/optional/doc/html/index.html)

For tests:
   - [Boost.Test](https://www.boost.org/doc/libs/1_84_0/libs/test/doc/html/index.html)

We recommend using [vcpkg](https://vcpkg.io/) to install dependencies.

## 6. Configuration

NZBGet needs a configuration file. 

An example configuration file is provided in "nzbget.conf", which
is installed into "<prefix>/share/nzbget" (where <prefix> depends on
system configuration and configure options - typically "/usr/local",
"/usr" or "/opt"). The installer adjusts the file according to your
system paths. If you have performed the installation step 
"make install-conf" this file is already copied to "<prefix>/etc" and
NZBGet finds it automatically. If you install the program manually
from a binary archive you have to copy the file from "<prefix>/share/nzbget"
to one of the locations listed below.

Open the file in a text editor and modify it accodring to your needs.

You need to set at least the option "MAINDIR" and one news server in
configuration file. The file has comments on how to use each option.

The program looks for configuration file in following standard 
locations (in this order):

On POSIX systems:
  <EXE-DIR>/nzbget.conf
  ~/.nzbget
  /etc/nzbget.conf
  /usr/etc/nzbget.conf
  /usr/local/etc/nzbget.conf
  /opt/etc/nzbget.conf
  
On Windows:
  <EXE-DIR>\nzbget.conf

If you put the configuration file in other place, you can use command-
line switch "-c <filename>" to point the program to correct location.

In special cases you can run program without configuration file using
switch "-n". You need to use switch "-o" to pass required configuration 
options via command-line.

## 7. Usage

NZBGet can be used in either standalone mode which downloads a single file 
or as a server which is able to queue up numerous download requests.

TIP for Windows users: NZBGet is controlled via various command line
parameters. For easier using there is a simple shell script included
in "nzbget-shell.bat". Start this script from Windows Explorer and you will
be running a command shell with PATH adjusted to find NZBGet executable.
Then you can type all commands without full path to nzbget.exe.

### Standalone mode:
--------------------

nzbget <nzb-file>

### Server mode:
----------------

First start the nzbget-server:

  - in console mode:

	nzbget -s
	
  - or in daemon mode (POSIX only):

	nzbget -D
	
	- or as a service (Windowx only, firstly install the service with command
	  "nzbget -install"):

  net start NZBGet
  
To stop server use:

  nzbget -Q  

TIP for POSIX users: with included script "nzbgetd" you can use standard
commands to control daemon:

  nzbgetd start
  nzbgetd stop
  etc.

When NZBGet is started in console server mode it displays a message that
it is ready to receive download requests. In daemon mode it doesn't print any
messages to console since it runs in background.

When the server is running it is possible to queue up downloads. This can be
done either in terminal with "nzbget -A <nzb-file>" or by uploading
a nzb-file into server's monitor-directory (<MAINDIR>/nzb by default).

To check the status of server start client and connect it to server:
  
  nzbget -C

The client have three different (display) outputmodes, which you can select
in configuration file (on client computer) or in command line. Try them:

  nzbget -o outputmode=log -C

  nzbget -o outputmode=color -C

  nzbget -o outputmode=curses -C

To list files in server's queue:

  nzbget -L
  
It prints something like:

  [1] nzbname\filename1.rar (50.00 MB)
  [2] nzbname\filename1.r01 (50.00 MB)
  [3] another-nzb\filename3.r01 (100.00 MB)
  [4] another-nzb\filename3.r02 (100.00 MB)

This is the list of individual files listed within nzb-file. To print
the list of nzb-files (without content) add G-modifier to the list command:

  [1] nzbname (4.56 GB)
  [2] another-nzb (4.20 GB)

The numbers in square braces are ID's of files or groups in queue.
They can be used in edit-command. For example to move file with
ID 2 to the top of queue:

  nzbget -E T 2
  
or to pause files with IDs from 10 to 20:

  nzbget -E P 10-20

or to delete files from queue:

  nzbget -E D 3 10-15 20-21 16

The edit-command has also a group-mode which affects all files from the
same nzb-file. You need to pass an ID of the group. For example to delete
the whole group 1:

  nzbget -E G D 1

The switch "o" is useful to override options in configuration files. 
For example:

  nzbget -o reloadqueue=no -o dupecheck=no -o parcheck=yes -s
  
or:

  nzbget -o createlog=no -C
  
### Running client & server on seperate machines:
-------------------------------------------------

Since nzbget communicates via TCP/IP it's possible to have a server running on
one computer and adding downloads via a client on another computer.

Do this by setting the "ControlIP" option in the nzbget.conf file to point to the
IP of the server (default is localhost which means client and server runs on 
same computer)

### Security warning
--------------------

NZBGet communicates via unsecured socket connections. This makes it vulnerable.
Although server checks the password passed by client, this password is still 
transmitted in unsecured way. For this reason it is highly recommended 
to configure your Firewall to not expose the port used by NZBGet to WAN. 

If you need to control server from WAN it is better to connect to server's
terminal via SSH (POSIX) or remote desktop (Windows) and then run
nzbget-client-commands in this terminal.

### Post processing scripts
---------------------------

After the download of nzb-file is completed nzbget can call post-processing
scripts, defined in configuration file.

Example post-processing scripts are provided in directory "scripts".

To use the scripts copy them into your local directory and set options
<ScriptDir>, <PostScript> and <ScriptOrder>.

For information on writing your own post-processing scripts please
visit NZBGet web site.

### Web-interface
-----------------

NZBGet has a built-in web-server providing the access to the program
functions via web-interface.

To activate web-interface set the option "WebDir" to the path with
web-interface files. If you install using "make install-conf" as
described above the option is set automatically. If you install using
binary files you should check if the option is set correctly.

To access web-interface from your web-browser use the server address
and port defined in NZBGet configuration file in options "ControlIP" and
"ControlPort". For example:

  http://localhost:6789/

For login credentials type username and the password defined by
options "ControlUsername" (default "nzbget") and "ControlPassword"
(default "tegbzn6789").

In a case your browser forget credentials, to prevent typing them each
time, there is a workaround - use URL in the form:

  http://localhost:6789/username:password/

Please note, that in this case the password is saved in a bookmark or in
browser history in plain text and is easy to find by persons having
access to your computer. 

## 8. Authors

NZBGet is developed and maintained by Andrey Prygunkov
(hugbug@users.sourceforge.net).

The original project was initially created by Sven Henkel
(sidddy@users.sourceforge.net) in 2004 and later developed by
Bo Cordes Petersen (placebodk@users.sourceforge.net) until 2005.
In 2007 the abandoned project was overtaken by Andrey Prygunkov.
Since then the program has been completely rewritten.

NZBGet distribution archive includes additional components
written by other authors:

Par2:
	Peter Brian Clements <peterbclements@users.sourceforge.net>

Par2 library API:
	Francois Lesueur <flesueur@users.sourceforge.net>

jQuery:
	John Resig <https://jquery.com>
	The Dojo Foundation <https://github.com/jquery/sizzle/wiki>

Bootstrap:
	Twitter, Inc <https://getbootstrap.com>

Raphaël:
	Dmitry Baranovskiy <http://raphaeljs.com>
	Sencha Labs <http://sencha.com>

Elycharts:
	Void Labs s.n.c. <http://void.it>

iconSweets:
	Yummygum <https://yummygum.com/>

Boost:
  Boost organization and wider Boost community <https://www.boost.org>


## 9. Copyright

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

The complete content of license is provided in file COPYING.

Additional exemption: compiling, linking, and/or using OpenSSL is allowed.

## 10. Contact

If you encounter any problem, feel free to contact us
	https://nzbget.com/contact/
