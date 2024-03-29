# dwm - dynamic window manager
> dwm is an extremely fast, small, and dynamic window manager for X.

## Docker
> Don't logout to test dwm anymore.
### before
```bash
cp -f dwm ./docker/
cp -f <st_path> ./docker/
cp -r scripts ./docker/
```
### build
```bash
docker build -t dwm_test .
docker run -d -v /usr/share/fonts/:/usr/share/fonts/:ro -p 5901:5901 --name suckless_dwm dwm_test
```
### use
```bash
# start
make start

# stop
make stop

# reflash
make clean test
```
### connect
> :dwm@127.0.0.1:5901
```
vncviewer
```
## Requirements
In order to build dwm you need the Xlib header files.

## Installation
Edit config.mk to match your local setup (dwm is installed into the /usr/local namespace by default).

Afterwards enter the following command to build and install dwm (if necessary as root):
```bash
make clean install
```
## Running dwm
Add the following line to your .xinitrc to start dwm using startx:
```bash
exec dwm
```
In order to connect dwm to a specific display, make sure that the DISPLAY environment variable is set correctly, e.g.:
```bash
DISPLAY=foo.bar:1 exec dwm
```
(This will start dwm on display :1 of the host foo.bar.)

In order to display status info in the bar, you can do something
like this in your .xinitrc:
```bash
while xsetroot -name "`date` `uptime | sed 's/.*,//'`"
do
    sleep 1
done &
exec dwm
```
## Configuration
The configuration of dwm is done by creating a custom config.h and (re)compiling the source code.
