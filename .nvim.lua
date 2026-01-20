local capabilities = require("cmp_nvim_lsp").default_capabilities()
capabilities.textDocument.completion.completionItem.snippetSupport = false

vim.lsp.config("clangd", {
  capabilities = capabilities,
  cmd = {
    "clangd",
    "--background-index",
    "--query-driver=/home/jared/Projects/NakOS/Toolchain/opt/cross/bin/i686-elf-g++",
  },
})

vim.lsp.enable("clangd")
