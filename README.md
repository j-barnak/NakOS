# NakOS

NakOS is an operating system written using C++.

![NakOS](https://user-images.githubusercontent.com/96548573/227746869-a1aa9cdb-babc-4143-a422-118469eccab9.png)

## Developing for NakOS

To develop for NakOS, you must first set up your cross-compiler. Instructions on how to do this could be found [here](https://wiki.osdev.org/GCC_Cross-Compiler#Why_cross-compilers_are_necessary). Put the 
cross compiler in folder called `Toolchain/`.

The way you configure and build gcc should be slightly modified when you work with C++. The guide will only correctly configure the freestanding libc libraries, but we want libstd++, gcc's version of C++
Standard Library. You instead build `libc` *and* `libstd++` like so:

```
mkdir build-gcc
cd build-gcc
# '--disable-hosted-libstdcxx' is added
../gcc-x.y.z/configure --target=$TARGET --prefix="$PREFIX" --disable-nls --enable-languages=c,c++ --without-headers --disable-hosted-libstdcxx
make all-gcc
make all-target-libgcc
# Need to add for freestanding C++ Standard Libraries
make all-target-libstdc++-v3
make install-gcc
# Need to add for freestanding C++ Standard Libraries
make install-target-libstdc++-v3
```
make install-target-libgcc

## Building NakOS

```
cmake -B build -DCMAKE_BUILD_TYPE=Debug -DCMAKE_EXPORT_COMPILE_COMMANDS=1 . -GNinja -DCMAKE_TOOLCHAIN_FILE=Toolchain/os-dev-toolchain.cmake
```

## LSP Setup

### Vim

If you're using `clangd`, you have to pass `--query-driver=/path/to/cross-compiler` as an argument. If you use CoC, your config file (you generate
this with `:CocLocalConfig`) should look like:

```
{
  "languageserver": {
    "clangd": {
      "command": "clangd",
      "args": ["--background-index", "--query-driver", "/home/jared/Projects/CPP/NakOS/Toolchain/opt/cross/bin/i686-elf-g++"],
      "rootPatterns": ["compile_flags.txt", "compile_commands.json", ".vim/", ".git/", ".hg/"],
      "filetypes": ["c", "cpp", "objc", "objcpp"]
    }
  }
}
```

You may have more properties within the configuration file and the path to the cross-compiler will certainly differ. For example,
my full `NakOS/.vim/coc-settings.json`, looks like:

```
{
  "languageserver": {
    "clangd": {
      "command": "clangd",
      "args": ["--query-driver", "/home/jared/Projects/CPP/NakOS/Toolchain/opt/cross/bin/i686-elf-g++"],
      "rootPatterns": ["compile_flags.txt", "compile_commands.json", ".vim/", ".git/", ".hg/"],
      "filetypes": ["c", "cpp", "objc", "objcpp"]
    }
  },

  "suggest.noselect": true
}

### Neovim

```
If you have **Neovim 0.9.0 or above**, you can have an `.nvim.lua` file with the following

```
require("lspconfig").clangd.setup({
    on_new_config = function(config)
            config.cmd = {
                "clangd",
                "--background-index",
                "--query-driver",
                "/home/jared/Projects/CPP/NakOS/Toolchain/opt/cross/bin/i686-elf-g++",
            }
        end
})
```
If you are using NeoVim and `lsp_config`, you could add the following to your `init.lua`. Replace `project_root` with your project directory 
and replace 

```
"/home/jared/Projects/CPP/NakOS/Toolchain/opt/cross/bin/i686-elf-g++",
```

with where your compiler is located

```
local lspconfig = require("lspconfig")
local project_root = "/home/jared/Projects/CPP/NakOS"

if vim.fn.getcwd() == project_root then
    lspconfig.clangd.setup({
        cmd = {
            "clangd",
            "--background-index",
            "--query-driver",
            "/home/jared/Projects/CPP/NakOS/Toolchain/opt/cross/bin/i686-elf-g++",
        },
        filetypes = { "c", "cpp", "objc", "objcpp" },
    })
end
```
An alternative way to configure your `init.lua` is by adding the following:

```
require("lspconfig").clangd.setup({
    on_new_config = function(config, root_dir)
        local path = "/home/jared/Projects/CPP/NakOS"
        if vim.startswith(root_dir, path) then
            config.cmd = {
                "clangd",
                "--background-index",
                "--query-driver",
                "/home/jared/Projects/CPP/NakOS/Toolchain/opt/cross/bin/i686-elf-g++",
            }
        end
    end,
})
```
Which accomplishes the same thing

And if you're using LazyVim, you can add create a folder under `lua/plugins` and add the following

```
-- File: ~/.config/nvim/lua/plugins/lspconfig.lua

return {
    "neovim/nvim-lspconfig",
    config = function()
        require("lspconfig").clangd.setup({
            cmd = {
                "clangd",
                "--background-index",
                "--query-driver",
                "/home/jared/Projects/CPP/NakOS/Toolchain/opt/cross/bin/i686-elf-g++",
            },
            filetypes = { "c", "cpp", "objc", "objcpp" },
        })
    end,
}
```
