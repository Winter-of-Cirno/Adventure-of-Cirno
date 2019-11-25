# Adventure-of-Cirno
<center>
This is a Touhou Project doujin game for Ti-nspire calculators.
</center>
<center>
<img src="demo1.png" />
</center>
<center>
To run this game on your Ti-nspire calculator,you need to install Ndless on it first.
<br>
*This game is unfinished,and there is only ONE stage in this game.*
</center>

### How to build the project?
+ For Ti-nspire calculators,you need ndless-sdk and nSDL.
  Make sure there is a macro definition "#define CALC" at the beginning of the file "game.cpp". 
  Then simply use the Makefile provided.

+ For PCs,you need SDL 1.2.
  Make sure there is a macro definition "#define PC" at the beginning of the file "game.cpp". 
  Then add "-lmingw32 -lSDLmain -lSDL" to your build option.

### How to run this game on Ti-nspire calculators?
+ Firstly, you need to install Ndless on your calculator.
+ Secondly, create a new folder "game" in the root folder on your calculator.
+ Thirdly, send all the files in the folder "\Adventure-of-Cirno\Nspire\release" on your PC to the folder "game" on your calculator.
+ Finally, run game.prg.tns or game.tns depending on the OS your calculator is running.

(*the correct name and place of the folder "game" on your calculator is essential to running.*)

### How to run this game on PCs?
+ I have already built a windows version, if you are using windows, you can run "\Adventure-of-Cirno\Windows\release\game.exe" directly.
+ If you are using other operating system, you can buid the project for your OS by yourself.


### key controls
+ Calculator:

  key|funcion
  -|-
  LSHIFT|bmob|
  TAB   | slow mode|
  Arrow Keys/<br>NUM 8246|move|

  *Autoshoot always enabled on the calculator mode,
   you don't need to press any key to shoot. 
+ PC:

  key|function|
  -|-
  Z|shoot|
  X|bmob|
  LSHIFT|slow mode|
  Arrow Keys|move|


+ Common

  key|funcion
  -|-
  LCTRL|skip dialog|
  Q|exit|
  R|restart|
  G|speed up(debug mode)|
