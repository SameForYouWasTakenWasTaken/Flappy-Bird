# 🎮 My very cool flappy bird game!

## 📌 Introduction
Hello, World! My name is Amar, and I am a 14-year-old (as of 2025) teenager in love with computers and gaming! This is my **very first** project in 
`C++` and I am *really* proud of it. This took me around 3 days to make, all of which had at least 3–5 hours of work put into this flappy bird game, and since it's
my first project, don't expect much.

## 🕹️ The gameplay
Well, the game is straightforward. Press `SPACEBAR` to jump and avoid the pipes coming at you. When you die, your controls are disabled and the bird falls. I didn't add a death
mechanic, because, well, I'm a little too lazy. 0_o

## 🔧 Want to poke around with the code?
Well, if you DO want to play around with everything I had created, feel free to poke around in the directory `include/Game/Config`, there are all the configurations
for the `Bird` and `Pipes`.

Inside the `Bird` and `Pipe` class (under `include/Game/Bird.hpp` or `include/Game/Pipe.hpp`), there is a `debug` flag, feel free to tick them on (Except for the pipes one, it's a little buggy)

# 🛠️ How to build it:

### ❗IMPORTANT
Before we dive into the building process, please do note that as of `21/07/2025` you can **ONLY** build this project on **WINDOWS**. Linux and Mac compatability will be one of the last things I will do.

## ✅ Prerequisites
- You need a [PC](https://en.wikipedia.org/wiki/Personal_computer).
- You need [git](https://git-scm.com/) installed.
- You need [CMake](https://cmake.org/) installed.
- A [frontal lobe](https://en.wikipedia.org/wiki/Frontal_lobe).


## 🛠️ Building process
### 📝  BAT FILE BUILDING
To build the actual project, install the `build_runfile.bat` file in the repository or using the releases
tab on GitHub.

❗Make sure there is no "Flappy-Bird" folder in the actual directory of the `.bat` file. Either
clone the entire repository and run the `.bat` file, or download the `.bat` file and it will **create** a Flappy-Bird
folder with the entire project already downloaded using `git`.

The `batch` file runs the `CMakeLists.txt` file using `CMake` and runs the commands found underneath here.
(with a few small changes, like specifying the build type and the build folder will have a specific name based on the build type)

Technically, you could use this `.bat` file with any `CMakeLists.txt` file, as it only runs the default
build command.
### 🖥️ COMMAND LINE BUILDING
First, open a command prompt inside any folder and clone the repository.

```cmd
git clone https://github.com/SameForYouWasTakenWasTaken/Flappy-Bird
``` 


Now we should create an empty folder called `build` for our build files to generate in:


```cmd 
mkdir build
```

Now we need to tell CMake to build our project in that build folder:

```cmd 
cmake -E chdir build cmake ..
```

After we have done that and waited quite a bit, we should finally build it:

```cmd 
cmake --build build
```

Once the project has finally built everything, enter the `build` folder and enter the `bin` folder. Your game should be ready, called as `main.exe`!

