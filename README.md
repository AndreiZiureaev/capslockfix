# A Linux driver that flashes the CapsLock LED after every system wake

It's a workaround for CapsLock being on when waking after suspend on Ubuntu. There are probably much better ways of doing this in userspace, but I wanted to write some Linux drivers...

## Installing
1. Download the source code.
```
$ git clone https://github.com/AndreiZiureaev/capslockfix.git
$ cd capslockfix
```

2. Read all of it to make sure it's not malware lol.

3. Install and run `ldclf.sh`.
```
$ sed -i "s|SRC_LOCATION=.*|SRC_LOCATION=$(pwd)|" ldclf.sh
$ sudo cp ldclf.sh /usr/local/bin/
$ sudo chmod u+x /usr/local/bin/ldclf.sh
$ sudo ldclf.sh
```

`sed` adds the location of the source code to `ldclf.sh`.

`cp` copies `ldclf.sh` to an appropriate place so that it could be run from anywhere on the command line.

`chmod` allows root to execute `ldclf.sh`.

`ldclf.sh` compiles and installs the module, so that the module is loaded at every boot.
`ldclf.sh` needs to be run every time the kernel is upgraded.
It recompiles the module for the current kernel and places the compiled module in the appropriate folder (among other things).

## Uninstalling
```
$ sudo rmmod capslockfix
$ sudo rm /usr/local/bin/ldclf.sh
$ sudo rm /lib/modules/$(uname -r)/kernel/drivers/leds/capslockfix.ko
```

Remove the `capslockfix` line from `/etc/modules`.

Maybe run `sudo depmod`.
