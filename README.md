# A Linux driver that flashes the CapsLock LED after every system wake

It's a workaround for CapsLock being on when waking after suspend on Ubuntu. There are probably much better ways of doing this un userspace, but I wanted to make some Linux drivers...

## Installing

```
$ git clone https://github.com/AndreiZiureaev/capslockfix.git
$ make
$ sudo insmod capslockfix.ko
```

## Uninstalling
```
$ make clean
$ sudo rmmod capslockfix
```
