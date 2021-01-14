#!/bin/sh

userresources=$HOME/.Xresources
usermodmap=$HOME/.Xmodmap
sysresources=/etc/X11/xinit/.Xresources
sysmodmap=/etc/X11/xinit/.Xmodmap


# bar
dwmblocks &

# compositor
picom -f &

# monitor
xrandr --output LVDS1 --primary --mode 1366x768

# wallpaper
nitrogen --restore &

# notif
systemctl --user import-environment DISPLAY

# loop
while true; do
	dwm >/dev/null 2>&1
done

# dwm
exec dwm
