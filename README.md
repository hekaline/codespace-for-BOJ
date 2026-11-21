# codespace-for-BOJ

## Online judge workflow

Create one self-contained source file per problem in `src/`, for example
`src/1000.cpp`. Each file should include its own `int main()` and handle input
and output through standard input/output. Start from `src/main.cpp` if you want
a ready-made template.

In VS Code, open the problem file and press **F5**. The active file is compiled
with C++20 and optimization, then run in the integrated terminal so you can
enter test input. Switch problems by opening another file in `src/` and
pressing **F5** again.

To select a problem from the command line with CMake:

```sh
cmake --preset debug -DPROBLEM_FILE=src/1000.cpp
cmake --build --preset debug
./build/debug/solution
```