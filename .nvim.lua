local capabilities = vim.lsp.protocol.make_client_capabilities()
capabilities = require("cmp_nvim_lsp").default_capabilities(capabilities)
capabilities.textDocument.completion.completionItem.snippetSupport = false

require("lspconfig").clangd.setup({
  capabilities = capabilities,
	on_new_config = function(config)
		config.cmd = {
			"clangd",
			"--background-index",
			"--query-driver=/home/jared/Projects/NakOS/Toolchain/opt/cross/bin/i686-elf-g++",
		}
	end,
})
