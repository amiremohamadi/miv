<p align="center"><img src="imgs/Miv-Logo.png" width="300"></p>

#### Currently under heavy development

## What is Miv?
Miv is a **STUPID** text editor. The term **"Miv"** has no meaning and is just a play on words with **"Vim"**! 

> It has no superiority over other editors and only is developed for personal purposes! also it can be a good resource if you want to know how text editors work.

## Compiling
Clone the project
```sh
git clone https://github.com/amiremohamadi/miv
```

Run the `makefile`.
```sh
cd miv/src
make # or sudo make install
```

And use like this:
```sh
./miv [path_to_file]
```

## Usage and default keybindings
You can change default key bindings by editing `defines.hh` file, but default values are:

| Key           | Behaviour     |
| ------------- |:-------------:|
| Ctrl + s      | Save The File |
| Ctrl + q      | Quit          |
| Arrow Keys    | Move The Cursor|
| Pagedown/Pageup      | Move Up And Down|

Don't forget, it's super stupid!


## Requirements
- ncurses (wncurses)

## Copying
Available to anybody free of charge, under the terms of GPL V.2 License.
