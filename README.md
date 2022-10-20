# Matthew55's DWM

## Features
- [Clickable statusbar](https://dwm.suckless.org/patches/statuscmd/) with Luke's build of [dwmblocks](https://github.com/lukesmithxyz/dwmblocks).
- Reads [XResources](https://dwm.suckless.org/patches/xresources/) colors/variables (i.e. works with `pywal`, etc.).
- New layouts: fibonacci, dwindle, and more.
- [Stacker](https://dwm.suckless.org/patches/stacker/): Move windows up the stack manually (`super-K/J`).
- Dmenu scripts: Found in [my dotfiles](https://github.com/matthew55/dotfiles/tree/main/.local/bin/dmenu-scripts).

## Link Pywal to Xresources
- Add `xrdb ~/.Xresources && xrdb -merge ~/.cache/wal/colors.Xresources` to your `.xinitrc` file.
